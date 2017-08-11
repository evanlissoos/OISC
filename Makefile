EXENAME = oisc
OBJS = main.o oisc.o

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++

all : $(EXENAME)

$(EXENAME) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

oisc.o : oisc.cpp oisc.h
	$(CXX) $(CXXFLAGS) oisc.cpp

main.o : main.cpp oisc.h
	$(CXX) $(CXXFLAGS) main.cpp

clean :
	rm -f *.o $(EXENAME)
