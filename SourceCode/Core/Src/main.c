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
#include "software_timer.h"
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
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_TIM2_Init(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
void display7SEG(int num);
void update7SEG(int index);
void updateClockBuffer();

void updateLEDMatrix(int* index,uint8_t* matrix_flag);
void display_row(uint8_t data);
void reset_all_row();

const int MAX_LED = 4;
int index_led = 0;
int led_buffer[4] = {1, 2, 5, 9};
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void display7SEG(int num) {
	int array[10][7] = {
		{0, 0, 0, 0, 0, 0, 1}, 	//0
		{1, 0, 0, 1, 1, 1, 1},  //1
		{0, 0, 1, 0, 0, 1, 0},  //2
		{0, 0, 0, 0, 1, 1, 0},  //3
		{1, 0, 0, 1, 1, 0, 0},	//4
		{0, 1, 0, 0, 1, 0, 0},  //5
		{0, 1, 0, 0, 0, 0, 0}, 	//6
		{0, 0, 0, 1, 1, 1, 1},	//7
		{0, 0, 0, 0, 0, 0, 0}, 	//8
		{0, 0, 0, 0, 1, 0, 0}   //9
	};
	HAL_GPIO_WritePin(SEG0_GPIO_Port, SEG0_Pin, array[num][0]);
	HAL_GPIO_WritePin(SEG1_GPIO_Port, SEG1_Pin, array[num][1]);
	HAL_GPIO_WritePin(SEG2_GPIO_Port, SEG2_Pin, array[num][2]);
	HAL_GPIO_WritePin(SEG3_GPIO_Port, SEG3_Pin, array[num][3]);
	HAL_GPIO_WritePin(SEG4_GPIO_Port, SEG4_Pin, array[num][4]);
	HAL_GPIO_WritePin(SEG5_GPIO_Port, SEG5_Pin, array[num][5]);
	HAL_GPIO_WritePin(SEG6_GPIO_Port, SEG6_Pin, array[num][6]);

}
//// Exercise 2
//void update_display(int* display_flag){
//	switch(*display_flag){
//		case 0:{
//			(*display_flag)++;
//			HAL_GPIO_WritePin(GPIOA, EN0_Pin, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(GPIOA, EN1_Pin, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(GPIOA, EN2_Pin, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(GPIOA, EN3_Pin, GPIO_PIN_SET);
//			display7SEG(1);
//			break;
//		}
//		case 1:{
//			(*display_flag)++;
//			HAL_GPIO_WritePin(GPIOA, EN0_Pin, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(GPIOA, EN1_Pin, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(GPIOA, EN2_Pin, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(GPIOA, EN3_Pin, GPIO_PIN_SET);
//			display7SEG(2);
//			break;
//		}
//		case 2:{
//			(*display_flag)++;
//			HAL_GPIO_WritePin(GPIOA, EN0_Pin, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(GPIOA, EN1_Pin, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(GPIOA, EN2_Pin, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(GPIOA, EN3_Pin, GPIO_PIN_SET);
//			display7SEG(3);
//			break;
//		}
//		case 3:{
//			(*display_flag) = 0;
//			HAL_GPIO_WritePin(GPIOA, EN0_Pin, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(GPIOA, EN1_Pin, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(GPIOA, EN2_Pin, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(GPIOA, EN3_Pin, GPIO_PIN_RESET);
//			display7SEG(0);
//			break;
//		}
//		default:{
//			break;
//		}
//	}
//}
void update7SEG(int index){
    switch (index){
        case 0:
            //Display the first 7SEG with led_buffer[0]
        	HAL_GPIO_WritePin(GPIOA, EN0_Pin, GPIO_PIN_RESET);
        	HAL_GPIO_WritePin(GPIOA, EN1_Pin, GPIO_PIN_SET);
        	HAL_GPIO_WritePin(GPIOA, EN2_Pin, GPIO_PIN_SET);
        	HAL_GPIO_WritePin(GPIOA, EN3_Pin, GPIO_PIN_SET);
        	display7SEG(led_buffer[index]);

            break;
        case 1:
            //Display the second 7SEG with led_buffer[1]
        	HAL_GPIO_WritePin(GPIOA, EN0_Pin, GPIO_PIN_SET);
        	HAL_GPIO_WritePin(GPIOA, EN1_Pin, GPIO_PIN_RESET);
        	HAL_GPIO_WritePin(GPIOA, EN2_Pin, GPIO_PIN_SET);
        	HAL_GPIO_WritePin(GPIOA, EN3_Pin, GPIO_PIN_SET);
        	display7SEG(led_buffer[index]);

            break;
        case 2:
            //Display the third 7SEG with led_buffer[2]
        	HAL_GPIO_WritePin(GPIOA, EN0_Pin, GPIO_PIN_SET);
        	HAL_GPIO_WritePin(GPIOA, EN1_Pin, GPIO_PIN_SET);
          	HAL_GPIO_WritePin(GPIOA, EN2_Pin, GPIO_PIN_RESET);
         	HAL_GPIO_WritePin(GPIOA, EN3_Pin, GPIO_PIN_SET);
  	      	display7SEG(led_buffer[index]);

            break;
        case 3:
            //Display the forth 7SEG with led_buffer[3]
        	HAL_GPIO_WritePin(GPIOA, EN0_Pin, GPIO_PIN_SET);
        	HAL_GPIO_WritePin(GPIOA, EN1_Pin, GPIO_PIN_SET);
        	HAL_GPIO_WritePin(GPIOA, EN2_Pin, GPIO_PIN_SET);
        	HAL_GPIO_WritePin(GPIOA, EN3_Pin, GPIO_PIN_RESET);
        	display7SEG(led_buffer[index]);

            break;
        default:
            break;
    }
}
void updateClockBuffer(){
	led_buffer[3]++;
	if(led_buffer[3]>=10){
		led_buffer[3] = 0;
		led_buffer[2]++;
	}
	if(led_buffer[2]>=6){
		led_buffer[1]++;
		led_buffer[2] =0;
	}
	if(led_buffer[1]>=10){
		led_buffer[0]++;
		led_buffer[1] =0;
	}
	if(led_buffer[0] == 2 && led_buffer[1] == 4){
		led_buffer[0] = 0;
		led_buffer[1] = 0;
	}
}

//Exercise 9
uint16_t col_trigger[] = {ENM0_Pin, ENM1_Pin, ENM2_Pin, ENM3_Pin, ENM4_Pin, ENM5_Pin, ENM6_Pin, ENM7_Pin};
uint16_t row_trigger[] = {ROW0_Pin, ROW1_Pin, ROW2_Pin, ROW3_Pin, ROW4_Pin, ROW5_Pin, ROW6_Pin, ROW7_Pin};
const int MAX_LED_MATRIX = 8;
int index_led_matrix = 0;
uint8_t matrix_buffer[8] = {0x00,0x18,0x24,0x24,0x3C,0x24,0x24,0x24};

void display_row(uint8_t data){
	for(int i = 0; i<MAX_LED_MATRIX; i++){
		HAL_GPIO_WritePin(GPIOA, col_trigger[i], !(data&0x80));
		data = data<<1;
	}
}

void reset_all_row(){
	for(int i = 0; i<MAX_LED_MATRIX; i++){
		HAL_GPIO_WritePin(GPIOB, row_trigger[i], SET);
	}
}


void updateLEDMatrix(int* matrix_flag,uint8_t* matrix_buffer){
    switch (*matrix_flag){
        case 0:{
        	(*matrix_flag)++;
        	reset_all_row();
        	HAL_GPIO_WritePin(GPIOB, ROW0_Pin, 0);
        	display_row(matrix_buffer[0]);
        	break;
        }
        case 1:{
        	(*matrix_flag)++;
        	reset_all_row();
        	HAL_GPIO_WritePin(GPIOB, ROW1_Pin, 0);
        	display_row(matrix_buffer[1]);
        	break;
        }
        case 2:{
        	(*matrix_flag)++;
        	reset_all_row();
        	HAL_GPIO_WritePin(GPIOB, ROW2_Pin, 0);
        	display_row(matrix_buffer[2]);
        	break;
        }
        case 3:{
        	(*matrix_flag)++;
        	reset_all_row();
        	HAL_GPIO_WritePin(GPIOB, ROW3_Pin, 0);
        	display_row(matrix_buffer[3]);
        	break;
        }
        case 4:{
        	(*matrix_flag)++;
        	reset_all_row();
        	HAL_GPIO_WritePin(GPIOB, ROW4_Pin, 0);
        	display_row(matrix_buffer[4]);
        	break;
        }
        case 5:{
        	(*matrix_flag)++;
        	reset_all_row();
        	HAL_GPIO_WritePin(GPIOB, ROW5_Pin, 0);
        	display_row(matrix_buffer[5]);
        	break;
        }
        case 6:{
        	(*matrix_flag)++;
        	reset_all_row();
        	HAL_GPIO_WritePin(GPIOB, ROW6_Pin, 0);
        	display_row(matrix_buffer[6]);
        	break;
        }
        case 7:{
        	(*matrix_flag) = 0;
        	reset_all_row();
        	HAL_GPIO_WritePin(GPIOB, ROW7_Pin, 0);
        	display_row(matrix_buffer[7]);
        	break;
        }
        default:
            break;
    }
}

//Exercise 10
uint8_t stored_buffer[8] = {0x00,0x18,0x24,0x24,0x3C,0x24,0x24,0x24};
void update_LED_buffer(uint8_t data[MAX_LED_MATRIX]){
	for(int i = 0; i<MAX_LED_MATRIX; i++){
		data[i] = data[i]<<1;
	}
}

void reset_buffer(){
	for(int i = 0; i<MAX_LED_MATRIX; i++){
		matrix_buffer[i] = stored_buffer[i];
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
  MX_TIM2_Init();
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */

  HAL_TIM_Base_Start_IT (& htim2 ) ;
  setTimer1(50);	// 7-Segment LED
  setTimer2(100);	// 2 LED_RED
  setTimer3(100);
  setTimer4(500);
//  int display_flag =0;

  int matrix_flag = 0;		//For exercise 9
  int shift_cycle_flag =0;	//For exercise 10
  int hour = 12, minute = 59, second = 50;		// For exercise 5
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  //Excercise 2
//	  if(timer1_flag == 1){
//		  setTimer1(50);
//		  update_display(&display_flag);
//	  }
//	  if(timer2_flag == 1){
//		  setTimer2(100);
//		  HAL_GPIO_TogglePin(GPIOA, DOT_Pin);
//		  HAL_GPIO_TogglePin(GPIOA, LED_Pin);
//	  }
//  }
	  //Exercise 5-7-8
	  if(timer1_flag == 1){
	  		setTimer1(25);
	  		update7SEG(index_led++);
	  		if(index_led > 3)	index_led = 0;

	  		//Exercise 10
	  		updateLEDMatrix(&matrix_flag, matrix_buffer);
	  }
	 if(timer2_flag == 1){
	 	 setTimer2(100);
	 	 HAL_GPIO_TogglePin(GPIOA, DOT_Pin);
	 	 HAL_GPIO_TogglePin(GPIOA, LED_Pin);
	 }
	 if(timer3_flag == 1){
		 setTimer3(100);
		 second++;

		 // This function call for Exercise 9
//		 updateLEDMatrix(&matrix_flag);
	 }
	 if(second >=60){
		 second = 0;
		 minute++;
	 }
	 if(minute >=60){
		 minute = 0;
		 hour++;
	 }
	 if(hour >=24){
		 hour = 0;
	 }
	 int temp_hour = led_buffer[0]*10 + led_buffer[1];
	 int temp_minute  = led_buffer[2]*10 +led_buffer[3];
	 if(temp_hour != hour || temp_minute != minute){
		 updateClockBuffer();
	 }

	 if(timer4_flag == 1){
		 setTimer4(500);
		 shift_cycle_flag++;
		 update_LED_buffer(matrix_buffer);

		 if(shift_cycle_flag>=8){
			 shift_cycle_flag = 0;
			 reset_buffer();
		 }
	 }
  /* USER CODE END 3 */
}
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
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7999;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 9;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

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
  HAL_GPIO_WritePin(GPIOA, ENM0_Pin|ENM1_Pin|DOT_Pin|LED_Pin
                          |EN0_Pin|EN1_Pin|EN2_Pin|EN3_Pin
                          |ENM2_Pin|ENM3_Pin|ENM4_Pin|ENM5_Pin
                          |ENM6_Pin|ENM7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, SEG0_Pin|SEG1_Pin|SEG2_Pin|ROW2_Pin
                          |ROW3_Pin|ROW4_Pin|ROW5_Pin|ROW6_Pin
                          |ROW7_Pin|SEG3_Pin|SEG4_Pin|SEG5_Pin
                          |SEG6_Pin|ROW0_Pin|ROW1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : ENM0_Pin ENM1_Pin DOT_Pin LED_Pin
                           EN0_Pin EN1_Pin EN2_Pin EN3_Pin
                           ENM2_Pin ENM3_Pin ENM4_Pin ENM5_Pin
                           ENM6_Pin ENM7_Pin */
  GPIO_InitStruct.Pin = ENM0_Pin|ENM1_Pin|DOT_Pin|LED_Pin
                          |EN0_Pin|EN1_Pin|EN2_Pin|EN3_Pin
                          |ENM2_Pin|ENM3_Pin|ENM4_Pin|ENM5_Pin
                          |ENM6_Pin|ENM7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : SEG0_Pin SEG1_Pin SEG2_Pin ROW2_Pin
                           ROW3_Pin ROW4_Pin ROW5_Pin ROW6_Pin
                           ROW7_Pin SEG3_Pin SEG4_Pin SEG5_Pin
                           SEG6_Pin ROW0_Pin ROW1_Pin */
  GPIO_InitStruct.Pin = SEG0_Pin|SEG1_Pin|SEG2_Pin|ROW2_Pin
                          |ROW3_Pin|ROW4_Pin|ROW5_Pin|ROW6_Pin
                          |ROW7_Pin|SEG3_Pin|SEG4_Pin|SEG5_Pin
                          |SEG6_Pin|ROW0_Pin|ROW1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	timerRun();
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
