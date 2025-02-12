#include <msp430g2553.h>
#include "system.h"
#include <intrinsics.h>
#include <stdint.h>
#include <display.h>
#include <stdio.h>
#include <control_motors.h>
#include <control_encoders.h>

#define PWM_FREQ 1200 //Freq PWM = 10 KhZ with SMCLK = DOSC/1 = 12Mhz

/**
 * main.c
 */
void main(void)
{
    // Stop watchdog timer to prevent time out reset
    WDTCTL = WDTPW | WDTHOLD;

    Init_motors();
    __enable_interrupt();

    while(1)
    {
        Speed_motor (20, RIGHT);
        Speed_motor (20, LEFT);
        __delay_cycles(1000000);
        Speed_motor (50, RIGHT);
        Speed_motor (50, LEFT);
        __delay_cycles(2000000);
        Speed_motor (100, RIGHT);
        Speed_motor (100, LEFT);
        __delay_cycles(3000000);
        Speed_motor (0, RIGHT);
        Speed_motor (0, LEFT);
        __delay_cycles(1000000);
        Speed_motor (-20, RIGHT);
        Speed_motor (-20, LEFT);
        __delay_cycles(1000000);
        Speed_motor (-50, RIGHT);
        Speed_motor (-50, LEFT);
        __delay_cycles(2000000);
        Speed_motor (-100, RIGHT);
        Speed_motor (-100, LEFT);
        __delay_cycles(3000000);
        Speed_motor (0, RIGHT);
        Speed_motor (0, LEFT);
        __delay_cycles(1000000);
    }
}
