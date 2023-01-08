#include <msp430.h>
#include "MSP430G553_Configure\configure.h"
#include "UART\uart.h"
#include "ADC\adc.h"

const unsigned int maxRes = 10000;
unsigned long ADCValue, ResValue;

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    configure_Clock();
    configure_ADC();
    configure_UART();

    while (1) {
        ADCValue = GetADCValue();
        ResValue = (ADCValue * maxRes) / 1023;
        UART_SendNumber(ResValue);
    }


    return 0;
}
