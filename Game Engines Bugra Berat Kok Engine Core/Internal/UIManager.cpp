#include "UIManager.h"
#include <algorithm>
#include <iostream>

UIManager::UIManager()
    : renderer(nullptr)
{
}

UIManager::~UIManager()
{
    RemoveAll();
}

void UIManager::AddElement(UIElement* element)
{
    if (!element)
    {
        std::cerr << "Cannot add null UI element!" << std::endl;
        return;
    }

    // ID kontrolü
    if (elementMap.find(element->GetID()) != elementMap.end())
    {
        std::cerr << "UI element with this ID already exists: " << element->GetID() << std::endl;
        return;
    }

    elements.push_back(element);
    elementMap[element->GetID()] = element;

    std::cout << "UI element added: " << element->GetID() << std::endl;
}

UIElement* UIManager::GetElement(const std::string& id)
{
    auto it = elementMap.find(id);
    if (it != elementMap.end())
        return it->second;

    return nullptr;
}

void UIManager::Update()
{
    for (UIElement* element : elements)
    {
        if (element && element->IsVisible())
        {
            element->Update();
        }
    }
}

void UIManager::Render()
{
    if (!renderer)
        return;

    for (UIElement* element : elements)
    {
        if (element && element->IsVisible())
        {
            element->Render(renderer);
        }
    }
}

void UIManager::HandleEvent(SDL_Event& event)
{
    for (UIElement* element : elements)
    {
        if (element && element->IsVisible() && element->IsEnabled())
        {
            element->HandleEvent(event);
        }
    }
}

void UIManager::RemoveElement(const std::string& id)
{
    auto it = elementMap.find(id);
    if (it != elementMap.end())
    {
        UIElement* element = it->second;

        // Vector'den sil
        elements.erase(std::remove(elements.begin(), elements.end(), element), elements.end());

        // Map'ten sil
        elementMap.erase(it);

        delete element;

        std::cout << "UI element removed: " << id << std::endl;
    }
}

void UIManager::RemoveAll()
{
    for (UIElement* element : elements)
    {
        delete element;
    }

    elements.clear();
    elementMap.clear();

    std::cout << "All UI elements removed." << std::endl;
}