#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "SensorHcsr04.h"
#include "xparameters.h"
#include "xil_io.h"


u16 result;

int main()
{
    init_platform();

	for(;;){
    print("Measuring....\n\r");
    result =  SENSORHCSR04_mReadReg(XPAR_SENSORHCSR04_0_S00_AXI_BASEADDR,SENSORHCSR04_S00_AXI_SLV_REG0_OFFSET);
    printf("Reg0: %d\n\r", result);
     result = SENSORHCSR04_mReadReg(XPAR_SENSORHCSR04_0_S00_AXI_BASEADDR,SENSORHCSR04_S00_AXI_SLV_REG1_OFFSET);
    printf("Reg1:%d\n\r", result);
     result = SENSORHCSR04_mReadReg(XPAR_SENSORHCSR04_0_S00_AXI_BASEADDR,SENSORHCSR04_S00_AXI_SLV_REG2_OFFSET);
    printf("Reg2:%d\n\r", result);
     result = SENSORHCSR04_mReadReg(XPAR_SENSORHCSR04_0_S00_AXI_BASEADDR,SENSORHCSR04_S00_AXI_SLV_REG3_OFFSET);
    printf("Reg3:%d\n\r", result);
	}

    cleanup_platform();
    return 0;
}