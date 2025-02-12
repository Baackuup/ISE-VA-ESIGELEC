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
	unsigned int current_bearing;
	int target_bearing;

	__enable_interrupt();


	 target_bearing = new_bearing (1800, -900);
	 display_number (target_bearing);
	    target_bearing = new_bearing (800, -900);
	     display_number (target_bearing);
	     target_bearing = new_bearing (1800, 900);
	      display_number (target_bearing);
	       target_bearing = new_bearing (2800, 900);
	          display_number (target_bearing);

	 while (1)
       {
	     Read_compass_16(&current_bearing);
          if (in_movement == 0) // If robot is not moving run a new movement
          {
            switch(movement_nb)
            {
            case 0: //to do: Run non_blockin straight forward or reverse and update system state
                              target_bearing = new_bearing (current_bearing, -900);
                              do{
                                  //nb_spin_steps(RIGHTr, 30, 3, 18);
                                  Speed_motor(50,LEFT);
                                  Speed_motor(-50,RIGHT);
                                  Read_compass_16(&current_bearing);
                                  display_number (current_bearing);
                              }while(current_bearing != target_bearing);
                              Speed_motor(0,LEFT);
                              Speed_motor(0, RIGHT);

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





#include <bearing.h>
uint16_t new_bearing(uint16_t current_bearing, int16_t change_course)
{
    int16_t sum = current_bearing + change_course;

        if((sum >= 0) && (sum <= 3599) )
        {
            return sum;
        }
        else if (sum >= 3599)
        {
            return (sum - 3600);
        }
        else if (sum < 0)
        {
                    return (sum + 3600);
        }
        else
        {
            return 0;
        }
}





#ifndef bearing_H_
#define bearing_H_
#include <stdint.h>

uint16_t new_bearing(uint16_t current_bearing, int16_t change_course);

#endif






