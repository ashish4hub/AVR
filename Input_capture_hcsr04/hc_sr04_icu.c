// Bare metal AVR code for ultrasonic sensor (HC-SR04) with input capture and non blocking state machine
// Demonstrates timeout handling, state-based measurement
#define F_CPU 16000000UL
#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
#define timeout 60000
#define trig PD7
#define echo PB0
volatile uint16_t start = 0, end = 0, dist = 0;

typedef enum {
  idle,
  wait,
  done
} state;
volatile state current = idle;
void timer1_cap_ini(void){
  TCCR1A = 0; // Normal mode
  TCCR1B = (1 << CS11); // Prescaler = 8 
  TCNT1 = 0; 
  TCCR1B |= (1 << ICNC1); // Enable input capture noise canceler
  TCCR1B |= (1 << ICES1); // Rising edge on pin PB0
  TIMSK1 = (1 << ICIE1); // Enable interrupt on capture
  sei();
}
void trig_ini(void){
  DDRD |= (1 << trig); // trig pin set as output
}
void ultrasonic_trigger(void){
  PORTD &= ~(1 << trig); // Initially low
  _delay_us(2);
  PORTD |= (1 << trig); // High for 10 microseconds
  _delay_us(10);
  PORTD &= ~(1 << trig); // Set to low 
}
ISR(TIMER1_CAPT_vect){
  // If rising edge
  if(TCCR1B & (1 << ICES1)){
    start = ICR1; // copy time in start
    TCCR1B &= ~(1 << ICES1); // Set pin as falling to detect falling edge time
  }
  else{
    end = ICR1; // Copy falling edge time
    current = done;
    TCCR1B |= (1 << ICES1); // Again set to rising 
  }
}
int main(void){
  DDRB &= ~(1 << echo); // Echo pin set as input
  trig_ini();
  timer1_cap_ini();
  volatile uint16_t duration = 0;
  while(1){
    if(current == idle){
      TCNT1 = 0;
      ultrasonic_trigger();
      current = wait;
    }
    if(current == wait){
      //Timeout if echo takes too long
      if(TCNT1 > timeout){
        current = idle; // Jumps to idle 
        dist = 0xFFFF; // Invalid distance
        TCCR1B |= (1 << ICES1); // ensure rising edge for mid-cycle timeout
      }
    }
    if(current == done){
      duration = end - start;
      current = idle;
      dist = duration / 116; // dist = (time * 0.5) / 58
    }
    _delay_ms(100);// Delay for pacing sensor
  }
}


// MCU : ATmega328P
// SENSOR USED : HC-SR04 (Ultrasonic)
// COMPILER : Avr-Gcc
// PROGRAMMER : USBasp
// LANGUAGE : C
// DISTANCE (dist) calculation : (time * 0.5 ) / 58, time = time taken for pulse to return (duration), dist = (duration / 116)
//trig pin -----> PD7
//echo pin -----> ICP1 (PB0)


