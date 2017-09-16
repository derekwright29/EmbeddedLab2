#include "port.h"
#include "timer.h"


void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    #if defined(QUESTION_2) || defined(QUESTION_3) || defined(QUESTION_4) || defined(QUESTION_5)
    //<CONFIGURE_PORTS>
    GPIO_configure();
    // Configure debug pin 1.7
    configure_1Pin7();
    //P1->OUT |= BIT7; // set debug pin high
    #endif





    #ifdef QUESTION_5
    //<CONFIGURE_TIMER>
    timer_a0_config();
    #endif

     __enable_irq(); //Global enable interrupts

    #ifdef QUESTION_3
    P1->IFG |= BIT7; //manually trigger port 1 interrupt
    #endif
    while (1);

}



