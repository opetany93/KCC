/*
 * uart.h
 *
 *  Created on: 13 sty 2018
 *      Author: opetany
 */

#ifndef UART_H_
#define UART_H_

#include <stdint.h>

void sendStrig(char* s);
void sendData(uint8_t* data, uint16_t size);
void sendLong(unsigned long long time);
uint16_t ReceiveData(void);


#endif /* UART_H_ */
