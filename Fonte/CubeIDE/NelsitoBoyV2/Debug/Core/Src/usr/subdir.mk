################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/usr/game_01_breakout.c \
../Core/Src/usr/lib_GameStruct.c \
../Core/Src/usr/lib_J3_ST7789VW.c \
../Core/Src/usr/main_nelsitoboy.c 

OBJS += \
./Core/Src/usr/game_01_breakout.o \
./Core/Src/usr/lib_GameStruct.o \
./Core/Src/usr/lib_J3_ST7789VW.o \
./Core/Src/usr/main_nelsitoboy.o 

C_DEPS += \
./Core/Src/usr/game_01_breakout.d \
./Core/Src/usr/lib_GameStruct.d \
./Core/Src/usr/lib_J3_ST7789VW.d \
./Core/Src/usr/main_nelsitoboy.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/usr/%.o Core/Src/usr/%.su Core/Src/usr/%.cyclo: ../Core/Src/usr/%.c Core/Src/usr/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu17 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G431xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-usr

clean-Core-2f-Src-2f-usr:
	-$(RM) ./Core/Src/usr/game_01_breakout.cyclo ./Core/Src/usr/game_01_breakout.d ./Core/Src/usr/game_01_breakout.o ./Core/Src/usr/game_01_breakout.su ./Core/Src/usr/lib_GameStruct.cyclo ./Core/Src/usr/lib_GameStruct.d ./Core/Src/usr/lib_GameStruct.o ./Core/Src/usr/lib_GameStruct.su ./Core/Src/usr/lib_J3_ST7789VW.cyclo ./Core/Src/usr/lib_J3_ST7789VW.d ./Core/Src/usr/lib_J3_ST7789VW.o ./Core/Src/usr/lib_J3_ST7789VW.su ./Core/Src/usr/main_nelsitoboy.cyclo ./Core/Src/usr/main_nelsitoboy.d ./Core/Src/usr/main_nelsitoboy.o ./Core/Src/usr/main_nelsitoboy.su

.PHONY: clean-Core-2f-Src-2f-usr

