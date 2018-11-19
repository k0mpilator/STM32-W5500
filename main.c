#include <stdio.h>
#include "mcu_handler.h"
#include "w5500_init.h"

int main(int argc, char* argv[])
{
	RCC_Configuration();
	USART1_Configuration();
	W5500_SPI_Init();

	W5500_Init();	
	Net_Conf();

	while(1)
	{
	}
}
