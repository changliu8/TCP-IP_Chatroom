EXECS = a4

all:	$(EXECS)

a4: a4.c
	gcc -Wall -o a4 a4.c a4_1.c a4-util.o
clean:
	rm -f $(EXECS)
