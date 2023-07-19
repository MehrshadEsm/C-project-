export LIBRARY_PATH=/opt/homebrew/Cellar/sdl2/2.26.5/lib/

game: main.cpp
	g++ main.cpp -o play -I /opt/homebrew/Cellar/sdl2_image/2.6.3_1/include/SDL2 -I /opt/homebrew/Cellar/sdl2/2.26.5/include/SDL2 -L /opt/homebrew/Cellar/sdl2_image/2.6.3_1/lib -lSDL2 -lSDL2_image -F /Library/Frameworks -rpath /Library/Frameworks
