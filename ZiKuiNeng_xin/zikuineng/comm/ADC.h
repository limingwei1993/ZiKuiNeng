/*
 * ADC.h
 *
 *  Created on: 2022Äê6ÔÂ16ÈÕ
 *      Author: EDY
 */

#ifndef COMM_ADC_H_
#define COMM_ADC_H_


#define ADC_CKPS   0x1

#define ADC_SHCLK  0x8   // S/H width in ADC module periods = 16 ADC clocks
#define AVG        1000  // Average sample limit
#define ZOFFSET    0x00  // Average Zero offset
#define BUF_SIZE   40    // Sample buffer size

void ADC_Init(void);
#endif /* COMM_ADC_H_ */
