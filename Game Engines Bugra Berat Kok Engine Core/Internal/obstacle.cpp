#include "Obstacle.h"

Obstacle::Obstacle(float x, float y, int w, int h)
{
    SetPosition(x, y);
    rect.w = w;
    rect.h = h;

    ChooseNewWaitTime();
}

void Obstacle::ChooseNewWaitTime()
{
    // 1�4 saniye aras� rastgele bekleme
    waitTime = static_cast<float>((rand() % 4) + 1);
}

void Obstacle::ChooseNewDirection()
{
    // Rastgele sa� veya sol y�n
    direction = (rand() % 2 == 0) ? 1 : -1;
}

void Obstacle::Update()
{
    float dt = TimeManager::GetInstance().GetDeltaTime();
    elapsedTime += dt;

    if (!isMoving)
    {
        // Bekleme modundayken s�re dolduysa hareket etmeye ba�la
        if (elapsedTime >= waitTime)
        {
            isMoving = true;
            elapsedTime = 0.0f;
            ChooseNewDirection();
        }
    }
    else
    {
        // Hareket s�resi boyunca hareket et
        if (elapsedTime < moveDuration)
        {
            posX += direction * speed * dt;
            rect.x = static_cast<int>(posX);
        }
        else
        {
            // Hareket bitti, tekrar beklemeye ge�
            isMoving = false;
            elapsedTime = 0.0f;
            ChooseNewWaitTime();
        }
    }
}

void Obstacle::Render(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // k�rm�z�
    SDL_RenderFillRect(renderer, &rect);
}
