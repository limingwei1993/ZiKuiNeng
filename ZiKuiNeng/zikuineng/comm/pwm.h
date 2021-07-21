/*
 * pwm.h
 *
 *  Created on: 2021Äê4ÔÂ20ÈÕ
 *      Author: Lee
 */

#ifndef COMM_PWM_H_
#define COMM_PWM_H_



void Pwm1_Switch1_Int(void);
void Pwm2_Switch2_Int(void);
void Pwm3_Switch3_Int(void);
void Pwm4_Switch4_Int(void);
void Pwm5_Motor1_Int(void);
void Pwm6_Motor2_Int(void);
void set_switch1_status(uint8_t status);
void set_switch2_status(uint8_t status);
void set_switch3_status(uint8_t status);
void set_switch4_status(uint8_t status);
void set_motor1_status(uint8_t status);
void set_motor2_status(uint8_t status);
#endif /* COMM_PWM_H_ */
