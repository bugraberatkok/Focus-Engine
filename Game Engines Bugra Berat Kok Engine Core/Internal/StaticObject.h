#pragma once
#include "BaseObject.h"

// Cansız objeler için (ağaç, kaya, duvar, pickup)
class StaticObject : public BaseObject
{
protected:
    bool hasCollision;  // Collision var mı?
    bool isPickup;      // Toplanabilir mi? (coin, powerup)

public:
    StaticObject();
    virtual ~StaticObject();

    // Collision
    void SetCollision(bool collision) { hasCollision = collision; }
    bool HasCollision() const { return hasCollision; }

    // Pickup
    void SetPickup(bool pickup) { isPickup = pickup; }
    bool IsPickup() const { return isPickup; }

    // Child'lar override edebilir
    virtual void OnCollect() {}  // Toplanınca ne olsun (coin için)

    void Update() override;
    void Render(SDL_Renderer* renderer) override;
};