################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Project_Settings/Startup_Code/Vector_Table.s \
../Project_Settings/Startup_Code/startup_cm7.s 

C_SRCS += \
../Project_Settings/Startup_Code/exceptions.c \
../Project_Settings/Startup_Code/nvic.c \
../Project_Settings/Startup_Code/startup.c \
../Project_Settings/Startup_Code/system.c 

OBJS += \
./Project_Settings/Startup_Code/Vector_Table.o \
./Project_Settings/Startup_Code/exceptions.o \
./Project_Settings/Startup_Code/nvic.o \
./Project_Settings/Startup_Code/startup.o \
./Project_Settings/Startup_Code/startup_cm7.o \
./Project_Settings/Startup_Code/system.o 

C_DEPS += \
./Project_Settings/Startup_Code/exceptions.d \
./Project_Settings/Startup_Code/nvic.d \
./Project_Settings/Startup_Code/startup.d \
./Project_Settings/Startup_Code/system.d 


# Each subdirectory must supply rules for building sources it contributes
Project_Settings/Startup_Code/%.o: ../Project_Settings/Startup_Code/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS Assembler'
	arm-none-eabi-gcc "@Project_Settings/Startup_Code/Vector_Table.args" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Project_Settings/Startup_Code/%.o: ../Project_Settings/Startup_Code/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Project_Settings/Startup_Code/exceptions.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


