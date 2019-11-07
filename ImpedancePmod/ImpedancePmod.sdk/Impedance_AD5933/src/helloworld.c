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
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "AD5933.h"
#include "MCP23S17.h"
#include "platform.h"
#include "xparameters.h"
#include "sleep.h"
//#include "xspi.h"		/* SPI device driver */
//#include "xiic.h"
//#include "xil_exception.h"
//#include "xgpiops.h"

#define RCAL 1		// choose 1,2,3
//#define RCAL2 2
//#define RCAL3 3

#define RFB 1		//choose 1,2,3,4
//#define RFB1 1
//#define RFB2 2
//#define RFB3 3
//#define RFB4 4

int main()
{
	init_platform();

	int probeVoltCycle, probeCurrentCycle = 0;  //cycle
	char RA, aPortSEL, bPortSEL = 0;

    int Status;
    startGPIOPS();
    Status = SPIStart(&SpiInstance, SPI_DEVICE_ID);
    if(Status != XST_SUCCESS) {
    	return XST_FAILURE;
    }

    print("EIT: Impedance measurement program by Gilles Lenaerts.\n\r");

    //Calibrate AD5933 with x resistor (41K now)
    calibration();


    while(1){

    	if (XGpioPs_ReadPin(&Gpio, Input_Pin))
    	{
    		probeCurrentCycle++;
    	}

    	if(probeCurrentCycle == 1)
    	{
			switch (probeVoltCycle)
			{
				case 1: aPortSEL = GPA1 | GPA2;
						bPortSEL = GPB0 | GPB7;
						break;

				case 2: aPortSEL = GPA3;
						bPortSEL = GPB0 | GPB6 | GPB7;
						break;

				case 3: aPortSEL = GPA0 | GPA1 | GPA3;
						bPortSEL = GPB0;
						break;

				case 4: aPortSEL = GPA0 | GPA2 | GPA3;
						bPortSEL=  GPB0 | GPB6;
						break;

				case 5:	aPortSEL = GPA0 | GPA1 | GPA2 | GPA3;
						bPortSEL=  GPB0 | GPB7;
						break;

				default: break;
			}
    	}
    	if(probeCurrentCycle == 2)
    	{

    	}


    	//Transfer & measure stage
    	portSelection(GPIOA_ADR,aPortSEL);
    	portSelection(GPIOB_ADR,bPortSEL);
    	XSpi_Transfer(&SpiInstance, arrayGPB, readBuffer, BUFFER_SIZE);
    	XSpi_Transfer(&SpiInstance, arrayGPA, readBuffer, BUFFER_SIZE);

    	measureImpedance();


    	// Prepare next cycle
    	if (probeVoltCycle > 5)
    		{
    			probeVoltCycle = 1;
    			if (probeCurrentCycle >= 8)
    			{
    				probeCurrentCycle = 0;
    			}
    			else probeCurrentCycle++;
    		}
    	else probeVoltCycle++;
    	//XSpi_SetSlaveSelect(&SpiInstance, 0x01);

    	//in = getchar();
 //   sleep_A9(3);
    }

    cleanup_platform();
    return 0;
}
void startGPIOPS()
{
	volatile int Delay;

	int status;
	XGpioPs_Config *GPIOConfigPtr;

	GPIOConfigPtr = XGpioPs_LookupConfig(XPAR_PS7_GPIO_0_DEVICE_ID);
	status = XGpioPs_CfgInitialize(&Gpio, GPIOConfigPtr,GPIOConfigPtr->BaseAddr);

	if (status != XST_SUCCESS) {
		printf("status error \n\r");
		return XST_FAILURE;
	}

    printf("Starting GPIO PS\n\r");

    printf("Running on MiniZED\n\r");
    	Input_Pin = 0;

	// Set Input pin
	XGpioPs_SetDirectionPin(&Gpio,Input_Pin,0);
	//Data = XGpioPs_ReadPin(&Gpio, Input_Pin);

    return;
}
