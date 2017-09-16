/*
 * port.c
 *
 *  Created on: Sep 12, 2017
 *      Author: admin
 */
#include "port.h"

#if defined(QUESTION_2) || defined(QUESTION_3) || defined(QUESTION_4) || defined(QUESTION_5)
void GPIO_configure(void) {
    P1->SEL0 &= ~(BIT0 | BIT1 | BIT4); // Set pins 1.0, 1.1, 1.4 to GPIO mode
    P1->SEL1 &= ~(BIT0 | BIT1 | BIT4);

    P2->SEL0 &= ~(BIT0 | BIT1 | BIT2); // Set pins 2.0, 2.1, 2.2 to GPIO mode
    P2->SEL1 &= ~(BIT0 | BIT1 | BIT2);

    P1->DIR &= ~(BIT4 | BIT1); // Set pins 1.1, 1.4 to input direction
    P1->DIR |= BIT0; //Set pin 1.0 to output
    P2->DIR |= (BIT0 | BIT1 | BIT2); //Set pins 2.0, 2.1, 2.2 to output

    P1->OUT &= ~(BIT0); //Set pin 1.0 to low
    P2->OUT &= ~(BIT0 | BIT1 | BIT2); //Set pins 2.0, 2.1, 2.2 to low

    P1->REN |= (BIT1 | BIT4); //Enabled pullup/pulldown registers
    P1->OUT |= (BIT1 | BIT4); //Pullup selected
    P1->IFG &= 0; //Clears interrupt flags
    P1->IES |= (BIT1 | BIT4); //Set high to low transition
    P1->IE |= (BIT1 | BIT4); //Enabled interrupts

    /* Enable Interrupts in the NVIC */
    NVIC_EnableIRQ(PORT1_IRQn);
}
#endif

#ifdef QUESTION_2
// Port 1 Interrupt handler function
void PORT1_IRQHandler() {
    int i;

    if (P1->IFG & BIT1) {
        for (i = 0; i < 50000; i++); //delay for de-bouncing
        P1->IFG &= ~BIT1; // clears flag

        P1->OUT ^= BIT0; // Toggles P1.0
    }
    else if (P1->IFG & BIT4) {
        for (i = 0; i < 50000; i++); //delay for de-bouncing
        P1->IFG &= ~BIT4; // clear flag

        P1->OUT ^= BIT0; //Toggles P1.0
    }
}
#endif

#if defined(QUESTION_3) || defined(QUESTION_5)
// Configure the GPIO
void configure_1Pin7() {
    /* Configure Latency Test Output Pin */
    P1->SEL0 &= ~BIT7; // set P1.7 to GPIO
    P1->SEL1 &= ~BIT7;
    P1->DIR |= BIT7; // output
    P1->IE |= BIT7; //enables interrupt

}
#endif

#ifdef QUESTION_3
void PORT1_IRQHandler() {
   if(P1->IFG & BIT7) {
       P1->OUT &= ~BIT7; // set pin back to zero. Test latency.

       P1->IFG &= ~BIT7; // clear flag
   }
}
#endif

#ifdef QUESTION_4
uint8_t state = 0; // global
void PORT1_IRQHandler() {
    //left button handling
    if(P1->IFG & BIT1) {
        P1->IFG &= ~BIT1; //clear flag
        P2->OUT = (P2->OUT + 1) % 8; //increment 3 RGB bits
    }

    //right button handling
    if(P1->IFG & BIT4) {
        P1->IFG &= ~BIT4; //clear flag
        P2->OUT = (P2->OUT + 7) % 8; //decrement 3 RGB bits
    }
}
#endif

