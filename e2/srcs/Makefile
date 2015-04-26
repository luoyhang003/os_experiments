src = e2.c
obj = e2.o
opt = -g -c

all:	e2
e2:	$(obj)
	gcc $(obj) -l pthread -o e2
e2.o:	$(src)
	gcc $(opt) $(src)
clean:
	rm e2 *.o
