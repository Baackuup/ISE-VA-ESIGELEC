/*
 *    MISRA C:2012 Cash Register project
 * ========================================
 * File Path     : Productdatabase.h
 * Author        : M.W.Richardson
 * Date          : 16/05/13
 * Copyright     : (c) 2013 Liverpool Data Research Associates
 */

#ifndef PRODUCTDATABASE_H
#define PRODUCTDATABASE_H
#include "Misrac_types.h"

#define MAX_PRODUCTS 6U

const struct Product* Productdatabase_getProduct(const LDRA_uint32_t bCode);
struct CountedProduct* Productdatabase_getCountedProduct(
  const struct Product* bProduct);
struct CountedProduct* Productdatabase_getSpecificCountedProduct(
  const LDRA_uint32_t anIndex);
void Productdatabase_resetCountedProducts(void);

#endif
