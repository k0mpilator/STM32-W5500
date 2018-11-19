
#ifndef __MCU_HANDLER_H__
#define __MCU_HANDLER_H__

#define W5500_SPI                       SPI2
#define W5500_SPI_CLK                   RCC_APB1Periph_SPI2

#define W5500_SPI_SCK_PIN               GPIO_Pin_13	
#define W5500_SPI_SCK_GPIO_PORT         GPIOB
#define W5500_SPI_SCK_GPIO_CLK          RCC_APB2Periph_GPIOB

#define W5500_SPI_MISO_PIN              GPIO_Pin_14
#define W5500_SPI_MISO_GPIO_PORT        GPIOB
#define W5500_SPI_MISO_GPIO_CLK         RCC_APB2Periph_GPIOB

#define W5500_SPI_MOSI_PIN              GPIO_Pin_15
#define W5500_SPI_MOSI_GPIO_PORT        GPIOB
#define W5500_SPI_MOSI_GPIO_CLK         RCC_APB2Periph_GPIOB

#define W5500_CS_PIN                    GPIO_Pin_12
#define W5500_CS_GPIO_PORT              GPIOB
#define W5500_CS_GPIO_CLK               RCC_APB2Periph_GPIOB

#define W5500_RESET_PIN                 GPIO_Pin_9
#define W5500_CS_GPIO_PORT              GPIOB
#define W5500_CS_GPIO_CLK               RCC_APB2Periph_GPIOB

#define USART1_TX						      GPIO_Pin_9	
#define USART1_TX_GPIO_PORT				GPIOA
#define USART1_TX_GPIO_CLK				RCC_APB2Periph_GPIOA

#define USART1_RX						      GPIO_Pin_10
#define USART1_RX_GPIO_PORT				GPIOA
#define USART1_RX_GPIO_CLK				RCC_APB2Periph_GPIOA

#define USART1_CTS						    GPIO_Pin_11
#define USART1_CTS_GPIO_PORT			GPIOA
#define USART1_CTS_GPIO_CLK				RCC_APB2Periph_GPIOA

#define USART1_RTS						    GPIO_Pin_12
#define USART1_RTS_GPIO_PORT			GPIOA
#define USART1_RTS_GPIO_CLK				RCC_APB2Periph_GPIOA

void RCC_Configuration(void);
void USART1_Configuration(void);
void W5500_SPI_Init(void);

#endif
