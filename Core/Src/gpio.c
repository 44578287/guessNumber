/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, Key_R0_Pin|Key_R1_Pin|Key_R2_Pin|Key_R3_Pin
                          |LedM_R3_Pin|BFOE_2_Pin|BFOE_1_Pin|LedM_R4_Pin
                          |LedM_R14_Pin|LedM_R15_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LedM_R1_Pin|LedM_R2_Pin|LedM_R5_Pin|LedM_R6_Pin
                          |LedM_R7_Pin|LedM_R8_Pin|LedM_R9_Pin|LedM_R10_Pin
                          |LedM_R11_Pin|LedM_R12_Pin|LedM_R13_Pin|LedM_R16_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LedM_C1_Pin|LedM_C2_Pin|LedM_C3_Pin|LedM_C11_Pin
                          |LedM_C12_Pin|LedM_C13_Pin|LedM_C14_Pin|LedM_C15_Pin
                          |LedM_C16_Pin|LedM_C5_Pin|LedM_C6_Pin|LedM_C7_Pin
                          |LedM_C8_Pin|LedM_C9_Pin|LedM_C10_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LedM_C4_GPIO_Port, LedM_C4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : Key_R0_Pin Key_R1_Pin Key_R2_Pin Key_R3_Pin
                           LedM_R3_Pin BFOE_2_Pin BFOE_1_Pin LedM_R4_Pin
                           LedM_R14_Pin LedM_R15_Pin */
  GPIO_InitStruct.Pin = Key_R0_Pin|Key_R1_Pin|Key_R2_Pin|Key_R3_Pin
                          |LedM_R3_Pin|BFOE_2_Pin|BFOE_1_Pin|LedM_R4_Pin
                          |LedM_R14_Pin|LedM_R15_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : LedM_R1_Pin LedM_R2_Pin LedM_R5_Pin LedM_R6_Pin
                           LedM_R7_Pin LedM_R8_Pin LedM_R9_Pin LedM_R10_Pin
                           LedM_R11_Pin LedM_R12_Pin LedM_R13_Pin LedM_R16_Pin */
  GPIO_InitStruct.Pin = LedM_R1_Pin|LedM_R2_Pin|LedM_R5_Pin|LedM_R6_Pin
                          |LedM_R7_Pin|LedM_R8_Pin|LedM_R9_Pin|LedM_R10_Pin
                          |LedM_R11_Pin|LedM_R12_Pin|LedM_R13_Pin|LedM_R16_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : Key_C0_Pin Key_C1_Pin Key_C2_Pin */
  GPIO_InitStruct.Pin = Key_C0_Pin|Key_C1_Pin|Key_C2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : LedM_C1_Pin LedM_C2_Pin LedM_C3_Pin LedM_C11_Pin
                           LedM_C12_Pin LedM_C13_Pin LedM_C14_Pin LedM_C15_Pin
                           LedM_C16_Pin LedM_C5_Pin LedM_C6_Pin LedM_C7_Pin
                           LedM_C8_Pin LedM_C9_Pin LedM_C10_Pin */
  GPIO_InitStruct.Pin = LedM_C1_Pin|LedM_C2_Pin|LedM_C3_Pin|LedM_C11_Pin
                          |LedM_C12_Pin|LedM_C13_Pin|LedM_C14_Pin|LedM_C15_Pin
                          |LedM_C16_Pin|LedM_C5_Pin|LedM_C6_Pin|LedM_C7_Pin
                          |LedM_C8_Pin|LedM_C9_Pin|LedM_C10_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : LedM_C4_Pin */
  GPIO_InitStruct.Pin = LedM_C4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(LedM_C4_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI4_15_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);

}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
