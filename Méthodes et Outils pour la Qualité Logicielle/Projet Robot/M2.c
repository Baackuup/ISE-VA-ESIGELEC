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
#include "non_blocking_movement.h"
#include "scheduler.h"

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
	int in_movement = 0, movement_nb = 0;

	__enable_interrupt();

	 while (1)
       {
          if (in_movement == 0) // If robot is not moving run a new movement
          {
            switch(movement_nb)
            {
              case 0: //to do:Run non_blocking straight forward movement and update system state
                  if (nb_straight_move(FORWARD, 50, 3, 18) == 0 )
                  {
                         in_movement = 1;
                  }
                  movement_nb = 1;
                  break;
              case 1: //to do: Run non_blockin straight reverse movement and update system state
                  if (nb_straight_move(REVERSE, 50, 3, 18) == 0 )
                  {
                         in_movement = 1;
                  }
                  movement_nb = 2;
                  break;
              case 2: //to do: Run non_blockin straight forward or reverse and update system state
                  if (nb_straight_move(FORWARD, 50, 3, 18) == 0 )
                  {
                         in_movement = 1;
                  }
                  movement_nb = 3;
                  break;
              default:
                  break;
            }
          }
          else //The robot is moving, check if it must stop
          {
              if (Tick_out) //Time trigger It is time to check.
              {
                  in_movement = check_stop_steps();
                  Tick_out = 0;
              }
          }
          //something to do at the same time the robot moves
          display_number (movement_nb);
       }
}







//non_blocking_movement.c

#include <non_blocking_movement.h>
distance_type left_wheel;
distance_type distance_to_stop;

int nb_straight_move(int direction, int speed, int turns2Add, int steps2Add)
{
    int initial_turns, initial_steps, target_turns, target_steps, target_absolute_steps;

    Read_distance(LEFT, &left_wheel);
    initial_turns = left_wheel.turns;
    initial_steps = left_wheel.steps;

    distance_to_stop.turns = initial_turns + turns2Add + ((initial_steps + steps2Add)/12);
    distance_to_stop.steps = (initial_steps + steps2Add) % 12;

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
    return 0;
}

uint8_t check_stop_steps()
{
    Read_distance(LEFT, &left_wheel);
        if  ((left_wheel.turns >= distance_to_stop.turns) && (left_wheel.steps >= distance_to_stop.steps) )
        {
            Speed_motor(0,LEFT);
            Speed_motor(0,RIGHT);
            return 0;
        }
        if  (left_wheel.turns > distance_to_stop.turns)
        {
            Speed_motor(0,LEFT);
            Speed_motor(0,RIGHT);
            return 0;
        }
        else
        {
            return 1;
        }
}









//non_blocking_movement.h

#include "system.h"
#include "display.h"
#include "control_motors.h"
#include "control_encoders.h"

#ifndef NON_BLOCKING_MOVEMENTS_H_
#define NON_BLOCKING_MOVEMENTS_H_

#define REVERSE 0
#define FORWARD 1

int nb_straight_move(int direction, int speed, int target_turns, int target_steps);
uint8_t check_stop_steps();

#endif










//scheduler.c

/*
 * scheduler.c
 *
 *  Created on: 29/1/2018
 *      Author: amarti
 */

#include "scheduler.h"

uint16_t Tick_out = 0;

/* Called from TA_0 ISR*/
void callback_2ms(void) 
{
  /*Maybe this is no the final place to declare this variable*/

 Tick_out = 1;
}












//scheduler.h

/*
 * scheduler.h
 *
 *  Created on: 29/1/2018
 *      Author: amarti
 */

#include <msp430g2553.h>
#include "stdint.h"

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

extern uint16_t Tick_out;

void callback_2ms(void);


#endif /* SCHEDULER_H_ */