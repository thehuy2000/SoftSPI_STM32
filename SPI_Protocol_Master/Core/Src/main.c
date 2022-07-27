
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <string.h>
/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);

void Soft_SPI_begin(void);
void Soft_SPI_end(void);
static void Soft_SPI_Init(void);

uint8_t Soft_SPI_TransferByte(unsigned char byte);

/* Private user code ---------------------------------------------------------*/
/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
 

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
	
	Soft_SPI_Init();
//	Soft_SPI_Write(byteTx);
  while (1)
  {
		/*Master send*/
		Soft_SPI_begin();
		uint8_t rev;
		rev = Soft_SPI_TransferByte('a'); // 0x61		97
		Soft_SPI_end();
		HAL_Delay(1000);
  }
}

/*Ham khoi tao SPI*/
	void Soft_SPI_Init(){
		HAL_GPIO_WritePin(GPIOA, MASTER_SCK_Pin, GPIO_PIN_RESET); // dua chan SCK ve muc 0
		HAL_GPIO_WritePin(GPIOA, MASTER_CS_Pin, GPIO_PIN_SET);		// dua chan CS ve muc 1
	}
	/*Ham de khoi dong SPI, san sang truyen du lieu*/
	void Soft_SPI_begin(){
			HAL_GPIO_WritePin(GPIOA, MASTER_CS_Pin, GPIO_PIN_RESET);		// dua chan CS ve muc 0, san sang truyen du lieu
	}
	/*Ham ket thuc truyen nhan du lieu cua Master*/
	void Soft_SPI_end(){
			HAL_GPIO_WritePin(GPIOA, MASTER_CS_Pin, GPIO_PIN_SET);		// dua chan CS len muc 1, dung truyen du lieu
			HAL_GPIO_WritePin(GPIOA, MASTER_SCK_Pin, GPIO_PIN_RESET); // dua chan SCK ve muc 0
	}
	// Thiet lap them toc do truyen bao nhieu bit/s ???????????
/*Ham truyen nhan du lieu tu Master*/
	// Mode 0, bitorder: MSB, f = 0,5kHz ==> T = 2ms
	uint8_t Soft_SPI_TransferByte(unsigned char byteOut){
			uint8_t byteIn = 0;  
			uint8_t temp;
		for(uint8_t i = 0x80; i > 0; i = i >> 1)
	 {
			temp = byteOut & i;
			HAL_GPIO_WritePin(GPIOA, MASTER_MOSI_Pin, temp);
			HAL_Delay(Thalf);
			HAL_GPIO_WritePin(GPIOA, MASTER_SCK_Pin, GPIO_PIN_SET);
			if(HAL_GPIO_ReadPin(GPIOA, MASTER_MISO_Pin) == 1)
					byteIn = byteIn | i;
			HAL_Delay(Thalf);
			HAL_GPIO_WritePin(GPIOA, MASTER_SCK_Pin, GPIO_PIN_RESET);
	 }
	 return byteIn;
 }

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, MASTER_MOSI_Pin|MASTER_SCK_Pin|MASTER_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(SLAVE_MISO_GPIO_Port, SLAVE_MISO_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : MASTER_MOSI_Pin MASTER_SCK_Pin MASTER_CS_Pin */
  GPIO_InitStruct.Pin = MASTER_MOSI_Pin|MASTER_SCK_Pin|MASTER_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : MASTER_MISO_Pin */
  GPIO_InitStruct.Pin = MASTER_MISO_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(MASTER_MISO_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : SLAVE_MOSI_Pin SLAVE_SCK_Pin SLAVE_CS_Pin */
  GPIO_InitStruct.Pin = SLAVE_MOSI_Pin|SLAVE_SCK_Pin|SLAVE_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : SLAVE_MISO_Pin */
  GPIO_InitStruct.Pin = SLAVE_MISO_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(SLAVE_MISO_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
