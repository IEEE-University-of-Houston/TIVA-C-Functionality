

/**
 * UART Demo
 * Author: Gantabya Kadel
 * For IEEEngage Tiva C Functionality Workshop
 * Reference: https://sites.google.com/site/luiselectronicprojects/tutorials/tiva-tutorials/tiva-uart/basic-use-of-uart-stdio
 */
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
//
#include "inc/hw_memmap.h"
#include "inc/hw_GPIO.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
//
#include "driverlib/uart.h"
#include "utils/uartstdio.c"
#include "utils/uartstdio.h"
//
void TurnOnRed(){
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 2);
}
void TurnOnGreen(){
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 8);
}
void TurnOnBlue(){
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 4);
}
void TurnOffRed(){
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0);
}
void TurnOffGreen(){
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0);
}
void TurnOffBlue(){
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0);
}

int main(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    //
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    //
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
    //
    SysCtlDelay(3);
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //

    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);
    UARTStdioConfig(0, 9600, 16000000);
    //

    char uartVal;
    UARTprintf("Hello World\nPlease Select From The Options Below!\n");
    UARTprintf("1 - Turn On Red LED\n2 - Turn On Blue LED\n3 - Turn On Green LED\n");
    UARTprintf("4 - Turn Off Red LED\n5 - Turn Off Blue LED\n6 - Turn Off Green LED\n");
    //
    //UARTprintf("Your Wrote The Character %c\n", UARTgetc());
    while(-1){
        uartVal = UARTgetc();
        //
        switch(uartVal){
            case '1':
                TurnOnRed();
                break;
            case '2':
                TurnOnBlue();
                break;
            case '3':
                TurnOnGreen();
                break;
            case '4':
                TurnOffRed();
                break;
            case '5':
                TurnOffBlue();
                break;
            case '6':
                TurnOffGreen();
                break;
        }
    }
	return 0;
}
