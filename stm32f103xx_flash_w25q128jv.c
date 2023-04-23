#include "stm32f103xx_flash_w25q128jv.h"

void W25_flash_enable(SPI_TypeDef *pSPIx)
{
	SPI_Enable(pSPIx);
	SPI_SendByte(pSPIx,W25_write_Enable);
	SPI_Disable(pSPIx);
}

uint8_t W25_flash_read_statusREG(SPI_TypeDef *pSPIx ,uint8_t RegADDR)
{
	uint8_t data ;
	SPI_Enable(pSPIx);
	SPI_SendByte(pSPIx,RegADDR);
	SPI_ReceiveData(SPI1,&data,1);
	SPI_Disable(SPI1);
	GPIO_PinEnDn(GPIOC,13,ENABLE);
	return data;
}

void W25_flash_erase(SPI_TypeDef *pSPIx)
{
	SPI_Enable(pSPIx);
	SPI_SendByte(pSPIx,W25_chip_erase_01);
	SPI_SendByte(pSPIx,W25_chp_erase_02);
	SPI_Disable(pSPIx);
}

void W25_flash_reset(SPI_TypeDef *pSPIx)
{
	SPI_Enable(pSPIx);
	SPI_SendByte(pSPIx,W25_reset1);
	SPI_Disable(pSPIx);
	delay();
	SPI_Enable(pSPIx);
	SPI_SendByte(pSPIx,W25_reset2);
	SPI_Disable(pSPIx);
	
}

void SPI_SendByte(SPI_TypeDef *pSPIx,uint8_t byte)
{
	uint8_t data = byte;
	SPI_SendData(pSPIx,&data,1);
}


void delay(void)
{
	for(int i = 0 ; i < 50 ; i++);
}

