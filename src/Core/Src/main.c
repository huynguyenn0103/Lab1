/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
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
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
void display7SEGa(int);
void display7SEGb(int);
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
  /* USER CODE BEGIN 2 */
  int time_green = 6;
  int time_yellow = 3;
  int time_red = 9;
  int time_total = time_green + time_yellow + time_red;

  int counter1 = time_total;
  int counter7Segled1 = time_red;

  int counter2 = time_total;
  int counter7Segled2 = time_green;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
	  if(counter1 == time_total - time_red){
	  //	  		  Red -> Green
	  	  		  HAL_GPIO_WritePin ( LED_RED1_GPIO_Port , LED_RED1_Pin , GPIO_PIN_SET );
	  	  		  HAL_GPIO_WritePin ( LED_GREEN1_GPIO_Port , LED_GREEN1_Pin , GPIO_PIN_RESET ) ;
	  	  		  counter7Segled1 = time_green;
	  	  	  }
	  //	  	     Green -> Yellow
	  	  	  else if(counter1 == time_total - time_red - time_green){
	  	  		  HAL_GPIO_WritePin ( LED_GREEN1_GPIO_Port , LED_GREEN1_Pin , GPIO_PIN_SET );
	  	  		  HAL_GPIO_WritePin ( LED_YELLOW1_GPIO_Port , LED_YELLOW1_Pin , GPIO_PIN_RESET ) ;
	  	  		  counter7Segled1 = time_yellow;
	  	  	  }
	  	  	  else if(counter1 == 0){
	  //	  		 Yellow -> Red
	  	  		  HAL_GPIO_WritePin ( LED_YELLOW1_GPIO_Port , LED_YELLOW1_Pin , GPIO_PIN_SET );
	  	  		  HAL_GPIO_WritePin ( LED_RED1_GPIO_Port , LED_RED1_Pin , GPIO_PIN_RESET ) ;
	  	  		  counter1 = time_total;
	  	  		  counter7Segled1 = time_red;
	  	  	  }

	  	  	  if (counter2 == time_total - time_green){
	  //	  		  Green -> Yellow
	  	  		  HAL_GPIO_WritePin ( LED_GREEN2_GPIO_Port , LED_GREEN2_Pin , GPIO_PIN_SET );
	  	  		  HAL_GPIO_WritePin ( LED_YELLOW2_GPIO_Port , LED_YELLOW2_Pin , GPIO_PIN_RESET ) ;
	  	  		  counter7Segled2 = time_yellow;
	  	  	  }
	  	  	  if (counter2 == time_total - time_green - time_yellow){
	  //	  		  Yellow -> Red
	  	  		  HAL_GPIO_WritePin ( LED_YELLOW2_GPIO_Port , LED_YELLOW2_Pin , GPIO_PIN_SET );
	  	  		  HAL_GPIO_WritePin ( LED_RED2_GPIO_Port , LED_RED2_Pin , GPIO_PIN_RESET ) ;
	  	  		 counter7Segled2 = time_red;
	  	  	  }
	  	  	  if (counter2 == 0){
	  //	  		  Red -> Green
	  	  	 	  HAL_GPIO_WritePin ( LED_RED2_GPIO_Port , LED_RED2_Pin , GPIO_PIN_SET );
	  	  	 	  HAL_GPIO_WritePin ( LED_GREEN2_GPIO_Port , LED_GREEN2_Pin , GPIO_PIN_RESET ) ;
	  	  	 	  counter2 = time_total;
	  	  	 	  counter7Segled2 = time_green;
	  	  	  }

	  	  	  display7SEGa(counter7Segled1--);
	  	  	  display7SEGb(counter7Segled2--);
	  	  	  counter1--;
	  	  	  counter2--;
	  	  	  HAL_Delay(1000);
    /* USER CODE BEGIN 3 */
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
  HAL_GPIO_WritePin(GPIOA, LED_RED1_Pin|LED_GREEN2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED_YELLOW1_Pin|LED_GREEN1_Pin|LED_RED2_Pin|LED_YELLOW2_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, Seg_a1_Pin|Seg_b1_Pin|Seg_c1_Pin|Seg_d2_Pin
                          |Seg_e2_Pin|Seg_d1_Pin|Seg_e1_Pin|Seg_f1_Pin
                          |Seg_g1_Pin|Seg_a2_Pin|Seg_b2_Pin|Seg_c2_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, Seg_f2_Pin|Seg_g2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LED_RED1_Pin LED_YELLOW1_Pin LED_GREEN1_Pin LED_RED2_Pin
                           LED_YELLOW2_Pin LED_GREEN2_Pin */
  GPIO_InitStruct.Pin = LED_RED1_Pin|LED_YELLOW1_Pin|LED_GREEN1_Pin|LED_RED2_Pin
                          |LED_YELLOW2_Pin|LED_GREEN2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : Seg_a1_Pin Seg_b1_Pin Seg_c1_Pin Seg_d2_Pin
                           Seg_e2_Pin Seg_f2_Pin Seg_g2_Pin Seg_d1_Pin
                           Seg_e1_Pin Seg_f1_Pin Seg_g1_Pin Seg_a2_Pin
                           Seg_b2_Pin Seg_c2_Pin */
  GPIO_InitStruct.Pin = Seg_a1_Pin|Seg_b1_Pin|Seg_c1_Pin|Seg_d2_Pin
                          |Seg_e2_Pin|Seg_f2_Pin|Seg_g2_Pin|Seg_d1_Pin
                          |Seg_e1_Pin|Seg_f1_Pin|Seg_g1_Pin|Seg_a2_Pin
                          |Seg_b2_Pin|Seg_c2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void display7SEGa(int counter){
	if(counter == 0){
			HAL_GPIO_WritePin(GPIOB, Seg_a1_Pin|Seg_b1_Pin|Seg_c1_Pin|Seg_d1_Pin|Seg_e1_Pin|Seg_f1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, Seg_g1_Pin, GPIO_PIN_SET);
		}
		else if(counter == 1){
			HAL_GPIO_WritePin(GPIOB,Seg_b1_Pin|Seg_c1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, Seg_a1_Pin|Seg_d1_Pin|Seg_e1_Pin|Seg_f1_Pin|Seg_g1_Pin, GPIO_PIN_SET);
		}
		else if(counter == 2){
			HAL_GPIO_WritePin(GPIOB,Seg_a1_Pin|Seg_b1_Pin|Seg_d1_Pin|Seg_e1_Pin|Seg_g1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, Seg_c1_Pin|Seg_f1_Pin, GPIO_PIN_SET);
		}
		else if(counter == 3){
			HAL_GPIO_WritePin(GPIOB,Seg_a1_Pin|Seg_b1_Pin|Seg_c1_Pin|Seg_d1_Pin|Seg_g1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, Seg_e1_Pin|Seg_f1_Pin, GPIO_PIN_SET);
		}
		else if (counter == 4){
			HAL_GPIO_WritePin(GPIOB,Seg_b1_Pin|Seg_c1_Pin|Seg_f1_Pin|Seg_g1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, Seg_a1_Pin|Seg_d1_Pin|Seg_e1_Pin, GPIO_PIN_SET);
		}
		else if (counter == 5){
			HAL_GPIO_WritePin(GPIOB,Seg_a1_Pin|Seg_c1_Pin|Seg_d1_Pin|Seg_f1_Pin|Seg_g1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, Seg_b1_Pin|Seg_e1_Pin, GPIO_PIN_SET);
		}
		else if (counter == 6){
			HAL_GPIO_WritePin(GPIOB,Seg_a1_Pin|Seg_c1_Pin|Seg_d1_Pin|Seg_e1_Pin|Seg_f1_Pin|Seg_g1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, Seg_b1_Pin, GPIO_PIN_SET);
		}
		else if (counter == 7){
			HAL_GPIO_WritePin(GPIOB,Seg_a1_Pin|Seg_b1_Pin|Seg_c1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, Seg_d1_Pin|Seg_e1_Pin|Seg_f1_Pin|Seg_g1_Pin, GPIO_PIN_SET);
		}
		else if (counter == 8){
			HAL_GPIO_WritePin(GPIOB,Seg_a1_Pin|Seg_b1_Pin|Seg_c1_Pin|Seg_d1_Pin|Seg_e1_Pin|Seg_f1_Pin|Seg_g1_Pin, GPIO_PIN_RESET);
		}
		else if (counter == 9){
			HAL_GPIO_WritePin(GPIOB,Seg_a1_Pin|Seg_b1_Pin|Seg_c1_Pin|Seg_d1_Pin|Seg_f1_Pin|Seg_g1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,Seg_e1_Pin, GPIO_PIN_SET);
		}
}
void display7SEGb(int counter){
	if(counter == 0){
			HAL_GPIO_WritePin(GPIOB, Seg_a2_Pin|Seg_b2_Pin|Seg_c2_Pin|Seg_d2_Pin|Seg_e2_Pin|Seg_f2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, Seg_g2_Pin, GPIO_PIN_SET);
		}
		else if(counter == 1){
			HAL_GPIO_WritePin(GPIOB,Seg_b2_Pin|Seg_c2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, Seg_a2_Pin|Seg_d2_Pin|Seg_e2_Pin|Seg_f2_Pin|Seg_g2_Pin, GPIO_PIN_SET);
		}
		else if(counter == 2){
			HAL_GPIO_WritePin(GPIOB,Seg_a2_Pin|Seg_b2_Pin|Seg_d2_Pin|Seg_e2_Pin|Seg_g2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, Seg_c2_Pin|Seg_f2_Pin, GPIO_PIN_SET);
		}
		else if(counter == 3){
			HAL_GPIO_WritePin(GPIOB,Seg_a2_Pin|Seg_b2_Pin|Seg_c2_Pin|Seg_d2_Pin|Seg_g2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, Seg_e2_Pin|Seg_f2_Pin, GPIO_PIN_SET);
		}
		else if (counter == 4){
			HAL_GPIO_WritePin(GPIOB,Seg_b2_Pin|Seg_c2_Pin|Seg_f2_Pin|Seg_g2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, Seg_a2_Pin|Seg_d2_Pin|Seg_e2_Pin, GPIO_PIN_SET);
		}
		else if (counter == 5){
			HAL_GPIO_WritePin(GPIOB,Seg_a2_Pin|Seg_c2_Pin|Seg_d2_Pin|Seg_f2_Pin|Seg_g2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, Seg_b2_Pin|Seg_e2_Pin, GPIO_PIN_SET);
		}
		else if (counter == 6){
			HAL_GPIO_WritePin(GPIOB,Seg_a2_Pin|Seg_c2_Pin|Seg_d2_Pin|Seg_e2_Pin|Seg_f2_Pin|Seg_g2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, Seg_b2_Pin, GPIO_PIN_SET);
		}
		else if (counter == 7){
			HAL_GPIO_WritePin(GPIOB,Seg_a2_Pin|Seg_b2_Pin|Seg_c2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, Seg_d2_Pin|Seg_e2_Pin|Seg_f2_Pin|Seg_g2_Pin, GPIO_PIN_SET);
		}
		else if (counter == 8){
			HAL_GPIO_WritePin(GPIOB,Seg_a2_Pin|Seg_b2_Pin|Seg_c2_Pin|Seg_d2_Pin|Seg_e2_Pin|Seg_f2_Pin|Seg_g2_Pin, GPIO_PIN_RESET);
		}
		else if (counter == 9){
			HAL_GPIO_WritePin(GPIOB,Seg_a2_Pin|Seg_b2_Pin|Seg_c2_Pin|Seg_d2_Pin|Seg_f2_Pin|Seg_g2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,Seg_e2_Pin, GPIO_PIN_SET);
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
