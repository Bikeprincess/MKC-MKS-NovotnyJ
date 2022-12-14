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

static const uint32_t gLedRegValues[9] = {
		0b00000000 << 20,
		0b00010000 << 20,
		0b00110000 << 20,
		0b01110000 << 20,
		0b11110000 << 20,
		0b11111000 << 20,
		0b11111100 << 20,
		0b11111110 << 20,
		0b11111111 << 20,
};

void sct_init(void)
{
	sct_led(0);
	return;
}

void sct_led(const uint32_t aVal)
{
	uint32_t iVal = aVal;
	for (volatile uint32_t i = 0; i < 32; i++)
	{
		HAL_GPIO_WritePin(SCT_SDI_GPIO_Port, SCT_SDI_Pin, iVal & 0x01);
		HAL_GPIO_WritePin(SCT_CLK_GPIO_Port, SCT_CLK_Pin,1);
		iVal >>= 1;
		HAL_GPIO_WritePin(SCT_CLK_GPIO_Port, SCT_CLK_Pin,0);
	}
	HAL_GPIO_WritePin(SCT_NLA_GPIO_Port, SCT_SDI_Pin,1);
	HAL_GPIO_WritePin(SCT_NLA_GPIO_Port, SCT_SDI_Pin,0);
	return;
}

void sct_value(const uint8_t aLed, const uint32_t aVal)
{
	uint32_t iVal = aVal;
	//while (iVal > 999) iVal /= 10;//check the input number for max value 999 and do div by 10 to number <= 999
	uint32_t iLedConst = gDisplayRegValues[1][(iVal/100)%10] | gDisplayRegValues[1][(iVal/10)%10] | gDisplayRegValues[1][iVal%10];
	iLedConst |= gLedRegValues[(aLed >= 9)?8:aLed];
	sct_led(iLedConst);
	return;
}
