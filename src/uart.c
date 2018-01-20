/*
 * uart.c
 *
 *  Created on: 13 sty 2018
 *      Author: opetany
 */

#include "../inc/uart.h"

#include "system.h"
#include "altera_up_avalon_rs232_regs.h"

static void sendByte(char byte)
{
	IOWR_ALT_UP_RS232_DATA(UART_0_BASE, byte);
}

void sendStrig(char* s)
{
	while(*s)
	{
		while( ALT_UP_RS232_CONTROL_WI_MSK & IORD_ALT_UP_RS232_CONTROL(UART_0_BASE) );
		sendByte(*s++);
	}
}

void sendData(uint8_t* data, uint16_t size)
{
	uint16_t i;

	for(i = 0; i < size; i++)
	{
		sendByte((char)*data++);
	}
}
void sendOneByte(uint8_t data)
{
	sendByte((char) data);

}
void sendLong(unsigned long long time){
	time=time|0x0000010000000000;

	sendOneByte((uint8_t)((time >> 40)&0xFF));
	sendOneByte((uint8_t)((time >> 32)&0xFF));
	sendOneByte((uint8_t)((time >> 24)&0xFF));
	sendOneByte((uint8_t)((time >> 16)&0xFF));
	sendOneByte((uint8_t)((time >> 8)&0xFF));
	sendOneByte((uint8_t)(time&0xFF));

}
