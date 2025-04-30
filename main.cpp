#include <SDL.h>
#include <iostream>

int main (int argc, char* args[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        std::cerr << "SDL Initialization Failed, SDL_ERROR: " << SDL_GetError() << std::endl;
    }

    SDL_Window* window = SDL_CreateWindow("MoveTheBox", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    
    if (window == nullptr){
        std::cerr << "Window Creation Failed, SDL_ERROR: " << SDL_GetError() << std::endl;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if(renderer == nullptr){
        std::cerr << "Renderer Creation Failed, SDL_ERROR: " << SDL_GetError() << std::endl;
    }

    SDL_Rect box = {100, 100, 50, 50};
    SDL_Color boxColor = {0, 255, 0, 255};
    const int speed = 5;
    const int dash = 15;
    bool running = true;
    SDL_Event event;
    const Uint8* keystates = SDL_GetKeyboardState(NULL);

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
    
        // Get key states (allows multiple keys)
        SDL_PumpEvents();  // Update key state
        bool isDashing = keystates[SDL_SCANCODE_SPACE];
    
        int moveSpeed = isDashing ? dash : speed;
    
        if (keystates[SDL_SCANCODE_UP]) {
            box.y -= moveSpeed;
        }
        if (keystates[SDL_SCANCODE_DOWN]) {
            box.y += moveSpeed;
        }
        if (keystates[SDL_SCANCODE_LEFT]) {
            box.x -= moveSpeed;
        }
        if (keystates[SDL_SCANCODE_RIGHT]) {
            box.x += moveSpeed;
        }
    
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, boxColor.r, boxColor.g, boxColor.b, boxColor.a);
        SDL_RenderFillRect(renderer, &box);

        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}