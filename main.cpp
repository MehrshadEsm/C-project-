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

    SDL_Surface* newImageSurface = IMG_Load("/Users/mehrshad/Desktop/bruh.png");
if (!newImageSurface)
{
    std::cout << "Failed to load new image: " << IMG_GetError() << std::endl;
    // Handle the error if the new image cannot be loaded
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

    // Create a new texture from the new image
    SDL_Texture* newImageTexture = SDL_CreateTextureFromSurface(renderer, newImageSurface);
     if (!newImageTexture)
     {
    std::cout << "Failed to create texture for new image: " << SDL_GetError() << std::endl;
    SDL_FreeSurface(newImageSurface);
    // Handle the error if the new texture cannot be created
}



    SDL_FreeSurface(imageSurface);
    // Free the surface used for loading the new image
    SDL_FreeSurface(newImageSurface);
    //main game/app loop

    SDL_Rect newImageRect;
    newImageRect.x = resW/2 - sdlRect.w/2; // Set the x-coordinate of the top-left corner
    newImageRect.y = resH/2 - sdlRect.h/2; // Set the y-coordinate of the top-left corner
    newImageRect.w = resW/10; // Set the width of the new image (adjust as needed)
    newImageRect.h = resW/6; // Set the height of the new image (adjust as needed)
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
                // Load the new image for the left arrow key
                newImageSurface = IMG_Load("/Users/mehrshad/Desktop/bruh.png");
                if (!newImageSurface)
                {
                    std::cout << "Failed to load new image: " << IMG_GetError() << std::endl;
                    // Handle the error if the new image cannot be loaded
                }

                // Update the new image texture with the new image
                SDL_DestroyTexture(newImageTexture);
                newImageTexture = SDL_CreateTextureFromSurface(renderer, newImageSurface);
                if (!newImageTexture)
                {
                    std::cout << "Failed to create texture for new image: " << SDL_GetError() << std::endl;
                    SDL_FreeSurface(newImageSurface);
                    // Handle the error if the new texture cannot be created
                }

                // Free the surface used for loading the new image
                SDL_FreeSurface(newImageSurface);
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_DOWN)
                {
                downArrowDown = true;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
                {
                rightArrowDown = true;
                // Load the new image for the right arrow key
                newImageSurface = IMG_Load("/Users/mehrshad/Desktop/bruhr.png");
                if (!newImageSurface)
                {
                    std::cout << "Failed to load new image: " << IMG_GetError() << std::endl;
                    // Handle the error if the new image cannot be loaded
                }

                // Update the new image texture with the new image
                SDL_DestroyTexture(newImageTexture);
                newImageTexture = SDL_CreateTextureFromSurface(renderer, newImageSurface);
                if (!newImageTexture)
                {
                    std::cout << "Failed to create texture for new image: " << SDL_GetError() << std::endl;
                    SDL_FreeSurface(newImageSurface);
                    // Handle the error if the new texture cannot be created
                }

                // Free the surface used for loading the new image
                SDL_FreeSurface(newImageSurface);
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
            newImageRect.y -= numPixelsToMovePerFrame;
            sdlRect.y -= numPixelsToMovePerFrame;
        }
        if (leftArrowDown)
        {
            //newImageSurface = IMG_Load("/Users/mehrshad/Desktop/bruh.png");
            newImageRect.x -= numPixelsToMovePerFrame;
            sdlRect.x -= numPixelsToMovePerFrame;
        }
        if (downArrowDown)
        {
            newImageRect.y += numPixelsToMovePerFrame;
            sdlRect.y += numPixelsToMovePerFrame;
        }
        if (rightArrowDown)
        {
            //newImageSurface = IMG_Load("/Users/mehrshad/Desktop/bruhr.png");
            newImageRect.x += numPixelsToMovePerFrame;
            sdlRect.x += numPixelsToMovePerFrame;
        }

        //bounds checking and correction
        if (newImageRect.x < 0)
        {
            newImageRect.x = 0;
        }
        else if (newImageRect.x + newImageRect.w - 1 >= resW)
        {
            newImageRect.x = resW - newImageRect.w;
        }
        if (newImageRect.y < 0)
        {
            newImageRect.y = 0;
        }
        else if (newImageRect.y + newImageRect.h - 1 >= resH)
        {
            newImageRect.y = resH - newImageRect.h;
        }

        // if (newImageRect.x < 0)
        // {
        //     newImageRect.x = 0;
        // }
        // else if (newImageRect.x + newImageRect.w - 1 >= resW)
        // {
        //     newImageRect.x = resW - newImageRect.w;
        // }
        // if (newImageRect.y < 0)
        // {
        //     newImageRect.y = 0;
        // }
        // else if (newImageRect.y + newImageRect.h - 1 >= resH)
        // {
        //     newImageRect.y = resH - newImageRect.h;
        // }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, imageTexture, nullptr, nullptr);

        // SDL_SetRenderDrawColor(renderer, 255, 100, 180, SDL_ALPHA_OPAQUE);
        // SDL_RenderFillRect(renderer, &sdlRect);
        //SDL_RenderPresent(renderer);

        SDL_RenderCopy(renderer, newImageTexture, nullptr, &newImageRect);

        

        // Update the screen
        SDL_RenderPresent(renderer);

        lastDrawTime = SDL_GetTicks64();
    
    }

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, imageTexture, nullptr, nullptr);
    SDL_RenderPresent(renderer);

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(imageTexture);
    SDL_DestroyTexture(newImageTexture);
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