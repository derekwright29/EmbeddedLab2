/*
 * port.h
 *
 *  Created on: Sep 12, 2017
 *      Author: Derek Wright
 */

#ifndef PORT_H_
#define PORT_H_
#include "msp.h"
#include <stdint.h>

#define QUESTION_5

#if defined(QUESTION_2) || defined(QUESTION_3) || defined(QUESTION_4) || defined(QUESTION_5)
//configures RGB LED, the two buttons, and P1.0 LED for questions 2-4, etc.
void GPIO_configure(void);
#endif

#if defined(QUESTION_3) || defined(QUESTION_5)
//Configures Pin 1.7 for o-scope latency testing.
void configure_1Pin7(void);
#endif

//Port1 Interrupt handler
#if defined(QUESTION_2) || defined(QUESTION_3) || defined(QUESTION_4)
// Port 1 Interrupt handler function
void PORT1_IRQHandler();
#endif

#endif /* PORT_H_ */
