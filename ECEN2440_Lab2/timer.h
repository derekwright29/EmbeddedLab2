/*
 * timer.h
 *
 *  Created on: Sep 12, 2017
 *      Author: admin
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "msp.h"
#include <stdint.h>

#define QUESTION_5

#ifdef QUESTION_5
//Configure timer registers
void timer_a0_config();

//timer interrupt handler
void TA0_0_IRQHandler();
#endif

#endif /* TIMER_H_ */
