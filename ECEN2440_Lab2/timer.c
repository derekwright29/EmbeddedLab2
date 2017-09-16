/*
 * timer.c
 *
 *  Created on: Sep 12, 2017
 *      Author: Derek Wright
 */
#include "timer.h"

#ifdef QUESTION_5
void timer_a0_config(){
    TIMER_A0->R = TIMER_A_CTL_CLR; // Reset count

    // SMCLK, Up mode, interrupts enabled, div set to 1,
    TIMER_A0->CCR[0] = 1000;    // Value to count to
    TIMER_A0->CTL = TIMER_A_CTL_SSEL__SMCLK | TIMER_A_CTL_MC__UP | TIMER_A_CTL_IE | TIMER_A_CTL_ID__1;
    TIMER_A0->CTL &= ~TIMER_A_CTL_IFG; // IFG cleared,

    TIMER_A0->CCTL[0] = TIMER_A_CCTLN_CCIE;   // TACCR0 interrupt enabled
    TIMER_A0->CCTL[0] &= ~(TIMER_A_CCTLN_CAP | TIMER_A_CCTLN_CCIFG); // making sure we are in compare mode and flag is cleared


    /* Enable Interrupts in the NVIC */
    NVIC_EnableIRQ(TA0_0_IRQn);
}
//timer interrupt handler
void TA0_0_IRQHandler() {
    if(TIMER_A0->CCTL[0] & TIMER_A_CCTLN_CCIFG) {
        P1->OUT ^= BIT0; // toggle P1.0 LED
        P1->OUT ^= BIT7; // toggle P1.7 pin

        TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG; // clear flag
    }
    if(TIMER_A0->CTL & TIMER_A_CTL_IFG) {
        P1->OUT ^= BIT0; // toggle P1.0 LED
        P1->OUT ^= BIT7; // toggle P1.7 pin

        TIMER_A0->CTL &= ~TIMER_A_CTL_IFG;
    }
    else {
        P1->OUT ^= BIT0; // toggle P1.0 LED
    }
}
#endif
