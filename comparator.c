#include <avr/io.h>

int main(void) 
{
    // Set PA0, PA1, PA2 as output pins for LED's
    PORTA.DIRSET = 0b00000111; 
    
    // Initialize the the LED's to be off at the start
    PORTA.OUT = 0b00000000;
    
     // Enable global interrupts.
    SREG = 0b10000000;
    
    AC0.CTRLA = 0b00000111;

    AC0.MUXCTRL = 0b00000011;
    
    VREF.ACREF = 0b00000101;
    
    AC0.INTCTRL = 0b00000001;
    
    AC0.DACREF = 0b10011001;
    
    // Variable to track state transitions
    int crossed = 0;
    
    while (1) 
    {
        // Check if the comparator has detected a crossing event
        switch ((AC0.STATUS & 0b10011001) ? 1 : 0)
        {
            // If the input voltage crosses the threshold
            case 1:
                if (crossed == 0)
                {
                    PORTA.OUT = 0b00000111; // Turn the LED's on
                    crossed = 1; // Mark that the threshold has been crossed
                }
                break;
            // If the voltage is below the threshold
            case 0:
                PORTA.OUT = 0b00000000; // Turn the LED's off
                crossed = 0; // reset crossed to 0
                break;
        }
        AC0.STATUS = 0b00000001; // Clear interrupt flag
    }
}
