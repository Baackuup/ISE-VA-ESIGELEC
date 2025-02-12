/*
 *    MISRA C:2012 Cash Register project
 * ========================================
 * File Path     : Userinterface.h
 * Author        : M.W.Richardson
 * Date          : 16/05/13
 * Copyright     : (c) 2013 Liverpool Data Research Associates
 */

#ifndef Userinterface_H
#define Userinterface_H

#include "Misrac_types.h"

/*
 * This is the file that can be easily replaced
 * by a different implementation of the printer, display
 * keyboard and barcode reader.
 */

void Userinterface_help(void);
LDRA_uint32_t Userinterface_parse(const LDRA_char_t aChar);
void Userinterface_show(LDRA_const_char_pt displayMsg);
void Userinterface_scan(LDRA_const_char_pt printerMsg);

#endif
