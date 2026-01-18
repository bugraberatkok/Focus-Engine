#pragma once
#include <SDL.h>
#include <functional>
#include <string>

// Tüm UI elemanları bundan türer
class UIElement
{
protected:
    SDL_Rect rect;           // Pozisyon ve boyut
    bool visible;            // Görünür mü?
    bool enabled;            // Aktif mi? (button için)
    std::string id;          // Unique ID

public:
    UIElement(const std::string& id, int x, int y, int w, int h)
        : id(id), visible(true), enabled(true)
    {
        rect = { x, y, w, h };
    }

    virtual ~UIElement() {}

    // Her UI element bunları implement eder
    virtual void Update() = 0;
    virtual void Render(SDL_Renderer* renderer) = 0;
    virtual void HandleEvent(SDL_Event& event) = 0;

    // Getters/Setters
    const SDL_Rect& GetRect() const { return rect; }
    void SetPosition(int x, int y) { rect.x = x; rect.y = y; }
    void SetSize(int w, int h) { rect.w = w; rect.h = h; }

    bool IsVisible() const { return visible; }
    void SetVisible(bool v) { visible = v; }

    bool IsEnabled() const { return enabled; }
    void SetEnabled(bool e) { enabled = e; }

    const std::string& GetID() const { return id; }

    // Mouse içinde mi kontrol
    bool Contains(int x, int y) const
    {
        return (x >= rect.x && x <= rect.x + rect.w &&
            y >= rect.y && y <= rect.y + rect.h);
    }
};