
#include "main.h"
#include "stm32f1xx_it.h"

extern DMA_HandleTypeDef hdma_adc1;
extern ADC_HandleTypeDef hadc1;
extern CAN_HandleTypeDef hcan;
extern I2C_HandleTypeDef hi2c1;
extern SPI_HandleTypeDef hspi1;
extern UART_HandleTypeDef huart3;
extern TIM_HandleTypeDef htim4;

void NMI_Handler(void)
{

   while (1)
  {
  }
}

void HardFault_Handler(void)
{

  while (1)
  {
  }
}

void MemManage_Handler(void)
{

  while (1)
  {
  }
}

void BusFault_Handler(void)
{

  while (1)
  {
  }
}

void UsageFault_Handler(void)
{

  while (1)
  {
  }
}

void DebugMon_Handler(void)
{

}

void DMA1_Channel1_IRQHandler(void)
{

  HAL_DMA_IRQHandler(&hdma_adc1);

}

void ADC1_2_IRQHandler(void)
{

  HAL_ADC_IRQHandler(&hadc1);

}

void CAN1_RX1_IRQHandler(void)
{

  HAL_CAN_IRQHandler(&hcan);

}

void CAN1_SCE_IRQHandler(void)
{

  HAL_CAN_IRQHandler(&hcan);

}

void EXTI9_5_IRQHandler(void)
{

  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_7);

}

void TIM4_IRQHandler(void)
{

  HAL_TIM_IRQHandler(&htim4);

}

void I2C1_EV_IRQHandler(void)
{

  HAL_I2C_EV_IRQHandler(&hi2c1);

}

void I2C1_ER_IRQHandler(void)
{

  HAL_I2C_ER_IRQHandler(&hi2c1);

}

void SPI1_IRQHandler(void)
{

  HAL_SPI_IRQHandler(&hspi1);

}

void USART3_IRQHandler(void)
{

  HAL_UART_IRQHandler(&huart3);

}

