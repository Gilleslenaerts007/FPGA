################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/drivers/DigiLED_v1_0/src/DigiLED.c 

OBJS += \
./src/drivers/DigiLED_v1_0/src/DigiLED.o 

C_DEPS += \
./src/drivers/DigiLED_v1_0/src/DigiLED.d 


# Each subdirectory must supply rules for building sources it contributes
src/drivers/DigiLED_v1_0/src/%.o: ../src/drivers/DigiLED_v1_0/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 gcc compiler'
	arm-none-eabi-gcc -Wall -O0 -g3 -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -I../../Digiled_bsp/ps7_cortexa9_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


