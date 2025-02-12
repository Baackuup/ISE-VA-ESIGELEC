#include <msp430g2553.h>
#include "system.h"
#include <intrinsics.h>
#include <stdint.h>
#include <sides.h>
#include <display.h>
#include <stdio.h>
#include <control_motors.h>
#include <control_encoders.h>
#include <compass.h>

#define PWM_FREQ 1200 //Freq PWM = 10 KhZ with SMCLK = DOSC/1 = 12Mhz

void main(void)
{
    unsigned int a;
    distance_type var;
    // Stop watchdog timer to prevent time out reset
    WDTCTL = WDTPW | WDTHOLD;

	Clock_graceInit_DCO_12M();
	display_init();

	compass_init_time_out();
    int bear;
    while (1)
    {
        Read_compass_8 (&bear);
        display_number(bear);
        __delay_cycles(1000000);
    }
}