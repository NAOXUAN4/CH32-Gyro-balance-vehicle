################################################################################
# MRS Version: 1.9.1
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../zf/filter.c \
../zf/zf_common_clock.c \
../zf/zf_common_debug.c \
../zf/zf_common_font.c \
../zf/zf_common_function.c \
../zf/zf_common_interrupt.c \
../zf/zf_device_mpu6050.c \
../zf/zf_device_tft180.c \
../zf/zf_driver_delay.c \
../zf/zf_driver_gpio.c \
../zf/zf_driver_soft_iic.c \
../zf/zf_driver_spi.c \
../zf/zf_driver_uart.c 

OBJS += \
./zf/filter.o \
./zf/zf_common_clock.o \
./zf/zf_common_debug.o \
./zf/zf_common_font.o \
./zf/zf_common_function.o \
./zf/zf_common_interrupt.o \
./zf/zf_device_mpu6050.o \
./zf/zf_device_tft180.o \
./zf/zf_driver_delay.o \
./zf/zf_driver_gpio.o \
./zf/zf_driver_soft_iic.o \
./zf/zf_driver_spi.o \
./zf/zf_driver_uart.o 

C_DEPS += \
./zf/filter.d \
./zf/zf_common_clock.d \
./zf/zf_common_debug.d \
./zf/zf_common_font.d \
./zf/zf_common_function.d \
./zf/zf_common_interrupt.d \
./zf/zf_device_mpu6050.d \
./zf/zf_device_tft180.d \
./zf/zf_driver_delay.d \
./zf/zf_driver_gpio.d \
./zf/zf_driver_soft_iic.d \
./zf/zf_driver_spi.d \
./zf/zf_driver_uart.d 


# Each subdirectory must supply rules for building sources it contributes
zf/%.o: ../zf/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"H:\MounRiver\CH32-Gyro-balance-vehicle\Core" -I"H:\MounRiver\CH32-Gyro-balance-vehicle\User" -I"H:\MounRiver\CH32-Gyro-balance-vehicle\Peripheral\inc" -I"H:\MounRiver\CH32-Gyro-balance-vehicle\Hardware" -I"H:\MounRiver\CH32-Gyro-balance-vehicle\sys" -I"H:\MounRiver\CH32-Gyro-balance-vehicle\zf" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

