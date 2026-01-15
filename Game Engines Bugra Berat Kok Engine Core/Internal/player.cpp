#include "Player.h"
#include "SpriteManager.h"
#include <SDL.h>

Player::Player(float x, float y, float scale)
{
    // Önce scale'i ayarla, sonra texture ver (SetTexture bunu kullanacak)
    SetScale(scale);
    SetPosition(x, y);

    SDL_Texture* tex = SpriteManager::GetInstance().LoadTexture(
        "player_idle",
        "../../../../Media/player_idle.png"
    );

    if (!tex)
    {
        SDL_Log("Player texture FAILED to load!");
    }

    SetTexture(tex);   // texW / texH burada doluyor, rect.w/h = texW * scale
}

void Player::Update()
{

    
    InputManager& input = InputManager::GetInstance();

    if (input.GetKey(SDL_SCANCODE_UP))
        posY -= speed;
    if (input.GetKey(SDL_SCANCODE_DOWN))
        posY += speed;
    if (input.GetKey(SDL_SCANCODE_LEFT))
        posX -= speed;
    if (input.GetKey(SDL_SCANCODE_RIGHT))
        posX += speed;

	// Rect pozisyonunu güncelle
    rect.x = static_cast<int>(posX);
    rect.y = static_cast<int>(posY);
}

void Player::Render(SDL_Renderer* renderer)
{
    // Sprite'ı çiz
    BaseObject::Render(renderer);

    // Debug için hitbox görmek istersen:
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderDrawRect(renderer, &rect);
}
