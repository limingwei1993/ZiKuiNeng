/*
 * include.h
 *
 *  Created on: 2021年4月20日
 *      Author: Lee
 */

#ifndef COMM_INCLUDE_H_
#define COMM_INCLUDE_H_
#include <initialization.h>
#include "ff.h"


#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "RS422.h"
#include "spi_ADS1258.h"
#include "time.h"
#include "EEPROM.h"
#include "SPI_SDCard.h"
#include "pwm.h"
#include "sdcard.h"
#include "initialization.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
extern uint8_t power_on;

#define Motor1_Start_speed  100
#define Motor2_Start_speed  100
extern uint32_t test_DAC;/*测试使用，测试DAC输出1V*/
extern uint8_t test_eeprom_read;
extern uint8_t test_eeprom_write;
extern uint8_t test_sd_read;
extern uint8_t test_sd_write;
extern uint8_t send_ADC_value;
extern uint8_t send_eeprom_data;
extern uint8_t Rs422_revice;
extern uint8_t Rs422_revice_type;
extern uint8_t switch1_on_off;
extern uint8_t switch2_on_off;
extern uint8_t switch3_on_off;
extern uint8_t switch4_on_off;
extern uint8_t motor1_on_off;
extern uint8_t motor2_on_off;
#endif /* COMM_INCLUDE_H_ */
