/*
 *    MISRA C:2012 Cash Register project
 * ========================================
 * File Path     : Specialoffer.c
 * Author        : M.W.Richardson
 * Date          : 16/05/13
 * Copyright     : (c) 2013 Liverpool Data Research Associates
 */

#include <string.h>
#include "Misrac_types.h"
#include "Specialoffer.h"

/*
 * Get the price which depends on which special offer, if any, is used
 */
LDRA_uint32_t Specialoffer_getPrice(const LDRA_uint32_t aQuantity,
    const LDRA_uint32_t aUnitPrice, const tSpecialoffer anOffer, LDRA_char_pt aProduct)
{
  LDRA_uint32_t price;
  switch (anOffer)
  {
    case BUY_ONE_GET_ONE_FREE:
	  if(!strcmp(aProduct, "Coconuts")){
        price = aUnitPrice * (aQuantity >> 1U);
	  }
      break;
    case TEN_PERCENT_OFF:
      price = (aUnitPrice * aQuantity * 9U) / 10U;
      break;
    case THREE_FOR_ONE_EURO:
      price = ((aQuantity / 3U) * 100U) + ((aQuantity % 3U) * aUnitPrice);
      break;
      /* no offer */
    default:
      price = aUnitPrice * aQuantity;
      break;
  }
  return price;
}

