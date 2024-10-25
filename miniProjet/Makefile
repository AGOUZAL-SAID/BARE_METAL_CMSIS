PREFIX       = arm-none-eabi-
AS           = $(PREFIX)as
CC           = $(PREFIX)gcc 
LD           = $(PREFIX)ld
INCLUDES      = -I CMSIS/Device/ST/STM32L4xx/Include -I CMSIS/Include
TARGET_ARCH  = -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -mthumb
CFLAGS       = -g -O1 -Wall -Wextra -Werror $(INCLUDES)
ASFLAGS      = -g -mcpu=cortex-m4 -mthumb
LDFLAGS      = -nostdlib -ffreestanding -T ld_ram.lds 

.PHONY: startgdbserver 

EXEC = main
OBJS = crt0.o  init.o  clocks.o main.o matrix.o image.o

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) $(TARGET_ARCH) $^ -o $@

image.o : image.raw
	$(PREFIX)objcopy -I binary -O elf32-littlearm -B armv7e-m $< $@

startgdbserver :
	JLinkGDBServer -device STM32L475VG -endian little -if SWD -speed auto -ir -LocalhostOnly

debug: $(EXEC)
	arm-none-eabi-gdb -x se203.gdb $<

clean :
	rm -f $(EXEC)
	rm -f $(OBJS)
