CXX = gcc
SDL = -framework SDL2 -framework SDL2_image -framework SDL2_ttf
# If your compiler is a bit older you may need to change -std=c++11 to -std=c++0x
CXXFLAGS = -Wall -c 
LDFLAGS = $(SDL)
EXE = honshu

all: $(EXE)

$(EXE): main.o

	$(CXX) $(LDFLAGS) $< -o $@

main.o: mainSDL.c

	$(CXX) $(CXXFLAGS) $< -o $@

clean:

	rm *.o && rm $(EXE)