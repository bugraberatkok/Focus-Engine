#pragma once
#include "Scene.h"
#include <string>

class UISceneBase : public Scene
{
public:
    explicit UISceneBase(const std::string& name)
        : Scene(name) {
    }
};
