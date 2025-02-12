/*
 *    MISRA C:2012 Cash Register project
 * ========================================
 * File Path     : Userinterface.c
 * Author        : M.W.Richardson
 * Date          : 16/05/13
 * Copyright     : (c) 2013 Liverpool Data Research Associates
 */

#include <stdio.h>

/* Used for random function */
#include <stdlib.h>

#include "Misrac_types.h"
#include "Userinterface.h"
#include "Cashregister.h"

/* Forward declarations */
/* ==================== */

static void goodbye(void);
static void randomShopping(void);

/* Private functions */
/* ================= */

/*
 * Function to print out a message at the end of the program
 */
static void goodbye(void)
{
  printf("\nok bye\n");
}

/*
 * Function that can be called to randomly select products
 */
static void randomShopping(void)
{
  LDRA_uint32_t index = 0U;
  LDRA_uint32_t code;

  printf("\n");
  Cashregister_start();
  while (index < (10U + ((LDRA_uint32_t) rand() % 50U )))
  {
    code = (LDRA_uint32_t) rand() % 7U;
    if (0U == code)
    {
      Cashregister_cancel();
    }
    else
    {
      Cashregister_barcode(12343U + code);
    }
    index++;
  }
  Cashregister_end();
}

/* Public functions */
/* ================ */

/*
 * Userinterface a help message to indicate what commands are available
 */
void Userinterface_help(void)
{
  printf("choices are :\n");
  printf("            : 0-9 to compose barcode\n");
  printf("            : b to enter barcode\n");
  printf("            : c to cancel last product\n");
  printf("            : r to do random shopping\n");
  printf("            : s to start\n");
  printf("            : e to end\n");
  printf("            : n for Coconuts\n");
  printf("            : p for Pears\n");
  printf("            : l for Lychees\n");
  printf("            : k for Kiwis\n");
  printf("            : g for Pommegranates\n");
  printf("            : w for Watermelons\n");
  printf("            : q to quit program\n");
}

/*
 * parse the character entered and issue appropriate command
 */

LDRA_uint32_t Userinterface_parse(const LDRA_char_t aChar)
{
  LDRA_uint32_t menu;
  if ((aChar >= '0') && (aChar <= '9'))
  {
    Cashregister_key((const LDRA_uint32_t)aChar - (const LDRA_uint32_t)'0');
	menu = 0u;
  }
  else
  {
    switch (aChar)
    {
      case 'b':
        Cashregister_code();
		menu = 1u;
        break;
      case 'n':
		/* Coconuts */
        Cashregister_barcode(12340U);
		menu = 2u;
        break;
      case 'l':
		/* Lychees */
        Cashregister_barcode(12346U);
		menu = 3u;
        break;
      case 'k':
		/* Kiwis */
        Cashregister_barcode(12347U);
		menu = 4u;
        break;
      case 'p':
		/* Pomegranates */
        Cashregister_barcode(12348U);
		menu = 5u;
        break;
      case 'g':
		/* Pears */
        Cashregister_barcode(12349U);
		menu = 6u;
        break;
      case 'w':
		/* Watermelons */
        Cashregister_barcode(12350U);
		menu = 7u;
        break;
      case 'c':
        Cashregister_cancel();
		menu = 8u;
        break;
      case 'e':
        Cashregister_end();
		menu = 9u;
        break;
      case 's':
        Cashregister_start();
		menu = 10u;
        break;
      case 'r':
        randomShopping();
		menu = 11u;
        break;
      case 'q':
        goodbye();
		menu = 12u;
        break;
      case '\n': /* ignore crlf */
      case '\r': /* ignore crlf */
		menu = 13u;
        break;
        /* For any other character, display the help message */
      default:
        Userinterface_help();
		menu = 14u;
        break;
    }
  }
  return menu;
}

/*
 * Simulates writing a message to the printer
 */
void Userinterface_scan(LDRA_const_char_pt printerMsg)
{
  printf(printerMsg);
  printf("\n");
}

/*
 * Simulates writing a message to the display
 */
void Userinterface_show(LDRA_const_char_pt displayMsg)
{
  printf(displayMsg);
  printf("\n");
}

