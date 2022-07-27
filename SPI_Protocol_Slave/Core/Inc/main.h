/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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



/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);
/*define pin master*/
#define MASTER_MOSI_Pin 				GPIO_PIN_1
#define MASTER_MOSI_GPIO_Port 	GPIOA
#define MASTER_MISO_Pin 				GPIO_PIN_2
#define MASTER_MISO_GPIO_Port 	GPIOA
#define MASTER_SCK_Pin 					GPIO_PIN_3
#define MASTER_SCK_GPIO_Port 		GPIOA
#define MASTER_CS_Pin 					GPIO_PIN_4
#define MASTER_CS_GPIO_Port 		GPIOA

/*define pin slave*/
#define SLAVE_MOSI_Pin 					GPIO_PIN_3
#define SLAVE_MOSI_GPIO_Port 		GPIOB
#define SLAVE_MISO_Pin 					GPIO_PIN_4
#define SLAVE_MISO_GPIO_Port 		GPIOB
#define SLAVE_SCK_Pin 					GPIO_PIN_5
#define SLAVE_SCK_GPIO_Port 		GPIOB
#define SLAVE_CS_Pin 						GPIO_PIN_6
#define SLAVE_CS_GPIO_Port 			GPIOB
/* USER CODE BEGIN Private defines */
#define message "Hello World 2022!"


#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
