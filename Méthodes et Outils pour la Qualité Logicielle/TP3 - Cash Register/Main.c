/*
 *    MISRA C:2012 Cash Register project
 * ========================================
 * File Path     : Main.c
 * Author        : M.W.Richardson
 * Date          : 16/05/13
 * Copyright     : (c) 2013 Liverpool Data Research Associates
 */
#include <stdio.h>

#include "Misrac_types.h"
#include "Userinterface.h"

/* 
 * Simple main that loops 
 * until the character 'q' is pressed
 * Then it exits
 */
LDRA_int32_t main(void) 
{
  LDRA_char_t theChar = '0';

  printf("LDRA MISRA C:2012 Cash Register\n");
  Userinterface_help();

  /* Parse characters received from the keyboard */
  while (theChar != 'q')
  {
    theChar = (LDRA_char_t) getchar();
    Userinterface_parse(theChar);
  }
  return 1;
}
