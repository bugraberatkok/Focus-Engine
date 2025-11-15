#include <iostream>
#include "SDL.h"
#include "Singleton.h" 
#include "InputManager.h"
#include "ObjectManager.h"
#include "TimeManager.h"
#include "BaseObject.h"
#include "PhysicsManager.h"

#include "obstacle.h"
#include "Player.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int FPS = 60;


int main(int argc, char* argv[])
{
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "SDL başlatılamadı! Hata: " << SDL_GetError() << std::endl;
        return 1;
    }

    // window creation
    window = SDL_CreateWindow("Game Engine",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN);

    if (!window) {
        std::cerr << "Error:  " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // renderer creation
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!renderer) {
        std::cerr << "Renderer oluşturulamadı! Hata: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }


    InputManager::CreateSingleton();
    ObjectManager::CreateSingleton();
    PhysicsManager::CreateSingleton();
    TimeManager::CreateSingleton();

    

    // renderer is declared to ObjectManager
    ObjectManager::GetInstance().SetRenderer(renderer);


    // Player Object
    Player* player = new Player(375.0f, 275.0f, 50, 50);

    //Obstacle Object
    Obstacle* obstacle1 = new Obstacle(200, 150, 50, 50);
     


    // example game loop


    bool isRunning = true;
    SDL_Event event;

    while (isRunning)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                isRunning = false;
            }
        }

        // Uptade and Render

        TimeManager::GetInstance().Update();
        InputManager::GetInstance().Update();

        // close with 'esc'
        if (InputManager::GetInstance().GetKey(SDL_SCANCODE_ESCAPE))
        {
            isRunning = false;
        }

        ObjectManager::GetInstance().Update();

        PhysicsManager::GetInstance().DetectAllCollisions();

        // draw everything
        ObjectManager::GetInstance().RenderAll();

    }

    // Exit and clear the screen.

    TimeManager::DestroySingleton();
    PhysicsManager::DestroySingleton();
    ObjectManager::DestroySingleton();
    InputManager::DestroySingleton();
    

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    std::cout << "Engine closed" << std::endl;
    return 0;
}