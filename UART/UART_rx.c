#define F_CPU 16000000UL
#include<avr/io.h>
#include<avr/interrupt.h>
#define BAUD 9600
#define BRC ((F_CPU / (16 * BAUD)) - 1)
#define led_pin PD2

volatile char rx_data;

// Initialising UART register 
void uart_rx_ini(){
  UBRR0H = (BRC >> 8);
  UBRR0L = BRC;
  UCSR0B = (1 << RXCIE0) | (1 << RXEN0);
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
  sei();
}
// isr function only read
ISR(USART_RX_vect){
  rx_data = UDR0;
}
int main(void){
  uart_rx_ini();
  DDRD &= ~(1 << PD0); // PD0 is the RX pin on avr set as input
  DDRD |= (1 << led_pin);
  while(1){
    if (rx_data == 'x'){
      PORTD |= (1 << led_pin);
      rx_data = 0;
    }
  }
}




// 'x' is only taken for demonstration
//This program demonstrates the setup of UART on AVR (ATmega328P) for receiving data from other devices, PC or MCUs
//In this program only byte can be read at a time, i.e, 'A', 'B', 'X'....
