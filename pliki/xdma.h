/* 
 * File:   xdma.h
 * Author: workshop
 *
 * Created on 4 marca 2020, 07:55
 */

#ifndef XDMA_H
#define	XDMA_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* XDMA_H */

#include <stdint.h> /*uint8_t etc.*/
#include <stdio.h>


//char myWriteBuffer[] = "Witaj DMA"; /*bufor nadawczy*/
//char myReadBuffer[10] ; /*bufor odbiorczy*/
//void DMA0_Initialize (void);
extern uint8_t tab1[512];

void swiatlo_go(void);
void light_go(uint8_t *ramka);

typedef enum 
{
    DMA_CHANNEL_0 =  0,       
    DMA_CHANNEL_1 =  1,       
    DMA_CHANNEL_2 =  2,       
    DMA_CHANNEL_3 =  3,       
    DMA_NUMBER_OF_CHANNELS = 4
} DMA_CHANNEL;



/** DMA Driver Hardware Flags

  @Summary
    Specifies the status of the DMA transfer 

  @Description
    This type specifies the status of the DMA transfer.
    More than one of these values may be OR'd together to create a complete
    status value.  To test a value of this type, the bit of interest must be
    AND'ed with value and checked to see if the result is non-zero.
*/
typedef enum
{
    /* Indicates that a channel address error has been detected */
    DMA_ADDRESS_ERROR_FLAG
        /*DOM-IGNORE-BEGIN*/  = (1 << 0) /*DOM-IGNORE-END*/,
    
    /* Indicates that a matching CHAIRQ has been detected and DMA transfer has been aborted */
    DMA_TRANSFER_ABORT_FLAG
        /*DOM-IGNORE-BEGIN*/  = (1 << 1) /*DOM-IGNORE-END*/,

    /* Indicates that the cell transfer has completed */
    DMA_CELL_TX_COMPLETE
        /*DOM-IGNORE-BEGIN*/  = (1 << 2) /*DOM-IGNORE-END*/,

    /* Indicates that the block transfer has completed */
    DMA_BLOCK_TX_COMPLETE
        /*DOM-IGNORE-BEGIN*/  = (1 << 3) /*DOM-IGNORE-END*/,

    /* Indicates that the destination pointer has reached the midpoint */
    DMA_DESTINATION_HALF_FULL
        /*DOM-IGNORE-BEGIN*/  = (1 << 4) /*DOM-IGNORE-END*/,

    /* Indicates that the destination pointer has reached the endpoint */
    DMA_DESTINATION_FULL
        /*DOM-IGNORE-BEGIN*/  = (1 << 5) /*DOM-IGNORE-END*/,

    /* Indicates that the source pointer has reached the midpoint */
    DMA_SOURCE_HALF_EMPTY
        /*DOM-IGNORE-BEGIN*/  = (1 << 6) /*DOM-IGNORE-END*/,

        /* Indicates that the source pointer has reached the endpoint */
    DMA_SOURCE_EMPTY
        /*DOM-IGNORE-BEGIN*/  = (1 << 7) /*DOM-IGNORE-END*/

}DMA_STATUS;

/**
  Section: Interface Routines
*/

/**
  @Summary
    This function initializes DMA channels

  @Description
    This routine initializes the DMA driver channel 
    making it ready for clients to open and use it. It also initializes any
    internal data structures.
    This routine must be called before any other DMA routine is called. 

  @Preconditions
    None.

  @Param
    None.

  @Returns
    None.

  @Comment
    
 
  @Example
    <code>
        char srcArray[100];
        char dstArray[100];
        int i;
        
        for (i=0; i<100; i++)
        {
            srcArray[i] = i+1;
            dstArray[i] = 0;
        }
        
        DMA_Initialize();
        DMA_ChannelEnable(DMA_CHANNEL_1);
        DMA_TransferCountSet(DMA_CHANNEL_1, 100);
        DMA_SourceAddressSet(DMA_CHANNEL_1,(uint32_t)& srcArray);
        DMA_DestinationAddressSet(DMA_CHANNEL_1,(uint32_t)& dstArray);
        
        DMA_TransferStartEnable(DMA_CHANNEL_1);

        while(!(DMA_Status(DMA_CHANNEL_1) & DMA_BLOCK_TX_COMPLETE));
        //Check for transfer results after transfer completes
        DMA_ChannelDisable(DMA_CHANNEL_1);
    </code>

*/
void DMA_Initialize(void);
    
/**
 @Summary
  Enables the channel in the DMA

 @Description
  This routine is used to enable a channel in the DMA. This routine
  sets the value of the CHEN bit to 1.
 
 @Preconditions
  DMA_Initializer() function should have been 
  called before calling this function.
 
 @Returns
  None

 @Param
  None
  
 @Example
 Refer to DMA_Initializer(); for an example
 */
void DMA_ChannelEnable(DMA_CHANNEL  channel);
/**
 @Summary
 Disables the channel in the DMA

 @Description
  This routine is used to disable a channel in the DMA. This routine
  sets the value of the CHEN bit to 0.
 
@Preconditions
 DMA_Initializer() function should have been 
 called before calling this function.
 
@Returns
 None

@Param
 None
  
@Example
 Refer to DMA_Initializer(); for an example
*/
void DMA_ChannelDisable(DMA_CHANNEL  channel);
/**
 @Summary
  Enables the start of a transfer in the DMA

 @Description
  This routine is used to enable a transfer to start in DMA. This routine
  sets the value of the CFORCE bit to 1.
 
 @Preconditions
  DMA_Initializer() function should have been 
  called before calling this function.
 
 @Returns
  None

 @Param
  None
  
 @Example
 Refer to DMA_Initializer(); for an example
 */
void DMA_TransferStartEnable(DMA_CHANNEL  channel);
/**
 @Summary
  Enables the abort of a transfer in the DMA

 @Description
  This routine is used to enable a transfer to abort in DMA. This routine
  sets the value of the CABORT bit to 1.
 
 @Preconditions
  DMA_Initializer() function should have been 
  called before calling this function.
 
 @Returns
  None

 @Param
  None
  
 @Example
 Refer to DMA_Initializer(); for an example
 */
void DMA_TransferAbortEnable(DMA_CHANNEL  channel);
/**
 @Summary
  Enables the start of a transfer if an interrupt matching CHSIRQ occurs in the DMA

 @Description
  This routine is used to enable a transfer to start in DMA when a interrupt matching 
  CHSIRQ occurs. This routine sets the value of the SIRQEN bit to 1.
 
 @Preconditions
  DMA_Initializer() function should have been 
  called before calling this function.
 
 @Returns
  None

 @Param
  None
  
 @Example
 Refer to DMA_Initializer(); for an example
 */
void DMA_TransferStartIRQEnable(DMA_CHANNEL  channel);
/**
 @Summary
  Enables the abort of a transfer if an interrupt matching CHAIRQ occurs in the DMA

 @Description
  This routine is used to enable a transfer to abort in DMA when a interrupt matching 
  CHAIRQ occurs. This routine sets the value of the AIRQEN bit to 1.
 
 @Preconditions
  DMA_Initializer() function should have been 
  called before calling this function.
 
 @Returns
  None

 @Param
  None
  
 @Example
 Refer to DMA_Initializer(); for an example
 */
void DMA_TransferAbortIRQEnable(DMA_CHANNEL  channel);
/**
  @Summary
    Sets the source size of the DMA

  @Description
    This routine is used to set the DMA source size. This routine sets the
    value of the DCHSSIZ register. 
 
  @Preconditions
    DMA_Initializer() function should have been 
    called before calling this function.
 
  @Returns
    None

  @Param
    None
  
  @Example
    Refer to DMA_Initializer(); for an example
 */
void DMA_SourceSizeSet(DMA_CHANNEL channel, uint16_t sourceSize);
/**
  @Summary
    Sets the destination size of the DMA

  @Description
    This routine is used to set the DMA destination size. This routine sets the
    value of the DCHDSIZ register. 
 
  @Preconditions
    DMA_Initializer() function should have been 
    called before calling this function.
 
  @Returns
    None

  @Param
    None
  
  @Example
    Refer to DMA_Initializer(); for an example
 */
void DMA_DestinationSizeSet(DMA_CHANNEL channel, uint16_t destinationSize);
/**
  @Summary
    Sets the transfer count of the DMA

  @Description
    This routine is used to set the DMA transfer count. This routine sets the
    value of the DMACNT register. 
 
  @Preconditions
    DMA_Initializer() function should have been 
    called before calling this function.
 
  @Returns
    None

  @Param
    None
  
  @Example
    Refer to DMA_Initializer(); for an example
 */
void DMA_TransferCountSet(DMA_CHANNEL channel, uint16_t transferCount);
/**
  @Summary
    Returns the transfer count of the DMA

  @Description
    This routine is used to determine the DMA transfer count. This routine
    returns the value of the DMACNT register. 
 
  @Preconditions
    DMA_Initializer() function should have been 
    called before calling this function.
 
  @Returns
    Returns the transfer count of the DMA

  @Param
    None
  
  @Example
    Refer to DMA_Initializer(); for an example
 */
uint16_t DMA_TransferCountGet(DMA_CHANNEL channel);
/**
  @Summary
    Sets the source address for the DMA

  @Description
    This routine is used to set the source address for a DMA channel. 
 
  @Preconditions
    DMA_Initializer() function should have been 
    called before calling this function.
 
  @Returns
    None

  @Param
    None
  
  @Example
    Refer to DMA_Initializer(); for an example
 */
void DMA_SourceAddressSet(DMA_CHANNEL channel, uint32_t);
/**
  @Summary
    Sets the destination address for the DMA

  @Description
    This routine is used to set the destination address for a DMA channel. 
 
  @Preconditions
    DMA_Initializer() function should have been 
    called before calling this function.
 
  @Returns
    None

  @Param
    None
  
  @Example
    Refer to DMA_Initializer(); for an example
 */
void DMA_DestinationAddressSet(DMA_CHANNEL channel, uint32_t);
/**
  @Summary
    Returns the DMA transfer status

  @Description
    This returns the DMA transfer status. The returned status may 
    contain a value with more than one of the bits
    specified in the DMA_STATUS enumeration set.  
    The caller should perform an "AND" with the bit of interest and verify if the
    result is non-zero (as shown in the example) to verify the desired status
    bit.

  @Preconditions
    DMA_Initializer function should have been called 
    before calling this function

  @Param
    None.

  @Returns
    A DMA_STATUS value describing the current status 
    of the transfer.

  @Example
    <code>
        while(!(DMA_StatusGet & DMA_DST_FULL ))
        {
           // Wait for the tranmission to complete
        }
    </code>
*/

DMA_STATUS DMA_StatusGet ( DMA_CHANNEL channel);

/**
  @Summary
    Callback for DMA Channel0.

  @Description
    This routine is callback for DMA Channel0

  @Param
    None.

  @Returns
    None
 
  @Example 
    Refer to DMA_Initialize(); for an example
*/
void DMA_Channel0_CallBack(void);

/**
  @Summary
    Callback for DMA Channel1.

  @Description
    This routine is callback for DMA Channel1

  @Param
    None.

  @Returns
    None
 
  @Example 
    Refer to DMA_Initialize(); for an example
*/
void DMA_Channel1_CallBack(void);

/**
  @Summary
    Callback for DMA Channel2.

  @Description
    This routine is callback for DMA Channel2

  @Param
    None.

  @Returns
    None
 
  @Example 
    Refer to DMA_Initialize(); for an example
*/
void DMA_Channel2_CallBack(void);

/**
  @Summary
    Callback for DMA Channel3.

  @Description
    This routine is callback for DMA Channel3

  @Param
    None.

  @Returns
    None
 
  @Example 
    Refer to DMA_Initialize(); for an example
*/
void DMA_Channel3_CallBack(void);


void DMA_Init(DMA_CHANNEL  channel);
void DMA_Force(void);