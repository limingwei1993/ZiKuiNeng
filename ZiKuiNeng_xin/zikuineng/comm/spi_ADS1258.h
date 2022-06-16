/*
 * spi_ADS8698.h
 *
 *  Created on: 2021Äê4ÔÂ21ÈÕ
 *      Author: Lee
 */

#ifndef COMM_SPI_ADS1258_H_
#define COMM_SPI_ADS1258_H_
#define HARDWARE_SPI      0
#define SIMULATION_SPI    1
#define SPI_MODE  SIMULATION_SPI
typedef struct ADC_CURRENT
{
    unsigned short collection_valid;
    float signal_1_temperature;
    float signal_1_pressure;
    float signal_2_temperature;
    float signal_2_pressure;
    float signal_3_temperature;
    float signal_3_pressure;
    float signa2_1_temperature;
    float signa2_1_pressure;
    float signa2_2_temperature;
    float signa2_2_pressure;
    float signa2_3_temperature;
    float signa2_3_pressure;
    unsigned char signal_1_temperature_err;
    unsigned char signal_1_pressure_err;
    unsigned char signal_2_temperature_err;
    unsigned char signal_2_pressure_err;
    unsigned char signal_3_temperature_err;
    unsigned char signal_3_pressure_err;
    unsigned char signa2_1_temperature_err;
    unsigned char signa2_1_pressure_err;
    unsigned char signa2_2_temperature_err;
    unsigned char signa2_2_pressure_err;
    unsigned char signa2_3_temperature_err;
    unsigned char signa2_3_pressure_err;
    float signal_average_temperature;
    float signal_average_pressure;
    float signa2_average_temperature;
    float signa2_average_pressure;
    unsigned char signal_average_temperature_err;
    unsigned char signal_average_pressure_err;
    unsigned char signa2_average_temperature_err;
    unsigned char signa2_average_pressure_err;
}ADC_CURRENT;
#define Reference_Voltage  3.3
#define Reference_Pressure  16
extern ADC_CURRENT ADC_CURRENT_mA;
void AD_Delay(void);
void AD_Delay1(void);
unsigned char ADS1258_ReadDate(void);
void ADS1258_Int(void);
uint8_t ADC_Read(void);
void ADS_SCLK_H(void);
void ADS_SCLK_L(void);
void SPI_MOSI_High(void);
void SPI_MOSI_Low(void);
uint8_t Get_SPI_MISO(void);

#if (SPI_MODE == HARDWARE_SPI)
void ADS1258_SPI_Int(void);
uint8_t Spi_Send(uint8_t data);
uint8_t  SPI_Read_Data(void);
#else

void SPI_END(void);
void SPI_START(void);
void SPI_SEND_BYTE(uint8_t senddata);
uint8_t SPI_READ_BYTE1(void);
#endif

#endif /* COMM_SPI_ADS1258_H_ */
