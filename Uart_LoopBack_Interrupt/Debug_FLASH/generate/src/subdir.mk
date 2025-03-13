################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../generate/src/Clock_Ip_Cfg.c \
../generate/src/Igf_Port_Ip_Cfg.c \
../generate/src/IntCtrl_Ip_Cfg.c \
../generate/src/Lpuart_Uart_Ip_Sa_PBcfg.c \
../generate/src/OsIf_Cfg.c \
../generate/src/Pit_Ip_PBcfg.c 

OBJS += \
./generate/src/Clock_Ip_Cfg.o \
./generate/src/Igf_Port_Ip_Cfg.o \
./generate/src/IntCtrl_Ip_Cfg.o \
./generate/src/Lpuart_Uart_Ip_Sa_PBcfg.o \
./generate/src/OsIf_Cfg.o \
./generate/src/Pit_Ip_PBcfg.o 

C_DEPS += \
./generate/src/Clock_Ip_Cfg.d \
./generate/src/Igf_Port_Ip_Cfg.d \
./generate/src/IntCtrl_Ip_Cfg.d \
./generate/src/Lpuart_Uart_Ip_Sa_PBcfg.d \
./generate/src/OsIf_Cfg.d \
./generate/src/Pit_Ip_PBcfg.d 


# Each subdirectory must supply rules for building sources it contributes
generate/src/%.o: ../generate/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@generate/src/Clock_Ip_Cfg.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


