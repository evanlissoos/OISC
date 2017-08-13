EXENAME = oisc
DIR_LIB = ./lib
OBJS = main.o $(DIR_LIB)/oisc.o $(DIR_LIB)/interactive_oisc.o #$(DIR_LIB)/mem_io.o

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++

all : $(EXENAME)

$(EXENAME) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

oisc.o : $(DIR_LIB)/oisc.cpp $(DIR_LIB)/oisc.h $(DIR_LIB)/cpu.h
	$(CXX) $(CXXFLAGS) $(DIR_LIB)/oisc.cpp

interactive_oisc.o : $(DIR_LIB)/interactive_oisc.cpp $(DIR_LIB)/interactive_oisc.h $(DIR_LIB)/oisc.h
	$(CXX) $(CXXFLAGS) $(DIR_LIB)/interactive_oisc.cpp

#mem_io.o : $(DIR_LIB)/mem_io.cpp $(DIR_LIB)/mem_io.h $(DIR_LIB)/cpu.h
#	$(CXX) $(CXXFLAGS) $(DIR_LIB)/mem_io.cpp

main.o : main.cpp $(DIR_LIB)/interactive_oisc.h
	$(CXX) $(CXXFLAGS) main.cpp

clean :
	rm -f *.o $(EXENAME)

cleano:
	rm -f *.o
	rm -f lib/*.o
