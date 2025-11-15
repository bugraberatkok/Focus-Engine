#include "Player.h"
#include "SDL.h"

Player::Player(float x, float y, int w, int h)
{
    SetPosition(x, y);
    rect.w = w;
    rect.h = h;
}

void Player::Update()
{
    // Input kontrol�
    InputManager& input = InputManager::GetInstance();

    if (input.GetKey(SDL_SCANCODE_UP))
        posY -= speed;
    if (input.GetKey(SDL_SCANCODE_DOWN))
        posY += speed;
    if (input.GetKey(SDL_SCANCODE_LEFT))
        posX -= speed;
    if (input.GetKey(SDL_SCANCODE_RIGHT))
        posX += speed;

    // Pozisyonu g�ncelle
    rect.x = static_cast<int>(posX);
    rect.y = static_cast<int>(posY);
}

void Player::Render(SDL_Renderer* renderer)
{
    // ye�il renkli kare
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}
