## Project owners

- Karim El Hosni
- Sara Beddouch
- Thierry Beaulieu
- Tuan Quoc Pham

## Project Summary

![Epreuve_finale](https://user-images.githubusercontent.com/46804791/208727113-7ae98ca2-8609-49e8-b4e5-8a14243ea954.png)

## Introduction

This project is made so that a 'robot' could follow a predefined path. For achieving this, an ATmega324pa was used as the main chip of the embedded system. The main program located in project/app/main.cpp where you can see that a finite state machine was designed to achieve this purpose. The hardware abstraction layer depends on the avr-libc library.

This project uses many tools such as timers, USART, interuptions, peripherals (infrared sensor, line detector, LCD screen and buttons), external memory and pwm.

- Footnote: even though this README is in english, the whole project was made during a course given by a francophone university. The rest of this project is therefore made in french.
