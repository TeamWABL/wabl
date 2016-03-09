# Makefile template for AVR projects
# @author	Stephen Papierski <stephenpapierski@gmail.com>
# @date		2015-03-23

#############################################
# COMMAND OVERVIEW
#############################################
# make			Runs make hex
# make hex		Generates hex file
# make libs		Compiles .c libraries, but does not link them
# make lst		Generates lst file
# make clean	Cleans file directory
#
# make flash	Flashes the MCU
# make terminal	Enters avrdude terminal mode
#############################################


#############################################
#SETTINGS
#############################################

# project name
PRG			:= wabl
SRC_FOLDER 	:= ./src

#optimization level
#-O0 = no optimization, -O1 = moderate optimization, -O2 = full optimization, -Os = optimized for size
#OPTIMIZE	= -O0
#OPTIMIZE	= -O1
#OPTIMIZE	= -O2
OPTIMIZE	= -Os

#MCU target
#MCU_TARGET     = at90s2313
#MCU_TARGET     = at90s2333
#MCU_TARGET     = at90s4414
#MCU_TARGET     = at90s4433
#MCU_TARGET     = at90s4434
#MCU_TARGET     = at90s8515
#MCU_TARGET     = at90s8535
#MCU_TARGET     = atmega128
#MCU_TARGET     = atmega1280
#MCU_TARGET     = atmega1281
#MCU_TARGET     = atmega1284p
#MCU_TARGET     = atmega16
#MCU_TARGET     = atmega163
#MCU_TARGET     = atmega164p
#MCU_TARGET     = atmega165
#MCU_TARGET     = atmega165p
#MCU_TARGET     = atmega168
#MCU_TARGET     = atmega169
#MCU_TARGET     = atmega169p
#MCU_TARGET     = atmega2560
#MCU_TARGET     = atmega2561
#MCU_TARGET     = atmega32
#MCU_TARGET     = atmega324p
#MCU_TARGET     = atmega325
#MCU_TARGET     = atmega3250
#MCU_TARGET     = atmega328p
#MCU_TARGET     = atmega329
#MCU_TARGET		= atmega3290
#MCU_TARGET     = atmega48
#MCU_TARGET     = atmega64
#MCU_TARGET     = atmega640
#MCU_TARGET     = atmega644
#MCU_TARGET     = atmega644p
#MCU_TARGET     = atmega645
#MCU_TARGET     = atmega6450
#MCU_TARGET     = atmega649
#MCU_TARGET     = atmega6490
#MCU_TARGET     = atmega8
#MCU_TARGET     = atmega8515
#MCU_TARGET     = atmega8535
#MCU_TARGET     = atmega88
#MCU_TARGET     = attiny2313
#MCU_TARGET     = attiny24
#MCU_TARGET     = attiny25
#MCU_TARGET     = attiny26
#MCU_TARGET     = attiny261
#MCU_TARGET     = attiny44
#MCU_TARGET     = attiny45
#MCU_TARGET     = attiny461
#MCU_TARGET     = attiny84
#MCU_TARGET     = attiny85
#MCU_TARGET     = attiny861
#MCU_TARGET		= atmega1284p
MCU_TARGET		= atmega1284p

PART			= m1284p

PORT			?= /dev/ttyUSB0

#############################################
#Pololu Library Settings
#############################################

ifeq ($(MCU_TARGET),atmega328p)
	DEVICE_SPECIFIC_FLAGS	= 
	DEVICE					= -lpololu_atmega328p
else 
ifeq ($(MCU_TARGET),atmega1284p)
	DEVICE_SPECIFIC_FLAGS	= -D_X2_1284
	DEVICE					= -lpololu_atmega1284p_x2
endif
endif

############################################

PROGRAMMER 	:= avrispv2
CC			:= avr-gcc
OBJCOPY		:= avr-objcopy
OBJDUMP		:= avr-objdump

FOLDERS 	:= ./ $(sort $(dir $(wildcard $(SRC_FOLDER)/*/)))

#SRC 		:= $(foreach folder, $(FOLDERS),$(wildcard $(folder)*.c))

SRC			:= ./src/main.c
# Custom Modules
#SRC			+= ./src/led/led.c
SRC			+= ./src/motor/motor.c
SRC			+= ./src/orientation/orient.c
SRC			+= ./src/test_code/test.c
SRC			+= ./src/uart/uart.c
SRC			+= ./src/lqr/lqr.c
SRC			+= ./src/encoder/encoder.c
SRC			+= ./src/safety/safety.c
SRC			+= ./src/sound/sound.c
SRC			+= ./src/communication/comm.c
# Libraries
SRC			+= ./libs/avr-systimer/tmr.c
SRC			+= ./libs/ringbuffer/ringbuffer.c

I2C_DIR		:= ./libs/i2cmaster
I2C_TRG		:= $(I2C_DIR)/i2cmaster

FULL_PRINTF := -Wl,-u,vfprintf -lprintf_flt -lm

CLEAN := *.o *.d *.hex *.map *.elf *.lst $(PRG)
CLEAN_PATH := $(foreach folder, $(FOLDERS), $(foreach pattern, $(CLEAN), $(folder)$(pattern)))

override CFLAGS		:= -MD -MP -g -Wall -mmcu=$(MCU_TARGET) $(DEVICE_SPECIFIC_FLAGS) $(FULL_PRINTF) $(OPTIMIZE)
override LDFLAGS	:= -Wl,-gc-sections -Wl,-Map,$(PRG).map $(DEVICE) -Wl,-relax

ADDITIONAL_CLEAN := $(foreach pattern, $(CLEAN), $(I2C_DIR)/$(pattern))

hex: $(PRG).hex

# compiles are .c src files, but does not link them
libs: $(SRC:%.c=%.o) $(I2C_TRG).o

# produces the lst file from the executable
lst: $(PRG).lst

# it cleans...
clean:
	@echo "Cleaning directories..."
	@$(foreach path, $(CLEAN_PATH), rm -f $(path))
	@$(foreach path, $(ADDITIONAL_CLEAN), rm -f $(path))

# automatically complies all c files and links them
# produces an executable with the name of $(PRG).elf
$(PRG).elf: $(SRC:%.c=%.o) $(I2C_TRG).o
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $(PRG).elf

# produces the hex frile from the executable
%.hex: %.elf
	$(OBJCOPY) -R .eeprom -O ihex $< $@

# compiles i2c assembly code
$(I2C_TRG).o: $(I2C_TRG).S
	avr-gcc -c -mmcu=$(MCU_TARGET) -I. -x assembler-with-cpp -Wa,-adhlns=$(I2C_TRG).lst,-gstabs $(I2C_TRG).S -o $(I2C_TRG).o
# produces the lst file from the executable
%.lst: %.elf
	$(OBJDUMP) -h -S $< > $@

# updates dependencies on header files
-include $(SRC:%.c=%.d)

# makes sure that MCU_TARGET is set
definitions_check:
ifndef MCU_TARGET
	$(error MCU_TARGET is not set)
endif

# flashes the hex file to the chip via the pocket programmer
flash: $(PRG).hex
	avrdude -v -v -v -v -p $(PART) -c $(PROGRAMMER) -P $(PORT) -B 50 -e -U flash:w:$(PRG).hex

# enters avrdude terminal mode
terminal:
	avrdude -p $(PART) -c $(PROGRAMMER) -P $(PORT) -t
