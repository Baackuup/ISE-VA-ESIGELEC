#include <msp430g2553.h>
#include "system.h"
#include <intrinsics.h>
#include <stdint.h>
#include <display.h>
#include <stdio.h>
#include <control_motors.h>
#include <control_encoders.h>

/**
 * main.c
 */
void main(void)
{
    // Stop watchdog timer to prevent time out reset
    WDTCTL = WDTPW | WDTHOLD;


    //Exercice T1
    Clock_graceInit_DCO_12M();
    display_init();

    unsigned int a;

    while(1)
    {
        for(a=0;a<=255;a++)
        {
            display_number(a);
            __delay_cycles(2400000);
        }
    }
}
