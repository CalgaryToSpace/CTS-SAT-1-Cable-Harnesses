#include <avr/io.h>

int main(void) {
    
    // Enable global interrupts.
    SREG = 0b10000000;
    
    // Set the ADC reference level to VDD.
    VREF.ADC0REF = 0b10000101;
    
    // Enable the ADC interrupt.
    ADC0.INTCTRL = 0b00000001;
    
    // Select PD2 (AIN2) as the ADC input.
    ADC0.MUXPOS = 0x02;

    // Select minimum clock divide.
    ADC0.CTRLC = 0x00;
    
    // Select single ended mode, 12 bit resolution and free-running modes.
    ADC0.CTRLA = 0b00000011;
    
    // Start conversion.
    ADC0.COMMAND = 0x01;
    
    // Set PA0, PA1, and PA2 as outputs for LEDs.
    PORTA.DIRSET = 0b00000111;

 
    while (1) 
    {
        // Check if ADC conversion is complete
        if (ADC0.INTFLAGS & 0b00000001) 
        {
            // Read the ADC result.
            int adc_value = ADC0.RES;

            // Clear the ADC interrupt flag.
            ADC0.INTFLAGS = 0b00000001;

            // Check voltage thresholds and update LEDs
            if (adc_value > 2665) 
            {
                PORTA.OUT = 0b00000100; // LED 3 (PA2) is on
            } 
            else if (adc_value > 1843) 
            {
                PORTA.OUT = 0b00000010; // LED 2 (PA1) is on
            } 
            else if (adc_value > 1023) 
            {
                PORTA.OUT = 0b00000001; // LED 1 (PA0) is on
            } 
            else 
            {
                PORTA.OUT = 0b00000000; // All LEDs are off
            }
        }
    }
}

