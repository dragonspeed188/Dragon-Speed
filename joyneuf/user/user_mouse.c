/*********************************************************************
 *
 *                Microchip USB C18 Firmware - Mouse Demo
 *
 *********************************************************************
 * FileName:        user_mouse.c
 * Dependencies:    See INCLUDES section below
 * Processor:       PIC18
 * Compiler:        C18 2.30.01+
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * The software supplied herewith by Microchip Technology Incorporated
 * (the ìCompanyÅE for its PICmicroÆ Microcontroller is intended and
 * supplied to you, the Companyís customer, for use solely and
 * exclusively on Microchip PICmicro Microcontroller products. The
 * software is owned by the Company and/or its supplier, and is
 * protected under applicable copyright laws. All rights are reserved.
 * Any use in violation of the foregoing restrictions may subject the
 * user to criminal sanctions under applicable laws, as well as to
 * civil liability for the breach of the terms and conditions of this
 * license.
 *
 * THIS SOFTWARE IS PROVIDED IN AN ìAS ISÅECONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Rawin Rojvanit       11/19/04    Original.
 ********************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include <usart.h>
#include "system\typedefs.h"

#include "system\usb\usb.h"

#include "io_cfg.h"             // I/O pin mapping
#include "user\user_mouse.h"
#include "delays.h"

/** V A R I A B L E S ********************************************************/
#pragma udata
char buffer[4];

/** P R I V A T E  P R O T O T Y P E S ***************************************/


/** D E C L A R A T I O N S **************************************************/
#pragma code
void UserInit(void)
{
	TRISA = 0x01;
}//end UserInit

/******************************************************************************
 * Function:        void ProcessIO(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is a place holder for other user routines.
 *                  It is a mixture of both USB and non-USB tasks.
 *
 * Note:            None
 *****************************************************************************/
void ProcessIO(void)
{   
    if((usb_device_state < CONFIGURED_STATE)||(UCONbits.SUSPND==1)) return;

	if(PORTAbits.RA0!=0) {
		buffer[0]=0;
		buffer[1]=0;
		buffer[2]=0;
		buffer[3]=0;
		if(!mHIDTxIsBusy()) HIDTxReport(buffer,4);
	}
	else {
		buffer[0]=-100;	//Throttle
		buffer[1]=150;	//X axis
		buffer[2]=-10;	//Y axis
		buffer[3]=0x41; //0001 0001 
//As for buffer[3],
//first 4 bits 0100 correspond to button #3 
//last 4 bits 0001 correspond to hat switch and mean a 90-deg rotation (counter clockwise)

		if(!mHIDTxIsBusy()) HIDTxReport(buffer,4);
	}		

}//end ProcessIO

/** EOF user_mouse.c *********************************************************/
