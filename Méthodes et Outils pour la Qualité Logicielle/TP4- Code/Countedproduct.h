/*
 *    MISRA C:2012 Cash Register project
 * ========================================
 * File Path     : Countedproduct.h
 * Author        : M.W.Richardson
 * Date          : 16/05/13
 * Copyright     : (c) 2013 Liverpool Data Research Associates
 */

#ifndef COUNTEDPRODUCT_H
#define COUNTEDPRODUCT_H

#include "Misrac_types.h"
#include "Product.h"

struct CountedProduct
{
  const struct Product* itsProduct;
  LDRA_uint32_t count;
};

#endif
