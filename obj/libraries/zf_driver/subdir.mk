################################################################################
# MRS Version: 1.9.1
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../libraries/zf_driver/zf_driver_adc.c \
../libraries/zf_driver/zf_driver_delay.c \
../libraries/zf_driver/zf_driver_dvp.c \
../libraries/zf_driver/zf_driver_encoder.c \
../libraries/zf_driver/zf_driver_exti.c \
../libraries/zf_driver/zf_driver_pit.c \
../libraries/zf_driver/zf_driver_pwm.c \
../libraries/zf_driver/zf_driver_soft_iic.c \
../libraries/zf_driver/zf_driver_spi.c \
../libraries/zf_driver/zf_driver_timer.c \
../libraries/zf_driver/zf_driver_uart.c \
../libraries/zf_driver/zf_driver_usb_cdc.c 

S_UPPER_SRCS += \
../libraries/zf_driver/zf_driver_irq.S 

OBJS += \
./libraries/zf_driver/zf_driver_adc.o \
./libraries/zf_driver/zf_driver_delay.o \
./libraries/zf_driver/zf_driver_dvp.o \
./libraries/zf_driver/zf_driver_encoder.o \
./libraries/zf_driver/zf_driver_exti.o \
./libraries/zf_driver/zf_driver_irq.o \
./libraries/zf_driver/zf_driver_pit.o \
./libraries/zf_driver/zf_driver_pwm.o \
./libraries/zf_driver/zf_driver_soft_iic.o \
./libraries/zf_driver/zf_driver_spi.o \
./libraries/zf_driver/zf_driver_timer.o \
./libraries/zf_driver/zf_driver_uart.o \
./libraries/zf_driver/zf_driver_usb_cdc.o 

S_UPPER_DEPS += \
./libraries/zf_driver/zf_driver_irq.d 

C_DEPS += \
./libraries/zf_driver/zf_driver_adc.d \
./libraries/zf_driver/zf_driver_delay.d \
./libraries/zf_driver/zf_driver_dvp.d \
./libraries/zf_driver/zf_driver_encoder.d \
./libraries/zf_driver/zf_driver_exti.d \
./libraries/zf_driver/zf_driver_pit.d \
./libraries/zf_driver/zf_driver_pwm.d \
./libraries/zf_driver/zf_driver_soft_iic.d \
./libraries/zf_driver/zf_driver_spi.d \
./libraries/zf_driver/zf_driver_timer.d \
./libraries/zf_driver/zf_driver_uart.d \
./libraries/zf_driver/zf_driver_usb_cdc.d 


# Each subdirectory must supply rules for building sources it contributes
libraries/zf_driver/%.o: ../libraries/zf_driver/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"E:\MouRiverPro\Gyro balance vehicle\Debug" -I"E:\MouRiverPro\Gyro balance vehicle\Core" -I"E:\MouRiverPro\Gyro balance vehicle\User" -I"E:\MouRiverPro\Gyro balance vehicle\Peripheral\inc" -I"E:\MouRiverPro\Gyro balance vehicle\Hardware" -I"E:\MouRiverPro\Gyro balance vehicle\sys" -I"E:\MouRiverPro\Gyro balance vehicle\libraries\zf_common" -I"E:\MouRiverPro\Gyro balance vehicle\libraries\zf_device" -I"E:\MouRiverPro\Gyro balance vehicle\libraries\zf_driver" -I"E:\MouRiverPro\Gyro balance vehicle\libraries\sdk" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
libraries/zf_driver/%.o: ../libraries/zf_driver/%.S
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -x assembler-with-cpp -I"E:\MouRiverPro\Gyro balance vehicle\Startup" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

