#include "Button.h"
#include "TextManager.h"
#include <iostream>

Button::Button(const std::string& id, int x, int y, int w, int h, const std::string& text)
    : UIElement(id, x, y, w, h),
    text(text),
    fontId("main_font"),
    isHovered(false),
    isPressed(false)
{
    // Varsayılan renkler
    normalColor = { 70, 70, 70, 255 };      // Gri
    hoverColor = { 100, 100, 100, 255 };    // Açık gri
    pressedColor = { 50, 50, 50, 255 };     // Koyu gri
    textColor = { 255, 255, 255, 255 };     // Beyaz
}

void Button::Update()
{
    // Şimdilik boş, gerekirse animasyon eklenebilir
}

void Button::Render(SDL_Renderer* renderer)
{
    if (!visible)
        return;

    // Buton rengini seç
    SDL_Color currentColor = normalColor;
    if (!enabled)
    {
        currentColor = { 50, 50, 50, 128 };  // Disabled = koyu ve transparan
    }
    else if (isPressed)
    {
        currentColor = pressedColor;
    }
    else if (isHovered)
    {
        currentColor = hoverColor;
    }

    // Buton arkaplanını çiz
    SDL_SetRenderDrawColor(renderer, currentColor.r, currentColor.g, currentColor.b, currentColor.a);
    SDL_RenderFillRect(renderer, &rect);

    // Kenarlık çiz
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_RenderDrawRect(renderer, &rect);

    // Text'i ortala ve çiz
    int textWidth, textHeight;
    TextManager::GetInstance().GetTextSize(text, fontId, textWidth, textHeight);

    int textX = rect.x + (rect.w - textWidth) / 2;
    int textY = rect.y + (rect.h - textHeight) / 2;

    TextManager::GetInstance().RenderText(text, fontId, textX, textY, textColor);
}

void Button::HandleEvent(SDL_Event& event)
{
    if (!visible || !enabled)
        return;

    if (event.type == SDL_MOUSEMOTION)
    {
        int mouseX = event.motion.x;
        int mouseY = event.motion.y;

        isHovered = Contains(mouseX, mouseY);
    }
    else if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        if (event.button.button == SDL_BUTTON_LEFT)
        {
            int mouseX = event.button.x;
            int mouseY = event.button.y;

            if (Contains(mouseX, mouseY))
            {
                isPressed = true;
            }
        }
    }
    else if (event.type == SDL_MOUSEBUTTONUP)
    {
        if (event.button.button == SDL_BUTTON_LEFT)
        {
            int mouseX = event.button.x;
            int mouseY = event.button.y;

            if (isPressed && Contains(mouseX, mouseY))
            {
                // Tıklama gerçekleşti!
                if (onClick)
                {
                    std::cout << "Button clicked: " << id << std::endl;
                    onClick();
                }
            }

            isPressed = false;
        }
    }
}