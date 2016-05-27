
life: TestingLifeFunc.o main.o LifeTest.o
	gcc -lm -o life  TestingLifeFunc.o main.o LifeFunc.o 

test: TestingLifeFunc.o testmain.o LifeTest.o 
	gcc -lm -o test TestingLifeFunc.o testmain.o LifeFunc.o  

main.o: main.c LifeFunc.h ConsoleWrap.h
	gcc -c main.c

TestingLifeFunc.o: TestingLifeFunc.c LifeFunc.h ConsoleWrap.h
	gcc -c TestingLifeFunc.c

LifeFunc.o: LifeFunc.c LifeFunc.h ConsoleWrap.h
	gcc -c LifeFunc.c

testmain.o: testmain.c
	gcc -c testmain.c
