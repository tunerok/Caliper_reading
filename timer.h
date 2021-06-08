#ifndef TIMER_H_
#define TIMER_H_

#include "MDR32F9Qx_timer.h"
#include "MDR32Fx.h"                    // Device header

#define ROUTE_TIME 10 // even 

extern volatile uint8_t recive_timeout;

void ini_timer(void);
void TIMER1_IRQHandler( void  );
void start_timing(void);
void stop_timing(void);

#endif
