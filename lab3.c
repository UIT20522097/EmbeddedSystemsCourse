#include <msp430.h> 
#include "UART\uart.h"
#include "MSP430G553_Configure\configure.h"

unsigned char data[] = {""};
unsigned int i = 0;
unsigned int lenght = 0;

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	configure_Clock();
	configure_IO();
	configure_UART();

	while(1) {

	}

	return 0;
}

// TX - Interrupt service
#pragma vector = USCIAB0TX_VECTOR
__interrupt void USCI0TX_ISR() {
    P1OUT |= BIT0;
    if (i < lenght && i != 0) UCA0TXBUF = data[i++];
    else UC0IE &= ~UCA0TXIE; // Disable USCI_A0 TX interrupt
    P1OUT &= ~BIT0;
}

// RX - Interrupt service
#pragma vector = USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR() {
    UC0IE &= ~UCA0TXIE; // Disable USCI_A0 TX interrupt
    P1OUT |= BIT6;
    data[lenght++] = UCA0RXBUF;
    UC0IE |= UCA0TXIE; // Enable USCI_A0 TX interrupt
    P1OUT &= ~BIT6;
    UCA0TXBUF = data[i++]; // TX next character
}