#include "can.h"
#include "FreeRTOS.h"

CAN_HandleTypeDef hcan;

void MX_CAN_Init(void) {

  hcan.Instance = CAN1;
  hcan.Init.Prescaler = 16;
  hcan.Init.Mode = CAN_MODE_NORMAL;
  hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan.Init.TimeSeg1 = CAN_BS1_1TQ;
  hcan.Init.TimeSeg2 = CAN_BS2_1TQ;
  hcan.Init.TimeTriggeredMode = DISABLE;
  hcan.Init.AutoBusOff = DISABLE;
  hcan.Init.AutoWakeUp = DISABLE;
  hcan.Init.AutoRetransmission = DISABLE;
  hcan.Init.ReceiveFifoLocked = DISABLE;
  hcan.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan) != HAL_OK) {
    Error_Handler();
  }
  // filters
  CAN_FilterTypeDef canfilter = {0};
  canfilter.FilterActivation = CAN_FILTER_ENABLE;
  canfilter.SlaveStartFilterBank = 14;
  canfilter.FilterBank = 0;
  canfilter.FilterFIFOAssignment = CAN_FILTER_FIFO0;
  canfilter.FilterIdHigh = 0x0000;
  canfilter.FilterIdLow = 0x0000;
  canfilter.FilterMaskIdHigh = 0x0000;
  canfilter.FilterMaskIdLow = 0x0000;
  canfilter.FilterMode = CAN_FILTERMODE_IDMASK;
  canfilter.FilterScale = CAN_FILTERSCALE_32BIT;
  HAL_CAN_ConfigFilter(&hcan, &canfilter);

  // enable interrupts
  HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING | CAN_IT_ERROR | CAN_IT_ERROR_WARNING |
                           CAN_IT_ERROR_PASSIVE | CAN_IT_BUSOFF | CAN_IT_LAST_ERROR_CODE |
                           CAN_IT_TX_MAILBOX_EMPTY | CAN_IT_TX_MAILBOX_EMPTY);
  HAL_CAN_Start(&hcan);
}

void HAL_CAN_MspInit(CAN_HandleTypeDef *canHandle) {

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if (canHandle->Instance == CAN1) {

    __HAL_RCC_CAN1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitStruct.Pin = GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // NVIC
    HAL_NVIC_SetPriority(USB_HP_CAN1_TX_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY + 1,
configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY + 1);
    HAL_NVIC_EnableIRQ(USB_HP_CAN1_TX_IRQn);
    HAL_NVIC_SetPriority(USB_LP_CAN1_RX0_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY + 1,
configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY + 1);
    HAL_NVIC_EnableIRQ(USB_LP_CAN1_RX0_IRQn);
    HAL_NVIC_SetPriority(CAN1_RX1_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY + 1,
configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY + 1);
    HAL_NVIC_EnableIRQ(CAN1_RX1_IRQn);
    HAL_NVIC_SetPriority(CAN1_SCE_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY + 1,
configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY + 1);
    HAL_NVIC_EnableIRQ(CAN1_SCE_IRQn);
  }
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef *canHandle) {

  if (canHandle->Instance == CAN1) {

    __HAL_RCC_CAN1_CLK_DISABLE();

    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_11 | GPIO_PIN_12);
    HAL_NVIC_DisableIRQ(USB_HP_CAN1_TX_IRQn);
    HAL_NVIC_DisableIRQ(USB_LP_CAN1_RX0_IRQn);
    HAL_NVIC_DisableIRQ(CAN1_RX1_IRQn);
    HAL_NVIC_DisableIRQ(CAN1_SCE_IRQn);
  }
}
