/*
 * sct.h
 *
 *  Created on: Oct 14, 2022
 *      Author: NovotnyJ
 */

//Pin definition for sct
//SDI on D5 - PB4
//CLK on D3 - PB3
//LA on D4 - PB5
//OE on D6 - PB10

#include <stdint.h>
#include "main.h"

#ifndef SCT_H_
#define SCT_H_



void sct_init(void);
void sct_led(const uint32_t aVal);
void sct_value(const uint8_t aLed, const uint32_t aVal);


#endif /* SCT_H_ */
