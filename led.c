// Bare-metal AVR LED blink using direct register access and F_CPU-based timing.
#define F_CPU 16000000UL
#include<avr/io.h>
#include<util/delay.h>
#define led_pin PD2
int main(void){
  DDRD |= (1 << led_pin); //Pin PD2 as output
  while(1){
    PORTD |= (1 << led_pin); //Pin PD2 as high, led on
    _delay_ms(1000); 
    PORTD &= ~(1 << led_pin); // Pin PD2 as low, led off
  }
}
