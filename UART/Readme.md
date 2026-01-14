# UART – Bare-Metal AVR (TX & RX with Ring Buffers)

This folder contains bare-metal UART (USART) implementations for AVR microcontrollers using **direct register access** and **interrupt-driven communication**.

Both **transmit (TX)** and **receive (RX)** are implemented using **ring buffers**, allowing non-blocking serial communication without polling delays.

---

## Implementations Included

### 1. UART TX (Interrupt-Driven)
- Uses **UDRE interrupt** to transmit data
- Implements a **TX ring buffer**
- Supports sending strings without blocking the main loop
- Demonstrates periodic transmission using a timer tick

### 2. UART RX (Interrupt-Driven)
- Uses **RX Complete interrupt**
- Implements an **RX ring buffer**
- Supports receiving full commands / lines (`\n` / `\r` terminated)
- Demonstrates command parsing (e.g., `LED ON`, `LED OFF`)

---

## Key Concepts Demonstrated

- USART register configuration (`UBRR0`, `UCSR0A/B/C`)
- Interrupt Service Routines (ISR)
- Ring buffer (circular buffer) design
- Non-blocking serial communication
- Producer–consumer model (ISR ↔ main loop)
- Line-based command handling
- Hardware timer usage for periodic tasks

---

## Hardware Used

- AVR microcontroller (e.g. ATmega328P)
- USB–UART converter (FTDI / CH340 / CP2102)
- Common GND between MCU and UART adapter

---

## UART Configuration

Parameter | Value |
Baud rate 9600
Data bits 8
Mode Asynchronous 

---

## Buffer Design Notes

- `rx_head` → next position ISR will write to
- `rx_tail` → next position main loop will read from
- `tx_head` → next position main loop will write to
- `tx_tail` → next position ISR will transmit from
- `head == tail` → buffer empty
- One buffer slot is intentionally left unused to distinguish full vs empty

---

## Software Details

- Language: C
- Toolchain: AVR-GCC
- Style: Bare-metal
- Timing: Hardware timer + interrupts
