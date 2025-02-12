






.c
#include <blocking_movements.h>

void straight_move(int direction, int speed, int target_turns, int target_steps)
{

    distance_type left_wheel;
    int initial_turns, initial_steps, final_turns, final_steps;

    Read_distance(LEFT, &left_wheel);
    initial_turns = left_wheel.turns;
    initial_steps = left_wheel.steps;

    final_turns = initial_turns + target_turns + (initial_steps + target_steps)/12;
    final_steps = (initial_steps + target_steps) % 12;
    while(1)
    {
        Read_distance(LEFT, &left_wheel);
        display_number(left_wheel.steps);
        if(direction == FORWARD && (   (left_wheel.turns)!= final_turns || (left_wheel.steps)!= final_steps   ) )
        {
            Speed_motor(speed,LEFT);
            Speed_motor(speed,RIGHT);
        }
        else if (direction == REVERSE && ((left_wheel.turns)!= final_turns || (left_wheel.steps)!= final_steps) )
        {
            Speed_motor(-speed,LEFT);
            Speed_motor(-speed,RIGHT);
        }
        else
        {
            Speed_motor(0,LEFT);
            Speed_motor(0,RIGHT);
        }
     }
}




















.h
#include "system.h"
#include "display.h"
#include "control_motors.h"
#include "control_encoders.h"

#ifndef BLOCKING_MOVEMENTS_H_
#define BLOCKING_MOVEMENTS_H_

#define REVERSE 0
#define FORWARD 1

void straight_move(int direction, int speed, int target_turns, int target_steps);

#endif



Questions :

- Which encoder did you use to measure distance (LEFT/RIGHT)? Why?

We used the LEFT encoder because the right encoder doesn't work on our robot.

- Do you think this function straight_move does call init_motors,
init_display, Init_encoders_distanc, or Clear_Distance?

The function doesn't call any of the line.

- It would be very useful, during development stage, to have some debugging info in the display,
like showing turns, steps, or any string you need in the display. This debugging code will never
run in the final, deployed application, so following Rule 2.2 (required) from MISRA-C, this code
must removed before compiling the final version of your program. Is there an automatic way
to do that? Do you know conditional compilation?

Yes, conditional compilation allows you to include or exclude certain code segments during compilation based on predefined conditions.
In the context of debugging, you can use preprocessor directives like #ifdef and #endif to enclose debugging statements.
By defining a macro (e.g., DEBUG) to control whether debugging code should be included, you can easily toggle debugging on or off.
During development, you can set the macro to enable debugging, and before compiling the final version for deployment, you can disable debugging by changing the macro definition.
This ensures that debugging code is automatically removed from the final compiled application, as required by Rule 2.2 from MISRA-C.

