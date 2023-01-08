#include <msp430.h>
#include "configure.h"

void configure_Clock(){
    if (CALBC1_8MHZ == 0xFF){
        while(1);
    }

    // DCO is 8MHz
    DCOCTL = 0;
    BCSCTL1 = CALBC1_8MHZ;
    DCOCTL = CALDCO_8MHZ;

    BCSCTL2 |= SELM_0;  // Select MCLK CPU is DCO

}

void configure_IO()    {
    // Setup output off led P1.0
    P1DIR |= BIT0;
    P1OUT &= ~BIT0;

    // Setup button in P1.3
    P1DIR &= ~BIT3; //Set input Port1
    P1REN |= BIT3;  // Allow resistor
    P1OUT |= BIT3;  // Up to high
}

void configure_buttonP1_3() {

    // Setup P1.3 interrupts
    P1IE |= BIT3; // Allow interrupt at P1.3
    P1IES |= BIT3; // Interrupt with high to low
    P1IFG &= ~BIT3; // Initial interrupt flag
}