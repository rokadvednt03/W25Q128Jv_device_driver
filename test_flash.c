#include "stm32f103xx_flash_w25q128jv.h"
#include "stm32f103xx_i2c.h"

void SPI_Conf(void);
void GPIO_Conf(void);
void W25_Flash_read_status_reg(void);


int main(void)
{
	char rcvBuff[10] = {0};
	char sendBuff[] = "JaySwaminarayan" ;
	SPI_Conf();
	GPIO_Conf();

		W25_flash_readMemory(SPI1,(uint8_t*)rcvBuff,20,W25_memBlock2);
		
		W25_Flash_read_status_reg();
	
		W25_flash_eraseblock(SPI1,W25_memBlock2);
		W25_Flash_read_status_reg();
		W25_flash_readMemory(SPI1,(uint8_t*)rcvBuff,20,W25_memBlock2);

		W25_flash_WriteMemory(SPI1,(uint8_t*)sendBuff,sizeof(sendBuff),W25_memBlock2);
		W25_flash_readMemory(SPI1,(uint8_t*)rcvBuff,20,W25_memBlock2);
		
	
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

