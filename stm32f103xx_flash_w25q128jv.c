#include "stm32f103xx_flash_w25q128jv.h"

void W25_flash_enable(SPI_TypeDef *pSPIx)
{
	delay();
	SPI_Enable(pSPIx);
	SPI_SendByte(pSPIx,W25_write_Enable);
	SPI_Disable(pSPIx);
}

uint8_t W25_flash_read_statusREG(SPI_TypeDef *pSPIx ,uint8_t RegADDR)
{
	uint8_t data ;
	delay();
	SPI_Enable(pSPIx);
	SPI_SendByte(pSPIx,RegADDR);
	SPI_ReceiveData(SPI1,&data,1);
	SPI_Disable(SPI1);
	GPIO_PinEnDn(GPIOC,13,ENABLE);
	return data;
}

void W25_flash_erase(SPI_TypeDef *pSPIx)
{
	delay();
	SPI_Enable(pSPIx);
	SPI_SendByte(pSPIx,W25_chip_erase_01);
	SPI_Disable(pSPIx);
}

void W25_flash_reset(SPI_TypeDef *pSPIx)
{
	delay();
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

void W25_flash_eraseblock(SPI_TypeDef *pSPIx , uint32_t memory_addr)
{
	uint8_t memAddr;
	W25_flash_enable(pSPIx);
	delay();
	SPI_Enable(pSPIx);
				SPI_SendByte(pSPIx,W25_block_erase_64K);
										memAddr = ((memory_addr >> 16) & (0xff));
				SPI_SendByte(pSPIx,memAddr);
										memAddr = ((memory_addr >> 8) & (0xff));
				SPI_SendByte(pSPIx,memAddr);
										memAddr = ((memory_addr) & (0xff));
				SPI_SendByte(pSPIx,memAddr);
										
	SPI_Disable(pSPIx);
	w25_erase_call_delay();
}


void W25_flash_WriteMemory(SPI_TypeDef *pSPIx , uint8_t *pTXBuffer , uint32_t len , uint32_t memory_addr)
{
	uint8_t memAddr;
	W25_flash_enable(pSPIx);
	delay();
	SPI_Enable(pSPIx);

				SPI_SendByte(pSPIx,W25_page_program);
										memAddr = ((memory_addr >> 16) & (0xff));
				SPI_SendByte(SPI1,memAddr);
										memAddr = ((memory_addr >> 8) & (0xff));
				SPI_SendByte(SPI1,memAddr);
										memAddr = ((memory_addr) & (0xff));
				SPI_SendByte(SPI1,memAddr);		
				SPI_SendData(pSPIx,pTXBuffer,len);
	SPI_Disable(pSPIx);

}


void W25_flash_readMemory(SPI_TypeDef *pSPIx , uint8_t *pRxBuffer , uint32_t len , uint32_t memory_addr)
{
	uint8_t memAddr;
	W25_flash_enable(pSPIx);
	delay();
	SPI_Enable(pSPIx);
				SPI_SendByte(pSPIx,W25_read_data);
										memAddr = ((memory_addr >> 16) & (0xff));
				SPI_SendByte(pSPIx,memAddr);
										memAddr = ((memory_addr >> 8) & (0xff));
				SPI_SendByte(pSPIx,memAddr);
										memAddr = ((memory_addr) & (0xff));
				SPI_SendByte(pSPIx,memAddr);		
				SPI_ReceiveData(pSPIx,pRxBuffer,len);
	SPI_Disable(pSPIx);
}



void delay(void)
{ 
	int i ;
	for(i = 0 ; i < 81 ; i++);
}



void w25_erase_call_delay(void)
{
	int ff ,de ;
	for( ff = 0 ; ff < 200 ; ff++)
		{
							for( de = 0 ; de < 81 ; de++)
							delay();
		}
}
