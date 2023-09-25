/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
enum state{RED1_GREEN2, RED1_YELLOW2, GREEN1_RED2, YELLOW1_RED2};
enum color{red, yellow, green};
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define red_counter 5
#define yellow_counter 2
#define green_counter 3
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
void on_light(enum color light, int number);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void on_light(enum color light, int number)
{
	/* Declare variables */
	GPIO_TypeDef *red_port = NULL;
	GPIO_TypeDef *yellow_port = NULL;
	GPIO_TypeDef *green_port = NULL;

	uint16_t red_pin = 0;
	uint16_t yellow_pin = 0;
	uint16_t green_pin = 0;

	GPIO_PinState red_state = SET;
	GPIO_PinState yellow_state = SET;
	GPIO_PinState green_state = SET;

	/* Select the LED cluster */
	if(number == 1)
	{
		red_port = RED_1_GPIO_Port;
		yellow_port = YELLOW_1_GPIO_Port;
		green_port = GREEN_1_GPIO_Port;

		red_pin = RED_1_Pin;
		yellow_pin = YELLOW_1_Pin;
		green_pin = GREEN_1_Pin;
	}
	else
	{
		red_port = RED_2_GPIO_Port;
		yellow_port = YELLOW_2_GPIO_Port;
		green_port = GREEN_2_GPIO_Port;

		red_pin = RED_2_Pin;
		yellow_pin = YELLOW_2_Pin;
		green_pin = GREEN_2_Pin;
	}

	/* Select light to turn on */
	switch (light)
	{
	case red:
		red_state = RESET;
		yellow_state = SET;
		green_state = SET;
		break;
	case yellow:
		red_state = SET;
		yellow_state = RESET;
		green_state = SET;
		break;
	default:
		red_state = SET;
		yellow_state = SET;
		green_state = RESET;
	}

	/* Function to turn on light */
	HAL_GPIO_WritePin(red_port, red_pin, red_state);
	HAL_GPIO_WritePin(yellow_port, yellow_pin, yellow_state);
	HAL_GPIO_WritePin(green_port, green_pin, green_state);
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	enum state current = RED1_GREEN2;
	int timer_counter_1 = red_counter;
	int timer_counter_2 = green_counter;
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
  on_light(red, 1);
  on_light(green, 2);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  switch (current)
	  {
	  case RED1_GREEN2:
		  if(timer_counter_2 <= 0)
		  {
			  current = RED1_YELLOW2;
			  on_light(yellow, 2);
			  timer_counter_2 = yellow_counter;
		  }
		  break;
	  case RED1_YELLOW2:
		  if(timer_counter_2 <= 0)
		  {
			  current = GREEN1_RED2;
			  on_light(green, 1);
			  timer_counter_1 = green_counter;
			  on_light(red, 2);
			  timer_counter_2 = red_counter;
		  }
		  break;
	  case GREEN1_RED2:
		  if(timer_counter_1 <= 0)
		  {
			  current = YELLOW1_RED2;
			  on_light(yellow, 1);
			  timer_counter_1 = yellow_counter;
		  }
		  break;
	  default:
		  if(timer_counter_1 <= 0)
		  {
			  current = RED1_GREEN2;
			  on_light(red, 1);
			  timer_counter_1 = red_counter;
			  on_light(green, 2);
			  timer_counter_2 = green_counter;
		  }
	  }
	  timer_counter_1--;
	  timer_counter_2--;
	  HAL_Delay(1000);
    /* USER CODE END WHILE */

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
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, RED_1_Pin|YELLOW_1_Pin|GREEN_1_Pin|RED_2_Pin
                          |YELLOW_2_Pin|GREEN_2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : RED_1_Pin YELLOW_1_Pin GREEN_1_Pin RED_2_Pin
                           YELLOW_2_Pin GREEN_2_Pin */
  GPIO_InitStruct.Pin = RED_1_Pin|YELLOW_1_Pin|GREEN_1_Pin|RED_2_Pin
                          |YELLOW_2_Pin|GREEN_2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
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
