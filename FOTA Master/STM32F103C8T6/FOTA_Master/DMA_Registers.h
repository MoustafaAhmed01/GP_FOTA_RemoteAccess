/******************************************************************************
 *
 * Module: DMA
 *
 * File Name: DMA_Regs.h
 *
 * Description: Header file for STM32F103C8T6 Microcontroller - DMA Registers Driver.
 *
 * Author: Ahmed Hatem
 ******************************************************************************/
#ifndef DMA_REGS_H
#define DMA_REGS_H

/*******************************************************************************
*                               DMA Base Addresses                         
*******************************************************************************/
#define DMA_1_BASE_ADDRESS                      (*((volatile uint32 *)0x40020000))      /*to 0x400203FF*/
#define DMA_2_BASE_ADDRESS                      (*((volatile uint32 *)0x40020400))      /*to 0x400207FF*/

/*******************************************************************************
*                              DMA Offset Addresses                         
*******************************************************************************/
#define DMA_ISR_OFFSET                          0x000
#define DMA_IFCR_OFFSET                         0x004

#define DMA_CCR1_OFFSET                         0x008
#define DMA_CNDTR1_OFFSET                       0x00C
#define DMA_CPAR1_OFFSET                        0x010
#define DMA_CMAR1_OFFSET                        0x014

#define DMA_CCR2_OFFSET                         0x01C
#define DMA_CNDTR2_OFFSET                       0x020
#define DMA_CPAR2_OFFSET                        0x024
#define DMA_CMAR2_OFFSET                        0x028

#define DMA_CCR3_OFFSET                         0x030
#define DMA_CNDTR3_OFFSET                       0x034
#define DMA_CPAR3_OFFSET                        0x038
#define DMA_CMAR3_OFFSET                        0x03C

#define DMA_CCR4_OFFSET                         0x044
#define DMA_CNDTR4_OFFSET                       0x048
#define DMA_CPAR4_OFFSET_OFFSET                 0x04C
#define DMA_CMAR4_OFFSET                        0x050

#define DMA_CCR5_OFFSET                         0x058
#define DMA_CNDTR5_OFFSET                       0x05C
#define DMA_CPAR5_OFFSET                        0x060
#define DMA_CMAR5_OFFSET                        0x064
        
#define DMA_CCR6_OFFSET                         0x06C
#define DMA_CNDTR6_OFFSET                       0x070
#define DMA_CPAR6_OFFSET                        0x074
#define DMA_CMAR6_OFFSET                        0x078

#define DMA_CCR7_OFFSET                         0x080
#define DMA_CNDTR7_OFFSET                       0x084
#define DMA_CPAR7_OFFSET                        0x088
#define DMA_CMAR7_OFFSET                        0x08C

/*******************************************************************************
 *          DMA channel configuration register (DMA_CCR) Bits Name             *
 ******************************************************************************/
#define MEM2MEM                                 (14U)
#define PL                                      (12U)  
#define MSIZE                                   (10U)
#define PSIZE                                   (8u)
#define MINC                                    (7U)
#define PINC                                    (6U)
#define CIRC                                    (5U)
#define DIR                                     (4U)
#define TEIE                                    (3U)
#define HTIE                                    (2U)
#define TCIE                                    (1U)
#define EN                                      (0U)

#endif /* DMA_REGS_H */