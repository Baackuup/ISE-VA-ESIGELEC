/*
 *    MISRA C:2012 Cash Register project
 * ========================================
 * File Path     : Cashregister.h
 * Author        : M.W.Richardson
 * Date          : 16/05/13
 * Copyright     : (c) 2013 Liverpool Data Research Associates
 */

#ifndef CASHREGISTER_H
#define CASHREGISTER_H

/*
 * This is the controlling object that receives commands.
 * It sends messages to a display and printer
 * It manages a list of products.
 * It uses the Productdatabase to identify products from a barcode.
 */

void Cashregister_barcode(const LDRA_uint32_t aCode);
void Cashregister_cancel(void);
void Cashregister_code(void);
void Cashregister_start(void);
void Cashregister_end(void);
void Cashregister_key(const LDRA_uint32_t aKey);

#endif
