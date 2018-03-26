#ifndef __SWITCH_H_
#define __SWITCH_H_
#include "INCLUDE.H"

sbit	switch_pin  =  P3^5;

void SWITCH_INIT( void );
void SCAN_SWITCH( void );

#endif