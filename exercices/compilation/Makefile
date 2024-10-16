CC       = gcc
PREFIX   =arm-none-eabi-
AS       = $(PREFIX)as
LD       = $(PREFIX)ld
ASFLAGS  = -g
LDFLAGS  = -g -Ttext 0x20000000
CFLAGS   = -c -O1 -Wall
ASFILES  = $(wildcard *.s)
ELFFILES = $(patsubst %.s,%.elf,$(ASFILES))
TARGET   = ex3-2

all: $(ELFFILES)

%.o:%.s
	$(AS) $(ASFLAGS) $< -o $@

%.elf:%.o
	$(LD) $(LDFLAGS) $< -o $@

$(TARGET): ex3-1.c
	$(CC) $(CFLAGS) -o $(TARGET) $<

.PHONY: clean


clean:
	rm -f $(ELFFILES)
