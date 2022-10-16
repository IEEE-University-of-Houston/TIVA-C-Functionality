# TIVA-C-Functionality
Texas Instruments’ Tiva C Series microcontrollers (MCs) traces its roots to the first MCs available on the market based on the ARM Cortex-M processor architecture. This has since quickly become the industry standard.

ECE and CpE students should, generally, get an introduction to these topics in their Microprocessor courses, whether they be Microprocessor Systems, Embedded Microcomputer Systems etc. Moreover, a Tiva C LaunchPad is, generally, an inexpensive microcontroller to acquire and has supporting IDEs that make for easier learning and development.

Tivas are frequently used in these microprocessor courses. In this workshop, student will get a general overview of Tiva C and some of its modules. Students will also be provided an opportunity to create functionalities with these Tiva modules as an introduction to something they may encounter in their coursework. 

![TIVA_C_Flyer_Updated](https://user-images.githubusercontent.com/25860232/196058159-d1554bae-1de0-4c1e-9ae9-6e814383a73f.png)

Session 1: What is Tiva C? Working with a Tiva C (09/29/22)
- Introduction and Background
- Ports and Input
    - Provide pin layout and APIs
    - This Goes with Overall Tiva Module Discussion from Datasheet
- General Purpose Input Output (GPIO)
- Universal Asynchronous Receivers/Transmitters (UARTs)
- Analog To Digital Converter (ADC)
- Pulse Width Modulator (PWM)
- Hibernation
- Recording: https://youtu.be/HejvJeOKDL4

![TIVA-C 2](https://user-images.githubusercontent.com/25860232/196058142-78e20e43-3788-4787-9725-babe238fcb14.png)

Session 2: Basic LED Blink & Color Change (10/19/22)
- Sample Code (with removed main functions)
- Overview of IDE
    - Code Composer Studio (“professional” tool)
    - Kiel (“professional” tool)
    - IAR Systems (“professional” tool)
    - Energia (“non-professional” tool)

Session 3: Working with a Distance Sensor (11/02/22)
- Intro To PID
- Use ADC module to convert read-in inputs to accurate distance value.
- Outputting Appropriate LED Signals Depending on the Distance
    - Example: Red → Too Close … Green → Good Distance 

Session 4: Connecting and Powering Wheels (11/17/22)
- Working with the PWM Module of Tiva C
- Control the “speed” with the readings from the Distance Sensor
    - For example: Stop if too close to object & Blink Red (5 sec)
