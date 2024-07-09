/******************************************************************************
 *
 * Module: Controller Area Network
 *
 * File Name: CAN.c
 *
 * Description: Source file for STM32F103C8T6 Microcontroller - CAN Driver.
 *
 * Author: Shady Alaa
 ******************************************************************************/

#include "CAN.h"
#include "Port.h"

#define CAN_MCR_MASK     0xFFFE7F03
#define CAN_BTR_MASK     0x3C80FC00
#define CAN_TDTxR_MASK   0xFFFFFFF0
#define CAN_FMR_MASK     0xFFFFC0FF

/* Disable interrupts (CPSID instruction) */   
STATIC void __disable_irq(void) 
{
    __asm("cpsid i"); 
}
/* Enable interrupts (CPSIE instruction) */
STATIC void __enable_irq(void) 
{
    __asm("cpsie i"); 
}   

/*
  Description:
    This function is used initiallize the CAN peripheral
 */
void CAN_Init(const CAN_ConfigType* Config_Ptr)
{
  /* Warining: First Make PIN A11(CAN_RX) & PIN A12(CAN_TX) Mode_Changeable at Port_PBCfg.c  */

  /* Set Pin 11 and Pin 12 in PORTA as CAN Receiver and CAN Transmitter respectively  */
  Port_SetPinMode( PORTA_PIN_11 , PORT_PIN_FUNC_ALT_CAN_RD );
  Port_SetPinMode( PORTA_PIN_12 , PORT_PIN_FUNC_ALT_CAN_TD );
    
  /* First we will check if we are at SLEEP mode */
  if( BIT_IS_SET(CAN1_MSR, SLAK) && BIT_IS_CLEAR(CAN1_MSR, INAK) )
  {
    /*  Exit Sleep Mode and Enter Initialization mode by: */
  
    /* 1- Clear SLEEP bit in CAN1_MCR register. */
    CLEAR_BIT(CAN1_MCR,SLEEP);
    
    /* 2- Set INRQ bit in CAN1_MCR register. */
    SET_BIT(CAN1_MCR,INRQ);
    
    /* 3- Wait for the ack from INAK bit to be set and the SLAK bit to be cleared in CAN1_MSR. */
    while(! ( BIT_IS_SET(CAN1_MSR,INAK) && BIT_IS_CLEAR(CAN1_MSR,SLAK) ));
  }
  /* Else check if you are at NORMAL mode */
  else if( BIT_IS_CLEAR(CAN1_MSR, SLAK) && BIT_IS_CLEAR(CAN1_MSR, INAK) )
  {
    /*  Exit NORMAL Mode and Enter Initialization mode by: */
  
    /* 1- Set INRQ bit in CAN1_MCR register. */
    SET_BIT(CAN1_MCR,INRQ);
    /* 2- Wait for the ack from INAK bit to be set and the SLAK bit to be cleared in CAN1_MSR. */
    while(! ( BIT_IS_SET(CAN1_MSR,INAK) && BIT_IS_CLEAR(CAN1_MSR,SLAK) ));
  }
  
  /*************** CAN1_MCR Register Configuration ***************/

  /* MAsk for Master Control register */
  CAN1_MCR &= CAN_MCR_MASK;

  /* Configure the register bits as required in the CAN_ConfigType pointer */
  CAN1_MCR |= ( Config_Ptr->Automatic_Bus_Off_Management << ABOM ) | ( Config_Ptr->Received_FIFO_Lock_Mode << RFLM ) | \
              ( Config_Ptr->MAilboxes_Priority << TXFP ) | ( Config_Ptr->Auto_Retransmission <<NART) | ( Config_Ptr->Automatic_wakeup_mode << AWUM ) | \
              ( Config_Ptr->Debug_freeze_Mode << DBF )   | ( Config_Ptr->Time_Mode << TTCM );

  /*************** CAN1_IER Register Configuration ***************/
  
  if( Config_Ptr->Rx_Interrupt == CAN_ENABLE )
  {
    /* Enable global interrupt */
    __enable_irq();
    
    /* Open interrupts for CAN */
    SET_BIT(NVIC_ISER0_REG, 20);
    
    /* Set the priority for CAN 1 */
    NVIC_PRI5_REG &= (0xFFFFFF00);
    NVIC_PRI5_REG |=  ( Config_Ptr->Priority_Level << 4);
    
    /* Activate interrupts for both FIFOs */
    SET_BIT(CAN1_IER, FMPIE0);
    SET_BIT(CAN1_IER, FMPIE1);    
  }

  /*************** CAN1_BTR Register Configuration ***************/

  /* MAsk for bit timing register */
  CAN1_BTR = 0;

  /* Bit timing Section for 72MHz Clock and 1Mbps */
  /*
                    1
   BaudRate = ---------------
               NominalBitTime
               
    NominalBitTime = ( 1 x tq ) + ( tBS1 ) +( tBS2 ) = tq x ( TS1 + TS2 + 3 )
    let tq = 1/72MHz
  
    tBS1 = tq x (TS1[3:0] + 1),
    tBS2 = tq x (TS2[2:0] + 1),
    tq = (BRP[9:0] + 1) x tPCLK
    where tq refers to the Time quantum
    tPCLK = time period of the APB clock
  */
  
  CAN1_BTR = Config_Ptr->BaudRate_BTR_Value;
  
  /* Select the required testing modes */
  CAN1_BTR |= (Config_Ptr->Silent_Mode << SILM) | (Config_Ptr->LoopBack_Mode<<LBKM);
  
  /* Initiate the Filters */
  Filters_Init(&Filter_Configurations);
  
}

/*
  Description:
    This function is used to perform a software master reset of the bxCAN controller.
 */
void Reset_bxCAN(void) 
{
    /* Set the RESET bit to force a master reset */
    SET_BIT(CAN1_MCR, RESET_CAN);

    /* Wait for the RESET bit to automatically clear (indicating the reset is complete) */
    while (BIT_IS_SET(CAN1_MCR, RESET_CAN));
}

/*
  Description:
    This function is intended to transmit a CAN frame using one of the mailboxes of the CAN controller. 
*/
void CAN_Transmitte(const CAN_Frame_Ptr* CAN_Frame)
{
  /* Define pointers to CAN Transmit registers, initialized to NULL */
  volatile uint32* CAN_TDTxR = NULL_PTR;
  volatile uint32* CAN_TIxR  = NULL_PTR;
  volatile uint32* CAN_TDLxR = NULL_PTR;
  volatile uint32* CAN_TDHxR = NULL_PTR;

  /* Select the appropriate mailbox based on MailBox_Number */
  switch (CAN_Frame->MailBox_Number)
  {
    case 0:
      CAN_TDTxR = &CAN1_TDT0R;
      CAN_TIxR  = &CAN1_TI0R;
      CAN_TDLxR = &CAN1_TDL0R;
      CAN_TDHxR = &CAN1_TDH0R; 
      break;
    case 1:
      CAN_TDTxR = &CAN1_TDT1R;
      CAN_TIxR  = &CAN1_TI1R;
      CAN_TDLxR = &CAN1_TDL1R;
      CAN_TDHxR = &CAN1_TDH1R; 
      break;
    case 2:
      CAN_TDTxR = &CAN1_TDT2R;
      CAN_TIxR  = &CAN1_TI2R;
      CAN_TDLxR = &CAN1_TDL2R;
      CAN_TDHxR = &CAN1_TDH2R; 
      break;
  }

  /* Initialize the identifier register */
  *CAN_TIxR = 0; // Clear register before setting new values
  *CAN_TIxR = (CAN_Frame->Identifier << STID) | (CAN_Frame->Identifier_Extention_Type << IDE) | (CAN_Frame->xRTR << RTR);

  /* Clear the data low register */
  *CAN_TDLxR = 0;

  /* Wait until the selected mailbox is ready */
  while (BIT_IS_CLEAR(CAN1_TSR, 26 + CAN_Frame->MailBox_Number));

  /* Set the Data Length Code (DLC) */
  *CAN_TDTxR = (*CAN_TDTxR & CAN_TDTxR_MASK) | (CAN_Frame->DLC_Size);
  
  /* If DLC size is less than or equal to 4, set the data low register */
  if ((CAN_Frame->DLC_Size) <= 4)
  {
    *CAN_TDLxR = CAN_Frame->Data_To_Be_Sent;
  }

  /*******************ERROR LINE****************************/
  /* Request transmission */
  SET_BIT(*CAN_TIxR, TXRQ);
  
  /* Wait until the transmission request is complete */
  while (BIT_IS_SET(*CAN_TIxR, TXRQ));
}

/*
  Description:
    This function is used to receive data from the FIFO according to specific filter
*/
uint32 CAN_Receive_Message(uint8 Required_Filter_ID)
{
  /* To store the received Data */
  uint32 Rx_Data = 0;
  
  /* To get the DLC of the received data */
  volatile uint16 DLC_Length = 0;
  
  /* To get the filter index that the message passed with */
  uint32 Filter_ID = 0;
  
  //CAN1_TDL0R = 0;
  
  while(1)
  {
    if( ( CAN1_RF0R & (0x00000003) ) != 0 )
    {
      Filter_ID = (uint32)(CAN1_RDT0R >> FMI);
      DLC_Length = (uint16)(CAN1_RDT0R >> DLC);
      
      /* Check if this is the required filter */
      if( Filter_ID == Required_Filter_ID )
      {
        /* This is the received data from the desired filter */
        Rx_Data = CAN1_RDL0R;
      }
      else
      {
        Rx_Data = -1;
      }
      /* Release the mailbox */
      SET_BIT(CAN1_RF0R,RFOM0);
      break;
    }
    //else if ( ( CAN1_RF1R & (0x00000003) ) != 0 )
    //{
    //  Filter_ID = (CAN1_RDT1R << FMI);
    //  //DLC_Length = (CAN1_RDT1R << DLC);
    //  
    //  /* Check if this is the required filter */
    //  if( Filter_ID == Required_Filter_ID )
    //  {
    //    /* This is the received data from the desired filter */
    //    Rx_Data = CAN1_RDL1R;
    //  }
    //  else
    //  {
    //    /* Do Nothing */
    //  }    
    //  /* Release the mailbox */
    //  SET_BIT(CAN1_RF1R,RFOM1);
    //  break;
    //}
  }
  return Rx_Data;
}


/* 
  Description:
    This function is used to configuer the whole 14 filters presented in bxCAN1
 */
void Filters_Init( const Filter_ConfigType* Config_Ptr )
{  
  /* Switch CAN controller to Initialization mode */
  CLEAR_BIT(CAN1_MCR, SLEEP);
  SET_BIT(CAN1_MCR, INRQ);

  /* Wait until the CAN controller enters Initialization mode */
  while (!(BIT_IS_SET(CAN1_MSR, INAK) && BIT_IS_CLEAR(CAN1_MSR, SLAK)));
  
  /* Set how many Bank filters are applied to CAN1 */
  //CAN1_FMR &= (0xFFFFC0FF) | ( FILTERS_NUMBER << 8 );
 
  /* Set the filter initialization mode */
  SET_BIT(CAN1_FMR,FINIT);
  
  /* Loop on all filters  */
  uint8 Counter;
  for(Counter = 0; Counter< Configured_FILTERS_NUMBER; Counter++ )
  {
    switch(Config_Ptr->Filter[Counter].filter_number)
    {
      case FILTER_Bank_0: 
        /* Deactivate the filter first */
        CLEAR_BIT(CAN1_FA1R,FACT0);
        
        /* Select the required  */
        Config_Ptr->Filter[Counter].Assigned_FIFO == FIFO_1 ? SET_BIT(CAN1_FFA1R,FFA0) : CLEAR_BIT(CAN1_FFA1R,FFA0);
        
        
        if( Config_Ptr->Filter[Counter].Scale ==SINGLE_32_BIT )
        {
          /* Select the scale in the CAN filter scale register as Single 32-bit */
          SET_BIT(CAN1_FS1R, FSC0);
          
          /*   31:24     |          23:21 - 20:16    |      15:8       |            7:0         */
          
          /* STID[10:3]  |   STID[2:0] EXID[17:13]   |   EXID[12:5]    |    EXID[4:0] IDE RTR 0 */
          if( Config_Ptr->Filter[Counter].Mode == LIST_ID_MODE )
          {
            /* Select it as LIST mode */
            SET_BIT(CAN1_FM1R, FBM0);
            
            //CAN1_F0R1 &= ~(0xFFE00007); 
            CAN1_F0R1 = 0;
            CAN1_F0R1 |= ( Config_Ptr->Filter[Counter].ID << STID ) \
                      |  ( Config_Ptr->Filter[Counter].xRTR << RTR) | ( Config_Ptr->Filter[Counter].Identifier_Extention_Type << IDE );
            
            CAN1_F0R2 = 0;
            //CAN1_F0R2 &= ~(0xFFE00007);
            CAN1_F0R2 |= ( Config_Ptr->Filter[Counter].ID << STID ) \
                      |  ( Config_Ptr->Filter[Counter].xRTR << RTR) | ( Config_Ptr->Filter[Counter].Identifier_Extention_Type << IDE );
          }
          else if ( Config_Ptr->Filter[Counter].Mode == MASK_MODE )
          {
            /* Select it as Mask mode */
            CLEAR_BIT(CAN1_FM1R, FBM0);
            
            CAN1_F0R1 = 0;
            //CAN1_F0R1 &= ~(0xFFE00007); 
            CAN1_F0R1 |= ( Config_Ptr->Filter[Counter].ID << STID ) \
                      |  ( Config_Ptr->Filter[Counter].xRTR << RTR) | ( Config_Ptr->Filter[Counter].Identifier_Extention_Type << IDE );
            
            CAN1_F0R2 = Config_Ptr->Filter[Counter].Masked_bits;
          }
        }   
        
        /* Activate the filter again */
        SET_BIT(CAN1_FA1R,FACT0);
      break;  

      case FILTER_Bank_1: 
        /* Deactivate the filter first */
        CLEAR_BIT(CAN1_FA1R,FACT1);
        
        /* Select the required  */
        Config_Ptr->Filter[Counter].Assigned_FIFO == FIFO_1 ? SET_BIT(CAN1_FFA1R,FFA1) : CLEAR_BIT(CAN1_FFA1R,FFA1);
        
        
        if( Config_Ptr->Filter[Counter].Scale ==SINGLE_32_BIT )
        {
          SET_BIT(CAN1_FS1R, FSC1);
          
          /*   31:24     |          23:21 - 20:16    |      15:8       |            7:0         */
          
          /* STID[10:3]  |   STID[2:0] EXID[17:13]   |   EXID[12:5]    |    EXID[4:0] IDE RTR 0 */
          if( Config_Ptr->Filter[Counter].Mode == LIST_ID_MODE )
          {
            /* Select it as LIST mode */
            SET_BIT(CAN1_FM1R, FBM0);
            
            CAN1_F1R1 = 0 ;
              
            CAN1_F1R1 |= ( Config_Ptr->Filter[Counter].ID << STID )\
                      |  ( Config_Ptr->Filter[Counter].xRTR << RTR) | ( Config_Ptr->Filter[Counter].Identifier_Extention_Type << IDE );
            
            CAN1_F1R2 = 0;
            CAN1_F1R2 |= ( Config_Ptr->Filter[Counter].ID << STID ) \
                      |  ( Config_Ptr->Filter[Counter].xRTR << RTR ) | ( Config_Ptr->Filter[Counter].Identifier_Extention_Type << IDE );
          }
          if( Config_Ptr->Filter[Counter].Mode == MASK_MODE )
          {
            /* Select it as MASK mode */
            CLEAR_BIT(CAN1_FM1R, FBM0);
            
            CAN1_F1R1 = 0 ;
              
            CAN1_F1R1 |= ( Config_Ptr->Filter[Counter].ID << STID )\
                      |  ( Config_Ptr->Filter[Counter].xRTR << RTR) | ( Config_Ptr->Filter[Counter].Identifier_Extention_Type << IDE );
            
            CAN1_F1R2 = Config_Ptr->Filter[Counter].Masked_bits;
          } 
        }   
        /* Activate the filter again */
        SET_BIT(CAN1_FA1R,FACT1);
        break;
    }
  }
  /* Activate Filters mode */
  CLEAR_BIT(CAN1_FMR,FINIT);
  
  /* Switch CAN controller to Normal mode */
  CLEAR_BIT(CAN1_MCR, SLEEP);
  CLEAR_BIT(CAN1_MCR, INRQ);
}

/* 
  Description:
      This function is used to enable interrupts for bxCAN1
 */
void CAN_Enable_Interrupts(void)
{
  /* Enable global interrupt */
  __enable_irq();
  
  /* Open interrupts for CAN */
  SET_BIT(NVIC_ISER0_REG, 20);
  
  /* Mask for priority register */
  NVIC_PRI5_REG &= (0xFFFFFF00);
  
  /* Set the priority for CAN 1 choose any fixed one i choose 1*/
  NVIC_PRI5_REG |=  ( 1 << 4);
  
  /* Activate interrupts for both FIFOs */
  SET_BIT(CAN1_IER, FMPIE0);
  SET_BIT(CAN1_IER, FMPIE1);    
}

/* 
  Description:
      This function is used to disable interrupts for bxCAN1
 */
void CAN_Disable_Interrupt(void)
{  
  /* Deactivate interrupts for both FIFOs */
  CLEAR_BIT(CAN1_IER, FMPIE0);
  CLEAR_BIT(CAN1_IER, FMPIE1);    
}