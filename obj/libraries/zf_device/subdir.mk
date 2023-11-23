################################################################################
# MRS Version: 1.9.1
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../libraries/zf_device/zf_device_absolute_encoder.c \
../libraries/zf_device/zf_device_bluetooth_ch9141.c \
../libraries/zf_device/zf_device_bluetooth_ch9141_ch2.c \
../libraries/zf_device/zf_device_camera.c \
../libraries/zf_device/zf_device_icm20602.c \
../libraries/zf_device/zf_device_ips114.c \
../libraries/zf_device/zf_device_ips200_parallel8.c \
../libraries/zf_device/zf_device_mpu6050.c \
../libraries/zf_device/zf_device_mt9v03x_dvp.c \
../libraries/zf_device/zf_device_oled.c \
../libraries/zf_device/zf_device_scc8660_dvp.c \
../libraries/zf_device/zf_device_tft180.c \
../libraries/zf_device/zf_device_type.c \
../libraries/zf_device/zf_device_virtual_oscilloscope.c \
../libraries/zf_device/zf_device_wireless_ch573.c \
../libraries/zf_device/zf_device_wireless_uart.c 

OBJS += \
./libraries/zf_device/zf_device_absolute_encoder.o \
./libraries/zf_device/zf_device_bluetooth_ch9141.o \
./libraries/zf_device/zf_device_bluetooth_ch9141_ch2.o \
./libraries/zf_device/zf_device_camera.o \
./libraries/zf_device/zf_device_icm20602.o \
./libraries/zf_device/zf_device_ips114.o \
./libraries/zf_device/zf_device_ips200_parallel8.o \
./libraries/zf_device/zf_device_mpu6050.o \
./libraries/zf_device/zf_device_mt9v03x_dvp.o \
./libraries/zf_device/zf_device_oled.o \
./libraries/zf_device/zf_device_scc8660_dvp.o \
./libraries/zf_device/zf_device_tft180.o \
./libraries/zf_device/zf_device_type.o \
./libraries/zf_device/zf_device_virtual_oscilloscope.o \
./libraries/zf_device/zf_device_wireless_ch573.o \
./libraries/zf_device/zf_device_wireless_uart.o 

C_DEPS += \
./libraries/zf_device/zf_device_absolute_encoder.d \
./libraries/zf_device/zf_device_bluetooth_ch9141.d \
./libraries/zf_device/zf_device_bluetooth_ch9141_ch2.d \
./libraries/zf_device/zf_device_camera.d \
./libraries/zf_device/zf_device_icm20602.d \
./libraries/zf_device/zf_device_ips114.d \
./libraries/zf_device/zf_device_ips200_parallel8.d \
./libraries/zf_device/zf_device_mpu6050.d \
./libraries/zf_device/zf_device_mt9v03x_dvp.d \
./libraries/zf_device/zf_device_oled.d \
./libraries/zf_device/zf_device_scc8660_dvp.d \
./libraries/zf_device/zf_device_tft180.d \
./libraries/zf_device/zf_device_type.d \
./libraries/zf_device/zf_device_virtual_oscilloscope.d \
./libraries/zf_device/zf_device_wireless_ch573.d \
./libraries/zf_device/zf_device_wireless_uart.d 


# Each subdirectory must supply rules for building sources it contributes
libraries/zf_device/%.o: ../libraries/zf_device/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"E:\MouRiverPro\Gyro balance vehicle\Debug" -I"E:\MouRiverPro\Gyro balance vehicle\Core" -I"E:\MouRiverPro\Gyro balance vehicle\User" -I"E:\MouRiverPro\Gyro balance vehicle\Peripheral\inc" -I"E:\MouRiverPro\Gyro balance vehicle\Hardware" -I"E:\MouRiverPro\Gyro balance vehicle\sys" -I"E:\MouRiverPro\Gyro balance vehicle\libraries\zf_common" -I"E:\MouRiverPro\Gyro balance vehicle\libraries\zf_device" -I"E:\MouRiverPro\Gyro balance vehicle\libraries\zf_driver" -I"E:\MouRiverPro\Gyro balance vehicle\libraries\sdk" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

