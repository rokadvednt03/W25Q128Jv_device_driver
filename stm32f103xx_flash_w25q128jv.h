#include "stm32f103xx_spi.h"
#include "stm32f103xx_gpio.h"

#define W25_dummy1 0xff
#define W25_dummy2 0x00
#define W25_write_Enable 0x06
#define W25_volatile_write_enable 0x50
#define W25_write_disable 0x04

#define W25_release_powerDown_ID 0xAB
#define W25_manufacture_ID 0x90
#define W25_JEDEC_ID 0x9F
#define W25_read_uniqe_ID 0x4B

#define W25_read_data 0x03
#define W25_page_program 0x02

#define W25_sector_erase_4K 0x20
#define W25_block_erase_32K 0x52
#define W25_block_erase_64K 0xD8
#define W25_chip_erase_01 0xC7
#define W25_chp_erase_02 0x60

#define W25_read_status_reg1  0x05
#define W25_write_status_reg1	0x01
#define W25_read_status_reg2 	0x35
#define W25_write_status_reg2	0x31
#define W25_read_status_reg3 0x15
#define W25_write_status_reg3	0x11

#define W25_reset1	0x66
#define W25_reset2	0x99

#define W25_memBlock2 0x800000

void W25_flash_enable(SPI_TypeDef *pSPIx);
uint8_t W25_flash_read_statusREG(SPI_TypeDef *pSPIx ,uint8_t RegADDR);
void W25_flash_erase(SPI_TypeDef *pSPIx);
void W25_flash_reset(SPI_TypeDef *pSPIx);

void W25_flash_eraseblock(SPI_TypeDef *pSPIx , uint32_t memory_addr);
void W25_flash_WriteMemory(SPI_TypeDef *pSPIx , uint8_t *pTXBuffer , uint32_t len , uint32_t memory_addr);
void W25_flash_readMemory(SPI_TypeDef *pSPIx , uint8_t *pRxBuffer , uint32_t len , uint32_t memory_addr);

void SPI_SendByte(SPI_TypeDef *pSPIx,uint8_t byte);
void delay(void);
