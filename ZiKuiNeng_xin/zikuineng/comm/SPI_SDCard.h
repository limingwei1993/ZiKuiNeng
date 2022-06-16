/*
 * SPI_SDCard.h
 *
 *  Created on: 2021Äê4ÔÂ22ÈÕ
 *      Author: Lee
 */

#ifndef COMM_SPI_SDCARD_H_
#define COMM_SPI_SDCARD_H_
#include "DSP2833x_Device.h"     /* DSP2833x Headerfile Include File*/

#define SD_LOAD_SUCCESS      1
#define SD_INIT_ERROR        0
#define FATFS_LOAD_SUCCESS   2
extern uint8_t SD_status;
void Spi_SDCard_Gpio_Int(void);
void Set_SPI_CLK_High(void);

void Set_SPI_CLK_Low(void);

void Set_SPI_MOSI_High(void);

void Set_SPI_MOSI_Low(void);
void Set_SPI_MISO_High(void);

void Set_SPI_MISO_Low(void);

void Set_SPI_CS_High(void);

void Set_SPI_CS_Low(void);

uint8_t Get_SPI_MISO_Status(void);

void delay_ns(uint32_t ns);

void delay_us(uint32_t us);

void delay_ms(uint32_t ms);

#endif /* COMM_SPI_SDCARD_H_ */
