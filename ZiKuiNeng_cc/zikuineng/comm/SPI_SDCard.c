/*
 * SPI_SDCard.c
 *
 *  Created on: 2021Äê4ÔÂ22ÈÕ
 *      Author: Lee
 */

#include "include.h"
uint8_t SD_status;
/**
  * @function Set_SPI_CLK_High
  * @brief    set spi CLK high
  * @param    None
  * @retval   None
  */
void Set_SPI_CLK_High(void)
{
    GpioDataRegs.GPCDAT.bit.GPIO73 = 1;
}
/**
  * @function Set_SPI_CLK_Low
  * @brief    set spi CLK low
  * @param    None
  * @retval   None
  */
void Set_SPI_CLK_Low(void)
{
    GpioDataRegs.GPCDAT.bit.GPIO73 = 0;
}
/**
  * @function Set_SPI_MOSI_High
  * @brief    set spi MOSI high
  * @param    None
  * @retval   None
  */
void Set_SPI_MOSI_High(void)
{
    GpioDataRegs.GPCDAT.bit.GPIO74 = 1;
}
/**
  * @function Set_SPI_MOSI_Low
  * @brief    set spi MOSI low
  * @param    None
  * @retval   None
  */
void Set_SPI_MOSI_Low(void)
{
    GpioDataRegs.GPCDAT.bit.GPIO74 = 0;
}
/**
  * @function Set_SPI_MISO_High
  * @brief    set spi MISO high
  * @param    None
  * @retval   None
  */
void Set_SPI_MISO_High(void)
{
    GpioDataRegs.GPCDAT.bit.GPIO75 = 1;
}
/**
  * @function Set_SPI_MISO_Low
  * @brief    set spi MISO low
  * @param    None
  * @retval   None
  */
void Set_SPI_MISO_Low(void)
{
    GpioDataRegs.GPCDAT.bit.GPIO75 = 0;
}
/**
  * @function Set_SPI_CS_High
  * @brief    set spi CS high
  * @param    None
  * @retval   None
  */
void Set_SPI_CS_High(void)
{
    GpioDataRegs.GPCDAT.bit.GPIO72 = 1;
}
/**
  * @function Set_SPI_CS_Low
  * @brief    set spi CS low
  * @param    None
  * @retval   None
  */
void Set_SPI_CS_Low(void)
{
    GpioDataRegs.GPCDAT.bit.GPIO72 = 0;
}
/**
  * @function Get_SPI_MISO_Status
  * @brief    get spi MISO status
  * @param    None
  * @retval   spi MISO status
  */
uint8_t Get_SPI_MISO_Status(void)
{
    return(GpioDataRegs.GPCDAT.bit.GPIO75 &0x00ff);
}
/**
  * @function delay_ns
  * @brief    delay ns
  * @param    ns: delay time
  * @retval   None
  */
void delay_ns(uint32_t ns)
{
  while(ns--);
}
/**
  * @function delay_us
  * @brief    delay us
  * @param    us: delay time
  * @retval   None
  */
void delay_us(uint32_t us)
{
  static volatile unsigned int delayval;

  delayval = us * 80;   // 100000 are about 10ms
  while(delayval--);
}
/**
  * @function delay_ms
  * @brief    delay ms
  * @param    ms: delay time
  * @retval   None
  */
void delay_ms(uint32_t ms)
{
  static volatile unsigned int delayval;

  delayval = ms * 800000;   // 100000 are about 10ms
  while(delayval--);
}

