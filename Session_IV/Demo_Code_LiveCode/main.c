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

char uartMsg[] = "";
int main(void)
{
	return 0;
}
//
void hardwareSetup(){

}
//
void turnRedOn(){

}
//
void turnBlueOn(){

}
//
void turnGreenOn(){

}
//
void turnRedOff(){

}
//
void turnBlueOff(){

}
void turnGreenOff(){

}
