/*
 * time.h
 *
 *  Created on: 2021��4��21��
 *      Author: Lee
 */

#ifndef COMM_TIME_H_
#define COMM_TIME_H_

extern uint32_t ADS_count; /*test code*/
void Time0_Int(float Freq, float Period);
void Time0_Interrupt_Handler(void);
void task_run(void);
#endif /* COMM_TIME_H_ */
