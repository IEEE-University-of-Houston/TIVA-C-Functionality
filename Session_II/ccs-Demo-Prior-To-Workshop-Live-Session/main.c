/*
 * Gantabya Kadel
 * 10/16/22
 * IEEEngage Tiva C Functionality Workshop
 * Utilizing Joshua Lamb's Example for Educational Purposes
 * Link for Article: https://www.egr.msu.edu/classes/ece480/capstone/fall15/group09/appnotes/JoshuaLambApplicationNote.pdf
 * Utilized Code Authored by Gantabya Kadel, Matthew Blam, Nhat Nguyen for Dr.Le's Embedded Course Project for Reference
 *
 * Example Utilized from Lamb's Article did not contain all the needed libraries.
 * Code has been "worked" on with more comments and new changes for Workshop Demo Use for PWM Module Example.
 *
 */
#include <stdlib.h>
// Standard C library
#include <stdint.h>
#include <stdbool.h>

/*
 * The two libraries above define variable types.
 * Types like uint32_t etc are defined in stdint.h
 * Types like bool are defined in stdbool.h
 */


#include "inc/hw_memmap.h"

/*
 * Library above defines the base port addresses for the GPIO ports.
 * And base memory address for PWM Output. Allows MC to know which reg to use.
 */

#include "inc/hw_GPIO.h"

/*
 * Library immediately above includes the set of values required to unlock specific function pins
 *  GPIO pins on the MC
 */

#include "driverlib/gpio.h"
/*
 * Library immediately above includes GPIO functional values and needed API functions.
 */

#include "driverlib/pin_map.h"
/*
 * Library above includes API functions based on pin for most TI MCs including this one.
 */

#include "driverlib/pwm.h"
/*
 * Library includes Functions for PWM.
 */

#include "driverlib/sysctl.h"
/*
 * Library includes drivers needed to access on chip modules.
 */
#include "inc/hw_types.h" // required for HWREG Macro

int main(void)
{
  // For Enabling each function used takes >= 1 unsigned int x32 (uint32_t)

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); // Port F Enabled
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1); // PWM 1 Enabled
    //PW1 is the PWM Module that Port F can use (datasheet)
    // Port F has LEDS associated with it so it helps in demo purposes.

    //SysCtlPWMClockSet(SYSCTL_PWMDIV_4); // setting the PWM Clock
    // SYSCTL_PWMDIV_1 divides the default clock for PWM to be divided by 1.
    // Doesn't really change much right now ... other than the clock being enabled.

    SysCtlPWMClockSet(SYSCTL_PWMDIV_64); // 1.25 MHz ... 80 MHz is clock speed of processor and division by 64 = 1.25

    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01;

    // These functions enable the access to the GPIO Pins of Port F.
    // Without "unlocking" them ... only default access to the pins would be there. Need them "unlocked" for PWM

    GPIOPinConfigure(GPIO_PF0_M1PWM4);
    GPIOPinConfigure(GPIO_PF1_M1PWM5);
    GPIOPinConfigure(GPIO_PF2_M1PWM6);
    GPIOPinConfigure(GPIO_PF3_M1PWM7);

   /*
    * Configuring individual pins of Port F for PWM module pins.
    * GPIO_PF0_M1PWM4 ==> PF0 (pin f 0) PWM Module 1 pin 4.
    * Pin 4 now becomes the output pin of the PWM Module to the GPIO Pin 4.
    */

    GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);

    // Configuring PWM
    PWMGenConfigure(PWM1_BASE, PWM_GEN_2, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
    PWMGenConfigure(PWM1_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
    // Configures PWM Module generator for M1 Generator 2 and 3.
    // Generator creates PWM Pulses
    // PWM1_BASE = module based used
    // PWM_GEN_2 = Generator 2 outputs to PWM pins 4 and 5 PWMPin 4 = PF0 ... PWMPin 5 = PF1
    // PWM_GEN_3 = Generator 3 outputs to PWM pings 6 and 7 PWMPin 6 = PF2 ... PWMPin 7 = PF3
    // PWM_GEN_MODE_DOWN counts values for generator down ... creates a "saw-tooth wave"
    // PWM_GEN_MODE_UP_DOWN creates a "triangle wave."
    // PWM_GEN_MODE_NO_SYNC ... doesn't allow the generator to sync with the clock before providing updates.

    uint32_t  width;


// From Google ... 10 million ticks = 1 second
    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_2, 10000000);
    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_3, 10000000);

    // API functions to generate Pulse period (modulation duration so to speak in a way)
    // 400 ==> 400 clock ticks as the period so a full cycle would be 400 * 2 = 800 clock ticks.

    // Setting the Pulse Width to 300 ticks
    // Pulse Width == Duty Cycle
    // clock period = 400 ticks ==> Cycle = 800 ticks
    // Thus, a Duty Cycle of 300 ticks would be 75% duty cycle for 400 tick period
    //          300/400 = 3/4 = .75 ==> 75%
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_4, 5000000);
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5, 10000000);
    // PWM Module Gen 2 Pins
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6, 5000000);
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7, 5000000);
    // PWM Module Gen 3 Pins

    PWMGenEnable(PWM1_BASE, PWM_GEN_2);
    PWMGenEnable(PWM1_BASE, PWM_GEN_3);
    // API Calls To Enable the PWM Module Generators. Done so here since values of gen are satisfied.

    //PWMOutputState(PWM1_BASE, (PWM_OUT_4_BIT | PWM_OUT_5_BIT | PWM_OUT_6_BIT | PWM_OUT_7_BIT ), true);
    //PWMOutputState(PWM1_BASE, (PWM_OUT_4_BIT), true);
    PWMOutputState(PWM1_BASE, (PWM_OUT_5_BIT), true);
    //PWMOutputState(PWM1_BASE, (PWM_OUT_6_BIT), true);
    //PWMOutputState(PWM1_BASE, (PWM_OUT_7_BIT), true);
    // Enables PWM Module to Modify Pens Set for PWM Output.

    while(1){
        for(width = 0; width < 10000000; width++){
            PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5,width);
        }
        SysCtlDelay(10000000);
        for(width = 10000000; width > 0; width--){
            PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5,width);
        }
        SysCtlDelay(10000000);
    }
   // return 0;
}
