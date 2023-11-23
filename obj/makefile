################################################################################
# MRS Version: 1.9.1
# 自动生成的文件。不要编辑！
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include zf/subdir.mk
-include sys/subdir.mk
-include User/subdir.mk
-include Startup/subdir.mk
-include Peripheral/src/subdir.mk
-include Hardware/subdir.mk
-include Core/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
Gyro\ balance\ vehicle.hex \

SECONDARY_LIST += \
Gyro\ balance\ vehicle.lst \

SECONDARY_SIZE += \
Gyro\ balance\ vehicle.siz \


# 所有目标
all: Gyro\ balance\ vehicle.elf secondary-outputs

# 工具调用
Gyro\ balance\ vehicle.elf: $(OBJS) $(USER_OBJS)
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -T "E:\MouRiverPro\Gyro balance vehicle\Ld\Link.ld" -nostartfiles -Xlinker --gc-sections -Wl,-Map,"Gyro balance vehicle.map" --specs=nano.specs --specs=nosys.specs -o "Gyro balance vehicle.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@	@
Gyro\ balance\ vehicle.hex: Gyro\ balance\ vehicle.elf
	@	riscv-none-embed-objcopy -O ihex "Gyro balance vehicle.elf"  "Gyro balance vehicle.hex"
	@	@
Gyro\ balance\ vehicle.lst: Gyro\ balance\ vehicle.elf
	@	riscv-none-embed-objdump --all-headers --demangle --disassemble "Gyro balance -M xw vehicle.elf" > "Gyro balance vehicle.lst"
	@	@
Gyro\ balance\ vehicle.siz: Gyro\ balance\ vehicle.elf
	@	riscv-none-embed-size --format=berkeley "Gyro balance vehicle.elf"
	@	@
# 其他目标
clean:
	-$(RM) $(ASM_UPPER_DEPS)$(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS) "Gyro balance vehicle.elf"
	-@
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
