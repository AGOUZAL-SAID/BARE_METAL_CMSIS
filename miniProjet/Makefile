PREFIX = arm-none-eabi-
AS     = $(PREFIX)as
GDB   = $(PREFIX)gdb

connect::
	JLinkGDBServer -device STM32L475VG -endian little -if SWD -speed auto -ir -LocalhostOnly

se203:: 
	$(GDB) -x se203.gdb $@
 

