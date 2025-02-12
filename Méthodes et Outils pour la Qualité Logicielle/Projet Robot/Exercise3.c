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

    Clock_graceInit_DCO_12M();
    display_init();

    Init_encoders_distance();
    Speed_motor (20, LEFT);
    distance_type abc;
    while(1)
    {
     	Read_distance (LEFT, &abc);
     	display_number(abc.turns);
    }

}