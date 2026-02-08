################################################################################
# MRS Version: 2.3.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/mxk/resband/reistance_band_v0_1/resistance_band/HAL/AS5600.c \
/home/mxk/resband/reistance_band_v0_1/resistance_band/HAL/LED.c \
/home/mxk/resband/reistance_band_v0_1/resistance_band/HAL/MCU.c \
/home/mxk/resband/reistance_band_v0_1/resistance_band/HAL/RTC.c \
/home/mxk/resband/reistance_band_v0_1/resistance_band/HAL/SLEEP.c 

C_DEPS += \
./HAL/AS5600.d \
./HAL/LED.d \
./HAL/MCU.d \
./HAL/RTC.d \
./HAL/SLEEP.d 

OBJS += \
./HAL/AS5600.o \
./HAL/LED.o \
./HAL/MCU.o \
./HAL/RTC.o \
./HAL/SLEEP.o 

DIR_OBJS += \
./HAL/*.o \

DIR_DEPS += \
./HAL/*.d \

DIR_EXPANDS += \
./HAL/*.234r.expand \


# Each subdirectory must supply rules for building sources it contributes
HAL/AS5600.o: /home/mxk/resband/reistance_band_v0_1/resistance_band/HAL/AS5600.c
	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -g -I"/home/mxk/resband/reistance_band_v0_1/SRC/Startup" -I"/home/mxk/resband/reistance_band_v0_1/resistance_band/HeartRate/APP/include" -I"/home/mxk/resband/reistance_band_v0_1/resistance_band/HeartRate/Profile/include" -I"/home/mxk/resband/reistance_band_v0_1/SRC/StdPeriphDriver/inc" -I"/home/mxk/resband/reistance_band_v0_1/resistance_band/HAL/include" -I"/home/mxk/resband/reistance_band_v0_1/SRC/Ld" -I"/home/mxk/resband/reistance_band_v0_1/resistance_band/LIB" -I"/home/mxk/resband/reistance_band_v0_1/SRC/RVMSIS" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
HAL/LED.o: /home/mxk/resband/reistance_band_v0_1/resistance_band/HAL/LED.c
	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -g -I"/home/mxk/resband/reistance_band_v0_1/SRC/Startup" -I"/home/mxk/resband/reistance_band_v0_1/resistance_band/HeartRate/APP/include" -I"/home/mxk/resband/reistance_band_v0_1/resistance_band/HeartRate/Profile/include" -I"/home/mxk/resband/reistance_band_v0_1/SRC/StdPeriphDriver/inc" -I"/home/mxk/resband/reistance_band_v0_1/resistance_band/HAL/include" -I"/home/mxk/resband/reistance_band_v0_1/SRC/Ld" -I"/home/mxk/resband/reistance_band_v0_1/resistance_band/LIB" -I"/home/mxk/resband/reistance_band_v0_1/SRC/RVMSIS" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
HAL/MCU.o: /home/mxk/resband/reistance_band_v0_1/resistance_band/HAL/MCU.c
	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -g -I"/home/mxk/resband/reistance_band_v0_1/SRC/Startup" -I"/home/mxk/resband/reistance_band_v0_1/resistance_band/HeartRate/APP/include" -I"/home/mxk/resband/reistance_band_v0_1/resistance_band/HeartRate/Profile/include" -I"/home/mxk/resband/reistance_band_v0_1/SRC/StdPeriphDriver/inc" -I"/home/mxk/resband/reistance_band_v0_1/resistance_band/HAL/include" -I"/home/mxk/resband/reistance_band_v0_1/SRC/Ld" -I"/home/mxk/resband/reistance_band_v0_1/resistance_band/LIB" -I"/home/mxk/resband/reistance_band_v0_1/SRC/RVMSIS" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
HAL/RTC.o: /home/mxk/resband/reistance_band_v0_1/resistance_band/HAL/RTC.c
	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -g -I"/home/mxk/resband/reistance_band_v0_1/SRC/Startup" -I"/home/mxk/resband/reistance_band_v0_1/resistance_band/HeartRate/APP/include" -I"/home/mxk/resband/reistance_band_v0_1/resistance_band/HeartRate/Profile/include" -I"/home/mxk/resband/reistance_band_v0_1/SRC/StdPeriphDriver/inc" -I"/home/mxk/resband/reistance_band_v0_1/resistance_band/HAL/include" -I"/home/mxk/resband/reistance_band_v0_1/SRC/Ld" -I"/home/mxk/resband/reistance_band_v0_1/resistance_band/LIB" -I"/home/mxk/resband/reistance_band_v0_1/SRC/RVMSIS" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
HAL/SLEEP.o: /home/mxk/resband/reistance_band_v0_1/resistance_band/HAL/SLEEP.c
	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -g -I"/home/mxk/resband/reistance_band_v0_1/SRC/Startup" -I"/home/mxk/resband/reistance_band_v0_1/resistance_band/HeartRate/APP/include" -I"/home/mxk/resband/reistance_band_v0_1/resistance_band/HeartRate/Profile/include" -I"/home/mxk/resband/reistance_band_v0_1/SRC/StdPeriphDriver/inc" -I"/home/mxk/resband/reistance_band_v0_1/resistance_band/HAL/include" -I"/home/mxk/resband/reistance_band_v0_1/SRC/Ld" -I"/home/mxk/resband/reistance_band_v0_1/resistance_band/LIB" -I"/home/mxk/resband/reistance_band_v0_1/SRC/RVMSIS" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

