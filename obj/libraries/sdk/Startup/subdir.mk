################################################################################
# MRS Version: 1.9.1
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../libraries/sdk/Startup/system_ch32v30x.c 

S_UPPER_SRCS += \
../libraries/sdk/Startup/startup_ch32v30x.S 

OBJS += \
./libraries/sdk/Startup/startup_ch32v30x.o \
./libraries/sdk/Startup/system_ch32v30x.o 

S_UPPER_DEPS += \
./libraries/sdk/Startup/startup_ch32v30x.d 

C_DEPS += \
./libraries/sdk/Startup/system_ch32v30x.d 


# Each subdirectory must supply rules for building sources it contributes
libraries/sdk/Startup/%.o: ../libraries/sdk/Startup/%.S
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -x assembler-with-cpp -I"E:\MouRiverPro\Gyro balance vehicle\Startup" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
libraries/sdk/Startup/%.o: ../libraries/sdk/Startup/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"E:\MouRiverPro\Gyro balance vehicle\Debug" -I"E:\MouRiverPro\Gyro balance vehicle\Core" -I"E:\MouRiverPro\Gyro balance vehicle\User" -I"E:\MouRiverPro\Gyro balance vehicle\Peripheral\inc" -I"E:\MouRiverPro\Gyro balance vehicle\Hardware" -I"E:\MouRiverPro\Gyro balance vehicle\sys" -I"E:\MouRiverPro\Gyro balance vehicle\libraries\zf_common" -I"E:\MouRiverPro\Gyro balance vehicle\libraries\zf_device" -I"E:\MouRiverPro\Gyro balance vehicle\libraries\zf_driver" -I"E:\MouRiverPro\Gyro balance vehicle\libraries\sdk" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

