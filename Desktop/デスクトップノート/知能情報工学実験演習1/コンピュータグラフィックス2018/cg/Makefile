C++	= g++
C++FLAGS = -g
OBJS = viewmgr.o object.o vector.o

.SUFFIXES: .o .cc .c++

.cc.o:
	$(C++) -c $(C++FLAGS) $<

all     :
	@echo '使用法: make ex0? の形で演習の番号を指定すること'

ex00	: $(OBJS) ex00.o
	$(C++) -g $(OBJS) ex00.o -o ex00

ex01	: $(OBJS) ex01.o
	$(C++) -g $(OBJS) ex01.o -o ex01

ex02	: $(OBJS) ex02.o
	$(C++) -g $(OBJS) ex02.o -o ex02

ex03	: $(OBJS) ex03.o
	$(C++) -g $(OBJS) ex03.o -o ex03

ex04	: $(OBJS) ex04.o
	$(C++) -g $(OBJS) ex04.o -o ex04

clean   :
	rm -f core *.o
