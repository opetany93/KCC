/* 
 * "Small Hello World" example. 
 * 
 * This example prints 'Hello from Nios II' to the STDOUT stream. It runs on
 * the Nios II 'standard', 'full_featured', 'fast', and 'low_cost' example 
 * designs. It requires a STDOUT  device in your system's hardware. 
 *
 * The purpose of this example is to demonstrate the smallest possible Hello 
 * World application, using the Nios II HAL library.  The memory footprint
 * of this hosted application is ~332 bytes by default using the standard 
 * reference design.  For a more fully featured Hello World application
 * example, see the example titled "Hello World".
 *
 * The memory footprint of this example has been reduced by making the
 * following changes to the normal "Hello World" example.
 * Check in the Nios II Software Developers Manual for a more complete 
 * description.
 * 
 * In the SW Application project (small_hello_world):
 *
 *  - In the C/C++ Build page
 * 
 *    - Set the Optimization Level to -Os
 * 
 * In System Library project (small_hello_world_syslib):
 *  - In the C/C++ Build page
 * 
 *    - Set the Optimization Level to -Os
 * 
 *    - Define the preprocessor option ALT_NO_INSTRUCTION_EMULATION 
 *      This removes software exception handling, which means that you cannot 
 *      run code compiled for Nios II cpu with a hardware multiplier on a core 
 *      without a the multiply unit. Check the Nios II Software Developers 
 *      Manual for more details.
 *
 *  - In the System Library page:
 *    - Set Periodic system timer and Timestamp timer to none
 *      This prevents the automatic inclusion of the timer driver.
 *
 *    - Set Max file descriptors to 4
 *      This reduces the size of the file handle pool.
 *
 *    - Check Main function does not exit
 *    - Uncheck Clean exit (flush buffers)
 *      This removes the unneeded call to exit when main returns, since it
 *      won't.
 *
 *    - Check Don't use C++
 *      This builds without the C++ support code.
 *
 *    - Check Small C library
 *      This uses a reduced functionality C library, which lacks  
 *      support for buffering, file IO, floating point and getch(), etc. 
 *      Check the Nios II Software Developers Manual for a complete list.
 *
 *    - Check Reduced device drivers
 *      This uses reduced functionality drivers if they're available. For the
 *      standard design this means you get polled UART and JTAG UART drivers,
 *      no support for the LCD driver and you lose the ability to program 
 *      CFI compliant flash devices.
 *
 *    - Check Access device drivers directly
 *      This bypasses the device file system to access device drivers directly.
 *      This eliminates the space required for the device file system services.
 *      It also provides a HAL version of libc services that access the drivers
 *      directly, further reducing space. Only a limited number of libc
 *      functions are available in this configuration.
 *
 *    - Use ALT versions of stdio routines:
 *
 *           Function                  Description
 *        ===============  =====================================
 *        alt_printf       Only supports %s, %x, and %c ( < 1 Kbyte)
 *        alt_putstr       Smaller overhead than puts with direct drivers
 *                         Note this function doesn't add a newline.
 *        alt_putchar      Smaller overhead than putchar with direct drivers
 *        alt_getchar      Smaller overhead than getchar with direct drivers
 *
 */

#include "sys/alt_stdio.h"
#include "sys/alt_irq.h"
#include <stdint.h>
#include <stdio.h>

#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "altera_up_avalon_rs232_regs.h"
#include "altera_up_avalon_rs232.h"

#include "../inc/pio_driver.h"
#include "../inc/delay.h"
#include "../inc/uart.h"

// MACROS
#define TRIGGER PIN_0
#define RESET 	PIN_1
#define CONV_END PIN_2

// VARIABLES
char buff[30];
uint8_t receivedData;
volatile uint8_t flag = 0;
volatile uint32_t set;

// UART VARIABLES
volatile uint32_t uart_context;		/* Kontekst do przerwañ z uartu */
void* uart_ptr = (void*) &uart_context;

//UART INTERRUPT FUNCTION
void handle_uart_interrupt(void* p, alt_u32 param)
{
	volatile uint32_t uart_ptr = (volatile uint32_t*) p;//pobierz kontekst

	sendStrig("Przerwanie\r\n");

	receivedData = ReceiveData();
	flag = 0x01;
}


int main()
{ 
	unsigned long long time;

	alt_putstr("KCC Project!\n");

	//SET PIO
	PIO_Direction(PIO_0_BASE , 0x0F);

	alt_irq_register(UART_0_IRQ, uart_ptr, handle_uart_interrupt);

   // SET IRQ ON
   set = IORD_ALT_UP_RS232_CONTROL(UART_0_BASE);
   set |= 0x01;
   IOWR_ALT_UP_RS232_CONTROL(UART_0_BASE, set);


   delayMs(10);

   sendStrig("KCC PROJ\r\n");

  while (1)
  {

	if(flag){
		//CLEAR FLAG
		flag = 0x0;

		//RECEIVE DATA

		sendStrig("Cos odebrano\r\n");

		if(receivedData == 0x66){  //START CONDITION

			sendStrig("Rozpoczynam Pomiar\r\n");

			PIO_SetBit(PIO_0_BASE , RESET);			// RESET COUNTERS
			delayMs(2);
			PIO_ClearBit(PIO_0_BASE , RESET);
			delayMs(2);

			PIO_SetBit(PIO_0_BASE , TRIGGER);			// SET TRIGER
			delayMs(55);
			PIO_ClearBit(PIO_0_BASE , TRIGGER);

			delayMs(55);
			while(!PIO_ReadBit(PIO_0_BASE, CONV_END));		// WHAIT FOR END OF MEASURE

			time =  (PIO_Read(CONV_MSB_BASE) << 4) | PIO_Read(CONV_LSB_BASE);

			sendLong(time);							//SEND MEASURMENT
		}
	}

  }

  return 0;
}
