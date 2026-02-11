################################################################################
# MRS Version: 2.3.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
d:/BaiduSyncdisk/Edith/墨小孔实习/resband/SRC/StdPeriphDriver/CH57x_adc.c \
d:/BaiduSyncdisk/Edith/墨小孔实习/resband/SRC/StdPeriphDriver/CH57x_clk.c \
d:/BaiduSyncdisk/Edith/墨小孔实习/resband/SRC/StdPeriphDriver/CH57x_flash.c \
d:/BaiduSyncdisk/Edith/墨小孔实习/resband/SRC/StdPeriphDriver/CH57x_gpio.c \
d:/BaiduSyncdisk/Edith/墨小孔实习/resband/SRC/StdPeriphDriver/CH57x_pwr.c \
d:/BaiduSyncdisk/Edith/墨小孔实习/resband/SRC/StdPeriphDriver/CH57x_spi0.c \
d:/BaiduSyncdisk/Edith/墨小孔实习/resband/SRC/StdPeriphDriver/CH57x_sys.c \
d:/BaiduSyncdisk/Edith/墨小孔实习/resband/SRC/StdPeriphDriver/CH57x_uart1.c 

C_DEPS += \
./StdPeriphDriver/CH57x_adc.d \
./StdPeriphDriver/CH57x_clk.d \
./StdPeriphDriver/CH57x_flash.d \
./StdPeriphDriver/CH57x_gpio.d \
./StdPeriphDriver/CH57x_pwr.d \
./StdPeriphDriver/CH57x_spi0.d \
./StdPeriphDriver/CH57x_sys.d \
./StdPeriphDriver/CH57x_uart1.d 

OBJS += \
./StdPeriphDriver/CH57x_adc.o \
./StdPeriphDriver/CH57x_clk.o \
./StdPeriphDriver/CH57x_flash.o \
./StdPeriphDriver/CH57x_gpio.o \
./StdPeriphDriver/CH57x_pwr.o \
./StdPeriphDriver/CH57x_spi0.o \
./StdPeriphDriver/CH57x_sys.o \
./StdPeriphDriver/CH57x_uart1.o 

DIR_OBJS += \
./StdPeriphDriver/*.o \

DIR_DEPS += \
./StdPeriphDriver/*.d \

DIR_EXPANDS += \
./StdPeriphDriver/*.234r.expand \


# Each subdirectory must supply rules for building sources it contributes
StdPeriphDriver/CH57x_adc.o: d:/BaiduSyncdisk/Edith/墨小孔实习/resband/SRC/StdPeriphDriver/CH57x_adc.c
	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -g -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/SRC/Startup" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/resistance_band/HeartRate/APP/include" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/resistance_band/HeartRate/Profile/include" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/SRC/StdPeriphDriver/inc" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/resistance_band/HAL/include" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/SRC/Ld" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/resistance_band/LIB" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/SRC/RVMSIS" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
StdPeriphDriver/CH57x_clk.o: d:/BaiduSyncdisk/Edith/墨小孔实习/resband/SRC/StdPeriphDriver/CH57x_clk.c
	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -g -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/SRC/Startup" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/resistance_band/HeartRate/APP/include" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/resistance_band/HeartRate/Profile/include" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/SRC/StdPeriphDriver/inc" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/resistance_band/HAL/include" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/SRC/Ld" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/resistance_band/LIB" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/SRC/RVMSIS" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
StdPeriphDriver/CH57x_flash.o: d:/BaiduSyncdisk/Edith/墨小孔实习/resband/SRC/StdPeriphDriver/CH57x_flash.c
	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -g -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/SRC/Startup" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/resistance_band/HeartRate/APP/include" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/resistance_band/HeartRate/Profile/include" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/SRC/StdPeriphDriver/inc" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/resistance_band/HAL/include" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/SRC/Ld" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/resistance_band/LIB" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/SRC/RVMSIS" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
StdPeriphDriver/CH57x_gpio.o: d:/BaiduSyncdisk/Edith/墨小孔实习/resband/SRC/StdPeriphDriver/CH57x_gpio.c
	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -g -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/SRC/Startup" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/resistance_band/HeartRate/APP/include" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/resistance_band/HeartRate/Profile/include" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/SRC/StdPeriphDriver/inc" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/resistance_band/HAL/include" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/SRC/Ld" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/resistance_band/LIB" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/SRC/RVMSIS" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
StdPeriphDriver/CH57x_pwr.o: d:/BaiduSyncdisk/Edith/墨小孔实习/resband/SRC/StdPeriphDriver/CH57x_pwr.c
	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -g -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/SRC/Startup" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/resistance_band/HeartRate/APP/include" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/resistance_band/HeartRate/Profile/include" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/SRC/StdPeriphDriver/inc" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/resistance_band/HAL/include" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/SRC/Ld" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/resistance_band/LIB" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/SRC/RVMSIS" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
StdPeriphDriver/CH57x_spi0.o: d:/BaiduSyncdisk/Edith/墨小孔实习/resband/SRC/StdPeriphDriver/CH57x_spi0.c
	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -g -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/SRC/Startup" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/resistance_band/HeartRate/APP/include" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/resistance_band/HeartRate/Profile/include" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/SRC/StdPeriphDriver/inc" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/resistance_band/HAL/include" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/SRC/Ld" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/resistance_band/LIB" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/SRC/RVMSIS" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
StdPeriphDriver/CH57x_sys.o: d:/BaiduSyncdisk/Edith/墨小孔实习/resband/SRC/StdPeriphDriver/CH57x_sys.c
	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -g -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/SRC/Startup" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/resistance_band/HeartRate/APP/include" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/resistance_band/HeartRate/Profile/include" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/SRC/StdPeriphDriver/inc" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/resistance_band/HAL/include" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/SRC/Ld" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/resistance_band/LIB" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/SRC/RVMSIS" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
StdPeriphDriver/CH57x_uart1.o: d:/BaiduSyncdisk/Edith/墨小孔实习/resband/SRC/StdPeriphDriver/CH57x_uart1.c
	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -g -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/SRC/Startup" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/resistance_band/HeartRate/APP/include" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/resistance_band/HeartRate/Profile/include" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/SRC/StdPeriphDriver/inc" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/resistance_band/HAL/include" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/SRC/Ld" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/resistance_band/LIB" -I"d:/BaiduSyncdisk/Edith/墨小孔实习/resband/SRC/RVMSIS" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

