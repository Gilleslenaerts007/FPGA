/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * NEED TO ADD GAINFACTOR ARRAY ON WHOLE FREQ SWEEP
 * CHANGE ARRAY TYPE FOR MAGN,REAL,IMAGINARY...
 */

#include <stdio.h>

#include "platform.h"
#include "xil_printf.h"
#include "xil_types.h"
#include "xil_exception.h"
#include "AD5933.h"
#include "MCP23S17.h"
#include "platform.h"
#include "xparameters.h"
#include "sleep.h"

#include "xuartps_hw.h"
#include "xgpiops.h"

//GPIOPS
static XGpioPs Gpio; /* The Instance of the GPIO Driver */
#define GPIO_BANK	XGPIOPS_BANK0
u32 Input_Pin;

void startGPIOPS();

int temper;

int main()
{
	init_platform();
	int rcalChoice;
    int Status;
    startGPIOPS();
    Status = SPIStart(&SpiInstance, SPI_DEVICE_ID);
    if(Status != XST_SUCCESS) {
    	return XST_FAILURE;
    }

    //Init MCPS GPIO EXAPNDER WITH CORRECT CONFIG
    setConfig[0] = MCP23S17_SPI_ADDR;
    setConfig[1] = IOCON;
    setConfig[2] = BANK_OFF | INT_MIRROR_OFF | SEQOP_OFF | DISSLW_OFF | HAEN_ON |  ODR_OFF |  INTPOL_LOW;
    XSpi_Transfer(&SpiInstance, setConfig, readBuffer, BUFFER_SIZE);

    //Set IO Directions
    setDirections[0] = MCP23S17_SPI_ADDR;
    setDirections[1] = IODIRA;
    setDirections[2] = 0x00;
    XSpi_Transfer(&SpiInstance, setDirections, readBuffer, BUFFER_SIZE);
    setDirections[1] = IODIRB;
    XSpi_Transfer(&SpiInstance, setDirections, readBuffer, BUFFER_SIZE);

    //Set Pullups
    setPullupsB[0] = MCP23S17_SPI_ADDR;
    setPullupsB[1] = GPPUA;
    setPullupsB[2] = 0x00;
    XSpi_Transfer(&SpiInstance, setPullupsB, readBuffer, BUFFER_SIZE);
    setPullupsB[1] = GPPUB;
    XSpi_Transfer(&SpiInstance, setPullupsB, readBuffer, BUFFER_SIZE);

	//Select ports
	arrayGPB[0] = MCP23S17_SPI_ADDR;
	arrayGPA[0] = MCP23S17_SPI_ADDR;

	arrayGPA[1] = GPIOA_ADR;
	arrayGPB[1] = GPIOB_ADR;

	arrayGPA[2] = 0x00;
	arrayGPB[2] = 0x00;

	XSpi_Transfer(&SpiInstance, arrayGPB, readBuffer, BUFFER_SIZE);
	XSpi_Transfer(&SpiInstance, arrayGPA, readBuffer, BUFFER_SIZE);

    print("EIT: Impedance measurement program by Gilles Lenaerts.\n\r");
    while(1){

    	//Debugging AD5933 Chip.
    	//temper = AD5933_GetTemperature();
    	//xil_printf("temp.:%d\n\r", temper);
    	if (XGpioPs_ReadPin(&Gpio, Input_Pin))
    	{
    		rcalChoice=0;
    		probeCurrentCycle=1;
    		probeVoltCycle = 0;
    		print("Choose Rcal for measurement..1,2 or 3. //Debugging\n\r");

    	    //Calibrate AD5933 with x resistor (10K Rcal 1)
    		while (rcalChoice == 0)
    		{
    			rcalChoice = inbyte(); //krijgt een Decimal 49 bij 1, 50 bij 2 -> -48 bij transfer naar func.
    		}
    		calibration(RCal_RFB_Select(rcalChoice-48,1)); // Loopt vast als er geen hw connected is bij AD5933GetTemp(), logisch :)
    		//debugging rcal for reference
    		//measureImpedance();
    		//writeSerialImpedanceArray();

    		//Measurement Cycle
        	while (probeCurrentCycle <= 8){
            	probeMeasureSelect();
            	if (probeCurrentCycle > 8) break;
            	measureImpedance();

        	}
    	}
    }
    cleanup_platform();
    return 0;
}

void startGPIOPS()
{
	//volatile int Delay;

	int status;
	XGpioPs_Config *GPIOConfigPtr;

	GPIOConfigPtr = XGpioPs_LookupConfig(XPAR_PS7_GPIO_0_DEVICE_ID);
	status = XGpioPs_CfgInitialize(&Gpio, GPIOConfigPtr,GPIOConfigPtr->BaseAddr);

	if (status != XST_SUCCESS) {
		printf("status error \n\r");
		return XST_FAILURE;
	}

    printf("Starting GPIO PS..\n\r");
	// Set Input pin
    Input_Pin = 0;
	XGpioPs_SetDirectionPin(&Gpio,Input_Pin,0);
}
