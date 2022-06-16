/*
 * spi_DAC8563.h
 *
 *  Created on: 2022Äê4ÔÂ1ÈÕ
 *      Author: EDY
 */

#ifndef SPI_DAC8563_H_
#define SPI_DAC8563_H_

#define LOW 0
#define HIGH 1

#define DAC_A   0
#define DAC_B   1

void set_CS(unsigned char status);
void set_CLK(unsigned char status);
void set_MOSI(unsigned char status);
void DAC8563_Init(void);
void DAC8563_SetData(uint8_t _ch, uint16_t _dac);
void SpiWriteCmd(unsigned long cmd);
void DAC8563_SetVoltage_mv(uint8_t DACselect, unsigned long Voltage);
#endif /* SPI_DAC8563_H_ */
