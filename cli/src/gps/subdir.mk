################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/gps/gpsClient.c 

OBJS += \
./src/gps/gpsClient.o 

C_DEPS += \
./src/gps/gpsClient.d 


# Each subdirectory must supply rules for building sources it contributes
src/gps/%.o: ../src/gps/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


