#include "stm32f103xx_flash_w25q128jv.h"

void SPI_Conf(void);
void GPIO_Conf(void);
void Flash_rcv_data(void);
void Flash_sendData(void);
void W25_Flash_read_status_reg(void);
	

int main(void)
{
	uint8_t rcvBuff[10] = {0};
	char sendBuff[] = "VedRo" ;
	SPI_Conf();
	GPIO_Conf();
		W25_flash_enable(SPI1);
		W25_flash_readMemory(SPI1,rcvBuff,10,W25_memBlock2);
		
		W25_Flash_read_status_reg();
		W25_flash_enable(SPI1);
		W25_flash_eraseblock(SPI1,W25_memBlock2);
		for(int ff = 0 ; ff < 20 ; ff++)
		{
							for(int de = 0 ; de < 2500 ; de++)
							delay();
		}
		W25_Flash_read_status_reg();
		W25_flash_enable(SPI1);
		W25_flash_readMemory(SPI1,rcvBuff,10,W25_memBlock2);
	
		Flash_sendData();
		
		W25_flash_enable(SPI1);
		W25_flash_readMemory(SPI1,rcvBuff,10,W25_memBlock2);
	
	GPIO_PinEnDn(GPIOC,13,ENABLE);
}




void GPIO_Conf(void)
{
	GPIO_Handle_t gpiopin;
	
	gpiopin.pGPIOx = GPIOA;
	gpiopin.GPIO_PinConfig.GPIO_ModeInOut = GPIO_OUT_50MHZ;
	gpiopin.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN_OUT_PP;
	
	GPIO_PeriClockControl(GPIOA,ENABLE);
	
	gpiopin.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_7;
	GPIO_Init(&gpiopin);
	
	gpiopin.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_6;
	GPIO_Init(&gpiopin);
	
	gpiopin.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
	GPIO_Init(&gpiopin);
	
	gpiopin.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_4;
	GPIO_Init(&gpiopin);
	
}

void SPI_Conf(void)
{
			
	SPI_Handle_t SPI_Flash;

	SPI_Flash.pSPIx = SPI1;
	SPI_Flash.spiconf.BaudRate = SPI_BRR_Fpclk_256;
	SPI_Flash.spiconf.Mode = SPI_MODE_Master;
	SPI_Flash.spiconf.SlvManage = SPI_SlvManage_Hard;
	
	SPI_PeriClockControl(SPI1,ENABLE);
	
	SPI_Init(&SPI_Flash);
	
}

void W25_Flash_read_status_reg(void)
{
	uint8_t reg;
	
										delay();
	SPI_Enable(SPI1);
		SPI_SendByte(SPI1,W25_read_status_reg1);
		SPI_ReceiveData(SPI1,&reg,1);
	SPI_Disable(SPI1);
										delay();
	SPI_Enable(SPI1);
		SPI_SendByte(SPI1,W25_read_status_reg2);
		SPI_ReceiveData(SPI1,&reg,1);
	SPI_Disable(SPI1);
										delay();
	SPI_Enable(SPI1);
		SPI_SendByte(SPI1,W25_read_status_reg3);
		SPI_ReceiveData(SPI1,&reg,1);
	SPI_Disable(SPI1);
	
}

void Flash_rcv_data(void)
{
	 uint8_t mem_addr;
	uint8_t data[10] = {0};
																delay();
	//MEMORY_RCV_DATA
	SPI_Enable(SPI1);
			SPI_SendByte(SPI1,W25_read_data);

												mem_addr = (W25_memBlock2>>16 & (0xFF));
										SPI_SendByte(SPI1,mem_addr);
												mem_addr = (W25_memBlock2>>8 & (0xFF));
										SPI_SendByte(SPI1,mem_addr);
												mem_addr = (W25_memBlock2 & (0xFF));
										SPI_SendByte(SPI1,(mem_addr));	

			SPI_ReceiveData(SPI1,data,5);
	SPI_Disable(SPI1);
	
	delay();

}

void Flash_sendData(void)
{
	uint8_t senddata[] = "VedRo";
	 uint8_t mem_addr;
		delay();
	SPI_Enable(SPI1);
		W25_flash_enable(SPI1);
	SPI_Disable(SPI1);
		delay();
		SPI_Enable(SPI1);
			SPI_SendByte(SPI1,W25_page_program);

												mem_addr = (W25_memBlock2>>16 & (0xFF));
										SPI_SendByte(SPI1,mem_addr);
												mem_addr = (W25_memBlock2>>8 & (0xFF));
										SPI_SendByte(SPI1,mem_addr);
												mem_addr = (W25_memBlock2 & (0xFF));
										SPI_SendByte(SPI1,(mem_addr));		
		
			SPI_SendData(SPI1,senddata,sizeof(senddata));
	SPI_Disable(SPI1);
	
}
