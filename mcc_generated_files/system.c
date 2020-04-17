
#include "pin_manager.h"
#include "clock.h"
#include "system.h"
#include "uart2.h"
#include "uart1.h"
#include "tmr3.h"
#include "interrupt_manager.h"
#include "exceptions.h"
#include "tmr1.h"
#include "../pliki/dma.h"

void SYSTEM_Initialize(void)
{
    PIN_MANAGER_Initialize();
    CLOCK_Initialize();
    INTERRUPT_Initialize();
    UART2_Initialize();
    UART1_Initialize();
    TMR3_Initialize();
    TMR1_Initialize();
    //---------modyfikacje najne
    Timer2_init(); // moja funcka
    moj_dma_init();
    INTERRUPT_GlobalEnable();
}

/**
 End of File
*/