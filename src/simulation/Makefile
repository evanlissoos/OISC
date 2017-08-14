EXENAME = oisc
DIR_LIB = ./lib
OBJS = main.o $(DIR_LIB)/oisc.o $(DIR_LIB)/interactive_oisc.o

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -pthread -c -g -O0 -Wall -Wextra
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++

all : $(EXENAME)

$(EXENAME) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

oisc.o : $(DIR_LIB)/oisc.cpp $(DIR_LIB)/oisc.h $(DIR_LIB)/cpu.h
	$(CXX) $(CXXFLAGS) $(DIR_LIB)/oisc.cpp

interactive_oisc.o : $(DIR_LIB)/interactive_oisc.cpp $(DIR_LIB)/interactive_oisc.h $(DIR_LIB)/oisc.h
	$(CXX) $(CXXFLAGS) $(DIR_LIB)/interactive_oisc.cpp

main.o : main.cpp $(DIR_LIB)/interactive_oisc.h $(DIR_LIB)/mem_io.hpp
	$(CXX) $(CXXFLAGS) main.cpp

clean :
	rm -f *.o $(EXENAME)

cleano:
	rm -f *.o
	rm -f lib/*.o
