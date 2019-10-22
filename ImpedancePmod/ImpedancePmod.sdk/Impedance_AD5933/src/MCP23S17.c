#include <stdio.h>
#include <math.h>
//#include "xparameters.h"
#include "MCP23S17.h"
//#include "xspi.h"		/* SPI device driver */
//#include "typedef.h"


/*
* Have to add Registers standard values, HAEN_ON, IODIR, BANK_ON
 */
int SPIStart(XSpi* spiPTR, u16 spiID){
	int Status;
	XSpi_Config *confPTR;

	confPTR = XSpi_LookupConfig(spiID);
	if(confPTR == NULL) {
		return XST_DEVICE_NOT_FOUND;
	}

	Status = XSpi_CfgInitialize(spiPTR, confPTR, confPTR->BaseAddress);
	if(Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	Status = XSpi_SetOptions(spiPTR, XSP_MASTER_OPTION |
			XSP_MANUAL_SSELECT_OPTION );
	if(Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	XSpi_Start(spiPTR);
	XSpi_IntrGlobalDisable(spiPTR);

	return XST_SUCCESS;
}

/*
* sorts input array on GPIO adresses.
 */
void portSelection(char RegisterADR, char Port){

	//arrayGPB[3], arrayGPA[3] = {0x00, 0x00, 0x00};
	//int size = (int)(sizeof(arraySelection) / sizeof(arraySelection[0]));

	if (RegisterADR == GPIOA_ADR) // GPIOA Register adress
	{
		arrayGPA[1] = GPIOA_ADR;
		arrayGPA[2] = Port;
	}
	else if(RegisterADR == GPIOB_ADR) // GPIOB Register adress
	{
		arrayGPB[1] = GPIOB_ADR;
		arrayGPB[2] = Port;
	}

	arrayGPB[0] = MCP23S17_SPI_ADDR;
	arrayGPA[0] = MCP23S17_SPI_ADDR;

	return;
}

