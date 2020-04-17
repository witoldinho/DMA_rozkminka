/*
    File Name:        :  dma.c
    Device            :  PIC32MM0256GPM048
    Compiler          :  XC32 2.05
    MPLAB             :  MPLAB X 4.15
    Created by        :  http://strefapic.blogspot.com
*/

//#include <proc/p32mm0256gpm028.h>
//include <proc/p32mm0256gpm048.h>

#include "../mcc_generated_files/mcc.h"
#include "dma.h"
#include "xdma.h"

 uint8_t tab2[] = {2, 1, 2, 3, 4, 5, 6, 7, 8, 9, 100, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 20, 251, 252, 15, 254, 2}; 


char myWriteBuffer[] = "Witaj DMA"; /*bufor nadawczy*/

void DMA0_Initialize2(void){

IEC3bits.DMA0IE = 0 ; /*disable DMA0 interrupt, datasheet page 66*/
IFS3bits.DMA0IF = 0 ; /*clear any existing DMA channel 0 interrupt flag, datasheet page 66*/

DMACONbits.ON = 1; /*enable the DMA controller*/
DCH0CONbits.CHEN = 0; /* channel off*/
DCH0CONbits.CHPRI = 3; /*channel priority 3*/

DCH0ECON=0; /*no start or stop IRQs, no pattern match*/

DCH0SSA = ((uint32_t)myWriteBuffer & 0x1FFFFFFF); // Convert virtual address to physical address
DCH0DSA = ((uint32_t)&SPI2BUF & 0x1FFFFFFF); // Convert virtual address to physical address

DCH0SSIZ = sizeof(myWriteBuffer); /*source size*/
DCH0DSIZ = 1; /*desination size, one byte per SPI transfer */
DCH0CSIZ = sizeof(myWriteBuffer); /*cell size*/

DCH0INTCLR = 0xFF;      /*clear existing all Interrupt flag*/
DCH0INTbits.CHCCIE = 1; /*Channel Cell Transfer Complete Interrupt Enable bit*/

IPC24bits.DMA0IP = 1 ; /*set interrupt priority*/
IPC24bits.DMA0IS = 0 ; /*set interrupt subpriority*/

 DCH0CONbits.CHEN = 1; /*channel on*/
 IEC3bits.DMA0IE = 1; /*enable DMA0 interrupt, datasheet page 66*/
 IFS3bits.DMA0IF = 0;

}


void moj_dma_init(void)
{
    IEC3bits.DMA0IE = 0 ; /*disable DMA0 interrupt, datasheet page 66*/
IFS3bits.DMA0IF = 0 ; /*clear any existing DMA channel 0 interrupt flag, datasheet page 66*/

DMACONbits.ON = 1; /*enable the DMA controller*/
DCH0CONbits.CHEN = 0; /* channel off*/
DCH0CONbits.CHPRI = 3; /*channel priority 3*/
//DCH0CONbits.CHAEN=1; 

DCH0ECON=0; /*no start or stop IRQs, no pattern match*/
DCH0ECONbits.CHSIRQ=18 ;//timer 2 v3ector=18 _UART1_TX_VECTOR ; //_UART1_TX_VECTOR =54


DCH0SSA = ((uint32_t)tab2 & 0x1FFFFFFF); // Convert virtual address to physical address
DCH0DSA = ((uint32_t)&U1TXREG & 0x1FFFFFFF); // Convert virtual address to physical address

DCH0SSIZ = sizeof(tab2); /*source size*/
DCH0DSIZ = 1; /*desination size, one byte per SPI transfer */
DCH0CSIZ = 1; //sizeof(tab2); /*cell size*/

DCH0INTCLR = 0xFF;      /*clear existing all Interrupt flag*/
//DCH0INTbits.CHCCIE = 1; /*Channel Cell Transfer Complete Interrupt Enable bit*/
DCH0INTbits.CHSDIE=1;
DCH0ECONbits.SIRQEN=1;
  

IPC24bits.DMA0IP = 1 ; /*set interrupt priority*/
IPC24bits.DMA0IS = 0 ; /*set interrupt subpriority*/

 DCH0CONbits.CHEN = 1; /*channel on*/
 IEC3bits.DMA0IE = 1; /*enable DMA0 interrupt, datasheet page 66*/
 IFS3bits.DMA0IF = 0;

IFS0bits.T2IF=0;
    
}

void Timer2_init(void)
{
  //  INTERRUPT_GlobalDisable();
  
  
    //T2CONbits.ON=0;
    T2CON=0x0;
      IEC0bits.T2IE=0;
   IFS0bits.T2IF=0;
  //   T2CONbits.TON   = 1;
    
    TMR2=0;
     T2CONbits.TCKPS=2;
     
     PR2= 131 ;// 12/(4x22728) - 1 = 131 
    IFS0bits.T2IF = 0;  // Clear interrupt flag for timer 2
    IPC4bits.T2IP=1;  // Interrupt priority 3
    IPC4bits.T2IS = 1;  // Sub-priority 1
 
    IEC0bits.T2IE = 1;  // Enable Timer 2 Interrupt
     T2CONbits.TON   = 1;
  // INTERRUPT_GlobalEnable();
    // Turn on timer 2
   
    
}

void dmafun(uint8_t *buffer, int num_bytes)
{
    
    IEC3bits.DMA0IE = 0 ; /*disable DMA0 interrupt, datasheet page 66*/
IFS3bits.DMA0IF = 0 ; /*clear any existing DMA channel 0 interrupt flag, datasheet page 66*/

DMACONbits.ON = 1; /*enable the DMA controller*/
DCH0CONbits.CHEN = 0; /* channel off*/
DCH0CONbits.CHPRI = 3; /*channel priority 3*/
//DCH0CONbits.CHAEN=1; 

DCH0ECON=0; /*no start or stop IRQs, no pattern match*/
DCH0ECONbits.CHSIRQ=18 ;//_UART1_TX_VECTOR ; //_UART1_TX_VECTOR =54


DCH0SSA = ((uint32_t)buffer & 0x1FFFFFFF); // Convert virtual address to physical address
DCH0DSA = ((uint32_t)&U1TXREG & 0x1FFFFFFF); // Convert virtual address to physical address

DCH0SSIZ = num_bytes; /*source size*/
DCH0DSIZ = 1; /*desination size, one byte per SPI transfer */
DCH0CSIZ = 1; //sizeof(tab2); /*cell size*/

DCH0INTCLR = 0xFF;      /*clear existing all Interrupt flag*/
//DCH0INTbits.CHCCIE = 1; /*Channel Cell Transfer Complete Interrupt Enable bit*/
DCH0INTbits.CHSDIE=1;
DCH0ECONbits.SIRQEN=1;
  

IPC24bits.DMA0IP = 1 ; /*set interrupt priority*/
IPC24bits.DMA0IS = 0 ; /*set interrupt subpriority*/
DCH0CONbits.CHEN = 1; /*channel on*/
 
 IEC3bits.DMA0IE = 1; /*enable DMA0 interrupt, datasheet page 66*/
 IFS3bits.DMA0IF = 0;

IFS0bits.T2IF=0;

}

void force(uint8_t *buffer, int num_bytes)
{
   IEC3bits.DMA0IE = 0 ; /*disable DMA0 interrupt, datasheet page 66*/
IFS3bits.DMA0IF = 0 ; /*clear any existing DMA channel 0 interrupt flag, datasheet page 66*/

DMACONbits.ON = 0; /*enable the DMA controller*/
DMACONbits.ON=1;
    DCH0CONCLR = 1 << 7;  //wylącz ch
//DCH0CONbits.CHEN = 0; /* channel off*/
DCH0CONbits.CHPRI = 3; /*channel priority 3*/
//DCH0CONbits.CHAEN=1; 

DCH0ECON=0; /*no start or stop IRQs, no pattern match*/
//DCH0ECONbits.CHSIRQ=18 ;//_UART1_TX_VECTOR ; //_UART1_TX_VECTOR =54



DCH0SSA = ((uint32_t)buffer & 0x1FFFFFFF); // Convert virtual address to physical address
DCH0DSA = ((uint32_t)&U1TXREG & 0x1FFFFFFF); // Convert virtual address to physical address

DCH0SSIZ = num_bytes; /*source size*/
DCH0DSIZ = 1; /*desination size, one byte per SPI transfer */
DCH0CSIZ = 1; //sizeof(tab2); /*cell size*/

DCH0INTCLR = 0xFF00FF;  ;      /*clear existing all Interrupt flag*/
//DCH0INTbits.CHCCIE = 1; /*Channel Cell Transfer Complete Interrupt Enable bit*/
//DCH0INTbits.CHSDIE=1;
DCH0INTbits.CHBCIF=1;
//DCH0ECONbits.SIRQEN=1;
  

IPC24bits.DMA0IP = 1 ; /*set interrupt priority*/
IPC24bits.DMA0IS = 0 ; /*set interrupt subpriority*/

 //DCH0CONbits.CHEN = 1; /*channel on*/
 DCH0CONSET = 1 << 7; 
 IEC3bits.DMA0IE = 1; /*enable DMA0 interrupt, datasheet page 66*/
 IFS3bits.DMA0IF = 0;

//IFS0bits.T2IF=0;  
    
 DCH0ECONbits.CFORCE=1;
    
}

void wysylka(const uint8_t *bufor)
{
    DMA_BUSY=1;
    IEC0bits.T2IE=1;
   // DMACONbits.ON=1;
    DCH0CONCLR=1<<7;
    LATBbits.LATB11=1;
    
     memcpy(tab2,bufor,512);
     LATBbits.LATB11=0;
    DCH0CONSET=1<<7;
    
}




void __attribute__ ((vector(_TIMER_2_VECTOR), interrupt(IPL1SOFT))) TMR2_ISR()
{
    IO_RB10_Toggle();
   //  IFS0CLR =1<_IFS0_T2IF_POSITION; //_IFS0_T2IF_MASK;
    IFS0bits.T2IF=0;
}



void __attribute__((used)) delayUs(unsigned int usec)
{
    unsigned int tWait, tStart;

    tWait=(SYSTEMCLOCK/2000000)*usec; 
    tStart=_mfc0(9,0);
    while((_mfc0(9,0)-tStart)<tWait);        // wait for the time to pass
}

  void __attribute__((used)) delayMs(unsigned int usec)
{
    unsigned int tWait, tStart;

    tWait=(SYSTEMCLOCK/2000)*usec; 
    tStart=_mfc0(9,0);
    while((_mfc0(9,0)-tStart)<tWait);        // wait for the time to pass
}

/* 
void __ISR(_DMA0_VECTOR) __DMA0Interrupt(void)
{
PORTBbits.RB6 = 1 ;     /*set LED ON*/
//DCH0INTCLR = 0xFF;      /*clear existing all DMA0 Interrupt flag*/
//IFS3bits.DMA0IF = 0 ;   /*clear existing DMA0 channel 0 interrupt flag, datasheet page 66*/
//}

//*/
        



