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
#include "stm32f0xx.h"

#ifndef SCT_H_
#define SCT_H_

#define SCT_PIN_CLK		(1<<3)
#define SCT_PIN_SDI		(1<<4)
#define SCT_PIN_LA		(1<<5)
#define SCT_PIN_OE		(1<<10)

#define sct_clk(x) do { if (x) GPIOB->BSSR = SCT_PIN_CLK;else GPIOB->BRR = SCT_PIN_CLK;} while (0)
#define sct_sdi(x) do { if (x) GPIOB->BSSR = SCT_PIN_SDI;else GPIOB->BRR = SCT_PIN_SDI;} while (0)
#define sct_nla(x) do { if (x) GPIOB->BSSR = SCT_PIN_LA;else GPIOB->BRR = SCT_PIN_LA;} while (0)
#define sct_noe(x) do { if (x) GPIOB->BSSR = SCT_PIN_OE;else GPIOB->BRR = SCT_PIN_OE;} while (0)

void sct_init(void);
void sct_led(const uint32_t aVal);


#endif /* SCT_H_ */
