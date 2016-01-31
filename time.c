#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
/* Timer count = (required delay/Clock Time Period) - 1
Here we have delay = 200ms and CTP = 625*(10^(-10)) 
So timer count = (16*(10^6)/5) -1
= 3199999
but even with a timer1 that is 16 bit, we can only count to 65535.
So if we use a prescaler of 1024, the clock time period increases by 1024.
now timer count = 3125 -1 = 3124.
*/
ISR (TIMER1_COMPA_vect)
{
    PORTB ^= (1<<5); //Left Shift 6 to make PB5 high
}
int main()
{
    cli(); //disable global interrupt

    OCR1A = 0xC34; //OCR1A is an output compare register. It is constantly compared with a timer, which generates a PWM pulse
    // 0xC34 = 3124
    TIMSK1 |= _BV(OCIE1A); //Set interrupt on compare match
    TCCR1B |= _BV(WGM12); // Mode 4, CTC on OCR1A
    TCCR1B |= (1<<CS12) | (1<<CS10);
    /*We need a prescaler of 1024
    Therefore, CS10 = 1, CS11 = 0 and CS12 = 0*/

    sei(); // enable global interrupt


    DDRB |= (1<<5); // Left Shift 6 to define PIN5 of PortB as output
    
    while(1) 
    {
    
        
    }
    return 0;
}