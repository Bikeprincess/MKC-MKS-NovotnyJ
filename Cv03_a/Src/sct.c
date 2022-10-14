#include "sct.h"

void sct_init(void)
{
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;//Clock enable for GPIO
	GPIOB->MODER |= GPIO_MODER_MODER3_0 | GPIO_MODER_MODER4_0 | GPIO_MODER_MODER5_0 | GPIO_MODER_MODER10_0;//Output conf
	GPIOB->BRR = SCT_PIN_CLK | SCT_PIN_SDI | SCT_PIN_LA | SCT_PIN_OE;
	return;
}

void sct_led(const uint32_t aVal)
{
	uint32_t iVal = aVal;
	for (volatile uint32_t i = 0; i < 32; i++)
	{
		sct_sdi(iVal & 0x01);
		sct_scl(1);
		iVal <<= 1;
		sct_scl(0);
	}
	cst_nla(1);
	cst_nla(0);
	return;
}
