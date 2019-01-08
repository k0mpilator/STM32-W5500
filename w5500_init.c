/*
 * w5500_init.c
 *
 *  Created on: 8 янв. 2019 г.
 *      Author: kompilator
 */

#include <stdio.h>
#include <stdarg.h>

#include "stm32f10x_conf.h"
#include "Ethernet/wizchip_conf.h"
#include "mcu_handler.h"
#include "w5500_init.h"
#include "Ethernet/socket.h"

#define DHCP_SOCKET     0
#define DNS_SOCKET      1
#define HTTP_SOCKET     2

static uint8_t wizchip_rw(uint8_t byte)
{
	/*!< Loop while DR register in not emplty */
	while (SPI_I2S_GetFlagStatus(W5500_SPI, SPI_I2S_FLAG_TXE) == RESET);

	/*!< Send byte through the SPI1 peripheral */
	SPI_I2S_SendData(W5500_SPI, byte);

	/*!< Wait to receive a byte */
	while (SPI_I2S_GetFlagStatus(W5500_SPI, SPI_I2S_FLAG_RXNE) == RESET);

	/*!< Return the byte read from the SPI bus */
	return SPI_I2S_ReceiveData(W5500_SPI);
}

static void  wizchip_select(void)
{
	GPIO_ResetBits(W5500_CS_GPIO_PORT, W5500_CS_PIN);
}

static void  wizchip_deselect(void)
{
	GPIO_SetBits(W5500_CS_GPIO_PORT, W5500_CS_PIN);
}

static void  wizchip_write(uint8_t wb)
{
	wizchip_rw(wb);
}

static uint8_t wizchip_read(void)
{
	return wizchip_rw(0xFF);
}

void W5500_Init(void)
{
	/*!< Deselect the FLASH: Chip Select high */
	wizchip_deselect();

	// Wiznet
	reg_wizchip_cs_cbfunc(wizchip_select, wizchip_deselect);
	reg_wizchip_spi_cbfunc(wizchip_read, wizchip_write);

	/* wizchip initialize*/
	uint8_t tmp;
	uint8_t memsize[2][8] = { {2,2,2,2,2,2,2,2},{2,2,2,2,2,2,2,2}};

	if(ctlwizchip(CW_INIT_WIZCHIP,(void*)memsize) == -1)
	{
		myprintf("WIZCHIP Initialized fail.\r\n");
		return;
	}

	/* PHY link status check */
	do {
		if(ctlwizchip(CW_GET_PHYLINK, (void*)&tmp) == -1) {
			;
			myprintf("Unknown PHY Link status.\r\n");
			return;
		}
	} while (tmp == PHY_LINK_OFF);
}

void display_Net_Info()
{
	wiz_NetInfo gWIZNETINFO;

	ctlnetwork(CN_GET_NETINFO, (void*) &gWIZNETINFO);
	myprintf("MAC: %02X:%02X:%02X:%02X:%02X:%02X\r\n", gWIZNETINFO.mac[0], gWIZNETINFO.mac[1], gWIZNETINFO.mac[2], gWIZNETINFO.mac[3], gWIZNETINFO.mac[4], gWIZNETINFO.mac[5]);
	myprintf("IP: %d.%d.%d.%d\r\n", gWIZNETINFO.ip[0], gWIZNETINFO.ip[1], gWIZNETINFO.ip[2], gWIZNETINFO.ip[3]);
	myprintf("GW: %d.%d.%d.%d\r\n", gWIZNETINFO.gw[0], gWIZNETINFO.gw[1], gWIZNETINFO.gw[2], gWIZNETINFO.gw[3]);
	myprintf("SN: %d.%d.%d.%d\r\n", gWIZNETINFO.sn[0], gWIZNETINFO.sn[1], gWIZNETINFO.sn[2], gWIZNETINFO.sn[3]);
	myprintf("DNS: %d.%d.%d.%d\r\n", gWIZNETINFO.dns[0], gWIZNETINFO.dns[1], gWIZNETINFO.dns[2], gWIZNETINFO.dns[3]);
}

void Net_Conf()
{
	wiz_NetInfo gWIZNETINFO = {
		{ 0x0c,0x29,0xab,0x00, 0x00, 0x00 },				// Mac address
		{ 192, 168, 1, 199 },								// IP address
		{ 192, 168, 1, 1},									// Gateway
		{ 255, 255, 255, 0},								// Subnet mask
		{ 8, 8, 8, 0},										// DNS Server
	};

	ctlnetwork(CN_SET_NETINFO, (void*) &gWIZNETINFO);

	display_Net_Info();
}
//------------------------------------------------------
void Net_Conn()
{
	myprintf("Creating socket...\r\n");
	uint8_t http_socket = HTTP_SOCKET;
	uint8_t code = socket(http_socket, Sn_MR_TCP, 10888, 0x00);
	if(code != http_socket) {
		myprintf("socket() failed, code = %d\r\n", code);
		return;
	}

	myprintf("Socket created, connecting...\r\n");
	uint8_t addr[]={192,168,1,148};
	code = connect(http_socket, addr, 49121);
	if(code != SOCK_OK) {
		myprintf("connect() failed, code = %d\r\n", code);
	    close(http_socket);
	    return;
	}

}
//-----------------------------------------------------
void Delay(volatile unsigned int nCount)
{
	for(; nCount!= 0;nCount--);
}

void myprintf(char *fmt, ...)
{
	va_list arg_ptr;
	char etxt[128]; // buffer size
	uint8_t i;

	va_start(arg_ptr, fmt);
	vsprintf(etxt, fmt, arg_ptr);
	va_end(arg_ptr);

	for (i = 0; etxt[i] != '\0'; i++) {
		USART_SendData(USART1, (u8) etxt[i]);
		while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET); // Tx buffer empty
	}
}
