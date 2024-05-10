/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define MAX30101_ADDR 0b10101110
#define  FIFO_WR_PTR 0x04
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;
DMA_HandleTypeDef hdma_i2c1_rx;
DMA_HandleTypeDef hdma_i2c1_tx;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
HAL_StatusTypeDef i2c_status;
uint8_t FIFOWP[5];
uint8_t FIFORP[5];
uint8_t FIFOData[6];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART2_UART_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
//  if(i2c_status == HAL_OK){
// 	  //Mode configuration
// 	  uint8_t Data[1] = {0b00000111};
// 	  HAL_I2C_Mem_Write(&hi2c1, 0b10101110, 0x09, I2C_MEMADD_SIZE_8BIT, Data, 1,100);
//   }
//
//   else if(i2c_status == HAL_OK){
// 	  //LED Pulse
// 	  uint8_t DataLED[1] = {0xFF};
// 	  HAL_I2C_Mem_Write(&hi2c1, 0b10101110, 0x0C, I2C_MEMADD_SIZE_8BIT, DataLED, 1,100);
// 	  HAL_I2C_Mem_Write(&hi2c1, 0b10101110, 0x0D, I2C_MEMADD_SIZE_8BIT, DataLED, 1,100);
// 	  HAL_I2C_Mem_Write(&hi2c1, 0b10101110, 0x0E, I2C_MEMADD_SIZE_8BIT, DataLED, 1,100);
// 	  HAL_I2C_Mem_Write(&hi2c1, 0b10101110, 0x0F, I2C_MEMADD_SIZE_8BIT, DataLED, 1,100);
//   }
//
//   else if(i2c_status == HAL_OK){
// 	  //Open LED-+
// 	  uint8_t DataMultiLED[1] = {0b00010011};
// 	  HAL_I2C_Mem_Write(&hi2c1, 0b10101110, 0x11, I2C_MEMADD_SIZE_8BIT, DataMultiLED, 1,100);
//   }

  //into Mode
  uint8_t DataMode[1] = {0x02};
  HAL_I2C_Mem_Write(&hi2c1, MAX30101_ADDR, 0x09, I2C_MEMADD_SIZE_8BIT, DataMode, 1, 100);

   //Mode configuration
   uint8_t Data[1] = {0b00000111};
   HAL_I2C_Mem_Write(&hi2c1, 0b10101110, 0x09, I2C_MEMADD_SIZE_8BIT, Data, 1,100);


   //LED Pulse
   uint8_t DataLED[1] = {0xFF};
   HAL_I2C_Mem_Write(&hi2c1, 0b10101110, 0x0C, I2C_MEMADD_SIZE_8BIT, DataLED, 1,100);
   HAL_I2C_Mem_Write(&hi2c1, 0b10101110, 0x0D, I2C_MEMADD_SIZE_8BIT, DataLED, 1,100);
   HAL_I2C_Mem_Write(&hi2c1, 0b10101110, 0x0E, I2C_MEMADD_SIZE_8BIT, DataLED, 1,100);
   HAL_I2C_Mem_Write(&hi2c1, 0b10101110, 0x0F, I2C_MEMADD_SIZE_8BIT, DataLED, 1,100);


   //Open LED-+
   uint8_t DataMultiLED[1] = {0b00010011};
   HAL_I2C_Mem_Write(&hi2c1, 0b10101110, 0x11, I2C_MEMADD_SIZE_8BIT, DataMultiLED, 1,100);

   //FIFO Configuration
   //Set sample average
   uint8_t DataFIFOConf[1] = {0b01011111};
   HAL_I2C_Mem_Write(&hi2c1, MAX30101_ADDR,0x08, I2C_MEMADD_SIZE_8BIT, DataFIFOConf, 1,100);

//   //Enable roll over if FIFO over flows
//   uint8_t DataFIFOEn[1] = {0b11111111};
//   HAL_I2C_Mem_Write(&hi2c1, MAX30101_ADDR, 0x08, I2C_MEMADD_SIZE_8BIT, DataFIFOEn, 1,100);

//Read FIFO

   //Read the FIFO Write Pointer
//   HAL_I2C_Mem_Read(&hi2c1, MAX30101_ADDR, 0x04, I2C_MEMADD_SIZE_8BIT, FIFOWP, 4, 100);
   HAL_I2C_Master_Transmit(&hi2c1, MAX30101_ADDR, 0x04, 1, 1000);
   HAL_I2C_Master_Receive(&hi2c1, MAX30101_ADDR, FIFOWP, 4, 1000);


   //Read the FIFO Read Pointer
//   HAL_I2C_Mem_Read(&hi2c1, MAX30101_ADDR, 0x06, I2C_MEMADD_SIZE_8BIT, pData, Size, 100);
   HAL_I2C_Master_Transmit(&hi2c1, MAX30101_ADDR, 0x06, 1, 1000);
   HAL_I2C_Master_Receive(&hi2c1, MAX30101_ADDR, FIFORP, 4, 1000);

   int8_t num_samples;
   num_samples = FIFOWP - FIFORP;
   if (num_samples < 1)
   {
	   num_samples += 32;
   }
   for (int8_t i = 0; i < num_samples; i++){
	   uint8_t sample[6];
	   HAL_I2C_Master_Transmit(&hi2c1, MAX30101_ADDR, 0x07, 1, 1000);
	   HAL_I2C_Master_Receive(&hi2c1, MAX30101_ADDR, FIFOData, 6, 1000);
   }


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  /* USER CODE END WHILE */

	  /* USER CODE BEGIN 3 */
//	  OpenLED();
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Stream0_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream0_IRQn);
  /* DMA1_Stream1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream1_IRQn);

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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void OpenLED(){
	if(i2c_status == HAL_OK){
		//Mode configuration
		uint8_t Data[1] = {0b00000111};
		HAL_I2C_Mem_Write(&hi2c1, 0b10101110, 0x09, I2C_MEMADD_SIZE_8BIT, Data, 1,100);
	}

	else if(i2c_status == HAL_OK){
		//LED Pulse
		uint8_t DataLED[1] = {0xFF};
		HAL_I2C_Mem_Write(&hi2c1, 0b10101110, 0x0C, I2C_MEMADD_SIZE_8BIT, DataLED, 1,100);
		HAL_I2C_Mem_Write(&hi2c1, 0b10101110, 0x0D, I2C_MEMADD_SIZE_8BIT, DataLED, 1,100);
		HAL_I2C_Mem_Write(&hi2c1, 0b10101110, 0x0E, I2C_MEMADD_SIZE_8BIT, DataLED, 1,100);
		HAL_I2C_Mem_Write(&hi2c1, 0b10101110, 0x0F, I2C_MEMADD_SIZE_8BIT, DataLED, 1,100);
	}

	else if(i2c_status == HAL_OK){
		//Open LED-+
		uint8_t DataMultiLED[1] = {0b00010011};
		HAL_I2C_Mem_Write(&hi2c1, 0b10101110, 0x11, I2C_MEMADD_SIZE_8BIT, DataMultiLED, 1,100);
	}
}

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
