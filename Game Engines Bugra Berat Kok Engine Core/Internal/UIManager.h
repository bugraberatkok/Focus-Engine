#pragma once
#include "Singleton.h"
#include "UIElement.h"
#include <SDL.h>
#include <map>
#include <vector>
#include <string>

class UIManager : public Singleton<UIManager>
{
    friend class Singleton<UIManager>;

private:
    UIManager();
    ~UIManager();

    SDL_Renderer* renderer;

    // Tüm UI elemanları
    std::vector<UIElement*> elements;

    // ID ile erişim için
    std::map<std::string, UIElement*> elementMap;

public:
    void SetRenderer(SDL_Renderer* r) { renderer = r; }

    // UI elemanı ekle
    void AddElement(UIElement* element);

    // UI elemanı bul
    UIElement* GetElement(const std::string& id);

    // Tüm elemanları güncelle
    void Update();

    // Tüm elemanları çiz
    void Render();

    // Event'leri handle et
    void HandleEvent(SDL_Event& event);

    // Temizlik
    void RemoveElement(const std::string& id);
    void RemoveAll();
};