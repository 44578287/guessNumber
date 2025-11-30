/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define B1_EXTI_IRQn EXTI4_15_IRQn
#define Key_R0_Pin GPIO_PIN_0
#define Key_R0_GPIO_Port GPIOC
#define Key_R1_Pin GPIO_PIN_1
#define Key_R1_GPIO_Port GPIOC
#define Key_R2_Pin GPIO_PIN_2
#define Key_R2_GPIO_Port GPIOC
#define Key_R3_Pin GPIO_PIN_3
#define Key_R3_GPIO_Port GPIOC
#define LedM_R1_Pin GPIO_PIN_0
#define LedM_R1_GPIO_Port GPIOA
#define LedM_R2_Pin GPIO_PIN_1
#define LedM_R2_GPIO_Port GPIOA
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define LedM_R5_Pin GPIO_PIN_4
#define LedM_R5_GPIO_Port GPIOA
#define LedM_R6_Pin GPIO_PIN_5
#define LedM_R6_GPIO_Port GPIOA
#define LedM_R7_Pin GPIO_PIN_6
#define LedM_R7_GPIO_Port GPIOA
#define LedM_R8_Pin GPIO_PIN_7
#define LedM_R8_GPIO_Port GPIOA
#define Key_C0_Pin GPIO_PIN_4
#define Key_C0_GPIO_Port GPIOC
#define Key_C0_EXTI_IRQn EXTI4_15_IRQn
#define Key_C1_Pin GPIO_PIN_5
#define Key_C1_GPIO_Port GPIOC
#define Key_C1_EXTI_IRQn EXTI4_15_IRQn
#define LedM_C1_Pin GPIO_PIN_0
#define LedM_C1_GPIO_Port GPIOB
#define LedM_C2_Pin GPIO_PIN_1
#define LedM_C2_GPIO_Port GPIOB
#define LedM_C3_Pin GPIO_PIN_2
#define LedM_C3_GPIO_Port GPIOB
#define LedM_C11_Pin GPIO_PIN_10
#define LedM_C11_GPIO_Port GPIOB
#define LedM_C12_Pin GPIO_PIN_11
#define LedM_C12_GPIO_Port GPIOB
#define LedM_C13_Pin GPIO_PIN_12
#define LedM_C13_GPIO_Port GPIOB
#define LedM_C14_Pin GPIO_PIN_13
#define LedM_C14_GPIO_Port GPIOB
#define LedM_C15_Pin GPIO_PIN_14
#define LedM_C15_GPIO_Port GPIOB
#define LedM_C16_Pin GPIO_PIN_15
#define LedM_C16_GPIO_Port GPIOB
#define Key_C2_Pin GPIO_PIN_6
#define Key_C2_GPIO_Port GPIOC
#define Key_C2_EXTI_IRQn EXTI4_15_IRQn
#define LedM_R3_Pin GPIO_PIN_7
#define LedM_R3_GPIO_Port GPIOC
#define BFOE_2_Pin GPIO_PIN_8
#define BFOE_2_GPIO_Port GPIOC
#define BFOE_1_Pin GPIO_PIN_9
#define BFOE_1_GPIO_Port GPIOC
#define LedM_R9_Pin GPIO_PIN_8
#define LedM_R9_GPIO_Port GPIOA
#define LedM_R10_Pin GPIO_PIN_9
#define LedM_R10_GPIO_Port GPIOA
#define LedM_R11_Pin GPIO_PIN_10
#define LedM_R11_GPIO_Port GPIOA
#define LedM_R12_Pin GPIO_PIN_11
#define LedM_R12_GPIO_Port GPIOA
#define LedM_R13_Pin GPIO_PIN_12
#define LedM_R13_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define LedM_R16_Pin GPIO_PIN_15
#define LedM_R16_GPIO_Port GPIOA
#define LedM_R4_Pin GPIO_PIN_10
#define LedM_R4_GPIO_Port GPIOC
#define LedM_R14_Pin GPIO_PIN_11
#define LedM_R14_GPIO_Port GPIOC
#define LedM_R15_Pin GPIO_PIN_12
#define LedM_R15_GPIO_Port GPIOC
#define LedM_C4_Pin GPIO_PIN_2
#define LedM_C4_GPIO_Port GPIOD
#define LedM_C5_Pin GPIO_PIN_4
#define LedM_C5_GPIO_Port GPIOB
#define LedM_C6_Pin GPIO_PIN_5
#define LedM_C6_GPIO_Port GPIOB
#define LedM_C7_Pin GPIO_PIN_6
#define LedM_C7_GPIO_Port GPIOB
#define LedM_C8_Pin GPIO_PIN_7
#define LedM_C8_GPIO_Port GPIOB
#define LedM_C9_Pin GPIO_PIN_8
#define LedM_C9_GPIO_Port GPIOB
#define LedM_C10_Pin GPIO_PIN_9
#define LedM_C10_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
