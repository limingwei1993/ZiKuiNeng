/*
 * Motor.h
 *
 *  Created on: 2021Äê4ÔÂ20ÈÕ
 *      Author: Lee
 */

#ifndef COMM_INITIALIZATION_H_
#define COMM_INITIALIZATION_H_
#include "DSP2833x_Device.h"     /* DSP2833x Headerfile Include File*/
typedef enum MOTOR_STATUS_TYPE
{
    MOTOR_RUN     =0X00,
    MOTOR_STOP    =0X01,
}MOTOR_STATUS;

void GIOP_Int(void);
void Configuration_Interrupt(void);
uint8_t  Get_Dial_Code(void);

#endif /* COMM_INITIALIZATION_H_ */
