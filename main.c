#include "stm32f4xx.h"
﻿

static void MX_USART2_UART_Init (void)
{
huart2.Instance = USART2;
huart2.Init.BaudRate = 115200;
huart2.Init.WordLength UART_WORDLENGTH_8B;
huart2.Init.StopBits UART_STOPBITS_1;
huart2.Init.Parity = UART_PARITY_NONE;
huart2.Init.Mode = UART_MODE_TX_RX;
huart2.Init.HwFlowCt1= UART_HWCONTROL_NONE;
huart2.Init.OverSampling = UART_OVERSAMPLING_16;
if (HAL UART_Init(&huart2) != HAL_OK)
{ Error_Handler(); }
}


static void MX_GPIO_Init(void)
{
GPIO_InitTypeDef GPIO_InitStruct = {0};
/* GPIO Ports Clock Enable */
__HAL_RCC_GPIOH_CLK_ENABLE(); 
__HAL_RCC_GPIOA_CLK_ENABLE(); 
__HAL_RCC_GPIOD_CLK_ENABLE();

/*Configure GPIO pin Output Level */ 
HAL_GPIO_WritePin(GPIOD,GPIO_PIN_15, GPIO_PIN_RESET);

/*Configure GPIO pin: PAL */
GPIO_InitStruct.Pin - GPIO_PIN_1;
GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
GPIO_InitStruct.Pull GPIO_NOPULL;
HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
/*Configure GPIO pin: PD15 */
GPIO_InitStruct.Pin = GPIO_PIN_15;
GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; 
GPIO_InitStruct.Pull = GPIO_NOPULL;
GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
HAL_GPIO_Init (GPIOD, &GPIO_InitStruct);

/*EXTI interrupt init*/
HAL_NVIC_Set_Priority(EXTI1_IRQn, 0, 0); 
HAL_NVIC_EnableIRQ (EXTI1_IRQn);
}


void GSM_SendSms(char * PhoneNumber, char * texto) {
// Preparing config message
char prefix = "AT+CMGS=\"";
char full_message = malloc(strlen(prefix) +strlen(PhoneNumber)); 
strcpy(full_message, prefix);
strcat(full_message, PhoneNumber);
strcat(full_message, "\"\r\n");
// Sending config message
HAL_UART_Transmit(&huart2, full massage, strlen(full_message));
// Waiting for confiramtion
uint8_t RX_BUFFER [10]="";
while (RX_BUFFER[0]=>')
HAL_UART_Receive(&huart2, RX_BUFFER, 10);
// Preparing Alert message
full message="";
strcpy(full_message, texto);
strcat(full_message, "\"\r\n");
// Sending Alert message
HAL_UART_Transmit(&huart2, full_massage, strlen(full_message));
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);
Intrusion_Detected=1;
HAL_Delay(10);
}


int main() {
HAL_Init();
SystemClock_Config();
MX_GPIO_Init();
MX_USART2_UART_Init();
	while (1) {
		if Intrusion_Detected) {
		GSM_SendSms("MyPhoneNumber","Alert Intrusion Detected");
		Intrusion_Detected = 0;
   			}
		}
}
