//spin_bearing.c

/*
 * spin_bearing.c
 *
 *  Created on: 16 févr. 2024
 *      Author: PIVON
 */


#include <spin_bearing.h>
#include <bearing.h>
int goaway=1;

void spin_bearing (int rotation, int speed, uint8_t bearing)
{
     if (bearing < 0 || bearing>3599)
        {
        return 0;
        }
    else
    {
        if (rotation != LEFTT || rotation != RIGHTT)
        {
            return 0;
        }
        else
        {
            if (rotation = LEFTT)
            {
                Speed_motor(-speed,LEFT);
                Speed_motor(speed,RIGHT);
                while (goaway)
                    {
                        if (*current_bearing == bearing)
                        {
                               Speed_motor(0,LEFT);
                               Speed_motor(0,RIGHT);
                               goaway = 0;
                        }
                     }
            if (rotation = RIGHTT)
            {
                Speed_motor(speed,LEFT);
                Speed_motor(-speed,RIGHT);
                while (goaway)
                {
                    if (*current_bearing == bearing)
                    {
                        Speed_motor(0,LEFT);
                        Speed_motor(0,RIGHT);
                        goaway = 0;
                    }
            }
        }
    }
}

