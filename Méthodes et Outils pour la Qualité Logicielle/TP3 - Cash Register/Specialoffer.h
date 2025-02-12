/*
 *    MISRA C:2012 Cash Register project
 * ========================================
 * File Path     : Specialoffer.h
 * Author        : M.W.Richardson
 * Date          : 16/05/13
 * Copyright     : (c) 2013 Liverpool Data Research Associates
 */

#ifndef SPECIALOFFER_H
#define SPECIALOFFER_H

#include "Misrac_types.h"


/* Various types of Special Offers available */
typedef enum {
   NO_OFFER, BUY_ONE_GET_ONE_FREE, TEN_PERCENT_OFF, THREE_FOR_ONE_EURO
} tSpecialoffer;

LDRA_uint32_t Specialoffer_getPrice(const LDRA_uint32_t aQuantity,
      const LDRA_uint32_t aUnitPrice, const tSpecialoffer anOffer,
	  LDRA_char_pt aProduct);

#endif
