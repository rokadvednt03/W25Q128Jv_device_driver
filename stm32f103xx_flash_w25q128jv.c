#include "stm32f103xx_flash_w25q128jv.h"

void flash_enable(SPI_TypeDef *pSPIx)
{
	SPI_SendByte(pSPIx,W25_write_Enable);
}


void SPI_SendByte(SPI_TypeDef *pSPIx,uint8_t byte)
{
	uint8_t data = byte;
	SPI_SendData(pSPIx,&data,1);
}
