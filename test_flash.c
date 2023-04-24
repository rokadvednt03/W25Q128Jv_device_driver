#include "stm32f103xx_flash_w25q128jv.h"
void SPI_Conf(void);
void GPIO_Conf(void);
void Flash_rcv_data(void);
void Flash_sendData(void);
void W25_Flash_read_status_reg(void);
	
	extern uint8_t data[] = "hello"  ;
	extern uint32_t len = sizeof(data);

int main(void)
{
	SPI_Conf();
	GPIO_Conf();
	
/*		W25_Flash_read_status_reg();
																delay();*/
	/*	W25_flash_reset(SPI1);
																delay();
		W25_Flash_read_status_reg();
																delay();*/

		Flash_sendData();
																delay();
		W25_Flash_read_status_reg();
																delay();
		Flash_rcv_data();
																delay();
		W25_Flash_read_status_reg();
																delay();
		Flash_rcv_data();
																delay();
	
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

void Flash_rcv_data(void)
{
	 uint8_t mem_addr;
/*	delay();
		SPI_Enable(SPI1);
		W25_flash_enable(SPI1);
	SPI_Disable(SPI1);
	delay();*/
		//W25_Flash_read_status_reg();
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
	uint8_t senddata[] = "Hello";
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
