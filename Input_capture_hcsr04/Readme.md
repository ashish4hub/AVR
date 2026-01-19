This is a bare metal AVR code for measuring distance using **Ultrasonic sesnor** (HC-SR04) and 16bit Timer1 Input capture unit (ICU) of ATmega328P.

This code directly configure hardware registers for-
- Generating trigger pulse
- Capture echo pulse width using Timer1
- Calculating distance based on **time of flight**
- Handle timeout condition safely

---
# Hardware used
- MCU : ATmega328P
- Sensor : HC-SR04 (Ultrasonic)
- Frequency : 16MHz
- Programmer : USBasp
---
# Pin connections 
- HC-SR04 (VCC) ---> ATmega328P (5V)
- HC-SR04 (Trig) ---> ATmega328P (PD7)
- HC-SR04 (echo) ---> ATmega328P ICP1 (PB0)
- HC-SR04 (GND) ---> ATmega328P (GND)

---
# Timer1 configuration for Input Capture 
- Timer1 is configured in Normal Mode
- Prescaler = 8
- Time frequency = 16MHz / 8 = 2MHz
- Time resolution = 1/2000000 = 0.5 microsecond per count
- **Input capture noise canceler** (ICNC1) enabled
- Input capture edge selection (ICES1)
  - Rising edge ---> start
  - Falling edge ---> end
- Input capture interrupt enabled (ICIE1)
---
# Working 
1. A 10 microsecond pulse is sent to HC-SR04
2. Sensor emits an ultrasonic burst
3. When echo pin goes HIGH, Timer1 captures the start time (start)
4. When echo pin goes LOW, Timer1 captures the end time (end)
5. Pulse width is calculated by, **(duration = end - start)**
6. Distance in cm is calculated by, **(distance = duration / 116)**
---
# Timeout 
A timeout machanism is implemented to prevent the MCU from waiting indefinitely if no object is detected or echo signal is lost
If TCNT1 exceeds defined timeout value :
- Measurement is aborted
- Distance (dist) is set to 0xFFFF (65535) to indicate invalid distance value
- Input capture (ICES1) is reset to detect next rising edge
---
# State Machine
This program uses simple state machine to avoid blocking delays while waiting for echo
- idle ---> Ready to trigger
- wait ---> Waiting for echo capturing or timeout
- done ---> Measurement completed
---
## Note
- Input capture noise canceler adds a fixed small delay (~ 4 timer cycle). Negligible for ultrasonic readings
- This program is for learning purpose


