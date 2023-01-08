#include <msp430.h> 


/**
 * main.c
 */

// P1.3 - Interrupt service
#pragma vector = PORT1_VECTOR
__interrupt void Port(void) {
    P1OUT |= BIT7;
    while ((P1IN & BIT3) != BIT3);
    P1OUT &= ~BIT7;
    P1IFG &= ~BIT3; // Delete interrupt flag at P1.3
}



int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	P1DIR |= BIT0 + BIT6 + BIT7; // Set output at Port1
	P1OUT &= ~(BIT6 + BIT7);
	P1OUT |= BIT0;  // Turn on LED1

	P1DIR &= ~BIT3; //Set input Port1
	P1REN |= BIT3;  // Allow resistor
	P1OUT |= BIT3;  // Up to high

    // Setup interrupts
	P1IE |= BIT3; // Allow interrupt at P1.3
	P1IES |= BIT3; // Interrupt with high to low
	P1IFG &= ~BIT3; // Initial interrupt flag

	_BIS_SR(GIE);   // Global interrupt enable

	while (1) {
	    P1OUT |= BIT0;
	    __delay_cycles(1000000); //(16Mhz)
	    P1OUT &= ~BIT0;
	    __delay_cycles(1000000);
	}

	return 0;
}



