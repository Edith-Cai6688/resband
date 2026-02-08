################################################################################
# MRS Version: 2.3.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/mxk/resband/reistance_band_v0_1/SRC/StdPeriphDriver/CH57x_adc.c \
/home/mxk/resband/reistance_band_v0_1/SRC/StdPeriphDriver/CH57x_clk.c \
/home/mxk/resband/reistance_band_v0_1/SRC/StdPeriphDriver/CH57x_flash.c \
/home/mxk/resband/reistance_band_v0_1/SRC/StdPeriphDriver/CH57x_gpio.c \
/home/mxk/resband/reistance_band_v0_1/SRC/StdPeriphDriver/CH57x_pwr.c \
/home/mxk/resband/reistance_band_v0_1/SRC/StdPeriphDriver/CH57x_sys.c \
/home/mxk/resband/reistance_band_v0_1/SRC/StdPeriphDriver/CH57x_uart1.c 

C_DEPS += \
./StdPeriphDriver/CH57x_adc.d \
./StdPeriphDriver/CH57x_clk.d \
./StdPeriphDriver/CH57x_flash.d \
./StdPeriphDriver/CH57x_gpio.d \
./StdPeriphDriver/CH57x_pwr.d \
./StdPeriphDriver/CH57x_sys.d \
./StdPeriphDriver/CH57x_uart1.d 

OBJS += \
./StdPeriphDriver/CH57x_adc.o \
./StdPeriphDriver/CH57x_clk.o \
./StdPeriphDriver/CH57x_flash.o \
./StdPeriphDriver/CH57x_gpio.o \
./StdPeriphDriver/CH57x_pwr.o \
./StdPeriphDriver/CH57x_sys.o \
./StdPeriphDriver/CH57x_uart1.o 

DIR_OBJS += \
./StdPeriphDriver/*.o \

DIR_DEPS += \
./StdPeriphDriver/*.d \

DIR_EXPANDS += \
./StdPeriphDriver/*.234r.expand \


# Each subdirectory must supply rules for building sources it contributes
StdPeriphDriver/CH57x_adc.o: /home/mxk/resband/reistance_band_v0_1/SRC/StdPeriphDriver/CH57x_adc.c
	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -g -I"/home/mxk/resband/reistance_band_v0_1/SRC/Startup" -I"/home/mxk/resband/reistance_band_v0_1/resistance_band/HeartRate/APP/include" -I"/home/mxk/resband/reistance_band_v0_1/resistance_band/HeartRate/Profile/include" -I"/home/mxk/resband/reistance_band_v0_1/SRC/StdPeriphDriver/inc" -I"/home/mxk/resband/reistance_band_v0_1/resistance_band/HAL/include" -I"/home/mxk/resband/reistance_band_v0_1/SRC/Ld" -I"/home/mxk/resband/reistance_band_v0_1/resistance_band/LIB" -I"/home/mxk/resband/reistance_band_v0_1/SRC/RVMSIS" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
StdPeriphDriver/CH57x_clk.o: /home/mxk/resband/reistance_band_v0_1/SRC/StdPeriphDriver/CH57x_clk.c
	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -g -I"/home/mxk/resband/reistance_band_v0_1/SRC/Startup" -I"/home/mxk/resband/reistance_band_v0_1/resistance_band/HeartRate/APP/include" -I"/home/mxk/resband/reistance_band_v0_1/resistance_band/HeartRate/Profile/include" -I"/home/mxk/resband/reistance_band_v0_1/SRC/StdPeriphDriver/inc" -I"/home/mxk/resband/reistance_band_v0_1/resistance_band/HAL/include" -I"/home/mxk/resband/reistance_band_v0_1/SRC/Ld" -I"/home/mxk/resband/reistance_band_v0_1/resistance_band/LIB" -I"/home/mxk/resband/reistance_band_v0_1/SRC/RVMSIS" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
StdPeriphDriver/CH57x_flash.o: /home/mxk/resband/reistance_band_v0_1/SRC/StdPeriphDriver/CH57x_flash.c
	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -g -I"/home/mxk/resband/reistance_band_v0_1/SRC/Startup" -I"/home/mxk/resband/reistance_band_v0_1/resistance_band/HeartRate/APP/include" -I"/home/mxk/resband/reistance_band_v0_1/resistance_band/HeartRate/Profile/include" -I"/home/mxk/resband/reistance_band_v0_1/SRC/StdPeriphDriver/inc" -I"/home/mxk/resband/reistance_band_v0_1/resistance_band/HAL/include" -I"/home/mxk/resband/reistance_band_v0_1/SRC/Ld" -I"/home/mxk/resband/reistance_band_v0_1/resistance_band/LIB" -I"/home/mxk/resband/reistance_band_v0_1/SRC/RVMSIS" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
StdPeriphDriver/CH57x_gpio.o: /home/mxk/resband/reistance_band_v0_1/SRC/StdPeriphDriver/CH57x_gpio.c
	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -g -I"/home/mxk/resband/reistance_band_v0_1/SRC/Startup" -I"/home/mxk/resband/reistance_band_v0_1/resistance_band/HeartRate/APP/include" -I"/home/mxk/resband/reistance_band_v0_1/resistance_band/HeartRate/Profile/include" -I"/home/mxk/resband/reistance_band_v0_1/SRC/StdPeriphDriver/inc" -I"/home/mxk/resband/reistance_band_v0_1/resistance_band/HAL/include" -I"/home/mxk/resband/reistance_band_v0_1/SRC/Ld" -I"/home/mxk/resband/reistance_band_v0_1/resistance_band/LIB" -I"/home/mxk/resband/reistance_band_v0_1/SRC/RVMSIS" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
StdPeriphDriver/CH57x_pwr.o: /home/mxk/resband/reistance_band_v0_1/SRC/StdPeriphDriver/CH57x_pwr.c
	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -g -I"/home/mxk/resband/reistance_band_v0_1/SRC/Startup" -I"/home/mxk/resband/reistance_band_v0_1/resistance_band/HeartRate/APP/include" -I"/home/mxk/resband/reistance_band_v0_1/resistance_band/HeartRate/Profile/include" -I"/home/mxk/resband/reistance_band_v0_1/SRC/StdPeriphDriver/inc" -I"/home/mxk/resband/reistance_band_v0_1/resistance_band/HAL/include" -I"/home/mxk/resband/reistance_band_v0_1/SRC/Ld" -I"/home/mxk/resband/reistance_band_v0_1/resistance_band/LIB" -I"/home/mxk/resband/reistance_band_v0_1/SRC/RVMSIS" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
StdPeriphDriver/CH57x_sys.o: /home/mxk/resband/reistance_band_v0_1/SRC/StdPeriphDriver/CH57x_sys.c
	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -g -I"/home/mxk/resband/reistance_band_v0_1/SRC/Startup" -I"/home/mxk/resband/reistance_band_v0_1/resistance_band/HeartRate/APP/include" -I"/home/mxk/resband/reistance_band_v0_1/resistance_band/HeartRate/Profile/include" -I"/home/mxk/resband/reistance_band_v0_1/SRC/StdPeriphDriver/inc" -I"/home/mxk/resband/reistance_band_v0_1/resistance_band/HAL/include" -I"/home/mxk/resband/reistance_band_v0_1/SRC/Ld" -I"/home/mxk/resband/reistance_band_v0_1/resistance_band/LIB" -I"/home/mxk/resband/reistance_band_v0_1/SRC/RVMSIS" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
StdPeriphDriver/CH57x_uart1.o: /home/mxk/resband/reistance_band_v0_1/SRC/StdPeriphDriver/CH57x_uart1.c
	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -g -I"/home/mxk/resband/reistance_band_v0_1/SRC/Startup" -I"/home/mxk/resband/reistance_band_v0_1/resistance_band/HeartRate/APP/include" -I"/home/mxk/resband/reistance_band_v0_1/resistance_band/HeartRate/Profile/include" -I"/home/mxk/resband/reistance_band_v0_1/SRC/StdPeriphDriver/inc" -I"/home/mxk/resband/reistance_band_v0_1/resistance_band/HAL/include" -I"/home/mxk/resband/reistance_band_v0_1/SRC/Ld" -I"/home/mxk/resband/reistance_band_v0_1/resistance_band/LIB" -I"/home/mxk/resband/reistance_band_v0_1/SRC/RVMSIS" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

