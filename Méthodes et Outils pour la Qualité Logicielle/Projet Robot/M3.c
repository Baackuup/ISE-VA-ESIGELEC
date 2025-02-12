//scheduler.c

/*
 * scheduler.c
 *
 *  Created on: 29/1/2018
 *      Author: amarti
 */
#include "scheduler.h"
#include <intrinsics.h>
#include <system.h>

static uint16_t Tick_out = 0;


/* Called from TA_0 ISR*/
void callback_2ms(void) 
{
    Tick_out = 1;
}



uint8_t check_and_clear_Tick_out_GIE(void)
{
    uint16_t local_Tick_out = 0;
    uint8_t interrupt_state = 0;

    interrupt_state = __get_interrupt_state();

    __disable_interrupt();

    local_Tick_out = Tick_out;
    Tick_out = 0;

    __set_interrupt_state(interrupt_state);

    return local_Tick_out;
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

//extern uint16_t Tick_out; uncomment only if you are in M2


void callback_2ms(void);
uint8_t check_and_clear_Tick_out_GIE(void);

#endif /* SCHEDULER_H_ */









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
              if (check_and_clear_Tick_out_GIE()==1) //Time trigger It is time to check.
              {
                  in_movement = check_stop_steps();
              }
          }
          //something to do at the same time the robot moves
          display_number (movement_nb);
       }
}
