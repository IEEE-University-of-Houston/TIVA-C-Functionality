/*
 * This is a "cleaned up" modularized version of the code writeen during workshop on 10/19/22
 * Above each function will contain a brief summary or few sentences decribing the purpose/task of said function
 *
 * Author: Gantabya Kadel
 * IEEEngage - Tiva C Functionality Workshop
 * For resources used please refer to the code on git hub in the directory "ccs-Demo-Prior-To-Workshop-Live-Session"
 */

// standard C libraries
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
// libraries for the board specifically
#include "inc/hw_memmap.h"
#include "inc/hw_GPIO.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/pwm.h"
#include "driverlib/sysctl.h"
#include "inc/hw_types.h"
//
// ----------------------------------------- Functions Below ---------------------------------------------------------------------------------------

/*
 * enablePeripherals function doesn't take or return any value.
 * It enables Fort F and PWM module 1 (one of the 2 PWM modules of Tiva C) to be configured.
 * It sets the PWM clock to the default Tiva C clock frequence divided by 64, which comes out about 1.25 MHz.
 * Default clock speed should be 80 MHz.
 * other options to set the clock as a ratio of default clock are SYSCTL_PWMDIV_1, SYSCTL_PWMDIV_4, SYSCTL_PWMDIV_16
 * They divide the default clock frequency by 1 through 16 respectively.
 * Lastly, this function also unlocks port F for alternate function ... for pwm ouputs.
 *
 * For further information please review datasheet and API library provided under the resources folder in the git repo.
 */
void enablePeripherals(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
    SysCtlPWMClockSet(SYSCTL_PWMDIV_64);
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01;
}
// -------------------------------------------------------------------------------------------------------------------------------------------------
/*
 * configureGPIO function doesn't take or return any value.
 * As the name suggests, it configures pins PF1 - PF3 as GPIO pins.
 * It also sets them as PWM GPIO pins
 * The reason for selecting pings PF1 - PF3 are in 2 parts:
 *  From documentation we know that Port F contains RBG LEDS ... PF1 = Red, PF2 = Blue, PF3 = Green
 *  And documentation also states each pin has a specific PWM generator and module blocks.
 *  PWM1 module block contains 4 generators much like PWM0 module block.
 *  PWM1 module block has 2 generators PWM1 and PWM2 that "talk to" pins PF0 - PF3.
 *  PF0 isn't utilized here because it isn't visible on the board like the LEDS pins are.
 *  As mentioned during presentation ... each PWM module block has 4 generators and each generator has 2 outputs for a total of 16 outputs.
 *  The Module block we're using here is module 1, the second module block on-board, PWM1.
 *  Of the 4 pwm generators allocated to PWM1, the generators PWM_GEN_2 and PWM_GEN_3 "talk" to output pins 4 - 7
 *  These pins on the board are PF0 - PF3 respectively.
 *  And since each generator has 2 outputs.
 *  PWM_GEN_2 outputs to PF0 and PF1 (pin 4 and 5) whereas PWM_GEN_3 outputs to PF2 and PF3 (pin 6 and 7)
 *
 *  For further information please review datasheet and API library provided under the resources folder in the git repo.
 */
void configureGPIO(){
    GPIOPinConfigure(GPIO_PF1_M1PWM5);
    GPIOPinConfigure(GPIO_PF2_M1PWM6);
    GPIOPinConfigure(GPIO_PF3_M1PWM7);
    GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
}
// -------------------------------------------------------------------------------------------------------------------------------------------------
/*
 * configureAndEnablePWM function doesn't take in any values nor does it return any.
 * As the name suggests the function below configures and enables the PWM module for function.
 * More specifically, it configures the counting method (for internal registers) as "PWM_GEN_MODE_DOWN"
 * This counting method creates a sawtooth wave for the counters.
 * The function then sets the pwm period to be 10 million ticks for both generators. 10 million ticks ~ 1 second (from a random google search)
 * Whether 10 million ticks is 1 sec or not isn't important ... as it provides a long enough period for us to "notice" modulation.
 * The period here is the amount of ticks in-between each pulse of modulation so to speak of the generators.
 * Finally for each of the pins (pins 5 - 7) the function sets a duty cycle of 50% with a value of 5 million ticks.
 * Lastly, the function enables both generator 2 and generator 3 for operation.
 *
 * For further information please review datasheet and API library provided under the resources folder in the git repo.
 */
void configureAndEnablePWM(){
    PWMGenConfigure(PWM1_BASE, PWM_GEN_2, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
    PWMGenConfigure(PWM1_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_2, 10000000);
    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_3, 10000000);
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5, 5000000);
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6, 5000000);
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7, 5000000);
    PWMGenEnable(PWM1_BASE, PWM_GEN_2);
    PWMGenEnable(PWM1_BASE, PWM_GEN_3);
}
// ------------------------------------------------------------------------------------------------------------------------------------------------
/*
 * The functions, enableAccessPin#, below all perform the same action for their respective pins. Pins 5 - 7.
 * They give MC the permission to output to their respective pins (in simple language).
 * We can actually achieve this for all of the pins with one like (see below):
 *        PWMOutputState(PWM1_BASE, (PWM_OUT_5_BIT | PWM_OUT_6_BIT | PWM_OUT_7_BIT), true);
 *  we can provide access for all pins the end-user is allowed to configure in similar manner ...
 *     .... As long as the BASE value like PWM1_BASE is the same for all pins in question.
 *  So this begs the questions ... why doesn't this script configure them together?
 *  => Simple Answer ... The demo here highlights each individual pin at a time.
 *      Configuring all of the LED pins at once will produce a white light and we can't see individual Pins in action.
 *
 * For further information please review datasheet and API library provided under the resources folder in the git repo.
 */
void enableAccessPin5(){
    PWMOutputState(PWM1_BASE, PWM_OUT_5_BIT, true);
}
void enableAccessPin6(){
    PWMOutputState(PWM1_BASE, PWM_OUT_6_BIT, true);
}
void enableAccessPin7(){
    PWMOutputState(PWM1_BASE, PWM_OUT_7_BIT, true);
}
/*
 * The functions, disableAccessPin#, below all perform the same action for their respective pins. Pins 5 - 7.
 * They perform the opposite action to the functions, enableAccessPin#.
 *
 * For further information please review datasheet and API library provided under the resources folder in the git repo.
 */
void disableAccessPin5(){
    PWMOutputState(PWM1_BASE, PWM_OUT_5_BIT, false);
}
void disableAccessPin6(){
    PWMOutputState(PWM1_BASE, PWM_OUT_6_BIT, false);
}
void disableAccessPin7(){
    PWMOutputState(PWM1_BASE, PWM_OUT_7_BIT, false);
}
// -------------------------------------------------------------------------------------------------------------------------------------------------
int main(){
    uint32_t width;
    enablePeripherals();
    configureGPIO();
    configureAndEnablePWM();
    /*
     * Below is an infinite loop that simulates the brightening of LEDS  with PWM
     * Each color (each individual pin) will start from 0 and go to 10 million ticks  & Go from 10 million ticks to 0 tick value.
     * This is basically going from 0% duty cycle to 100% duty cycle. (just about)
     * we'll be alternating the pulse width
     */
    while(1){
// ---------------------------------------- Pin 5 ==> PF1 Below ==> Red --------------------------------------------------------------------
        enableAccessPin5();
        for(width = 0; width < 10000000; width++){
            PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5, width);
        }
        //SysCtlDelay(100000);

        for(width = 10000000; width > 0; width--){
            PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5, width);
        }
        //SysCtlDelay(100000);
        disableAccessPin5();
// ------------------------------------------ Pin 6 ==> PF2 Below ==> Blue -------------------------------------------------------------------
        enableAccessPin6();
        for(width = 0; width < 10000000; width++){
            PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6, width);
        }
        //SysCtlDelay(100000);

        for(width = 10000000; width > 0; width--){
            PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6, width);
        }
        //SysCtlDelay(100000);
        disableAccessPin6();
// ------------------------------------------- Pin 7 ==> PF3 Below ==> Green -------------------------------------------------------------------
        enableAccessPin7();
        for(width = 0; width < 10000000; width++){
            PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7, width);
        }
        //SysCtlDelay(100000);

        for(width = 10000000; width > 0; width--){
            PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7, width);
        }
        //SysCtlDelay(100000);
        disableAccessPin7();
    } // while loop end brace
// Removing the SysCtlDelays() seems to have smoothened out the color transitions.
    // I have kept the commented out, just in case someone wants them.
/*
 * Feel free to experiment with various RGB combinations. You would only need to enable and disable Access to the respective Pins.
 * And also to write to set the PWMPulse width for them under one of the RGB for loops.
 * For example for a red + green combo you can have access to pin 5 and 7 enabled and then may write to both red and green
 *          under either the pin 5 for loop or pin 7 for loop.
 *
 * Lastly, feel free to decrease the width count if you feel that the count is too long or short.
 */
}
