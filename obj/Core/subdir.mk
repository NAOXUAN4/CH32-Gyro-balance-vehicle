################################################################################
# MRS Version: 1.9.1
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/core_riscv.c 

OBJS += \
./Core/core_riscv.o 

C_DEPS += \
./Core/core_riscv.d 


# Each subdirectory must supply rules for building sources it contributes
Core/%.o: ../Core/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"E:\MouRiverPro\Gyro balance vehicle\Core" -I"E:\MouRiverPro\Gyro balance vehicle\User" -I"E:\MouRiverPro\Gyro balance vehicle\Peripheral\inc" -I"E:\MouRiverPro\Gyro balance vehicle\Hardware" -I"E:\MouRiverPro\Gyro balance vehicle\sys" -I"E:\MouRiverPro\Gyro balance vehicle\zf" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

