/*
 * ADC.c
 *
 *  Created on: 2022��6��16��
 *      Author: EDY
 */
#include "DSP2833x_Adc.h"
#include "DSP2833x_DMA.h"
#include "DSP2833x_GlobalPrototypes.h"
#include "DSP2833x_Dma_defines.h"
#include "ADC.h"
#pragma DATA_SECTION(DMABuf1,"DMARAML4");
volatile Uint16 DMABuf1[60];

volatile Uint16 *DMADest;
volatile Uint16 *DMASource;
__interrupt void local_DINTCH1_ISR(void);

void ADC_Init(void)
{
    uint8_t i=0;
    InitAdc();  // For this example, init the ADC
    AdcRegs.ADCTRL1.bit.ACQ_PS = ADC_SHCLK; //
    AdcRegs.ADCTRL1.bit.CONT_RUN=1;
    AdcRegs.ADCTRL3.bit.ADCCLKPS = ADC_CKPS;
    AdcRegs.ADCTRL1.bit.SEQ_CASC = 1;        //1 ����ģʽ��16��ͨ����
   // AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 0x1;
  //  AdcRegs.ADCTRL2.bit.RST_SEQ1 = 0x1;
    AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0x2;
    AdcRegs.ADCCHSELSEQ1.bit.CONV01 = 0x3;
    AdcRegs.ADCCHSELSEQ1.bit.CONV02 = 0x4;
    AdcRegs.ADCCHSELSEQ1.bit.CONV03 = 0x5;
    AdcRegs.ADCCHSELSEQ2.bit.CONV04 = 0x6;
    AdcRegs.ADCCHSELSEQ2.bit.CONV05 = 0x7;
    //
    // Set up ADC to perform 4 conversions for every SOC
    //
    AdcRegs.ADCMAXCONV.bit.MAX_CONV1 = 5;

    DMAInitialize();

       //
       // Clear Table
       //
       for (i=0; i<60; i++)
       {
           DMABuf1[i] = 0;
       }

       //
       // Configure DMA Channel
       //

       //
       // Point DMA destination to the beginning of the array
       //
       DMADest   = &DMABuf1[0];

       //
       // Point DMA source to ADC result register base
       //
       DMASource = &AdcMirror.ADCRESULT0;

       DMACH1AddrConfig(DMADest,DMASource);
      /*
       * ����1--ÿ�δ������ݸ�����6
       * ����2--Դ��ַ�ƶ�����μ�1
       * ����3--Ŀ���ַ�ƶ����𽥼�1
       * */
       DMACH1BurstConfig(6,1,1);
       /*
      * ����1--����������9
      * ����2--�������Դ��ַ����������μ�1
      * ����3--�������Ŀ���ַ��������0
      * */
       DMACH1TransferConfig(9,0,1);
       /*
             * ����1--��һ��Դ��ַ���ʹ�С�룺��1
             * ����2--��һ��Դ��ʼ��ַ���ã�����
             * ����3--������ٿ�ʼ��һ��Ŀ�꿪ʼ��0
             * ����4--��һ��Ŀ�꿪ʼ��ַ���ã���1
             * */
       DMACH1WrapConfig(1,0,0,1);
       /*
        * DMA_SEQ1INT--DMA����Դ��ADC 1ͨ��
        * PERINT_ENABLE--�ⲿ�жϴ���DMAʹ�ܣ�ʹ��
        * ONESHOT_DISABLE--һ�δ�����DMA���ݴ�����һ�δ���ֻ1��DMA����
        * CONT_ENABLE--��������ʹ�ܣ���������
        * SYNC_DISABLE--ͬ�����ã���ʹ��
        * SYNC_SRC--ͬ��ģʽ��SRC������SYNCҪ��ʹ�ܣ�
        * OVRFLOW_DISABLE--����ж�:��ʹ��
        * SIXTEEN_BIT--����λ��16
        * CHINT_END--���䴥��DMA���ƣ����������
        * CHINT_ENABLE--DMA�ж�ʹ�ܣ�ʹ��
        * */
       DMACH1ModeConfig(DMA_SEQ1INT,PERINT_ENABLE,ONESHOT_DISABLE,CONT_ENABLE,
                        SYNC_DISABLE,SYNC_SRC,OVRFLOW_DISABLE,SIXTEEN_BIT,
                        CHINT_END,CHINT_ENABLE);

       StartDMACH1();

       //
       // Start SEQ1
       //
       AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 0x1;
}

__interrupt void
local_DINTCH1_ISR(void)
{
    //
    // To receive more interrupts from this PIE group, acknowledge this
    // interrupt
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

