################################################################################
# MRS Version: 2.3.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../APP/OY8699.c \
../APP/resband.c \
../APP/resband_main.c \
../APP/tension.c 

C_DEPS += \
./APP/OY8699.d \
./APP/resband.d \
./APP/resband_main.d \
./APP/tension.d 

OBJS += \
./APP/OY8699.o \
./APP/resband.o \
./APP/resband_main.o \
./APP/tension.o 

DIR_OBJS += \
./APP/*.o \

DIR_DEPS += \
./APP/*.d \

DIR_EXPANDS += \
./APP/*.234r.expand \


# Each subdirectory must supply rules for building sources it contributes
APP/%.o: ../APP/%.c
	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -g -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/SRC/Startup" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/resistance_band/HeartRate/APP/include" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/resistance_band/HeartRate/Profile/include" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/SRC/StdPeriphDriver/inc" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/resistance_band/HAL/include" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/SRC/Ld" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/resistance_band/LIB" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/SRC/RVMSIS" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

