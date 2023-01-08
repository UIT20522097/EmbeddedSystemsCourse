#include<msp430.h>
#include "uart.h"


void configure_UART()   {
    P1SEL = BIT1 + BIT2;    // P1.1 = RXD, P1.2 = TXD
    P1SEL2 = BIT1 + BIT2;   // P1.1 = RXD, P1.2 = TXD
    UCA0CTL1 |= UCSWRST;    // USCI state - Setup configure

    UCA0CTL0 = 0x00;    // No Parity Bit, 8 bit data, 1 bit stop, Low bit first out

    UCA0CTL1 = UCSSEL_2 | UCSWRST; // Select Clock UART (SMCLK) is DCO 8Mhz

    UCA0MCTL = UCBRF_1 | UCBRS_0 | UCOS16;

    // 8MHz 9600
    UCA0BR0 = 52;
    UCA0BR1 = 00;

    UCA0CTL1 &= ~UCSWRST;   // Release module USCI state

    IE2 |= UCA0RXIE;    // Rx UART interrupt

    _BIS_SR(GIE);   // Enable interrupt service routine
}

void UART_SendByte (unsigned char byte) {
    while(!(IFG2 & UCA0TXIFG)); // waiting buffer register to available
    UCA0TXBUF = byte;
}

void UART_SendNumber(unsigned long number) {
    unsigned char i = 0;
    unsigned char temp[10];
    unsigned char lenght = 0;

    if (number == 0) {
        UART_SendByte('0');
        return;
    }

    while (number != 0) {
        temp[i++] = number % 10;
        number /= 10;
    }

    lenght = i;

    for (i = 0; i < lenght; i++) {
        UART_SendByte(temp[lenght - i - 1] + '0');
    }
}