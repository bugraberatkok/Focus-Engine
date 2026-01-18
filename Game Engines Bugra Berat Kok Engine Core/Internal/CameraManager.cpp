#include "CameraManager.h"
#include "BaseObject.h"
#include "TimeManager.h"
#include <cmath>

CameraManager::CameraManager()
    : cameraX(0.0f),
    cameraY(0.0f),
    screenWidth(1920),
    screenHeight(1080),
    target(nullptr),
    minX(0.0f),
    maxX(0.0f),
    minY(0.0f),
    maxY(0.0f),
    hasBounds(false),
    smoothSpeed(0.1f),
    smoothEnabled(true)
{
}

void CameraManager::SetScreenSize(int w, int h)
{
    screenWidth = w;
    screenHeight = h;
}

void CameraManager::SetTarget(BaseObject* obj)
{
    target = obj;
}

void CameraManager::SetBounds(float minX_, float maxX_, float minY_, float maxY_)
{
    minX = minX_;
    maxX = maxX_;
    minY = minY_;
    maxY = maxY_;
    hasBounds = true;
}

void CameraManager::SetPosition(float x, float y)
{
    cameraX = x;
    cameraY = y;
}
void CameraManager::Reset()
{
    // 1. Takip edilen objeyi unut (Çok Önemli!)
    target = nullptr;

    // 2. Pozisyonu sıfırla
    cameraX = 0.0f;
    cameraY = 0.0f;

    // 3. Harita sınırlarını kaldır (Yeni harita kendi sınırını koyacak)
    hasBounds = false;
    minX = 0; maxX = 0;
    minY = 0; maxY = 0;

    // 4. Diğer ayarları varsayılana döndür
    smoothEnabled = true;
}
void CameraManager::Update()
{
    if (!target)
        return;

    // Target'ın merkezini al
    const SDL_Rect& rect = target->GetRect();
    float targetCenterX = rect.x + rect.w / 2.0f;
    float targetCenterY = rect.y + rect.h / 2.0f;

    // Kamera hedef: oyuncu ekranın ortasında olsun
    float desiredX = targetCenterX - screenWidth / 2.0f;
    float desiredY = targetCenterY - screenHeight / 2.0f;

    // Smooth camera
    if (smoothEnabled)
    {
        float dt = TimeManager::GetInstance().GetDeltaTime();
        float lerpSpeed = smoothSpeed * dt * 60.0f; // 60 FPS normalize

        cameraX += (desiredX - cameraX) * lerpSpeed;
        cameraY += (desiredY - cameraY) * lerpSpeed;
    }
    else
    {
        cameraX = desiredX;
        cameraY = desiredY;
    }

    // Bounds kontrolü
    if (hasBounds)
    {
        if (cameraX < minX) cameraX = minX;
        if (cameraY < minY) cameraY = minY;
        if (cameraX > maxX - screenWidth) cameraX = maxX - screenWidth;
        if (cameraY > maxY - screenHeight) cameraY = maxY - screenHeight;
    }
}

int CameraManager::WorldToScreenX(float worldX) const
{
    return static_cast<int>(worldX - cameraX);
}

int CameraManager::WorldToScreenY(float worldY) const
{
    return static_cast<int>(worldY - cameraY);
}

float CameraManager::ScreenToWorldX(int screenX) const
{
    return screenX + cameraX;
}

float CameraManager::ScreenToWorldY(int screenY) const
{
    return screenY + cameraY;
}