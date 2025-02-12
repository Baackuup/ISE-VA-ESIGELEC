/*
 *    MISRA C:2012 Cash Register project
 * ========================================
 * File Path     : Misrac_types.h
 * Author        : M.W.Richardson
 * Date          : 16/05/13
 * Copyright     : (c) 2013 Liverpool Data Research Associates
 */

#ifndef MISRAC_TYPES_H
#define MISRAC_TYPES_H

/*
 * MISRA C 2012 Types for a 32 bit machine
 */

/* plain 8 bit character */
typedef char LDRA_char_t;

/* pointer to plain 8 bit character */
typedef char* LDRA_char_pt;

/* pointer to const plain 8 bit character */
typedef const char* LDRA_const_char_pt;

/* signed 8 bit integer */
/* min = -128 */
/* max = 127 */
typedef signed char LDRA_int8_t;

/* signed 16 bit integer */
/* min = -32768 */
/* max = 32767 */
typedef signed short LDRA_int16_t;

/* signed 32 bit integer */
/* min = -2147483648 */
/* max = 2147483647 */
typedef signed int LDRA_int32_t;

/* signed 64 bit integer */
typedef signed long LDRA_int64_t;

/* unsigned 8 bit integer */
/* min = 0U */
/* max = 255U */
typedef unsigned char LDRA_uint8_t;

/* unsigned 16 bit integer */
/* min = 0U */
/* max = 65535U */
typedef unsigned short LDRA_uint16_t;

/* unsigned 32 bit integer */
/* min = 0U */
/* max = 4294967295U */
typedef unsigned int LDRA_uint32_t;

/* unsigned 64 bit integer */
typedef unsigned long LDRA_uint64_t;

/* 32 bit floating point */
typedef float LDRA_float32_t;

/* 64 bit floating point */
typedef double LDRA_float64_t;

/* 128 bit floating point */
typedef long double LDRA_float128_t;

#endif
