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
#include "spi.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "hal_max7219.h"
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
uint32_t  white_alarm = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
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
  MX_SPI1_Init();
  MX_TIM6_Init();
  MX_TIM7_Init();
  /* USER CODE BEGIN 2 */
  MAX7219_HandleTypeDef hmax7219;
  hmax7219.Init.hspi = &hspi1;
  hmax7219.Init.CSPort = MAX1719_CS_GPIO_Port;
  hmax7219.Init.CSPin = MAX1719_CS_Pin;
  HAL_MAX7219_Init(&hmax7219);

  HAL_TIM_Base_Start_IT(&htim6);
  // HAL_TIM_Base_Start(&htim6);
  /* USER CODE END 2 */

  /* Initialize leds */
  BSP_LED_Init(LED_GREEN);

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  HAL_GPIO_WritePin(MAX1719_CS_GPIO_Port, MAX1719_CS_Pin, GPIO_PIN_SET);

  HAL_MAX7219_SendMessage(&hmax7219,
                          HAL_MAX7219_ADDRESS_DISPLAY_TEST,
                          HAL_MAX7219_COMMAND_TEST_DISABLE);

  HAL_MAX7219_SendMessage(&hmax7219,
                          HAL_MAX7219_ADDRESS_SHUTDOWN,
                          HAL_MAX7219_COMMAND_NORMAL_OPERATION);

  HAL_MAX7219_SendMessage(&hmax7219,
                          HAL_MAX7219_ADDRESS_DECODE_MODE,
                          HAL_MAX7219_COMMAND_CODE_B_DIGIT_7_0);

  HAL_MAX7219_SendMessage(&hmax7219,
                          HAL_MAX7219_ADDRESS_SCAN_LIMIT,
                          HAL_MAX7219_COMMAND_SCAN_7_0);

  HAL_MAX7219_SendMessage(&hmax7219,
                          HAL_MAX7219_ADDRESS_INTENSITY,
                          HAL_MAX7219_COMMAND_INTENSITY_MIN);

  HAL_MAX7219_SendMessage(&hmax7219,
                          HAL_MAX7219_ADDRESS_DIGIT_0,
                          HAL_MAX7219_COMMAND_CODE_B_FONT_0);
  HAL_MAX7219_SendMessage(&hmax7219,
                          HAL_MAX7219_ADDRESS_DIGIT_1,
                          HAL_MAX7219_COMMAND_CODE_B_FONT_1);
  HAL_MAX7219_SendMessage(&hmax7219,
                          HAL_MAX7219_ADDRESS_DIGIT_2,
                          HAL_MAX7219_COMMAND_CODE_B_FONT_2);
  HAL_MAX7219_SendMessage(&hmax7219,
                          HAL_MAX7219_ADDRESS_DIGIT_3,
                          HAL_MAX7219_COMMAND_CODE_B_FONT_3);
  HAL_MAX7219_SendMessage(&hmax7219,
                          HAL_MAX7219_ADDRESS_DIGIT_4,
                          HAL_MAX7219_COMMAND_CODE_B_FONT_4);
  HAL_MAX7219_SendMessage(&hmax7219,
                          HAL_MAX7219_ADDRESS_DIGIT_5,
                          HAL_MAX7219_COMMAND_CODE_B_FONT_5);
  HAL_MAX7219_SendMessage(&hmax7219,
                          HAL_MAX7219_ADDRESS_DIGIT_6,
                          HAL_MAX7219_COMMAND_CODE_B_FONT_6);
  HAL_MAX7219_SendMessage(&hmax7219,
                          HAL_MAX7219_ADDRESS_DIGIT_7,
                          HAL_MAX7219_COMMAND_CODE_B_FONT_7);

  while (1)
  {
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

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE2);

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
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
  if (htim->Instance == TIM6) {
    HAL_GPIO_TogglePin(TEST_PIN_GPIO_Port, TEST_PIN_Pin);
    white_alarm++;
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
