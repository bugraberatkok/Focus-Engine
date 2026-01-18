#pragma once
#include "Singleton.h"
#include <SDL.h>

class BaseObject;

class CameraManager : public Singleton<CameraManager>
{
    friend class Singleton<CameraManager>;

private:
    CameraManager();

    float cameraX;
    float cameraY;

    int screenWidth;
    int screenHeight;

    BaseObject* target;

    float minX, maxX;
    float minY, maxY;
    bool hasBounds;

    float smoothSpeed;
    bool smoothEnabled;

public:
    void SetScreenSize(int w, int h);
    void SetTarget(BaseObject* obj);
    BaseObject* GetTarget() const { return target; }

    void SetBounds(float minX, float maxX, float minY, float maxY);
    void DisableBounds() { hasBounds = false; }

    void SetPosition(float x, float y);
    float GetX() const { return cameraX; }
    float GetY() const { return cameraY; }

    void SetSmoothSpeed(float speed) { smoothSpeed = speed; }
    void SetSmoothEnabled(bool enabled) { smoothEnabled = enabled; }

    void Update();
    void Reset();

    int WorldToScreenX(float worldX) const;
    int WorldToScreenY(float worldY) const;

    float ScreenToWorldX(int screenX) const;
    float ScreenToWorldY(int screenY) const;

};