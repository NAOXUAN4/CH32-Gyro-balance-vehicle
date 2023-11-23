################################################################################
# MRS Version: 1.9.1
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Hardware/CONTROL.c \
../Hardware/ENCODER.c \
../Hardware/EXIT.c \
../Hardware/MONLCD.c \
../Hardware/MOTOR.c \
../Hardware/My_Math.c \
../Hardware/PWM.c \
../Hardware/pid.c 

OBJS += \
./Hardware/CONTROL.o \
./Hardware/ENCODER.o \
./Hardware/EXIT.o \
./Hardware/MONLCD.o \
./Hardware/MOTOR.o \
./Hardware/My_Math.o \
./Hardware/PWM.o \
./Hardware/pid.o 

C_DEPS += \
./Hardware/CONTROL.d \
./Hardware/ENCODER.d \
./Hardware/EXIT.d \
./Hardware/MONLCD.d \
./Hardware/MOTOR.d \
./Hardware/My_Math.d \
./Hardware/PWM.d \
./Hardware/pid.d 


# Each subdirectory must supply rules for building sources it contributes
Hardware/%.o: ../Hardware/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"E:\MouRiverPro\Gyro balance vehicle\Core" -I"E:\MouRiverPro\Gyro balance vehicle\User" -I"E:\MouRiverPro\Gyro balance vehicle\Peripheral\inc" -I"E:\MouRiverPro\Gyro balance vehicle\Hardware" -I"E:\MouRiverPro\Gyro balance vehicle\sys" -I"E:\MouRiverPro\Gyro balance vehicle\zf" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

