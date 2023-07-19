#include <iostream>
#include <SDL2/SDL.h>
#include <SDL_image.h>
using namespace std;
int main(int argc, char const *argv[])
{
    int resW = 1280;
    int resH = 720;

    SDL_Rect sdlRect;
    sdlRect.w = resW/30;
    sdlRect.h = resH/10;
    sdlRect.x = resW/2 - sdlRect.w/2;
    sdlRect.y = resH/2 - sdlRect.h/2;
    int numPixelsToMovePerFrame = sdlRect.w/4;

    bool upArrowDown = false;
    bool leftArrowDown = false;
    bool downArrowDown = false;
    bool rightArrowDown = false;

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    bool appIsRunning = true;
    
    int numMillisToThrottle = 6;
    Uint64 lastDrawTime = SDL_GetTicks64();

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not be initialized: " << SDL_GetError();
    }
    else
    {
        std::cout << "SDL video system is ready to go\n";
    }

    int imgFlags = IMG_INIT_PNG; // Use IMG_INIT_PNG for PNG images. You can use multiple flags if needed.
if (!(IMG_Init(imgFlags) & imgFlags))
{
    std::cout << "SDL_image could not be initialized: " << IMG_GetError();
    SDL_Quit();
    return 1;
}

SDL_Surface* imageSurface = IMG_Load("/Users/mehrshad/Desktop/background.jpg");
    if (!imageSurface)
    {
        std::cout << "Failed to load image: " << IMG_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Create an application window with the following settings:
    window = SDL_CreateWindow(
        "An SDL2 window",        // window title
        SDL_WINDOWPOS_UNDEFINED, // initial x position
        SDL_WINDOWPOS_UNDEFINED, // initial y position
        resW,                     // width, in pixels
        resH,                     // height, in pixels
        SDL_WINDOW_SHOWN         // flags - see below
    );

    // Check that the window was successfully created
    if (window == NULL)
    {
        // In the case that the window could not be made...
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == NULL)
    {
        // In the case that the renderer could not be made...
        printf("Could not create renderer: %s\n", SDL_GetError());
        return 1;
    }

     SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    if (!imageTexture)
    {
        std::cout << "Failed to create texture: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(imageSurface);
        SDL_Quit();
        return 1;
    }


    SDL_FreeSurface(imageSurface);
    //main game/app loop
    while (appIsRunning)
    {
        //slowing things down a little, you can delete this if you like
        while (SDL_GetTicks64() - lastDrawTime < numMillisToThrottle){}

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // Handle each specific event
            if (event.type == SDL_QUIT)
            {
                appIsRunning = false;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.scancode == SDL_SCANCODE_UP)
                {
                upArrowDown = true;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_LEFT)
                {
                leftArrowDown = true;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_DOWN)
                {
                downArrowDown = true;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
                {
                rightArrowDown = true;
                }
            }
            else if (event.type == SDL_KEYUP)
            {
                if (event.key.keysym.scancode == SDL_SCANCODE_UP)
                {
                upArrowDown = false;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_LEFT)
                {
                leftArrowDown = false;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_DOWN)
                {
                downArrowDown = false;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
                {
                rightArrowDown = false;
                }
            }
        }

        //move rectangle
        if (upArrowDown)
        {
            sdlRect.y -= numPixelsToMovePerFrame;
        }
        if (leftArrowDown)
        {
            sdlRect.x -= numPixelsToMovePerFrame;
        }
        if (downArrowDown)
        {
            sdlRect.y += numPixelsToMovePerFrame;
        }
        if (rightArrowDown)
        {
            sdlRect.x += numPixelsToMovePerFrame;
        }

        //bounds checking and correction
        if (sdlRect.x < 0)
        {
            sdlRect.x = 0;
        }
        else if (sdlRect.x + sdlRect.w - 1 >= resW)
        {
            sdlRect.x = resW - sdlRect.w;
        }
        if (sdlRect.y < 0)
        {
            sdlRect.y = 0;
        }
        else if (sdlRect.y + sdlRect.h - 1 >= resH)
        {
            sdlRect.y = resH - sdlRect.h;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, imageTexture, nullptr, nullptr);

        SDL_SetRenderDrawColor(renderer, 255, 100, 180, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &sdlRect);
        //SDL_RenderPresent(renderer);

        

        // Update the screen
        SDL_RenderPresent(renderer);

        lastDrawTime = SDL_GetTicks64();
        
        lastDrawTime = SDL_GetTicks64();
    }

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, imageTexture, nullptr, nullptr);
    SDL_RenderPresent(renderer);

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(imageTexture);
    std::cout << "exiting..." << std::endl;
    IMG_Quit();
    SDL_Quit();
    return 0;
}

// #include <SFML/Graphics.hpp>

// int main() {
//     sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");

//     while (window.isOpen()) {
//         sf::Event event;
//         while (window.pollEvent(event)) {
//             if (event.type == sf::Event::Closed) {
//                 window.close();
//             }
//         }

//         window.clear(sf::Color::White);
//         // Draw your game elements here
//         window.display();
//     }

//     return 0;
// }