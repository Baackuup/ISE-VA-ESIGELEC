/*
 *    MISRA C:2012 Cash Register project
 * ========================================
 * File Path     : Product.h
 * Author        : M.W.Richardson
 * Date          : 16/05/13
 * Copyright     : (c) 2013 Liverpool Data Research Associates
 */

#ifndef PRODUCT_H
#define PRODUCT_H

#include "Specialoffer.h"
#include "Misrac_types.h"

struct Product
{
  LDRA_char_pt name;
  LDRA_uint32_t barcode;
  LDRA_uint32_t unitPrice;
  tSpecialoffer specialOffer;
};

#endif
