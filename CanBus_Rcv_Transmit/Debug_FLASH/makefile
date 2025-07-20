################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include generate/src/subdir.mk
-include board/subdir.mk
-include RTD/src/subdir.mk
-include Project_Settings/Startup_Code/subdir.mk
-include Project_Settings/Linker_Files/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_SIZE += \
FlexCAN_Ip_Example_S32K344.siz \


# All Target
all: FlexCAN_Ip_Example_S32K344.elf secondary-outputs

# Tool invocations
FlexCAN_Ip_Example_S32K344.elf: $(OBJS) C:/Users/acalg/OneDrive/Belgeler/github/S32K344_Examples/CanBus_Rcv_Transmit/Project_Settings/Linker_Files/linker_flash_s32k344.ld $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Standard S32DS C Linker'
	arm-none-eabi-gcc -o "FlexCAN_Ip_Example_S32K344.elf" "@FlexCAN_Ip_Example_S32K344.args"  $(USER_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

FlexCAN_Ip_Example_S32K344.siz: FlexCAN_Ip_Example_S32K344.elf
	@echo 'Invoking: Standard S32DS Print Size'
	arm-none-eabi-size --format=berkeley FlexCAN_Ip_Example_S32K344.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) ./*
	-@echo ' '

post-build:
	-arm-none-eabi-objcopy -v -O srec "FlexCAN_Ip_Example_S32K344.elf" "FlexCAN_Ip_Example_S32K344.s19";arm-none-eabi-objcopy -v -O ihex "FlexCAN_Ip_Example_S32K344.elf" "FlexCAN_Ip_Example_S32K344.hex";arm-none-eabi-objcopy -v -O binary "FlexCAN_Ip_Example_S32K344.elf" "FlexCAN_Ip_Example_S32K344.bin";  C:/Users/acalg/OneDrive/Belgeler/github/S32K344_Examples/CanBus_Rcv_Transmit\\..\\NXPBuggerTools\\nbc.exe  C:/Users/acalg/OneDrive/Belgeler/github/S32K344_Examples/CanBus_Rcv_Transmit\\ConfigFile\\nbc.cfg "FlexCAN_Ip_Example_S32K344.bin" "FlexCAN_Ip_Example_S32K344.cwa"
	-@echo ' '

secondary-outputs: $(SECONDARY_SIZE)

.PHONY: all clean dependents post-build

-include ../makefile.targets
