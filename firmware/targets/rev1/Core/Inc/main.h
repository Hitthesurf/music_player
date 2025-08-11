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
#include "stm32h5xx_hal.h"

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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define DISPLAY_SPI2_MOSI_Pin GPIO_PIN_1
#define DISPLAY_SPI2_MOSI_GPIO_Port GPIOC
#define RIGHT_PWM_AUDIO_Pin GPIO_PIN_2
#define RIGHT_PWM_AUDIO_GPIO_Port GPIOC
#define DISPLAY_RST_Pin GPIO_PIN_0
#define DISPLAY_RST_GPIO_Port GPIOA
#define DISPLAY_DC_Pin GPIO_PIN_1
#define DISPLAY_DC_GPIO_Port GPIOA
#define DISPLAY_CS_Pin GPIO_PIN_2
#define DISPLAY_CS_GPIO_Port GPIOA
#define DISPLAY_SPI2_SCK_Pin GPIO_PIN_13
#define DISPLAY_SPI2_SCK_GPIO_Port GPIOB
#define ENC_A_Pin GPIO_PIN_6
#define ENC_A_GPIO_Port GPIOC
#define ENC_B_Pin GPIO_PIN_7
#define ENC_B_GPIO_Port GPIOC
#define SW1_Pin GPIO_PIN_8
#define SW1_GPIO_Port GPIOA
#define SW2_Pin GPIO_PIN_9
#define SW2_GPIO_Port GPIOA
#define SW3_Pin GPIO_PIN_10
#define SW3_GPIO_Port GPIOA
#define SW4_Pin GPIO_PIN_11
#define SW4_GPIO_Port GPIOA
#define SW5_Pin GPIO_PIN_12
#define SW5_GPIO_Port GPIOA
#define PWM_BUZZER_Pin GPIO_PIN_7
#define PWM_BUZZER_GPIO_Port GPIOB
#define LEFT_PWM_AUDIO_Pin GPIO_PIN_8
#define LEFT_PWM_AUDIO_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
