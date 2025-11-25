G = g++ -Wextra -std=c++14 

f = window_show.cpp Game.cpp BoardSetUpSection.cpp PossibleSection.cpp DrawingSection.cpp PathAndFunctionSection.cpp King_sUpdate.cpp ScrollSetUp1.cpp Event.cpp Main.cpp

l = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

build:
	$(G) $(f) -o chess $(l)

run:
	./chess

clean:
	rm chess

cl:
	clear
