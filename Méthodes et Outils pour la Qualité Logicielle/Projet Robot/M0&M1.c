// blocking_movements.c

#include <blocking_movements.h>
distance_type left_wheel;

int straight_move(int direction, int speed, int turns2Add, int steps2Add)
{

        int initial_turns, initial_steps, target_turns, target_steps, target_absolute_steps, notthere =1;

        Read_distance(LEFT, &left_wheel);
        initial_turns = left_wheel.turns;
        initial_steps = left_wheel.steps;

        target_turns = initial_turns + turns2Add + (initial_steps + steps2Add)/12;
        target_steps = (initial_steps + steps2Add) % 12;
        target_absolute_steps = initial_turns * 12 + initial_steps + steps2Add + turns2Add*12;

       if((direction != REVERSE) && (direction != FORWARD))
       {
           return 1;
       }
       if(speed < 0 || speed>100 )
       {
           return 1;
       }


       if(direction == FORWARD )
       {
            Speed_motor(speed,LEFT);
            Speed_motor(speed,RIGHT);
       }
       else if (direction == REVERSE )
       {
           Speed_motor(-speed,LEFT);
           Speed_motor(-speed,RIGHT);
       }

    while (notthere)
    {
        display_number(left_wheel.steps);
        /*if (check_turns_and_steps(target_turns,target_steps) == 1)
        {
            Speed_motor(0,LEFT);
            Speed_motor(0,RIGHT);
            notthere = 0;
        }*/
        if (check_absolute_steps(target_absolute_steps) == 1)
                {
                    Speed_motor(0,LEFT);
                    Speed_motor(0,RIGHT);
                    notthere = 0;
                }
    }
return 0;
}

uint8_t check_turns_and_steps (uint16_t target_turns, uint8_t target_steps)
{
    Read_distance(LEFT, &left_wheel);
    if  ((left_wheel.turns >= target_turns) && (left_wheel.steps >= target_steps) )
    {
        return 1;
    }
    if  (left_wheel.turns > target_turns)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

uint8_t  check_absolute_steps (uint16_t target_absolute_steps)
{
    Read_distance(LEFT, &left_wheel);
       if  ( ((left_wheel.turns*12) + left_wheel.steps) >= target_absolute_steps)
       {
           return 1;
       }
       else
       {
           return 0;
       }
}















// blocking_movements.h

#include "system.h"
#include "display.h"
#include "control_motors.h"
#include "control_encoders.h"

#ifndef BLOCKING_MOVEMENTS_H_
#define BLOCKING_MOVEMENTS_H_

#define REVERSE 0
#define FORWARD 1

int straight_move(int direction, int speed, int target_turns, int target_steps);
uint8_t check_turns_and_steps (uint16_t target_turns, uint8_t target_steps);
uint8_t  check_absolute_steps (uint16_t target_absolute_steps);

#endif






//main.c

#include <msp430g2553.h>
#include "system.h"
#include <intrinsics.h>
#include <stdint.h>
#include "display.h"
#include "control_motors.h"
#include "control_encoders.h"
#include "blocking_movements.h"
#include "compass.h"
#include "sides.h"

#define PWM_FREQ 1200 //Freq PWM = 10 KhZ with SMCLK = DOSC/1 = 12Mhz
/**
 * main.c
 */
void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	Clock_graceInit_DCO_12M();
	display_init();
	Init_motors();
	Init_encoders_distance();
	compass_init_time_out();
	display_init ();

	__enable_interrupt();

	 straight_move(REVERSE,50,3,18);
}








Which solution (turns-steps pair or absolute steps) do you think is better?

The absolute_steps is more simple but requires more power.