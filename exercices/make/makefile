CC     		:= arm-none-eabi-gcc
OBJS   		:= main.o t1.o t2.o stubs.o
LFLAGS 		:= -L/opt/mylibs
CFLAGS 		:= -c -g -O2 $(MB)
VPATH  		 =  libs
WAR    		:= -Wall -Werror
MB 	   		:= -mthumb
.PHONY 		: hello clean

hello : $(OBJS) t1.h t2.h
	$(CC) $(LFLAGS) $(MB) $(OBJS) -lm -o $@

t1.o: t1.h
t2.o: t2.h

clean : 
	rm -f $(OBJS) hello
