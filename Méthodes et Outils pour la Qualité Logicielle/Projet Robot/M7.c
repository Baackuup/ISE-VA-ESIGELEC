main 
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
#include <bearing.h>

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
	unsigned int bearing =0;

	__enable_interrupt();

	 new_bearing (&bearing, -900);
	 display_number (bearing);
	    new_bearing (&bearing, -900);
	     display_number (bearing);
	     new_bearing (&bearing, 900);
	      display_number (bearing);
	       new_bearing (&bearing, 900);
	          display_number (bearing);

	 while (1)
       {
	     Read_compass_16(&bearing);
          if (in_movement == 0) // If robot is not moving run a new movement
          {
            switch(movement_nb)
            {
            case 0: //to do: Run non_blockin straight forward or reverse and update system state
                              bearing = new_bearing (&bearing, -900);

                              in_movement = 1;
                              movement_nb = 1;
                              break;
              /*case 1: //to do: Run non_blockin straight reverse movement and update system state
                  if (nb_spin_steps(LEFTr, 50, 3, 18) == 0);
                  {
                         in_movement = 1;
                  }
                  movement_nb = 2;
                  break;
              case 2: //to do: Run non_blockin straight forward or reverse and update system state
                  if (nb_spin_steps(RIGHTr, 50, 3, 18) == 0 )
                  {
                         in_movement = 1;
                  }
                  movement_nb = 3;
                  break;
              case 3: //to do: Run non_blockin straight forward or reverse and update system state
                  target_bearing = new_bearing (current_bearing, -900);
                  do{
                      nb_spin_steps(RIGHTr, 10, 3, 18);
                  }while(current_bearing != target_bearing);

                  in_movement = 1;
                  movement_nb = 4;
                  break;*/
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
       }
}






bearing.c 
#include <bearing.h>

uint8_t new_bearing(uint16_t *current_bearing, int16_t change_course)
{
    int16_t sum;
    sum = *current_bearing + change_course;

        if((sum >= -3600) && (sum <= 3600))
        {
            if((sum >= 0) && (sum <= 3599) )
            {
                *current_bearing = sum;
                return 0;
            }
            else if (sum >= 3600)
            {
                *current_bearing = (sum % 3600);
                return 0;
            }
            else if (sum < 0)
            {
                *current_bearing = sum + 3600;
                return 0;
            }
            else
            {
                return 0;
            }
        }
}



bearing.h
#ifndef bearing_H_
#define bearing_H_

#include <stdint.h>

uint8_t new_bearing(uint16_t *current_bearing, int16_t change_course);

#endif

