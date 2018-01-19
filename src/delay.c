/*
 * delay.c
 *
 *  Created on: 13 sty 2018
 *      Author: opetany
 */

#include "../inc/delay.h"
#include "system.h"
#include "altera_avalon_timer_regs.h"

void delayMs(uint32_t ms)
{
	uint32_t cnt = 0;

	// activate the time
   IOWR_ALTERA_AVALON_TIMER_CONTROL(SYS_TIMER_BASE,
				   ALTERA_AVALON_TIMER_CONTROL_CONT_MSK
				 | ALTERA_AVALON_TIMER_CONTROL_START_MSK);

   while(cnt < ms)
   {
	   while( !(ALTERA_AVALON_TIMER_STATUS_TO_MSK & IORD_ALTERA_AVALON_TIMER_STATUS(SYS_TIMER_BASE)) );
	   IOWR_ALTERA_AVALON_TIMER_STATUS(SYS_TIMER_BASE, 0);
	   cnt++;
   }

   IOWR_ALTERA_AVALON_TIMER_CONTROL(SYS_TIMER_BASE,
   				   ALTERA_AVALON_TIMER_CONTROL_CONT_MSK
   				 | ALTERA_AVALON_TIMER_CONTROL_STOP_MSK);
}

