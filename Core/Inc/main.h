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
#include "stm32f1xx_hal.h"

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
#define L1_PWM_Pin GPIO_PIN_0
#define L1_PWM_GPIO_Port GPIOA
#define L2_PWM_Pin GPIO_PIN_1
#define L2_PWM_GPIO_Port GPIOA
#define R1_PWM_Pin GPIO_PIN_2
#define R1_PWM_GPIO_Port GPIOA
#define R2_PWM_Pin GPIO_PIN_3
#define R2_PWM_GPIO_Port GPIOA
#define R_A_Pin GPIO_PIN_6
#define R_A_GPIO_Port GPIOA
#define R_B_Pin GPIO_PIN_7
#define R_B_GPIO_Port GPIOA
#define MPU6050_SCL_Pin GPIO_PIN_10
#define MPU6050_SCL_GPIO_Port GPIOB
#define MPU6050_SDA_Pin GPIO_PIN_11
#define MPU6050_SDA_GPIO_Port GPIOB
#define R_IN2_Pin GPIO_PIN_12
#define R_IN2_GPIO_Port GPIOB
#define R_IN1_Pin GPIO_PIN_13
#define R_IN1_GPIO_Port GPIOB
#define L_IN2_Pin GPIO_PIN_14
#define L_IN2_GPIO_Port GPIOB
#define L_IN1_Pin GPIO_PIN_15
#define L_IN1_GPIO_Port GPIOB
#define L_A_Pin GPIO_PIN_8
#define L_A_GPIO_Port GPIOA
#define L_B_Pin GPIO_PIN_9
#define L_B_GPIO_Port GPIOA
#define OLED_SCL_Pin GPIO_PIN_8
#define OLED_SCL_GPIO_Port GPIOB
#define OLED_SDA_Pin GPIO_PIN_9
#define OLED_SDA_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
