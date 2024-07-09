/******************************************************************************
 *
 * Module: CAN
 *
 * File Name: CAN_Regs.h
 *
 * Description: Header file for STM32F103C8T6 Microcontroller - CAN Registers Driver.
 *
 * Author: Ahmed Hatem
 ******************************************************************************/

#ifndef CAN_REGS_H
#define CAN_REGS_H

#include "Std_Types.h"

/******************************************************************************
*                        CAN Registers Base Address
******************************************************************************/
#define CAN_1_BASE_ADDRESS                            (*((volatile uint32 *)0x40006400 ))     /* To 0x4000 67FF */ 
#define CAN_2_BASE_ADDRESS                            (*((volatile uint32 *)0x40006800 ))     /* To 0x4000 6BFF */          

/******************************************************************************
*                       CAN Registers Offset Address
******************************************************************************/
#define CAN_MCR_Offset                                0x000
#define CAN_MSR_Offset                                0x004
#define CAN_TSR_Offset                                0x008
#define CAN_RF0R_Offset                               0x00C

#define CAN_RF1R_Offset                               0x010
#define CAN_IER_Offset                                0x014
#define CAN_ESR_Offset                                0x018
#define CAN_BTR_Offset                                0x01C

#define CAN_TI0R_Offset                               0x180
#define CAN_TDT0R_Offset                              0x184
#define CAN_TDL0R_Offset                              0x188
#define CAN_TDH0R_Offset                              0x18C

#define CAN_TI1R_Offset                               0x190
#define CAN_TDT1R_Offset                              0x194
#define CAN_TDL1R_Offset                              0x198
#define CAN_TDH1R_Offset                              0x19C

#define CAN_TI2R_Offset                               0x1A0
#define CAN_TDT2R_Offset                              0x1A4
#define CAN_TDL2R_Offset                              0x1A8
#define CAN_TDH2R_Offset                              0x1AC

#define CAN_RI0R_Offset                               0x1B0
#define CAN_RDT0R_Offset                              0x1B4
#define CAN_RDL0R_Offset                              0x1B8
#define CAN_RDH0R_Offset                              0x1BC

#define CAN_RI1R_Offset                               0x1C0
#define CAN_RDT1R_Offset                              0x1C4
#define CAN_RDL1R_Offset                              0x1C8
#define CAN_RDH1R_Offset                              0x1CC

#define CAN_FMR_Offset                                0x200
#define CAN_FM1R_Offset                               0x204

#define CAN_FS1R_Offset                               0x20C

#define CAN_FFA1R_Offset                              0x214
#define CAN_FA1R_Offset                               0x21C

#define CAN_F0R1_Offset                               0x240
#define CAN_F0R2_Offset                               0x244

#define CAN_F1R1_Offset                               0x248
#define CAN_F1R2_Offset                               0x24C

#define CAN_F2R1_Offset                               0x250
#define CAN_F2R2_Offset                               0x254

#define CAN_F3R1_Offset                               0x258
#define CAN_F3R2_Offset                               0x25C

#define CAN_F4R1_Offset                               0x260
#define CAN_F4R2_Offset                               0x264

#define CAN_F5R1_Offset                               0x268
#define CAN_F5R2_Offset                               0x26C

#define CAN_F6R1_Offset                               0x270
#define CAN_F6R2_Offset                               0x274

#define CAN_F7R1_Offset                               0x278
#define CAN_F7R2_Offset                               0x27C

#define CAN_F8R1_Offset                               0x280
#define CAN_F8R2_Offset                               0x284
#define CAN_F9R1_Offset                               0x288
#define CAN_F9R2_Offset                               0x28C

#define CAN_F10R1_Offset                              0x290
#define CAN_F10R2_Offset                              0x294
#define CAN_F11R1_Offset                              0x298
#define CAN_F11R2_Offset                              0x29C

#define CAN_F12R1_Offset                              0x2A0
#define CAN_F12R2_Offset                              0x2A4
#define CAN_F13R1_Offset                              0x2A8
#define CAN_F13R2_Offset                              0x2AC

#define CAN_F14R1_Offset                              0x2B0
#define CAN_F14R2_Offset                              0x2B4
#define CAN_F15R1_Offset                              0x2B8
#define CAN_F15R2_Offset                              0x2BC

#define CAN_F16R1_Offset                              0x2C0
#define CAN_F16R2_Offset                              0x2C4
#define CAN_F17R1_Offset                              0x2C8
#define CAN_F17R2_Offset                              0x2CC

#define CAN_F18R1_Offset                              0x2D0
#define CAN_F18R2_Offset                              0x2D4
#define CAN_F19R1_Offset                              0x2D8
#define CAN_F19R2_Offset                              0x2DC

#define CAN_F20R1_Offset                              0x2E0
#define CAN_F20R2_Offset                              0x2E4
#define CAN_F21R1_Offset                              0x2E8
#define CAN_F21R2_Offset                              0x2EC

#define CAN_F22R1_Offset                              0x2F0
#define CAN_F22R2_Offset                              0x2F4
#define CAN_F23R1_Offset                              0x2F8
#define CAN_F23R2_Offset                              0x2FC

#define CAN_F24R1_Offs                                0x300
#define CAN_F24R2_Offset                              0x304
#define CAN_F25R1_Offet                               0x308
#define CAN_F25R2_Offset                              0x30C

#define CAN_F26R1_Offset                              0x310
#define CAN_F26R2_Offset                              0x314
#define CAN_F27R1_Offset                              0x318
#define CAN_F27R2_Offset                              0x31C



/*********************************************************************************
*                                CAN 1 Registers
**********************************************************************************/
#define CAN1_MCR                               (*((volatile uint32 *)0x40006400 ))
#define CAN1_MSR                               (*((volatile uint32 *)0x40006404 ))
#define CAN1_TSR                               (*((volatile uint32 *)0x40006408 ))
#define CAN1_RF0R                              (*((volatile uint32 *)0x4000640C ))

#define CAN1_RF1R                              (*((volatile uint32 *)0x40006410 ))
#define CAN1_IER                               (*((volatile uint32 *)0x40006414 ))
#define CAN1_ESR                               (*((volatile uint32 *)0x40006418 ))
#define CAN1_BTR                               (*((volatile uint32 *)0x4000641C ))

#define CAN1_TI0R                              (*((volatile uint32 *)0x40006580 ))
#define CAN1_TDT0R                             (*((volatile uint32 *)0x40006584 ))
#define CAN1_TDL0R                             (*((volatile uint32 *)0x40006588 ))
#define CAN1_TDH0R                             (*((volatile uint32 *)0x4000658C ))

#define CAN1_TI1R                              (*((volatile uint32 *)0x40006590 ))
#define CAN1_TDT1R                             (*((volatile uint32 *)0x40006594 ))
#define CAN1_TDL1R                             (*((volatile uint32 *)0x40006598 ))
#define CAN1_TDH1R                             (*((volatile uint32 *)0x4000659C ))

#define CAN1_TI2R                              (*((volatile uint32 *)0x400065A0 ))
#define CAN1_TDT2R                             (*((volatile uint32 *)0x400065A4 ))
#define CAN1_TDL2R                             (*((volatile uint32 *)0x400065A8 ))
#define CAN1_TDH2R                             (*((volatile uint32 *)0x400065AC ))

#define CAN1_RI0R                              (*((volatile uint32 *)0x400068B0 ))
#define CAN1_RDT0R                             (*((volatile uint32 *)0x400065B4 ))
#define CAN1_RDL0R                             (*((volatile uint32 *)0x400065B8 ))
#define CAN1_RDH0R                             (*((volatile uint32 *)0x400065BC ))

#define CAN1_RI1R                              (*((volatile uint32 *)0x400065C0 ))
#define CAN1_RDT1R                             (*((volatile uint32 *)0x400065C4 ))
#define CAN1_RDL1R                             (*((volatile uint32 *)0x400065C8 ))
#define CAN1_RDH1R                             (*((volatile uint32 *)0x400065CC ))

#define CAN1_FMR                               (*((volatile uint32 *)0x40006600 ))
#define CAN1_FM1R                              (*((volatile uint32 *)0x40006604 ))

#define CAN1_FS1R                              (*((volatile uint32 *)0x4000660C ))

#define CAN1_FFA1R                             (*((volatile uint32 *)0x40006614 ))
#define CAN1_FA1R                              (*((volatile uint32 *)0x4000661C ))

#define CAN1_F0R1                              (*((volatile uint32 *)0x40006640 ))
#define CAN1_F0R2                              (*((volatile uint32 *)0x40006644 ))

#define CAN1_F1R1                              (*((volatile uint32 *)0x40006648 ))
#define CAN1_F1R2                              (*((volatile uint32 *)0x4000664C ))

#define CAN1_F2R1                              (*((volatile uint32 *)0x40006650 ))
#define CAN1_F2R2                              (*((volatile uint32 *)0x40006654 ))

#define CAN1_F3R1                              (*((volatile uint32 *)0x40006658 ))
#define CAN1_F3R2                              (*((volatile uint32 *)0x4000665C ))

#define CAN1_F4R1                              (*((volatile uint32 *)0x40006660 ))
#define CAN1_F4R2                              (*((volatile uint32 *)0x40006664 ))

#define CAN1_F5R1                              (*((volatile uint32 *)0x40006668 ))
#define CAN1_F5R2                              (*((volatile uint32 *)0x4000666C ))

#define CAN1_F6R1                              (*((volatile uint32 *)0x40006670 ))
#define CAN1_F6R2                              (*((volatile uint32 *)0x40006674 ))

#define CAN1_F7R1                              (*((volatile uint32 *)0x40006678 ))
#define CAN1_F7R2                              (*((volatile uint32 *)0x4000667C ))

#define CAN1_F8R1                              (*((volatile uint32 *)0x40006680 ))
#define CAN1_F8R2                              (*((volatile uint32 *)0x40006684 ))
#define CAN1_F9R1                              (*((volatile uint32 *)0x40006688 ))
#define CAN1_F9R2                              (*((volatile uint32 *)0x4000668C ))

#define CAN1_F10R1                             (*((volatile uint32 *)0x40006690 ))
#define CAN1_F10R2                             (*((volatile uint32 *)0x40006694 ))
#define CAN1_F11R1                             (*((volatile uint32 *)0x40006698 ))
#define CAN1_F11R2                             (*((volatile uint32 *)0x4000669C ))

#define CAN1_F12R1                             (*((volatile uint32 *)0x400066A0 ))
#define CAN1_F12R2                             (*((volatile uint32 *)0x400066A4 ))
#define CAN1_F13R1                             (*((volatile uint32 *)0x400066A8 ))
#define CAN1_F13R2                             (*((volatile uint32 *)0x400066AC ))

#define CAN1_F14R1                             (*((volatile uint32 *)0x400066B0 ))
#define CAN1_F14R2                             (*((volatile uint32 *)0x400066B4 ))
#define CAN1_F15R1                             (*((volatile uint32 *)0x400066B8 ))
#define CAN1_F15R2                             (*((volatile uint32 *)0x400066BC ))

#define CAN1_F16R1                             (*((volatile uint32 *)0x400066C0 ))
#define CAN1_F16R2                             (*((volatile uint32 *)0x400066C4 ))
#define CAN1_F17R1                             (*((volatile uint32 *)0x400066C8 ))
#define CAN1_F17R2                             (*((volatile uint32 *)0x400066CC ))

#define CAN1_F18R1                             (*((volatile uint32 *)0x400066D0 ))
#define CAN1_F18R2                             (*((volatile uint32 *)0x400066D4 ))
#define CAN1_F19R1                             (*((volatile uint32 *)0x400066D8 ))
#define CAN1_F19R2                             (*((volatile uint32 *)0x400066DC ))

#define CAN1_F20R1                             (*((volatile uint32 *)0x400066E0 ))
#define CAN1_F20R2                             (*((volatile uint32 *)0x400066E4 ))
#define CAN1_F21R1                             (*((volatile uint32 *)0x400066E8 ))
#define CAN1_F21R2                             (*((volatile uint32 *)0x400066EC ))

#define CAN1_F22R1                             (*((volatile uint32 *)0x400066F0 ))
#define CAN1_F22R2                             (*((volatile uint32 *)0x400066F4 ))
#define CAN1_F23R1                             (*((volatile uint32 *)0x400066F8 ))
#define CAN1_F23R2                             (*((volatile uint32 *)0x400066FC ))

#define CAN1_F24R1                             (*((volatile uint32 *)0x40006700 ))
#define CAN1_F24R2                             (*((volatile uint32 *)0x40006704 ))
#define CAN1_F25R1                             (*((volatile uint32 *)0x40006708 ))
#define CAN1_F25R2                             (*((volatile uint32 *)0x4000670C ))

#define CAN1_F26R1                             (*((volatile uint32 *)0x40006710 ))
#define CAN1_F26R2                             (*((volatile uint32 *)0x40006714 ))
#define CAN1_F27R1                             (*((volatile uint32 *)0x40006718 ))
#define CAN1_F27R2                             (*((volatile uint32 *)0x4000671C ))

/*******************************************************************************
 *            CAN master control register (CAN_MCR) Bits Name                  *
 *******************************************************************************/
#define DBF                                    (16u)
#define RESET_CAN                              (15u)
#define TTCM                                   (7u)
#define ABOM                                   (6u)
#define AWUM                                   (5u)
#define NART                                   (4u)
#define RFLM                                   (3u)
#define TXFP                                   (2u)    
#define SLEEP                                  (1u)
#define INRQ                                   (0u)
  
/*******************************************************************************
 *               CAN master status register (CAN_MSR) Bits Name                *
 *******************************************************************************/
#define RX                                     (11u)
#define SAMP                                   (10u)
#define RXM                                    (9u)
#define TXM                                    (8u)
#define SLAKI                                  (4u)
#define WKUI                                   (3u)
#define ERRI                                   (2u)
#define SLAK                                   (1u)    
#define INAK                                   (0u)
   
/******************************************************************************
*                CAN transmit status register (CAN_TSR)                       *
******************************************************************************/
#define LOW2                                   (31u)
#define LOW1                                   (30u)
#define LOW0                                   (29u)
#define TME2                                   (28u)
#define TME1                                   (27u)
#define TME0                                   (26u)

#define CODE                                   (24u)
#define ABRQ2                                  (23u)    
#define TERR2                                  (19u)
#define ALST2                                  (18u)
#define TXOK2                                  (17U)
#define RQCP2                                  (16u)

#define ABRQ1                                  (15u)    
#define TERR1                                  (11u)
#define ALST1                                  (10u)
#define TXOK1                                  (9u)
#define RQCP1                                  (8u)

#define ABRQ0                                  (7u)    
#define TERR0                                  (3u)
#define ALST0                                  (2u)
#define TXOK0                                  (1u)
#define RQCP0                                  (0u)
   
/******************************************************************************
*              CAN receive FIFO 0 register (CAN_RF0R) Bits Name               *
******************************************************************************/
#define RFOM0                                  (5u)    
#define FOVR0                                  (4u)
#define FULL0                                  (3u)
#define FMP0                                   (0u)

/******************************************************************************
*              CAN receive FIFO 1 register (CAN_RF1R) Bits Name               *
******************************************************************************/
#define RFOM1                                  (5u)    
#define FOVR1                                  (4u)
#define FULL1                                  (3u)
#define FMP1                                   (0u)

/******************************************************************************
*             CAN interrupt enable register (CAN_IER) Bits Name               *
******************************************************************************/
#define SLKIE                                  (17u)    
#define WKUIE                                  (16u)
#define ERRIE                                  (15u)
#define LECIE                                  (11u)
#define BOFIE                                  (10u)    
#define EPVIE                                  (9u)
#define EWGIE                                  (8u)
#define FOVIE1                                 (6u)
#define FFIE1                                  (5u)    
#define FMPIE1                                 (4u)
#define FOVIE0                                 (3u)
#define FFIE0                                  (2u)
#define FMPIE0                                 (1u)
#define TMEIE                                  (0u)

/******************************************************************************
*               CAN error status register (CAN_ESR) Bits Name                 *
******************************************************************************/
#define REC                                    (24u)    
#define TEC                                    (16u)
#define LEC                                    (4u)
#define BOFF                                   (2u)
#define EPVF                                   (1u)    
#define EWGF                                   (0u)

/******************************************************************************
*               CAN bit timing register (CAN_BTR) Bits Name                 *
******************************************************************************/
#define SILM                                    (31u)    
#define LBKM                                    (30u)
#define SJW                                     (24u)
#define TS2                                     (20u)
#define TS1                                     (16u)    
#define BRP                                     (0u)
 
/******************************************************************************
*       CAN TX mailbox identifier register (CAN_TIxR) Bits Name               *
******************************************************************************/
#define STID                                    (21u)    
#define EXID                                    (3u)    
#define IDE                                     (2u)
#define RTR                                     (1u)
#define TXRQ                                    (0u)

/************************************************************************************
*    CAN mailbox data length control and time stamp register (CAN_TDTxR) Bits Name  *
*************************************************************************************/
#define TIME                                    (16u)    
#define TGT                                     (8u)    
#define DLC                                     (0u)

/************************************************************************************
*              CAN mailbox data low register (CAN_TDLxR) Bits Name                  *
*************************************************************************************/
#define DATA3                                    (24u)    
#define DATA2                                    (16u)    
#define DATA1                                    (7u)
#define DATA0                                    (0u)

/************************************************************************************
*             CAN mailbox data high register (CAN_TDLxR) Bits Name                  *
*************************************************************************************/
#define DATA7                                    (24u)    
#define DATA6                                    (16u)    
#define DATA5                                    (7u)
#define DATA4                                    (0u)

/************************************************************************************
*  CAN receive FIFO mailbox data length control and time stamp register (CAN_RDTxR) * 
*************************************************************************************/
#define TIME                                    (16u)    
#define FMI                                     (8u)    
#define DLC                                     (0u)                                  

/************************************************************************************
*                  CAN filter master register (CAN_FMR) Bits Name                   * 
*************************************************************************************/
#define CAN2SB                                  (8u)    
#define FINIT                                   (0u)                                  

/************************************************************************************
*                   CAN filter mode register (CAN_FM1R) Bits Name                   * 
*************************************************************************************/
#define FBM27                                  (27u)    
#define FBM26                                  (26u)    
#define FBM25                                  (25u)    
#define FBM24                                  (24u)    
#define FBM23                                  (23u)    
#define FBM22                                  (22u)    
#define FBM21                                  (21u)    
#define FBM20                                  (20u)    
#define FBM19                                  (19u)    
#define FBM18                                  (18u)    
#define FBM17                                  (17u)    
#define FBM16                                  (16u)    
#define FBM15                                  (15u)    
#define FBM14                                  (14u)    
#define FBM13                                  (13u)    
#define FBM12                                  (12u)    
#define FBM11                                  (11u)    
#define FBM10                                  (10u)    
#define FBM9                                   (9u)    
#define FBM8                                   (8u)    
#define FBM7                                   (7u)    
#define FBM6                                   (6u)    
#define FBM5                                   (5u)    
#define FBM4                                   (4u)    
#define FBM3                                   (3u)    
#define FBM2                                   (2u)    
#define FBM1                                   (1u)    
#define FBM0                                   (0u)    
   
/************************************************************************************
*                   CAN filter scale register (CAN_FS1R) Bits Name                  * 
*************************************************************************************/
#define FSC27                                  (27u)    
#define FSC26                                  (26u)    
#define FSC25                                  (25u)    
#define FSC24                                  (24u)    
#define FSC23                                  (23u)    
#define FSC22                                  (22u)    
#define FSC21                                  (21u)    
#define FSC20                                  (20u)    
#define FSC19                                  (19u)    
#define FSC18                                  (18u)    
#define FSC17                                  (17u)    
#define FSC16                                  (16u)    
#define FSC15                                  (15u)    
#define FSC14                                  (14u)    
#define FSC13                                  (13u)    
#define FSC12                                  (12u)    
#define FSC11                                  (11u)    
#define FSC10                                  (10u)    
#define FSC9                                   (9u)    
#define FSC8                                   (8u)    
#define FSC7                                   (7u)    
#define FSC6                                   (6u)    
#define FSC5                                   (5u)    
#define FSC4                                   (4u)    
#define FSC3                                   (3u)    
#define FSC2                                   (2u)    
#define FSC1                                   (1u)    
#define FSC0                                   (0u)    
   
/************************************************************************************
*              CAN filter FIFO assignment register (CAN_FFA1R) Bits Name            * 
*************************************************************************************/
#define FFA27                                  (27u)    
#define FFA26                                  (26u)    
#define FFA25                                  (25u)    
#define FFA24                                  (24u)    
#define FFA23                                  (23u)    
#define FFA22                                  (22u)    
#define FFA21                                  (21u)    
#define FFA20                                  (20u)    
#define FFA19                                  (19u)    
#define FFA18                                  (18u)    
#define FFA17                                  (17u)    
#define FFA16                                  (16u)    
#define FFA15                                  (15u)    
#define FFA14                                  (14u)    
#define FFA13                                  (13u)    
#define FFA12                                  (12u)    
#define FFA11                                  (11u)    
#define FFA10                                  (10u)    
#define FFA9                                   (9u)    
#define FFA8                                   (8u)    
#define FFA7                                   (7u)    
#define FFA6                                   (6u)    
#define FFA5                                   (5u)    
#define FFA4                                   (4u)    
#define FFA3                                   (3u)    
#define FFA2                                   (2u)    
#define FFA1                                   (1u)    
#define FFA0                                   (0u)    
   
/************************************************************************************
*                  CAN filter activation register (CAN_FA1R) Bits Name              * 
*************************************************************************************/
#define FACT27                                  (27u)    
#define FACT26                                  (26u)    
#define FACT25                                  (25u)    
#define FACT24                                  (24u)    
#define FACT23                                  (23u)    
#define FACT22                                  (22u)    
#define FACT21                                  (21u)    
#define FACT20                                  (20u)    
#define FACT19                                  (19u)    
#define FACT18                                  (18u)    
#define FACT17                                  (17u)    
#define FACT16                                  (16u)    
#define FACT15                                  (15u)    
#define FACT14                                  (14u)    
#define FACT13                                  (13u)    
#define FACT12                                  (12u)    
#define FACT11                                  (11u)    
#define FACT10                                  (10u)    
#define FACT9                                   (9u)    
#define FACT8                                   (8u)    
#define FACT7                                   (7u)    
#define FACT6                                   (6u)    
#define FACT5                                   (5u)    
#define FACT4                                   (4u)    
#define FACT3                                   (3u)    
#define FACT2                                   (2u)    
#define FACT1                                   (1u)    
#define FACT0                                   (0u)    

/************************************************************************************
*               CAN  Filter bank i register x (CAN_FiRx)  Bits Name                 * 
*************************************************************************************/
#define FB29                                  (29u)    
#define FB28                                  (28u)    
#define FB27                                  (27u)    
#define FB26                                  (26u)    
#define FB25                                  (25u)    
#define FB24                                  (24u)    
#define FB23                                  (23u)    
#define FB22                                  (22u)    
#define FB21                                  (21u)    
#define FB20                                  (20u)    
#define FB19                                  (19u)    
#define FB18                                  (18u)    
#define FB17                                  (17u)    
#define FB16                                  (16u)    
#define FB15                                  (15u)    
#define FB14                                  (14u)    
#define FB13                                  (13u)    
#define FB12                                  (12u)    
#define FB11                                  (11u)    
#define FB10                                  (10u)    
#define FB9                                   (9u)    
#define FB8                                   (8u)    
#define FB7                                   (7u)    
#define FB6                                   (6u)    
#define FB5                                   (5u)    
#define FB4                                   (4u)    
#define FB3                                   (3u)    
#define FB2                                   (2u)    
#define FB1                                   (1u)    
#define FB0                                   (0u)
   
#endif /* CAN_REGS_H */