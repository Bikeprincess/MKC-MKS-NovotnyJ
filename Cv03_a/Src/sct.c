#include "sct.h"

static const uint32_t gDisplayRegValues[3][10] = {
{
//PCDE--------GFAB @ DIS1
0b0111000000000111 << 16,
0b0100000000000001 << 16,
0b0011000000001011 << 16,
0b0110000000001011 << 16,
0b0100000000001101 << 16,
0b0110000000001110 << 16,
0b0111000000001110 << 16,
0b0100000000000011 << 16,
0b0111000000001111 << 16,
0b0110000000001111 << 16,
},
{
//----PCDEGFAB---- @ DIS2
0b0000011101110000 << 0,
0b0000010000010000 << 0,
0b0000001110110000 << 0,
0b0000011010110000 << 0,
0b0000010011010000 << 0,
0b0000011011100000 << 0,
0b0000011111100000 << 0,
0b0000010000110000 << 0,
0b0000011111110000 << 0,
0b0000011011110000 << 0,
},
{
//PCDE--------GFAB @ DIS3
0b0111000000000111 << 0,
0b0100000000000001 << 0,
0b0011000000001011 << 0,
0b0110000000001011 << 0,
0b0100000000001101 << 0,
0b0110000000001110 << 0,
0b0111000000001110 << 0,
0b0100000000000011 << 0,
0b0111000000001111 << 0,
0b0110000000001111 << 0,
},
};

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
		sct_clk(1);
		iVal >>= 1;
		sct_clk(0);
	}
	sct_nla(1);
	sct_nla(0);
	return;
}

void sct_value(const uint32_t aVal)
{
	uint32_t iVal = aVal;
	//while (iVal > 999) iVal /= 10;//check the input number for max value 999 and do div by 10 to number <= 999
	uint32_t iLedConst = gDisplayRegValues[1][(iVal/100)%10] | gDisplayRegValues[1][(iVal/10)%10] | gDisplayRegValues[1][iVal%10];
	sct_led(iLedConst);
	return;
}
