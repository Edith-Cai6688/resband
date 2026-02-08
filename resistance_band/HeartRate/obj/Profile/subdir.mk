################################################################################
# MRS Version: 2.3.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Profile/battservice.c \
../Profile/devinfoservice.c \
../Profile/resbandservice.c 

C_DEPS += \
./Profile/battservice.d \
./Profile/devinfoservice.d \
./Profile/resbandservice.d 

OBJS += \
./Profile/battservice.o \
./Profile/devinfoservice.o \
./Profile/resbandservice.o 

DIR_OBJS += \
./Profile/*.o \

DIR_DEPS += \
./Profile/*.d \

DIR_EXPANDS += \
./Profile/*.234r.expand \


# Each subdirectory must supply rules for building sources it contributes
Profile/%.o: ../Profile/%.c
	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -g -I"/home/mxk/resband/reistance_band_v0_1/SRC/Startup" -I"/home/mxk/resband/reistance_band_v0_1/resistance_band/HeartRate/APP/include" -I"/home/mxk/resband/reistance_band_v0_1/resistance_band/HeartRate/Profile/include" -I"/home/mxk/resband/reistance_band_v0_1/SRC/StdPeriphDriver/inc" -I"/home/mxk/resband/reistance_band_v0_1/resistance_band/HAL/include" -I"/home/mxk/resband/reistance_band_v0_1/SRC/Ld" -I"/home/mxk/resband/reistance_band_v0_1/resistance_band/LIB" -I"/home/mxk/resband/reistance_band_v0_1/SRC/RVMSIS" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

