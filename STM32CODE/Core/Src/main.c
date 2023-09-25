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
enum segment{a_, b_, c_, d_, e_, f_, g_};
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define red_counter 5
#define yellow_counter 2
#define green_counter 3
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
GPIO_TypeDef *light_port[2][3] = {
		{RED_1_GPIO_Port, YELLOW_1_GPIO_Port, GREEN_1_GPIO_Port},
		{RED_2_GPIO_Port, YELLOW_2_GPIO_Port, GREEN_2_GPIO_Port}
};
uint16_t light_pin[2][3] = {
		{RED_1_Pin, YELLOW_1_Pin, GREEN_1_Pin},
		{RED_2_Pin, YELLOW_2_Pin, GREEN_2_Pin}
};
GPIO_TypeDef *C7SEG_port[2][7] = {
		{a_1_GPIO_Port, b_1_GPIO_Port, c_1_GPIO_Port, d_1_GPIO_Port, e_1_GPIO_Port, f_1_GPIO_Port, g_1_GPIO_Port},
		{a_2_GPIO_Port, b_2_GPIO_Port, c_2_GPIO_Port, d_2_GPIO_Port, e_2_GPIO_Port, f_2_GPIO_Port, g_2_GPIO_Port}
};
uint16_t C7SEG_pin[2][7] = {
		{a_1_Pin, b_1_Pin, c_1_Pin, d_1_Pin, e_1_Pin, f_1_Pin, g_1_Pin},
		{a_2_Pin, b_2_Pin, c_2_Pin, d_2_Pin, e_2_Pin, f_2_Pin, g_2_Pin}
};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
void on_light(enum color light, int cluster);
void display7SEG(int num, int cluster);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void on_light(enum color light, int cluster)
{
	cluster--;
	switch (light)
	{
	case red:
		HAL_GPIO_WritePin(light_port[cluster][red], light_pin[cluster][red], RESET);
		HAL_GPIO_WritePin(light_port[cluster][yellow], light_pin[cluster][yellow], SET);
		HAL_GPIO_WritePin(light_port[cluster][green], light_pin[cluster][green], SET);
		break;
	case yellow:
		HAL_GPIO_WritePin(light_port[cluster][red], light_pin[cluster][red], SET);
		HAL_GPIO_WritePin(light_port[cluster][yellow], light_pin[cluster][yellow], RESET);
		HAL_GPIO_WritePin(light_port[cluster][green], light_pin[cluster][green], SET);
		break;
	default:
		HAL_GPIO_WritePin(light_port[cluster][red], light_pin[cluster][red], SET);
		HAL_GPIO_WritePin(light_port[cluster][yellow], light_pin[cluster][yellow], SET);
		HAL_GPIO_WritePin(light_port[cluster][green], light_pin[cluster][green], RESET);
	}
}
void display7SEG(int num, int cluster)
{
	cluster--;
	switch (num)
	{
	case 0:
		HAL_GPIO_WritePin(C7SEG_port[cluster][a_], C7SEG_pin[cluster][a_], RESET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][b_], C7SEG_pin[cluster][b_], RESET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][c_], C7SEG_pin[cluster][c_], RESET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][d_], C7SEG_pin[cluster][d_], RESET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][e_], C7SEG_pin[cluster][e_], RESET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][f_], C7SEG_pin[cluster][f_], RESET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][g_], C7SEG_pin[cluster][g_], SET);
		break;
	case 1:
		HAL_GPIO_WritePin(C7SEG_port[cluster][a_], C7SEG_pin[cluster][a_], SET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][b_], C7SEG_pin[cluster][b_], RESET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][c_], C7SEG_pin[cluster][c_], RESET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][d_], C7SEG_pin[cluster][d_], SET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][e_], C7SEG_pin[cluster][e_], SET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][f_], C7SEG_pin[cluster][f_], SET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][g_], C7SEG_pin[cluster][g_], SET);
		break;
	case 2:
		HAL_GPIO_WritePin(C7SEG_port[cluster][a_], C7SEG_pin[cluster][a_], RESET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][b_], C7SEG_pin[cluster][b_], RESET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][c_], C7SEG_pin[cluster][c_], SET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][d_], C7SEG_pin[cluster][d_], RESET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][e_], C7SEG_pin[cluster][e_], RESET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][f_], C7SEG_pin[cluster][f_], SET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][g_], C7SEG_pin[cluster][g_], RESET);
		break;
	case 3:
		HAL_GPIO_WritePin(C7SEG_port[cluster][a_], C7SEG_pin[cluster][a_], RESET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][b_], C7SEG_pin[cluster][b_], RESET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][c_], C7SEG_pin[cluster][c_], RESET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][d_], C7SEG_pin[cluster][d_], RESET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][e_], C7SEG_pin[cluster][e_], SET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][f_], C7SEG_pin[cluster][f_], SET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][g_], C7SEG_pin[cluster][g_], RESET);
		break;
	case 4:
		HAL_GPIO_WritePin(C7SEG_port[cluster][a_], C7SEG_pin[cluster][a_], SET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][b_], C7SEG_pin[cluster][b_], RESET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][c_], C7SEG_pin[cluster][c_], RESET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][d_], C7SEG_pin[cluster][d_], SET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][e_], C7SEG_pin[cluster][e_], SET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][f_], C7SEG_pin[cluster][f_], RESET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][g_], C7SEG_pin[cluster][g_], RESET);
		break;
	case 5:
		HAL_GPIO_WritePin(C7SEG_port[cluster][a_], C7SEG_pin[cluster][a_], RESET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][b_], C7SEG_pin[cluster][b_], SET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][c_], C7SEG_pin[cluster][c_], RESET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][d_], C7SEG_pin[cluster][d_], RESET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][e_], C7SEG_pin[cluster][e_], SET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][f_], C7SEG_pin[cluster][f_], RESET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][g_], C7SEG_pin[cluster][g_], RESET);
		break;
	case 6:
		HAL_GPIO_WritePin(C7SEG_port[cluster][a_], C7SEG_pin[cluster][a_], RESET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][b_], C7SEG_pin[cluster][b_], SET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][c_], C7SEG_pin[cluster][c_], RESET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][d_], C7SEG_pin[cluster][d_], RESET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][e_], C7SEG_pin[cluster][e_], RESET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][f_], C7SEG_pin[cluster][f_], RESET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][g_], C7SEG_pin[cluster][g_], RESET);
		break;
	case 7:
		HAL_GPIO_WritePin(C7SEG_port[cluster][a_], C7SEG_pin[cluster][a_], RESET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][b_], C7SEG_pin[cluster][b_], RESET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][c_], C7SEG_pin[cluster][c_], RESET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][d_], C7SEG_pin[cluster][d_], SET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][e_], C7SEG_pin[cluster][e_], SET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][f_], C7SEG_pin[cluster][f_], SET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][g_], C7SEG_pin[cluster][g_], SET);
		break;
	case 8:
		HAL_GPIO_WritePin(C7SEG_port[cluster][a_], C7SEG_pin[cluster][a_], RESET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][b_], C7SEG_pin[cluster][b_], RESET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][c_], C7SEG_pin[cluster][c_], RESET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][d_], C7SEG_pin[cluster][d_], RESET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][e_], C7SEG_pin[cluster][e_], RESET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][f_], C7SEG_pin[cluster][f_], RESET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][g_], C7SEG_pin[cluster][g_], RESET);
		break;
	case 9:
		HAL_GPIO_WritePin(C7SEG_port[cluster][a_], C7SEG_pin[cluster][a_], RESET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][b_], C7SEG_pin[cluster][b_], RESET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][c_], C7SEG_pin[cluster][c_], RESET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][d_], C7SEG_pin[cluster][d_], RESET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][e_], C7SEG_pin[cluster][e_], SET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][f_], C7SEG_pin[cluster][f_], RESET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][g_], C7SEG_pin[cluster][g_], RESET);
		break;
	default:
		HAL_GPIO_WritePin(C7SEG_port[cluster][a_], C7SEG_pin[cluster][a_], RESET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][b_], C7SEG_pin[cluster][b_], SET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][c_], C7SEG_pin[cluster][c_], SET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][d_], C7SEG_pin[cluster][d_], RESET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][e_], C7SEG_pin[cluster][e_], RESET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][f_], C7SEG_pin[cluster][f_], RESET);
		HAL_GPIO_WritePin(C7SEG_port[cluster][g_], C7SEG_pin[cluster][g_], RESET);
	}
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
	  display7SEG(timer_counter_1, 1);
	  display7SEG(timer_counter_2, 2);
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
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, RED_1_Pin|YELLOW_1_Pin|GREEN_1_Pin|RED_2_Pin
                          |YELLOW_2_Pin|GREEN_2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, a_1_Pin|b_1_Pin|c_1_Pin|d_2_Pin
                          |e_2_Pin|f_2_Pin|g_2_Pin|d_1_Pin
                          |e_1_Pin|f_1_Pin|g_1_Pin|a_2_Pin
                          |b_2_Pin|c_2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : RED_1_Pin YELLOW_1_Pin GREEN_1_Pin RED_2_Pin
                           YELLOW_2_Pin GREEN_2_Pin */
  GPIO_InitStruct.Pin = RED_1_Pin|YELLOW_1_Pin|GREEN_1_Pin|RED_2_Pin
                          |YELLOW_2_Pin|GREEN_2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : a_1_Pin b_1_Pin c_1_Pin d_2_Pin
                           e_2_Pin f_2_Pin g_2_Pin d_1_Pin
                           e_1_Pin f_1_Pin g_1_Pin a_2_Pin
                           b_2_Pin c_2_Pin */
  GPIO_InitStruct.Pin = a_1_Pin|b_1_Pin|c_1_Pin|d_2_Pin
                          |e_2_Pin|f_2_Pin|g_2_Pin|d_1_Pin
                          |e_1_Pin|f_1_Pin|g_1_Pin|a_2_Pin
                          |b_2_Pin|c_2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

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
