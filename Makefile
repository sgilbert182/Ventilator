##########################################################################################################################
# File automatically-generated by tool: [projectgenerator] version: [3.4.0] date: [Tue Apr 14 16:17:44 BST 2020] 
##########################################################################################################################

# ------------------------------------------------
# Generic Makefile (based on gcc)
#
# ChangeLog :
#	2017-02-10 - Several enhancements + project update mode
#   2015-07-22 - first version
# ------------------------------------------------

######################################
# target
######################################

TARGET = VentilatorTestBed

######################################
# building variables
######################################
# debug build?
DEBUG = 1
# optimization
OPT = -O0


#######################################
# paths
#######################################
# Build path
BUILD_DIR = build

######################################
# source
######################################
#C++ SOURCES
# C sources
CPP_SOURCES =  \
Src/main.cpp \
ASL/ThreadTemplate/Src/SoftwareTimerBase.cpp \
ASL/ThreadTemplate/Src/ThreadBase.cpp \
ASL/ThreadTemplate/Src/ThreadControl.cpp \
ASL/Utilities/Src/SubscribeBase.cpp \
ASL/Utilities/Src/SubscribeDebounce.cpp \
ASL/Utilities/Src/GPIODebounceTools.cpp \
BBD/ILI9340/ILI9340.cpp \
APL/Src/WatchdogTask.cpp \
APL/Src/test.cpp \
APL/Src/PneumaticActuator.cpp \
APL/Src/UserInput.cpp \
APL/Src/DebounceTask.cpp \
APL/Src/ButtonHandler.cpp \
APL/Src/AnemometerTask.cpp \
BBD/ILI9340/ILI9340_CTranslator.cpp \
GUI/Widgets/Base/widgetBase.cpp \
GUI/Widgets/Control/controlWidget.cpp


# C sources
C_SOURCES =  \
Src/freertos.c \
Src/stm32f7xx_it.c \
Src/stm32f7xx_hal_msp.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_cortex.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_eth.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_tim.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_tim_ex.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_uart.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_uart_ex.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pcd.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pcd_ex.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_usb.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rcc.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rcc_ex.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_flash.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_flash_ex.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_gpio.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dma.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dma_ex.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pwr.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pwr_ex.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_i2c.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_i2c_ex.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_exti.c \
Src/system_stm32f7xx.c \
Middlewares/Third_Party/FreeRTOS/Source/croutine.c \
Middlewares/Third_Party/FreeRTOS/Source/event_groups.c \
Middlewares/Third_Party/FreeRTOS/Source/list.c \
Middlewares/Third_Party/FreeRTOS/Source/queue.c \
Middlewares/Third_Party/FreeRTOS/Source/stream_buffer.c \
Middlewares/Third_Party/FreeRTOS/Source/tasks.c \
Middlewares/Third_Party/FreeRTOS/Source/timers.c \
Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.c \
Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c \
Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1/port.c \
Src/stm32f7xx_hal_timebase_tim.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_spi.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_spi_ex.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_iwdg.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_adc.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_adc_ex.c \
GUI/Images/VentilatorCrowdLogo-02-01.c
#GUI/Config/GUIConf.c \
GUI/Config/GUIDRV_ILI9340.c \
GUI/OS/GUI_X_OS.c 

#BBD/ILI9341/ILI9341_STM32_Driver.c
#BBD/LiquidCrystal_I2C-master
#BBD/LiquidCrystal_I2C-master
#BBD/LCD1602/Src/lcd16x2.c 

# ASM sources
ASM_SOURCES =  \
startup_stm32f767xx.s

#DEPS := $(OBJS:.o=.d)

#######################################
# binaries
#######################################
PREFIX = arm-none-eabi-
# The gcc compiler bin path can be either defined in make command via GCC_PATH variable (> make GCC_PATH=xxx)
# either it can be added to the PATH environment variable.
ifdef GCC_PATH
CPP= $(GCC_PATH)/$(PREFIX)g++
CC = $(GCC_PATH)/$(PREFIX)gcc
AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy
AR = $(GCC_PATH)/$(PREFIX)ar
OD = $(GCC_PATH)/$(PREFIX)objdump
SZ = $(GCC_PATH)/$(PREFIX)size
else
CPP= $(PREFIX)g++
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
AR = $(PREFIX)ar
OD = $(PREFIX)objdump
SZ = $(PREFIX)size
endif

HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S
LD  = $(CPP)

#######################################
# CFLAGS
#######################################
# cpu
CPU = -mcpu=cortex-m7

# fpu
FPU = -mfpu=fpv5-d16

# float-abi
FLOAT-ABI = -mfloat-abi=hard

# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# macros for gcc
# AS defines
AS_DEFS = 

# C defines
C_DEFS =  \
-DUSE_HAL_DRIVER \
-DSTM32F767xx

# C defines
CPP_DEFS =  \
-DUSE_HAL_DRIVER \
-DSTM32F767xx \

# AS includes
AS_INCLUDES =  \
-I\Inc

# C includes
C_INCLUDES =  \
-IInc \
-IDrivers/STM32F7xx_HAL_Driver/Inc \
-IDrivers/STM32F7xx_HAL_Driver/Inc/Legacy \
-IMiddlewares/Third_Party/FreeRTOS/Source/include \
-IMiddlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 \
-IMiddlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 \
-IDrivers/CMSIS/Device/ST/STM32F7xx/Include \
-IDrivers/CMSIS/Include \
-IASL/Inc \
-IAPL/Inc \
-IBBD/LCD1602/Inc \
-IBBD/ILI9340 \
-IGUI/Config \
-IGUI/inc \
-IGUI/Fonts \
-IGUI/Widgets/Base \
-IGUI/Widgets/Control \
-IGUI/Widgets/Graph

CPP_INCLUDES = \
-IASL/Inc \
-IAPL/Inc \
-IASL/ThreadTemplate/Inc \
-IASL/Utilities/Inc \
-IBBD/ILI9340

#C_INCLUDES += $(CPP_INCLUDES)
#makefile includes
#-include Middlewares/ST/STemWin/subdir.mk

ERRFLAGS = -Wall -Wformat-nonliteral -Wpointer-arith \
-Wmissing-declarations -Wcast-qual -Wwrite-strings \
-Wno-unused-parameter -Wfloat-equal -Wno-switch \
#-Wdouble-promotion # -Winline -Wundef -Wshadow -Wcast-align \
-Wno-missing-field-initializers -Wextra -Werror 

CERRFLAGS = $(ERRFLAGS) \
-Wbad-function-cast -Wmissing-prototypes -Wstrict-prototypes -Wnested-externs

CPPERRFLAGS = $(ERRFLAGS) -std=c++2a \
-Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op \
-Wmissing-include-dirs -Wnoexcept -Woverloaded-virtual \
-Wredundant-decls -Wsign-conversion -Wsign-promo  -Wstrict-null-sentinel \
-Wstrict-overflow=5 -Wswitch-default -Wno-unused -Werror=c++0x-compat -Wshadow -Wcast-align \
-pedantic \
-Wextra \
#-Weffc++
#-ansi \
#-Wold-style-cast 

# compile gcc flags
ASFLAGS  = $(MCU) $(AS_DEFS)  $(AS_INCLUDES)  $(OPT) -fdata-sections -ffunction-sections
CFLAGS   = $(MCU) $(C_DEFS)   $(C_INCLUDES)   $(OPT) -std=gnu11 -ffreestanding $(CERRFLAGS) $(ERRFLAGS) -fno-exceptions -Wpedantic -fdata-sections -ffunction-sections
CPPFLAGS = $(MCU) $(CPP_DEFS) $(C_INCLUDES) $(CPP_INCLUDES) $(OPT) -std=gnu++2a -fno-rtti $(CPPERRFLAGS) -fpermissive -ffreestanding -fno-exceptions --specs=nano.specs

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif


# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)" -g -ggdb

CPPFLAGS += -MMD -MP -MF"$(@:%.o=%.d)" -g -ggdb

#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT = STM32F767ZITx_FLASH.ld

# libraries
LIBS = -lc -lm -lnosys #GUI/Lib/STemWin532_CM7_GCC.a
LIBDIR =
LDFLAGS = -static $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections --specs=nosys.specs -flto

# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin


#######################################
# build the application
#######################################
# list of C++ objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(CPP_SOURCES:.cpp=.o)))
vpath %.cpp $(sort $(dir $(CPP_SOURCES)))
# list of C objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.cpp Makefile | $(BUILD_DIR) 
	$(CPP) -c $(CPPFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.cpp=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	@echo Compiling $(<F)
	@$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(LD) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@	
	
$(BUILD_DIR):
	mkdir $@		

#######################################
# clean up
#######################################
clean:
	-rm -fR $(BUILD_DIR)
  
#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)

# *** EOF ***
