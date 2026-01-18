# LED fade using TIMER0 PWM 
*This program demonstrate hardware **PWM** Generation on AVR microcontroller (ATmega328P) using **Timer0** in **Fast PWM Mode**. An LED is is connected to the Pin OC0A (PD6) smoothly fades in and fades out by varying the duty cycle.*
---
# Hardware Used
- Microcontroller: ATmega328P
- Programmer: USBasp
- LED connected to pin **OC0A**
---
# Configuration 
- Timer: TIMER0
- Mode: Fast PWM mode
- Output: Non-inverting (clear OC0A on compare match)
- Prescaler: 64
---
# Working
- Timer0 is configured in Fast PWM mode
- OC0A (PD6) pin is enabled as PWM output pin
- The duty cycle (OCR0A) is gradually increased from 0 to 254 fade in led
- Duty cycle is then decreased from 255 to 1 to fade out led
- A 5 ms delay is used between to create smooth visual
