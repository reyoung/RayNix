//! Defines Multi-type ints, make sure developers can get fix sized int.
//! 定义多种类型的int，让开发者可以获得固定长度的int

#ifndef STDINT_H_INCLUDED
#define STDINT_H_INCLUDED

typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef signed short int int16_t;
typedef unsigned short int uint16_t;
typedef signed int int32_t;
typedef unsigned int uint32_t;
#ifdef i386
typedef signed long long int int64_t;
typedef unsigned long long int uint64_t;
typedef int                     intptr_t; 
typedef unsigned int            uintptr_t; 
#else
typedef signed long int int64_t;
typedef unsigned long int uint64_t;
typedef long                    intptr_t;
typedef unsigned long           uintptr_t; 
#endif

#endif