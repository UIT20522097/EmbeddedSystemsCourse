#ifndef UART_H
#define UART_H

#include <msp430.h>

void configure_UART();
void UART_SendByte(unsigned char byte);
void UART_SendNumber(unsigned long number);

#endif
