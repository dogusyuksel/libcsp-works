#include "main.h"
#include "FreeRTOS.h"
#include "adc.h"
#include "can.h"
#include "dma.h"
#include "gpio.h"
#include "i2c.h"
#include "printf.h"
#include "rtc.h"
#include "task.h"
#include "cspcan.h"
#include "usart.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "csp/csp.h"

void SystemClock_Config(void);
void uart_log(const char *format, ...);

void uart_log(const char *format, ...) {
  va_list arguments;
  char buffer[128] = {0};

  va_start(arguments, format);
  vsnprintf_(buffer, sizeof(buffer), format, arguments);
  va_end(arguments);

  if (strlen(buffer) == 0) {
    return;
  }

  HAL_UART_Transmit(&huart3, (uint8_t *)buffer, strlen((char *)buffer),
                    strlen((char *)buffer));
}



void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
  if (GPIO_Pin == GPIO_PIN_1) {
    uart_log("PPS\n");
  }
  portYIELD_FROM_ISR(pdTRUE);
}

int main(void) {

  HAL_Init();

  SystemClock_Config();

  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_CAN_Init();
  MX_USART3_UART_Init();

  uart_log("application started!\n");

  csp_init();
  xTaskCreate(task_csp_router, "csp_router", 512, NULL, 2, NULL);
  xTaskCreate(task_csp_server, "csp_server", 2048, NULL, 2, NULL);

  if (can_add_interface(LOCAL_NODE_ID, CSP_NETMASK) != 0) {
    uart_log("Failed to add CSP CAN interface\r\n");
  } else {
    uart_log("CSP Initialised Succesfully\r\n");
  }

  vTaskStartScheduler();

  while (1) {
  }
}

void SystemClock_Config(void) {
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  RCC_OscInitStruct.OscillatorType =
      RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK |
                                RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC | RCC_PERIPHCLK_ADC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
    Error_Handler();
  }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {

  if (htim->Instance == TIM1) {
    HAL_IncTick();
  }
}

void Error_Handler(void) {
  __disable_irq();
  while (1) {
  }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line) {}
#endif /* USE_FULL_ASSERT */
