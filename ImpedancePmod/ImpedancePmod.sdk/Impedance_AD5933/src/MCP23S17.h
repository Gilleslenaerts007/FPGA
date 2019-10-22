#ifndef _MCP23S17_H_
#define _MCP23S17_H_

/*****************************************************************************/
/***************************** Include Files *********************************/
/*****************************************************************************/
#include "xil_types.h"
#include "xparameters.h"
#include "xspi.h"		/* SPI device driver */
//#include "xiic.h"
#include "xil_exception.h"
#include "xgpiops.h"
#include "sleep.h"
#include "platform_config.h"
#include "xil_printf.h"
#include "platform.h"

// MCP23S17 SPI Address
//#define SPI_BASEADDR 					XPAR_AXI_SPI_0_BASEADDR
#define MCP23S17_SPI_ADDR      			0x40

// Registers Address
#define    IODIRA    (0x00)      // MCP23x17 I/O Direction Register
#define    IODIRB    (0x01)      // 1 = Input (default), 0 = Output
#define GPIOA_ADR 0x12  // port A
#define GPIOB_ADR 0x13  // port B

// I/O config
#define BANK_OFF 0x00  // addressing mode
#define BANK_ON 0x80
#define HAEN_ON 0x08  // hardware addressing (A2,A1,A0) all GND IF ON
#define HAEN_OFF 0x00

// MCP GPIO Port Selection Defines
#define	GPB0	0x01
#define	GPB1	0x02
#define	GPB2	0x04
#define	GPB3	0x08
#define	GPB4	0x10
#define	GPB5	0x20
#define	GPB6	0x40
#define	GPB7	0x80
#define	GPA0	0x01
#define	GPA1	0x02
#define	GPA2	0x04
#define	GPA3	0x08
#define	GPA4	0x10
#define	GPA5	0x20
#define	GPA6	0x40
#define	GPA7	0x80

// User DEFINES
#define BUFFER_SIZE 3
#define gpioSelect 0x0000FF // mask for GPIO port selection

#define SPI_DEVICE_ID		XPAR_SPI_0_DEVICE_ID
static XSpi SpiInstance;

static XGpioPs Gpio; /* The Instance of the GPIO Driver */
#define GPIO_BANK	XGPIOPS_BANK0
u32 Input_Pin;

typedef u8 dataBuffer[BUFFER_SIZE];
char readBuffer[BUFFER_SIZE];
u8 writeBuffer[BUFFER_SIZE];
char dummybuffer[BUFFER_SIZE];

char arrayGPB[3], arrayGPA[3];

/**
* sorts input array on GPIO adresses and sends SPI port selects to both registers(GPA&GPB).
 */
void portSelection(char RegisterADR, char Port);

/*
* Start SPI module with correct register values.
 */
int SPIStart(XSpi* spiPTR, u16 spiID);

#endif	// _MCP23S17_H_
