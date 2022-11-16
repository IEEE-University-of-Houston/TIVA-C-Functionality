/**
 * UART Demo
 * Author: Gantabya Kadel
 * For IEEEngage Tiva C Functionality Workshop
 * Date: 11/16/22
 * Reference: https://sites.google.com/site/luiselectronicprojects/tutorials/tiva-tutorials/tiva-uart/basic-use-of-uart-stdio
 */
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_GPIO.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.c"
#include "utils/uartstdio.h"
//
#define BAUDRATE 9600
#define CLKFREQ 16000000
//
/*
 * hardwareSetup function doesn't take or return any value.
 * As the name suggests, it's a method responsible for configuring the hardware for use.
 * More specifically, it configures UART and GPIO PF to be used for the demo.
 *
 * For Information on the specific libraries and API functions called please review the datasheet & API library resources provided under resources folder.
 * */
void hardwareSetup();
/*
 * The functions below are used to turn on/ off RGB LEDS of PORT F.
 * PINS are PF1 - PF3 (RED, BLUE, GREEN) LEDS.
 * These functions neither take values nor return any values.
 */
void turnRedOn();
void turnBlueOn();
void turnGreenOn();
void turnRedOff();
void turnBlueOff();
void turnGreenOff();
//

char uartMsg[] = "Hello World\nPlease Select From The Options Below\n1 - Turn On Red LED\n2 - Turn On Blue LED\n3 - Turn On Green LED\n4 - Turn Off RED LED\n5 - Turn Off Blue LED\n6 - Turn Off Green LED\n";
int main(void)
{
    char uartRXVal;
    hardwareSetup();
    UARTprintf("%s", uartMsg);
    //
    while(-1){
       uartRXVal = UARTgetc();
       //
       switch(uartRXVal){
           case '1':
               turnRedOn();
               break;
           case '2':
               turnBlueOn();
               break;
           case '3':
               turnGreenOn();
               break;
           case '4':
               turnRedOff();
               break;
           case '5':
               turnBlueOff();
               break;
           case '6':
               turnGreenOff();
               break;
       }
    }
	return 0;
}
//
void hardwareSetup(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);

    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);
    UARTStdioConfig(0, BAUDRATE, CLKFREQ);
}
//
void turnRedOn(){
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 2);
    // 0010 => 2
}
//
void turnBlueOn(){
    // 0100 => 4
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 4);
}
//
void turnGreenOn(){
// 1000 => 8
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 8);
}
//
void turnRedOff(){
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0);
}
//
void turnBlueOff(){
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0);
}
void turnGreenOff(){
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0);
}
