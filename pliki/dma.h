/*
    File Name:        :  dma.h
    Device            :  PIC32MM0256GPM048
    Compiler          :  XC32 2.05
    MPLAB             :  MPLAB X 4.15
    Created by        :  http://strefapic.blogspot.com
*/


#ifndef _DMA_H
#define _DMA_H
#include <stdint.h> /*uint8_t etc.*/
#include <string.h>
#define  SYSTEMCLOCK 12000000 

extern uint8_t tab2[512];
extern  volatile uint8_t DMA_BUSY;


//char myWriteBuffer[] = "Witaj DMA"; /*bufor nadawczy*/
char myReadBuffer[10] ; /*bufor odbiorczy*/
void moj_dma_init(void); 
void DMA0_Initialize2 (void);
void Timer2_init(void);
void dmafun(uint8_t *buffer, int num_bytes);
void force(uint8_t *buffer, int num_bytes);
void wysylka(const uint8_t *bufor);
 void __attribute__((used)) delayUs(unsigned int usec);
 void __attribute__((used)) delayMs(unsigned int usec);


#endif

 /* 
 DMA0_handler catches the end of the DMA interrupt, which is advised over constantly checking the flag in a loop.
void __attribute__((vector(DMA_RX_INTERRUPT_FUNC(_,_VECTOR)), interrupt(DMA_RX_IPL_FUNC(IPL,SRS)), nomips16)) DMA_RX_handler()
{
    DMA_RX_IF_CLEAR();
    SPI_TX_IF_CLEAR();
    SPI_RX_IF_CLEAR();
    DMA_RX_IE_OFF();
    DCH_RX_CHAN_FUNC(CONCLR) = 1 << 7;                     // CHEN = 1
    DCH_TX_CHAN_FUNC(CONCLR) = 1 << 7;                     // CHEN = 1

    DMA_BUSY = 0;            // DMA is done / no longer busy
}
  * */