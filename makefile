OBJ = main.o wifiscan.o graph.o
APPNAME = wifi.a

$(APPNAME) : $(OBJ)
	gcc -o $(APPNAME) $(OBJ) -lm

%.o : %.c 
	gcc -c -o $@ $< 

clean : 
	rm $(OBJ) $(APPNAME)

archive :
	tar cf wifi.tar *.c *.h makefile
