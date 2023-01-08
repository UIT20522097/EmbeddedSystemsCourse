#include <msp430.h>
#include "adc.h"

void configure_ADC() {
    ADC10CTL1 - INCH_5 | ADC10SSEL_0;

    ADC10AE0 = BIT5;

    ADC10CTL0 = SREF_0;

    ADC10CTL0 |= ADC10ON + ENC;
}

unsigned int GetADCValue() {
    ADC10CTL0 |= ADC10SC;

    while (ADC10CTL1 & 1);

    return ADC10MEM;
}
