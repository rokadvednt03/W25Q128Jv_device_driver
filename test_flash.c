#include "stm32f103xx_flash_w25q128jv.h"


int main(void)
{
	uint8_t data = W25_write_Enable;
	char a[] = "hello world";
		GPIO_Handle_t gpiopin;
	SPI_Handle_t SPI_Flash;
	gpiopin.pGPIOx = GPIOA;
	gpiopin.GPIO_PinConfig.GPIO_ModeInOut = GPIO_OUT_50MHZ;
	gpiopin.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN_OUT_PP;
	
	SPI_Flash.pSPIx = SPI1;
	SPI_Flash.spiconf.BaudRate = SPI_BRR_Fpclk_256;
	SPI_Flash.spiconf.Mode = SPI_MODE_Master;
	SPI_Flash.spiconf.SlvManage = SPI_SlvManage_Hard;
	
	GPIO_PeriClockControl(GPIOA,ENABLE);
	SPI_PeriClockControl(SPI1,ENABLE);
	
	SPI_Init(&SPI_Flash);
	
	gpiopin.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_7;
	GPIO_Init(&gpiopin);
	
	gpiopin.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_6;
	GPIO_Init(&gpiopin);
	
	gpiopin.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
	GPIO_Init(&gpiopin);
	
	gpiopin.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_4;
	GPIO_Init(&gpiopin);
		
	flash_enable(SPI1);
}
