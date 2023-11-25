################################################################################
# MRS Version: 1.9.1
# �Զ����ɵ��ļ�����Ҫ�༭��
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../sys/sys.c 

OBJS += \
./sys/sys.o 

C_DEPS += \
./sys/sys.d 


# Each subdirectory must supply rules for building sources it contributes
sys/%.o: ../sys/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"H:\MounRiver\CH32-Gyro-balance-vehicle\Core" -I"H:\MounRiver\CH32-Gyro-balance-vehicle\User" -I"H:\MounRiver\CH32-Gyro-balance-vehicle\Peripheral\inc" -I"H:\MounRiver\CH32-Gyro-balance-vehicle\Hardware" -I"H:\MounRiver\CH32-Gyro-balance-vehicle\sys" -I"H:\MounRiver\CH32-Gyro-balance-vehicle\zf" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

