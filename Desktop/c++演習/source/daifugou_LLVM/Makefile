# Makefile 
CC	= gcc -std=c99
CFLAGS = -Wall -g
CXX = g++ -std=c++11
CXXFLAGS = -Wall -g
#
INCDIRS = -I./

.PHONY: clean

%.o:%.c
	$(CC) $(CCFLAGS) $(INCDIRS) -c $<

%.o:%.cpp
	$(CXX) $(CXXFLAGS) $(INCDIRS) -c $<

#
INCLUDES = card.h cardset.h 
DAIFUGOUINCLUDES = $(INCLUDES) dealer.h player.h group08.h simpleplayer.h think_ta1.h 

CARDSOBJS 		= card.o cardset.o 
XCARDSOBJS 		= cardset_remove.o cardset_draw.o 
DAIFUGOUOBJS 	= dealer.o player.o group08.o simpleplayer.o daifugou.o
TA1OBJS 		= think_ta1.o 

all: daifugou.exe 
#all: daifugou.exe taikai.exe

$(CARDSOBJS): $(INCLUDES)
$(DAIFUGOUOBJS): $(DAIFUGOUINCLUDES)

#$(TA1OBJS): $(DAIFUGOUINCLUDES) hidden/think_ta1.cpp
#	$(CXX) $(CXXFLAGS) $(INCDIRS) -c hidden/$*.cpp
#	
#$(XCARDSOBJS): $(INCLUDES) hidden/cardset_remove.cpp hidden/cardset_draw.cpp
#	$(CXX) $(CXXFLAGS) $(INCDIRS) -c hidden/$*.cpp

libhidden.a: $(XCARDSOBJS) $(TA1OBJS) $(INCLUDES)
	ar rcs libhidden.a $(XCARDSOBJS) $(TA1OBJS) 

daifugou.exe: $(CARDSOBJS) $(DAIFUGOUOBJS) $(TA1OBJS) $(XCARDSOBJS) 
	$(CXX) $(CXXFLAGS) $(INCDIRS) -o daifugou.exe $(CARDSOBJS) $(DAIFUGOUOBJS) $(XCARDSOBJS) $(TA1OBJS) 

#taikai.exe: $(CARDSOBJS) $(DAIFUGOUOBJS) libhidden.a
#	$(CXX) $(CXXFLAGS) $(INCDIRS) -o taikai.exe $(CARDSOBJS) $(DAIFUGOUOBJS) libhidden.a

#taikai.o: $(DAIFUGOUINCLUDES)
#scuredealer.o: securedealer.h $(DAIFUGOUINCLUDES)
#taikai.exe: taikai.o securedealer.o $(CARDSOBJS) $(DAIFUGOUOBJS) $(HIDDENOBJS) 
#	$(CXX) $(CXXFLAGS) $(INCDIRS) -o taikai.exe taikai.o securedealer.o $(CARDSOBJS) $(DAIFUGOUOBJS) $(HIDDENOBJS) 

clean: 
	rm -rf $(CARDSOBJS) $(DAIFUGOUOBJS) daifugou.exe *.dSYM *~

clean_all:
	rm -rf *.o *.exe *.a
