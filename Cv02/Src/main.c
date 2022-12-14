/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include <stdbool.h>
#include "stm32f0xx.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

void blikac(void);
void tlacitka(void);

#define LED_TIME_BLINK	300
#define LED_TIME_SHORT	100
#define LED_TIME_LONG	1000
#define BUTTON_DELAY_TIME	5
//LED1 = PA4
//LED2 = PB0
//SW1 = PC1
//SW2 = PC0

//Led dev board - PA5
//SW dev board - PC13

volatile uint32_t Tick = 0;
//volatile bool WakeUpButton = false;

int main(void)
{
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOBEN | RCC_AHBENR_GPIOCEN;//Clock enable for GPIO
	GPIOA->MODER |= GPIO_MODER_MODER5_0 | GPIO_MODER_MODER4_0;//Output conf
	GPIOB->MODER |= GPIO_MODER_MODER0_0;//Output conf
	GPIOC->PUPDR |= GPIO_PUPDR_PUPDR0_0 | GPIO_PUPDR_PUPDR1_0 | GPIO_PUPDR_PUPDR13_0;//enable pull up
	// turn off led at start
	GPIOA->BRR = (1<<5) | (1<<4);
	GPIOB->BRR = (1<<0);
	//INT
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;//Povolení hodin
	//From HW
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PC; // select PC0 for EXTI0
	SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI13_PC; // select PC13 for EXTI13
	EXTI->IMR |= EXTI_IMR_MR0 | EXTI_IMR_MR13; // mask
	EXTI->FTSR |= EXTI_FTSR_TR0 | EXTI_FTSR_TR13; // trigger on falling edge
	//NVIC_EnableIRQ(EXTI0_1_IRQn); // enable EXTI0_1
	//NVIC_EnableIRQ(EXTI4_15_IRQn); // enable EXTI4_15 - for dev board

	//SysTicks
	SysTick_Config(8000);//1 ms tick


    /* Loop forever */
	for(;;)
	{
		//GPIOA->ODR ^= (1<<5); // toggle
		//for (volatile uint32_t i = 0; i < 100000; i++) {}
		blikac();
		tlacitka();
	}
}

/*
void EXTI4_15_IRQHandler(void)
{
	if (EXTI->PR & EXTI_PR_PR13) { // check line 0 has triggered the IT
		EXTI->PR |= EXTI_PR_PR13; // clear the pending bit
		GPIOA->ODR ^= (1<<5); // toggle led on dev board
	}
}

void EXTI0_1_IRQHandler(void)
{
	if (EXTI->PR & EXTI_PR_PR0) { // check line 0 has triggered the IT
		EXTI->PR |= EXTI_PR_PR0; // clear the pending bit
		GPIOB->ODR ^= (1<<0);//Toggle led
	}
}*/

void SysTick_Handler(void)
{
	Tick++;
}

void blikac(void)
{
	static uint32_t delay = 0;
	if (Tick > (delay + LED_TIME_BLINK))
	{
		delay = Tick;
		GPIOA->ODR ^= (1<<4); // toggle led on shield
		//GPIOA->ODR ^= (1<<5); // toggle led on dev board
	}
}

void tlacitka(void)
{
	//Button check and turn on leds
	static uint32_t delay = 0;
	static uint32_t TurnOffLedTime = 0;
	uint32_t new_IDR = GPIOC->IDR;
	static uint16_t debounce_SW1 = 0xFFFF, debounce_SW2 = 0xFFFF;
	if (Tick > (delay + BUTTON_DELAY_TIME))
	{
		delay = Tick;
		debounce_SW1 <<= 1;
		debounce_SW2 <<= 1;
		if (!(~new_IDR & (((1<<0) | (1<<13)))))//PC0 as short time - SW2
			debounce_SW2 |= 0x00001;
		if (!(~new_IDR & (((1<<1) | (1<<13)))))//PC1 as long time
			debounce_SW1 |= 0x00001;

		//Turn on led
		if (debounce_SW1 == 0x7FFF)
		{
			TurnOffLedTime = Tick + LED_TIME_LONG;
			GPIOB->BSRR = (1<<0);
		}
		if (debounce_SW2 == 0x7FFF)
		{
			TurnOffLedTime = Tick + LED_TIME_SHORT;
			GPIOB->BSRR = (1<<0);
			GPIOA->BSRR = (1<<5);//For develop
		}
	}

	//Turning off the leds
	if (Tick > TurnOffLedTime)
	{
		GPIOB->BRR = (1<<0);
		GPIOA->BRR = (1<<5);//for develop
	}
}



