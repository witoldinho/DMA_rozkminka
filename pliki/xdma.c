//#include <proc/p32mm0256gpm028.h> // przeszakdzaoło w kompilacji

//#include <proc/p32mm0256gpm028.h>

#include "../mcc_generated_files/mcc.h"
#include "xdma.h"
#include "dma.h"


uint8_t tab1[512];


//#include "dma.h"

//char myWriteBuffer[] = "Witaj DMA"; /*bufor nadawczy*/
 void DMA_Init(DMA_CHANNEL  channel)
  {
     switch(channel) {
     case DMA_CHANNEL_0: 
     DMACONbits.ON=0;
      DCH0CON=0;
     //DCH0ECON= 0x1110 ;  //0; // 0x1110; timer1
      DCH0ECONbits.CHSIRQ=54;
      
  DCH0INTCLR = 0xFF;
      DCH0SSA= ((uint32_t)& (*tab1)) &  0x1FFFFFFF ; //0x00; // (address & 0x1FFFFFFF);
    // CHDSA 0; 
    DCH0DSA= ((uint32_t)& U1TXREG) &  0x1FFFFFFF;//0x00;
    // CHSSIZ 0; 
    DCH0SSIZ= 512 ;//sizeof(tab0);
    // CHDSIZ 0; 
    DCH0DSIZ= 1;
    // CHCSIZ 1; 
    DCH0CSIZ= 0x01;
    // DCHPDAT 0; 
    DCH0DAT= 0x00;
    // Clearing Channel 0 Interrupt Flag;
    IFS3CLR= 1 << _IFS3_DMA0IF_POSITION;
    // Enabling Channel 0 Interrupt
    IEC3bits.DMA0IE = 1;
     //  DMACON = (0x8000 | 0x01) & 0x7FFF; //Enable DMA later

    // CHCHNS Chain to channel higher; CHAEN disabled; CHEN enabled; CHCHN disabled; CHBUSY disabled; CHAED disabled; CHPRI Priority 0; 
     //0x80 & 0xFF7F; //Enable DMA Channel later;
    // AIRQEN disabled; CABORT disabled; CHAIRQ 0; SIRQEN enabled; CHSIRQ 17; PATEN disabled; CFORCE disabled; 
    // CHSDIE enabled; CHSDIF No interrupt; CHERIF No interrupt; CHSHIE disabled; CHSHIF No interrupt; CHERIE enabled; CHCCIF No interrupt; CHBCIE disabled; CHBCIF No interrupt; CHDDIF No interrupt; CHDDIE enabled; CHCCIE disabled; CHDHIF No interrupt; CHDHIE disabled; CHTAIE disabled; CHTAIF No interrupt; 
  //  DCH0INT= 0xA10000;
    
 //  DCH0INTbits.CHDDIE=1;
   // DCH0INTbits.CHCCIE=1;
    // CHSSA 0; 
    DMACONbits.ON=1;
    DCH0CONbits.CHEN=1;
     break;
     //-------------------------end of channel 0 ------------------------------
      case DMA_CHANNEL_1:  //channel 1
     DMACONbits.ON=1;
     IEC3bits.DMA1IE = 0 ; /*disable DMA0 interrupt, datasheet page 66*/
IFS3bits.DMA1IF = 0 ; /*clear any existing DMA channel 0 interrupt flag, datasheet page 66*/
      DCH1CON=0;
      DCH1ECON=0;
          DCH1SSA= ((uint32_t)& (*tab1)) &  0x1FFFFFFF ; //0x00; // (address & 0x1FFFFFFF);
    // CHDSA 0; 
    DCH1DSA= ((uint32_t)& U1TXREG) &  0x1FFFFFFF;//0x00;
    // CHSSIZ 0; 
    DCH1SSIZ= 512 ;//sizeof(tab0);
    // CHDSIZ 0; 
    DCH1DSIZ= 1;
    // CHCSIZ 1; 
    DCH1CSIZ= 0x01; 
   
    DCH1DAT= 0x00;// DCHPDAT 0; 
    DCH1INTCLR = 0xFF;  
    DCH1CONbits.CHPRI=3; 
    DCH1INTbits.CHCCIE=1;
    //DCH1INTbits.CHDDIE=1;
  //  DCH1CONbits.CHAED=1;
    DCH1CONbits.CHAEN=1;
    IPC24bits.DMA1IP=1;
    IPC24bits.DMA1IS=0;
    IFS3CLR= 1 << _IFS3_DMA1IF_POSITION   ;// Clearing Channel 0 Interrupt Flag;
    // Enabling Channel 0 Interrupt
    IEC3bits.DMA1IE = 1;
     
    DMACONbits.ON=1;
    DCH1CONbits.CHEN=1;
    
     
          break;
          //----------------------------end of channel 1
          case DMA_CHANNEL_2:
              // rezerwa
              break;
         default:
             // rezerwa
             break;
     }
    
  }
 
 void DMA_Force(void)
 {
     DCH1ECONbits.CFORCE=1;
         while(!(DMA_StatusGet(DMA_CHANNEL_1) & DMA_DESTINATION_FULL));
     
 }

void swiatlo_go(void)
{
    printf(" sw  IN "); 
    //IO_RD0_SetHigh();
    while(!(DMA_StatusGet(DMA_CHANNEL_0) & DMA_BLOCK_TX_COMPLETE));
      printf("\n\r stan dma po sw in [dh0int-%08X,SSA-%08X, DSA %08X , ] \n\r",DCH0INT,DCH0SSA,DCH0DSA);
     
      //DMACONbits.ON = 0;
    //DMACONbits.CHEN=1;
    DCH0CONbits.CHEN=0;
      
       U1STAbits.UTXINV=1;
        delayUs(90);
        U1STAbits.UTXINV=0;
        delayUs(16);
       // UART1_Write(0);
        
     DCH0INTCLR=0xff;
    // DMACONbits.ON = 1;
     DCH0CONbits.CHEN=1;
     printf(" sw OUT "); 
    //DMACONbits.ON=0;
    //DCH0CONbits.CHEN=0;
}

void light_go(uint8_t *ramka)
{
   // printf(" sw light  IN "); 
  //  IO_RD0_SetHigh();
    //memcpy(tab1,ramka,512);
//    DMX_DIR_RX;
    // printf("\n\r stan dma po sw in [dh0int-%08X,SSA-%08X, DSA %08X , ] \n\r",DCH0INT,DCH0SSA,DCH0DSA);
    while(!(DMA_StatusGet(DMA_CHANNEL_0) & DMA_BLOCK_TX_COMPLETE));
     // printf("\n\r stan dma po sw in [dh0int-%08X,SSA-%08X, DSA %08X , ] \n\r",DCH0INT,DCH0SSA,DCH0DSA);
//     DMX_DIR_TX;
   //   DMACONbits.ON = 0;
    //DMACONbits.CHEN=1;
    DCH0CONbits.CHEN=0;
  //  DCH0SSA=0;
   // DCH0SSA=((uint32_t)& ramka) &  0x1FFFFFFF ; 
    //DCH0SSA=513;
       U1STAbits.UTXINV=1;
        delayUs(90);
        U1STAbits.UTXINV=0;
        delayUs(16);
        UART1_Write(0);
        
     DCH0INTCLR=0xff;
    // DMACONbits.ON = 1;
     DCH0CONbits.CHEN=1;
     //printf(" sw light OUT "); 
}

/**
  DMA Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    dma.c

  @Summary
    This is the generated driver implementation file for the DMA driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This source file provides APIs for DMA.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.166.0
        Device            :  PIC32MM0256GPM048
    The generated drivers are tested against the following:
        Compiler          :  XC32 v2.30
        MPLAB 	          :  MPLAB X v5.30
*/

/*
    (c) 2019 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/


void DMA_Initialize(void) 
{ 
    // DMABUSY disabled; SUSPEND Normal DMA operation; ON enabled; 
    DMACON = (0x8000 | 0x01) & 0x7FFF; //Enable DMA later

    // CHCHNS Chain to channel higher; CHAEN disabled; CHEN enabled; CHCHN disabled; CHBUSY disabled; CHAED disabled; CHPRI Priority 0; 
    DCH0CON= 0x80 & 0xFF7F; //Enable DMA Channel later;
    // AIRQEN disabled; CABORT disabled; CHAIRQ 0; SIRQEN enabled; CHSIRQ 17; PATEN disabled; CFORCE disabled; 
    DCH0ECON= 0x1110 ;//0; // 0x1110; timer1
    // CHSDIE enabled; CHSDIF No interrupt; CHERIF No interrupt; CHSHIE disabled; CHSHIF No interrupt; CHERIE enabled; CHCCIF No interrupt; CHBCIE disabled; CHBCIF No interrupt; CHDDIF No interrupt; CHDDIE enabled; CHCCIE disabled; CHDHIF No interrupt; CHDHIE disabled; CHTAIE disabled; CHTAIF No interrupt; 
  //  DCH0INT= 0xA10000;
    DCH0INTCLR = 0xFF;
 //  DCH0INTbits.CHDDIE=1;
   // DCH0INTbits.CHCCIE=1;
    // CHSSA 0; 
    DCH0SSA= 0x00;
    // CHDSA 0; 
    DCH0DSA= 0x00;
    // CHSSIZ 0; 
    DCH0SSIZ= 0x00;
    // CHDSIZ 0; 
    DCH0DSIZ= 0x00;
    // CHCSIZ 1; 
    DCH0CSIZ= 0x01;
    // DCHPDAT 0; 
    DCH0DAT= 0x00;
    // Clearing Channel 0 Interrupt Flag;
    IFS3CLR= 1 << _IFS3_DMA0IF_POSITION;
    // Enabling Channel 0 Interrupt
    IEC3bits.DMA0IE = 1;

    // CHEN disabled; CHCHNS Chain to channel higher; CHAEN disabled; CHCHN disabled; CHBUSY disabled; CHPRI Priority 0; CHAED disabled; 
    DCH1CON= 0x00 & 0xFF7F; //Enable DMA Channel later;
    // AIRQEN disabled; CHAIRQ 0; SIRQEN disabled; CHSIRQ 0; CABORT disabled; PATEN disabled; CFORCE disabled; 
    DCH1ECON= 0x00;
    // CHSDIE enabled; CHSDIF No interrupt; CHERIF No interrupt; CHSHIE disabled; CHSHIF No interrupt; CHERIE enabled; CHCCIF No interrupt; CHBCIE disabled; CHBCIF No interrupt; CHDDIF No interrupt; CHDDIE enabled; CHCCIE disabled; CHDHIF No interrupt; CHDHIE disabled; CHTAIE disabled; CHTAIF No interrupt; 
    DCH1INT= 0xA10000;
    // CHSSA 0; 
    DCH1SSA= 0x00;
    // CHDSA 0; 
    DCH1DSA= 0x00;
    // CHSSIZ 0; 
    DCH1SSIZ= 0x00;
    // CHDSIZ 0; 
    DCH1DSIZ= 0x00;
    // CHCSIZ 1; 
    DCH1CSIZ= 0x01;
    // DCHPDAT 0; 
    DCH1DAT= 0x00;
    // Clearing Channel 1 Interrupt Flag;
    IFS3CLR= 1 << _IFS3_DMA1IF_POSITION;

    // CHPRI Priority 0; CHCHNS Chain to channel higher; CHAEN disabled; CHCHN disabled; CHEN disabled; CHBUSY disabled; CHAED disabled; 
    DCH2CON= 0x00 & 0xFF7F; //Enable DMA Channel later;
    // AIRQEN disabled; CHAIRQ 0; SIRQEN disabled; CABORT disabled; PATEN disabled; CHSIRQ 0; CFORCE disabled; 
    DCH2ECON= 0x00;
    // CHSDIE enabled; CHSDIF No interrupt; CHERIF No interrupt; CHSHIE disabled; CHSHIF No interrupt; CHERIE enabled; CHCCIF No interrupt; CHBCIE disabled; CHBCIF No interrupt; CHDDIF No interrupt; CHDDIE enabled; CHCCIE disabled; CHDHIF No interrupt; CHDHIE disabled; CHTAIE disabled; CHTAIF No interrupt; 
    DCH2INT= 0xA10000;
    // CHSSA 0; 
    DCH2SSA= 0x00;
    // CHDSA 0; 
    DCH2DSA= 0x00;
    // CHSSIZ 0; 
    DCH2SSIZ= 0x00;
    // CHDSIZ 0; 
    DCH2DSIZ= 0x00;
    // CHCSIZ 1; 
    DCH2CSIZ= 0x01;
    // DCHPDAT 0; 
    DCH2DAT= 0x00;
    // Clearing Channel 2 Interrupt Flag;
    IFS3CLR= 1 << _IFS3_DMA2IF_POSITION;

    // CHPRI Priority 0; CHAED disabled; CHEN disabled; CHCHNS Chain to channel higher; CHCHN disabled; CHAEN disabled; CHBUSY disabled; 
    DCH3CON= 0x00 & 0xFF7F; //Enable DMA Channel later;
    // AIRQEN disabled; CHAIRQ 0; SIRQEN disabled; CABORT disabled; PATEN disabled; CHSIRQ 0; CFORCE disabled; 
    DCH3ECON= 0x00;
    // CHSDIE enabled; CHSDIF No interrupt; CHERIF No interrupt; CHSHIE disabled; CHSHIF No interrupt; CHERIE enabled; CHCCIF No interrupt; CHBCIE disabled; CHBCIF No interrupt; CHDDIF No interrupt; CHDDIE enabled; CHCCIE disabled; CHDHIF No interrupt; CHDHIE disabled; CHTAIE disabled; CHTAIF No interrupt; 
    DCH3INT= 0xA10000;
    // CHSSA 0; 
    DCH3SSA= 0x00;
    // CHDSA 0; 
    DCH3DSA= 0x00;
    // CHSSIZ 0; 
    DCH3SSIZ= 0x00;
    // CHDSIZ 0; 
    DCH3DSIZ= 0x00;
    // CHCSIZ 1; 
    DCH3CSIZ= 0x01;
    // DCHPDAT 0; 
    DCH3DAT= 0x00;
    // Clearing Channel 3 Interrupt Flag;
    IFS3CLR= 1 << _IFS3_DMA3IF_POSITION;
    
    //Enable DMA
    DMACONbits.ON = 1; 
    
    //Enable DMA Channel 0
    DCH0CONbits.CHEN = 1;
}

void __attribute__ ((weak)) DMA_Channel0_CallBack(void)
{
    // Add your custom callback code here
    //IO_RB8_Toggle();
    IO_RB8_Toggle();
    //if(DCH0INTbits.CHSDIF)
        if(DCH0INTbits.CHBCIF)
        {
           // LATDbits.LATD0=1;
            LATDINV=1<<0;
             DMA_BUSY=0;
             
         //   DMA_BUSY=0;
    }
   //  IEC3bits.DMA0IE = 0 ; /*disable DMA0 interrupt, datasheet page 66*/
  //  IFS3bits.DMA0IF = 0 ; // 
    IEC0bits.T2IE=0;
   IFS0bits.T2IF=0;
    DCH0CONCLR=1<<7;
   DCH0INTCLR = 0xFF;
   DMACONbits.ON=0;
}

void __attribute__ ( ( vector ( _DMA0_VECTOR ) , interrupt ( IPL1SOFT ) ) ) DMA0_ISR( void )
{
    DMA_Channel0_CallBack();

    //Clear flag
    IFS3CLR= 1 << _IFS3_DMA0IF_POSITION;
}

void __attribute__ ((weak)) DMA_Channel1_CallBack(void)
{
    // Add your custom callback code here
  // DCH1INTCLR = 0xFF;
}

void __attribute__ ( ( vector ( _DMA1_VECTOR ) , interrupt ( IPL1SOFT ) ) ) DMA1_ISR( void )
{
    DMA_Channel1_CallBack();

    //Clear flag
    IFS3CLR= 1 << _IFS3_DMA1IF_POSITION;
}

void __attribute__ ((weak)) DMA_Channel2_CallBack(void)
{
    // Add your custom callback code here
}

void __attribute__ ( ( vector ( _DMA2_VECTOR ) , interrupt ( IPL1SOFT ) ) ) DMA2_ISR( void )
{
    DMA_Channel2_CallBack();

    //Clear flag
    IFS3CLR= 1 << _IFS3_DMA2IF_POSITION;
}

void __attribute__ ((weak)) DMA_Channel3_CallBack(void)
{
    // Add your custom callback code here
}

void __attribute__ ( ( vector ( _DMA3_VECTOR ) , interrupt ( IPL1SOFT ) ) ) DMA3_ISR( void )
{
    DMA_Channel3_CallBack();

    //Clear flag
    IFS3CLR= 1 << _IFS3_DMA3IF_POSITION;
}

void DMA_ChannelEnable(DMA_CHANNEL  channel)
{
    switch(channel) {
        case DMA_CHANNEL_0:
                DCH0CONbits.CHEN = 1;
                IFS3CLR= 1 << _IFS3_DMA0IF_POSITION;
                IEC3bits.DMA0IE = 1;
                break; 
        case DMA_CHANNEL_1:
                DCH1CONbits.CHEN = 1;
                IFS3CLR= 1 << _IFS3_DMA1IF_POSITION;
                IEC3bits.DMA1IE = 1;
                break; 
        case DMA_CHANNEL_2:
                DCH2CONbits.CHEN = 1;
                IFS3CLR= 1 << _IFS3_DMA2IF_POSITION;
                IEC3bits.DMA2IE = 1;
                break; 
        case DMA_CHANNEL_3:
                DCH3CONbits.CHEN = 1;
                IFS3CLR= 1 << _IFS3_DMA3IF_POSITION;
                IEC3bits.DMA3IE = 1;
                break; 
        default: break;
    }
}
void DMA_ChannelDisable(DMA_CHANNEL  channel)
{
    switch(channel) {
        case DMA_CHANNEL_0:
                DCH0CONbits.CHEN = 0;
                IFS3CLR= 1 << _IFS3_DMA0IF_POSITION;
                IEC3bits.DMA0IE = 0;
                break;    
        case DMA_CHANNEL_1:
                DCH1CONbits.CHEN = 0;
                IFS3CLR= 1 << _IFS3_DMA1IF_POSITION;
                IEC3bits.DMA1IE = 0;
                break;    
        case DMA_CHANNEL_2:
                DCH2CONbits.CHEN = 0;
                IFS3CLR= 1 << _IFS3_DMA2IF_POSITION;
                IEC3bits.DMA2IE = 0;
                break;    
        case DMA_CHANNEL_3:
                DCH3CONbits.CHEN = 0;
                IFS3CLR= 1 << _IFS3_DMA3IF_POSITION;
                IEC3bits.DMA3IE = 0;
                break;    
        default: break;
    }
}
void DMA_TransferStartEnable(DMA_CHANNEL  channel)
{
    switch(channel) {
        case DMA_CHANNEL_0:
                DCH0ECONbits.CFORCE = 1;
                break; 
        case DMA_CHANNEL_1:
                DCH1ECONbits.CFORCE = 1;
                break; 
        case DMA_CHANNEL_2:
                DCH2ECONbits.CFORCE = 1;
                break; 
        case DMA_CHANNEL_3:
                DCH3ECONbits.CFORCE = 1;
                break; 
        default: break;
    }
}
void DMA_TransferAbortEnable(DMA_CHANNEL  channel)
{
    switch(channel) {
        case DMA_CHANNEL_0:
                DCH0ECONbits.CABORT = 1;
                break; 
        case DMA_CHANNEL_1:
                DCH1ECONbits.CABORT = 1;
                break; 
        case DMA_CHANNEL_2:
                DCH2ECONbits.CABORT = 1;
                break; 
        case DMA_CHANNEL_3:
                DCH3ECONbits.CABORT = 1;
                break; 
        default: break;
    }
}
void DMA_TransferStartIRQEnable(DMA_CHANNEL  channel)
{
    switch(channel) {
        case DMA_CHANNEL_0:
                DCH0ECONbits.SIRQEN = 1;
                break; 
        case DMA_CHANNEL_1:
                DCH1ECONbits.SIRQEN = 1;
                break; 
        case DMA_CHANNEL_2:
                DCH2ECONbits.SIRQEN = 1;
                break; 
        case DMA_CHANNEL_3:
                DCH3ECONbits.SIRQEN = 1;
                break; 
        default: break;
    }
}
void DMA_TransferAbortIRQEnable(DMA_CHANNEL  channel)
{
    switch(channel) {
        case DMA_CHANNEL_0:
                DCH0ECONbits.AIRQEN = 1;
                break; 
        case DMA_CHANNEL_1:
                DCH1ECONbits.AIRQEN = 1;
                break; 
        case DMA_CHANNEL_2:
                DCH2ECONbits.AIRQEN = 1;
                break; 
        case DMA_CHANNEL_3:
                DCH3ECONbits.AIRQEN = 1;
                break; 
        default: break;
    }
}
void DMA_SourceSizeSet(DMA_CHANNEL channel, uint16_t sourceSize)
{
    switch(channel) {
        case DMA_CHANNEL_0:
                DCH0SSIZ = sourceSize;
                break;
        case DMA_CHANNEL_1:
                DCH1SSIZ = sourceSize;
                break;
        case DMA_CHANNEL_2:
                DCH2SSIZ = sourceSize;
                break;
        case DMA_CHANNEL_3:
                DCH3SSIZ = sourceSize;
                break;
        default: break;
    }
}
void DMA_DestinationSizeSet(DMA_CHANNEL channel, uint16_t destinationSize)
{
    switch(channel) {
        case DMA_CHANNEL_0:
                DCH0DSIZ = destinationSize;
                break;
        case DMA_CHANNEL_1:
                DCH1DSIZ = destinationSize;
                break;
        case DMA_CHANNEL_2:
                DCH2DSIZ = destinationSize;
                break;
        case DMA_CHANNEL_3:
                DCH3DSIZ = destinationSize;
                break;
        default: break;
    }
}
void DMA_TransferCountSet(DMA_CHANNEL channel, uint16_t transferCount)
{
    switch(channel) {
        case DMA_CHANNEL_0:
                DCH0CSIZ = transferCount;
                break;
        case DMA_CHANNEL_1:
                DCH1CSIZ = transferCount;
                break;
        case DMA_CHANNEL_2:
                DCH2CSIZ = transferCount;
                break;
        case DMA_CHANNEL_3:
                DCH3CSIZ = transferCount;
                break;
        default: break;
    }
}
uint16_t DMA_TransferCountGet(DMA_CHANNEL channel)
{
    switch(channel) {
        case DMA_CHANNEL_0:
                return (DCH0CSIZ);
        case DMA_CHANNEL_1:
                return (DCH1CSIZ);
        case DMA_CHANNEL_2:
                return (DCH2CSIZ);
        case DMA_CHANNEL_3:
                return (DCH3CSIZ);
        default: return 0;
    }
}
void DMA_SourceAddressSet(DMA_CHANNEL  channel, uint32_t address) {
    switch(channel) {
        case DMA_CHANNEL_0:
                // Convert virtual address to physical address
                DCH0SSA = (address & 0x1FFFFFFF);
                break;
        case DMA_CHANNEL_1:
                // Convert virtual address to physical address
                DCH1SSA = (address & 0x1FFFFFFF);
                break;
        case DMA_CHANNEL_2:
                // Convert virtual address to physical address
                DCH2SSA = (address & 0x1FFFFFFF);
                break;
        case DMA_CHANNEL_3:
                // Convert virtual address to physical address
                DCH3SSA = (address & 0x1FFFFFFF);
                break;
        default: break;
    }    
}

void DMA_DestinationAddressSet(DMA_CHANNEL  channel, uint32_t address) {
    switch(channel) {
        case DMA_CHANNEL_0:
                // Convert virtual address to physical address
                DCH0DSA = (address & 0x1FFFFFFF);
                break;
        case DMA_CHANNEL_1:
                // Convert virtual address to physical address
                DCH1DSA = (address & 0x1FFFFFFF);
                break;
        case DMA_CHANNEL_2:
                // Convert virtual address to physical address
                DCH2DSA = (address & 0x1FFFFFFF);
                break;
        case DMA_CHANNEL_3:
                // Convert virtual address to physical address
                DCH3DSA = (address & 0x1FFFFFFF);
                break;
        default: break;
    }    
}

DMA_STATUS DMA_StatusGet (DMA_CHANNEL channel ) {
    switch(channel) {
        case DMA_CHANNEL_0:
                return (DCH0INT);
        case DMA_CHANNEL_1:
                return (DCH1INT);
        case DMA_CHANNEL_2:
                return (DCH2INT);
        case DMA_CHANNEL_3:
                return (DCH3INT);
        default: return 0;
    }    
}




/* 
void __ISR(_DMA0_VECTOR) __DMA0Interrupt(void)
{
PORTBbits.RB6 = 1 ;     /*set LED ON*/
//DCH0INTCLR = 0xFF;      /*clear existing all DMA0 Interrupt flag*/
//IFS3bits.DMA0IF = 0 ;   /*clear existing DMA0 channel 0 interrupt flag, datasheet page 66*/
//}

//*/
        