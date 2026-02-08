################################################################################
# MRS Version: 2.3.0
# Automatically-generated file. Do not edit!
################################################################################
-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include StdPeriphDriver/subdir.mk
-include Startup/subdir.mk
-include RVMSIS/subdir.mk
-include Profile/subdir.mk
-include HAL/subdir.mk
-include APP/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
Resband.hex \

SECONDARY_LIST += \
Resband.lst \

SECONDARY_SIZE += \
Resband.siz \


# All Target
all: 
	$(MAKE) --no-print-directory main-build 

main-build: Resband.elf secondary-outputs

# Tool invocations
Resband.elf: $(OBJS) $(USER_OBJS_ESCAPE)
	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -g -T "/home/mxk/resband/reistance_band_v0_1/SRC/Ld/Link.ld" -nostartfiles -Xlinker --gc-sections -L"/home/mxk/resband/reistance_band_v0_1/resistance_band/HeartRate" -L"/home/mxk/resband/reistance_band_v0_1/resistance_band/LIB" -L"/home/mxk/resband/reistance_band_v0_1/SRC/StdPeriphDriver" -Xlinker --print-memory-usage -Wl,-Map,"Resband.map" --specs=nano.specs --specs=nosys.specs -o "Resband.elf" $(OBJS) $(LIBS)
Resband.hex: Resband.elf
	@	riscv-none-embed-objcopy -O ihex "Resband.elf" "Resband.hex"
Resband.lst: Resband.elf
	@	riscv-none-embed-objdump --source --all-headers --demangle --line-numbers --wide "Resband.elf" > "Resband.lst"
Resband.siz: Resband.elf
	riscv-none-embed-size --format=berkeley "Resband.elf"

# Other Targets
clean:
	-$(RM) $(DIR_OBJS) $(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE) Resband.elf
	-$(RM) $(DIR_EXPANDS) $(CALLGRAPH_DOT)
	-$(RM) $(DIR_DEPS)
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets