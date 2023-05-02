export LIBRARY_PATH=/opt/homebrew/Cellar/sdl2/2.26.5/lib/
game:
	g++ main.cpp -o play -I include -L lib -l SDL2-2.0.0