/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    iwdg.c
  * @brief   This file provides code for the configuration
  *          of the IWDG instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "iwdg.h"

IWDG_HandleTypeDef hiwdg;

/* Reload formula

RL =	time(ms) * 40000	- 1
		4 * (PR) * 1000

f =		40000
		(nclks*PR)

time(ms) = 	1 * RL * PRESCALE * 1000
				40000

RL = 	time (ms) * 40000
		1 * PRESCALE * 1000


RL: 12 bit value = max of 4095
*/

/* IWDG init function */
void iwdg_init(void)
{
	hiwdg.Instance = IWDG;
	hiwdg.Init.Prescaler = IWDG_PRESCALER_16;
	hiwdg.Init.Reload = 2550;

	int time_value = hiwdg.Init.Reload*16*1000/40000;
	if (HAL_IWDG_Init(&hiwdg) != HAL_OK)
	{
		// Error_Handler();
		printf("IWDG init error\n");
	}
	else {
		printf("IWDG initialized ok with t= %d ms!\n", time_value);
	}


	// uint16_t RL_reg = (IWDG->RLR & 0x0FFF);
	// printf("RL_reg: %u\n", RL_reg);

	// IWDG->RLR = 505;
	// RL_reg = (IWDG->RLR & 0x0FFF);
	// printf("RL_reg: %u\n", RL_reg);
}
void iwdg_refresh(void) {
	HAL_IWDG_Refresh(&hiwdg);
}
