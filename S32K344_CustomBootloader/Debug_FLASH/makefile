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
SECONDARY_FLASH += \
S32K344_CustomBootloader.srec \

SECONDARY_SIZE += \
S32K344_CustomBootloader.siz \


# All Target
all: S32K344_CustomBootloader.elf secondary-outputs

# Tool invocations
S32K344_CustomBootloader.elf: $(OBJS) C:\Users\fvzdr\OneDrive\Belgeler\Github\S32_DS_Workspace\S32K344_CustomBootloader\Project_Settings\Linker_Files\linker_flash_s32k344.ld $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Standard S32DS C Linker'
	arm-none-eabi-gcc -o "S32K344_CustomBootloader.elf" "@S32K344_CustomBootloader.args"  $(USER_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

S32K344_CustomBootloader.srec: S32K344_CustomBootloader.elf
	@echo 'Invoking: Standard S32DS Create Flash Image'
	arm-none-eabi-objcopy -O srec S32K344_CustomBootloader.elf  "S32K344_CustomBootloader.srec"
	@echo 'Finished building: $@'
	@echo ' '

S32K344_CustomBootloader.siz: S32K344_CustomBootloader.elf
	@echo 'Invoking: Standard S32DS Print Size'
	arm-none-eabi-size --format=berkeley S32K344_CustomBootloader.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) ./*
	-@echo ' '

post-build:
	-arm-none-eabi-objcopy -v -O srec "S32K344_CustomBootloader.elf" "S32K344_CustomBootloader.s19";arm-none-eabi-objcopy -v -O ihex "S32K344_CustomBootloader.elf" "S32K344_CustomBootloader.hex";arm-none-eabi-objcopy -v -O binary "S32K344_CustomBootloader.elf" "S32K344_CustomBootloader.bin"
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents post-build

-include ../makefile.targets
