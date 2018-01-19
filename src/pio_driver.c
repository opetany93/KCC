/*
 * pio_driver.c
 *
 *  Created on: 14 maj 2016
 *      Author: opetany
 */

#include "../inc/pio_driver.h"
#include "altera_avalon_pio_regs.h"
#include "system.h"

// ==================================================================================
void PIO_Write(int port, int value)
{
	IOWR_ALTERA_AVALON_PIO_DATA(port, value);
}

// ==================================================================================
int  PIO_Read(int port)
{
	return IORD_ALTERA_AVALON_PIO_DATA(port);
}

// ==================================================================================
int PIO_ReadBit(int port, int pin)
{
	return IORD_ALTERA_AVALON_PIO_DATA(port) & pin;
}

// ==================================================================================
void PIO_SetBit(int port, int value)
{
	IOWR_ALTERA_AVALON_PIO_SET_BITS(port, value);
}

// ==================================================================================
void PIO_ClearBit(int port, int value)
{
	IOWR_ALTERA_AVALON_PIO_CLEAR_BITS(port, value);
}

// ==================================================================================
void PIO_Direction(int port, int value)
{
	IOWR_ALTERA_AVALON_PIO_DIRECTION(port, value);
}
