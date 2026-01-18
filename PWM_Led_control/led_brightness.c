//This program demostrates the use of PWM to control the brightness of LED using ATmega328P Microcontroller. 
#define F_CPU 16000000UL
#include<avr/io.h>
#include<util/delay.h>
#include<stdint.h>
void config(void){
  TCCR0A = (1 << WGM00) | (1 << WGM01) | (1 << COM0A1); // Enable PWM on PD6
  TCCR0B = (1 << CS00) | (1 << CS01); // Prescaler 64
}
int main(void){
  DDRD |= (1 << PD6);
  config();
  while(1){
    //Smoothly increase led brightness
    for(int16_t i = 0; i < 255; i++){
      OCR0A = i;
      _delay_ms(5);
    }
    _delay_ms(1000); //Wait 1 second
    //Smoothly decrease led brightness
    for(int16_t j = 255; j > 0; j--){
      OCR0A = j;
      _delay_ms(5);
    }
    _delay_ms(1000); //wait 1 second
  }
}
