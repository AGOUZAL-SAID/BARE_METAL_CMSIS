CC     := arm-none-eabi-gcc
OBJS:= main.o t1.o t2.o stubs.o
LFLAGS := -L/opt/mylibs
CFLAGS := -c -g -O2 $(MB)
VPATH =  libs
WAR:= -Wall -Werror
MB := -mthumb
.PHONY : hello clean

hello : $(OBJS)
	$(CC) $(LFLAGS) $(MB) $(OBJS) -lm -o $@

clean : 
	rm -f $(OBJS) hello
