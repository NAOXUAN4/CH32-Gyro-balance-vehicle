################################################################################
# MRS Version: 1.9.1
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Hardware/zf/zf_common_clock.c \
../Hardware/zf/zf_common_debug.c \
../Hardware/zf/zf_common_font.c \
../Hardware/zf/zf_common_function.c \
../Hardware/zf/zf_common_interrupt.c \
../Hardware/zf/zf_device_tft180.c \
../Hardware/zf/zf_driver_delay.c \
../Hardware/zf/zf_driver_gpio.c \
../Hardware/zf/zf_driver_spi.c \
../Hardware/zf/zf_driver_uart.c 

OBJS += \
./Hardware/zf/zf_common_clock.o \
./Hardware/zf/zf_common_debug.o \
./Hardware/zf/zf_common_font.o \
./Hardware/zf/zf_common_function.o \
./Hardware/zf/zf_common_interrupt.o \
./Hardware/zf/zf_device_tft180.o \
./Hardware/zf/zf_driver_delay.o \
./Hardware/zf/zf_driver_gpio.o \
./Hardware/zf/zf_driver_spi.o \
./Hardware/zf/zf_driver_uart.o 

C_DEPS += \
./Hardware/zf/zf_common_clock.d \
./Hardware/zf/zf_common_debug.d \
./Hardware/zf/zf_common_font.d \
./Hardware/zf/zf_common_function.d \
./Hardware/zf/zf_common_interrupt.d \
./Hardware/zf/zf_device_tft180.d \
./Hardware/zf/zf_driver_delay.d \
./Hardware/zf/zf_driver_gpio.d \
./Hardware/zf/zf_driver_spi.d \
./Hardware/zf/zf_driver_uart.d 


# Each subdirectory must supply rules for building sources it contributes
Hardware/zf/%.o: ../Hardware/zf/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"E:\MouRiverPro\Gyro balance vehicle\Debug" -I"E:\MouRiverPro\Gyro balance vehicle\Core" -I"E:\MouRiverPro\Gyro balance vehicle\User" -I"E:\MouRiverPro\Gyro balance vehicle\Peripheral\inc" -I"E:\MouRiverPro\Gyro balance vehicle\Hardware" -I"E:\MouRiverPro\Gyro balance vehicle\sys" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

