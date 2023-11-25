################################################################################
# MRS Version: 1.9.1
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/ch32v30x_it.c \
../User/main.c \
../User/system_ch32v30x.c 

OBJS += \
./User/ch32v30x_it.o \
./User/main.o \
./User/system_ch32v30x.o 

C_DEPS += \
./User/ch32v30x_it.d \
./User/main.d \
./User/system_ch32v30x.d 


# Each subdirectory must supply rules for building sources it contributes
User/%.o: ../User/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"H:\MounRiver\CH32-Gyro-balance-vehicle\Core" -I"H:\MounRiver\CH32-Gyro-balance-vehicle\User" -I"H:\MounRiver\CH32-Gyro-balance-vehicle\Peripheral\inc" -I"H:\MounRiver\CH32-Gyro-balance-vehicle\Hardware" -I"H:\MounRiver\CH32-Gyro-balance-vehicle\sys" -I"H:\MounRiver\CH32-Gyro-balance-vehicle\zf" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

