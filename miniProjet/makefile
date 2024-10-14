CC          := arm-none-eabi-gcc 
LD           = arm-none-eabi-ld
TARGET_ARCH := -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -mthumb
CFLAGS      := -g -O1
LDFLAGS      = -nostdlib -ffreestanding -T ld_ram.lds 
C_FILES     := $(wildcard *.c)
OBJS   := $(patsubst %.c, %.o, $(C_FILES))
EXCUTABLES := $(patsubst %.c, %, $(C_FILES))
PREFIX       = arm-none-eabi-
AS           = $(PREFIX)as
.PHONY: startgdbserver 

ifeq ($(EXEC),)
	$(error il faut definir le variable EXEC par le nom d'excutable à a linker)
endif

$(EXEC): $(EXEC).o crt0.o init.o
	$(CC) $(LDFLAGS) $^ -o $@ 

startgdbserver :
	JLinkGDBServer -device STM32L475VG -endian little -if SWD -speed auto -ir -LocalhostOnly

clean :
	rm -f *.o $(EXCUTABLES)