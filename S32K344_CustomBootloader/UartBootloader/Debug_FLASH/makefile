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
-include FreeRTOS/Source/portable/MemMang/subdir.mk
-include FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1/subdir.mk
-include FreeRTOS/Source/subdir.mk
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
UartBootloader.siz \


# All Target
all: UartBootloader.elf secondary-outputs

# Tool invocations
UartBootloader.elf: $(OBJS) C:/Users/ARGE13/Documents/Git/S32K344_Examples/S32K344_CustomBootloader/UartBootloader/Project_Settings/Linker_Files/linker_flash_s32k344.ld $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Standard S32DS C Linker'
	arm-none-eabi-gcc -o "UartBootloader.elf" "@UartBootloader.args"  $(USER_OBJS)  -lc -lm -lgcc
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

UartBootloader.siz: UartBootloader.elf
	@echo 'Invoking: Standard S32DS Print Size'
	arm-none-eabi-size --format=berkeley UartBootloader.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) ./*
	-@echo ' '

post-build:
	-arm-none-eabi-objcopy -v -O srec "UartBootloader.elf" "UartBootloader.s19";arm-none-eabi-objcopy -v -O ihex "UartBootloader.elf" "UartBootloader.hex";arm-none-eabi-objcopy -v -O binary "UartBootloader.elf" "UartBootloader.bin"
	-@echo ' '

secondary-outputs: $(SECONDARY_SIZE)

.PHONY: all clean dependents post-build

-include ../makefile.targets
