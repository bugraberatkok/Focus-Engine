#pragma once
#include "UIElement.h"
#include <string>
#include <functional>

class Button : public UIElement
{
private:
    std::string text;
    std::string fontId;

    SDL_Color normalColor;
    SDL_Color hoverColor;
    SDL_Color pressedColor;
    SDL_Color textColor;

    bool isHovered;
    bool isPressed;

    std::function<void()> onClick;  // Callback

public:
    Button(const std::string& id, int x, int y, int w, int h, const std::string& text);

    void Update() override;
    void Render(SDL_Renderer* renderer) override;
    void HandleEvent(SDL_Event& event) override;

    // Callback ayarla
    void SetOnClick(std::function<void()> callback) { onClick = callback; }

    // Renkler
    void SetNormalColor(SDL_Color color) { normalColor = color; }
    void SetHoverColor(SDL_Color color) { hoverColor = color; }
    void SetPressedColor(SDL_Color color) { pressedColor = color; }
    void SetTextColor(SDL_Color color) { textColor = color; }

    // Font
    void SetFont(const std::string& font) { fontId = font; }

    // Text
    void SetText(const std::string& txt) { text = txt; }
    const std::string& GetText() const { return text; }
};