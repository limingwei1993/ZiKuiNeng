/*
 * ADC.c
 *
 *  Created on: 2022年6月16日
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
    AdcRegs.ADCTRL1.bit.SEQ_CASC = 1;        //1 级联模式（16个通道）
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
       * 参数1--每次传输数据个数：6
       * 参数2--源地址移动：逐次加1
       * 参数3--目标地址移动：逐渐加1
       * */
       DMACH1BurstConfig(6,1,1);
       /*
      * 参数1--触发次数：9
      * 参数2--处理完后，源地址增加量：逐次加1
      * 参数3--处理完后，目标地址增加量：0
      * */
       DMACH1TransferConfig(9,0,1);
       /*
             * 参数1--下一次源地址发送大小与：加1
             * 参数2--下一次源开始地址设置：不变
             * 参数3--传输多少开始下一次目标开始：0
             * 参数4--下一次目标开始地址设置：加1
             * */
       DMACH1WrapConfig(1,0,0,1);
       /*
        * DMA_SEQ1INT--DMA请求源：ADC 1通道
        * PERINT_ENABLE--外部中断触发DMA使能：使能
        * ONESHOT_DISABLE--一次触发，DMA传递次数：一次触发只1次DMA传输
        * CONT_ENABLE--连续传输使能：连续传输
        * SYNC_DISABLE--同步启用：不使能
        * SYNC_SRC--同步模式：SRC（首先SYNC要先使能）
        * OVRFLOW_DISABLE--溢出中断:不使能
        * SIXTEEN_BIT--数据位：16
        * CHINT_END--传输触发DMA机制：传输结束。
        * CHINT_ENABLE--DMA中断使能：使能
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

