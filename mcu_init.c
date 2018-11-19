#include "stm32f10x_conf.h"
#include "w5500_init.h"
#include "mcu_handler.h"

void RCC_Configuration(void)
{
	/* SPI2 Clock Enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

	/* GPIOA, GPIOB, UART1 Clock Enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_USART1, ENABLE);
}

void USART1_Configuration(void)
{
	USART_InitTypeDef USART_InitStructure;
	USART_ClockInitTypeDef USART_ClockInitStruct;

	GPIO_InitTypeDef GPIO_InitStructure;

	/* Configure USART Tx as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin =  USART1_TX | USART1_RTS;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Configure USART Rx as input floating */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = USART1_RX | USART1_CTS;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* USARTx configuration ------------------------------------------------------*/
	/* USARTx configured as follow:
	   - BaudRate = 115200 baud
	   - Word Length = 8 Bits
	   - One Stop Bit
	   - No parity
	   - Hardware flow control disabled (RTS and CTS signals)
	   - Receive and transmit enabled
	 */
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_ClockInitStruct.USART_Clock = USART_Clock_Disable;
	USART_ClockInitStruct.USART_CPOL = USART_CPOL_Low;
	USART_ClockInitStruct.USART_CPHA = USART_CPHA_2Edge;
	USART_ClockInitStruct.USART_LastBit = USART_LastBit_Disable;

	/* Configure the USARTx */
	USART_Init(USART1, &USART_InitStructure);
	USART_ClockInit(USART1, &USART_ClockInitStruct);

	/* Enable the USARTx */
	USART_Cmd(USART1, ENABLE);
}

void W5500_SPI_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;

	/*!< Configure W5500_SPI pins: SCK */
	GPIO_InitStructure.GPIO_Pin = W5500_SPI_SCK_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(W5500_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

	/*!< Configure W5500_SPI pins: MOSI */
	GPIO_InitStructure.GPIO_Pin = W5500_SPI_MOSI_PIN;
	GPIO_Init(W5500_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);

	/*!< Configure W5500_SPI pins: MISO */
	GPIO_InitStructure.GPIO_Pin = W5500_SPI_MISO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(W5500_SPI_MISO_GPIO_PORT, &GPIO_InitStructure);

	/*!< Configure W5500_CS_PIN pin: W5500 CS pin */
	GPIO_InitStructure.GPIO_Pin = W5500_CS_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(W5500_CS_GPIO_PORT, &GPIO_InitStructure);

	/*!< SPI configuration */
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;

	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;

	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(W5500_SPI, &SPI_InitStructure);

	/*!< Enable the W5500_SPI  */
	SPI_Cmd(W5500_SPI, ENABLE);

	GPIO_ResetBits(GPIOB, W5500_RESET_PIN);
	Delay(0xEFFFFF); 
	GPIO_SetBits(GPIOB, W5500_RESET_PIN);
}
