#pragma once
#include "Scene.h"
#include "Tilemap.h"
#include <string>

struct TilemapSpec
{
    bool enabled = false;
    std::string tilesetPath;
    std::string groundCsvPath;
    int tileSize = 16;
    int mapW = 0;
    int mapH = 0;
};

class GameSceneBase : public Scene
{
public:
    explicit GameSceneBase(const std::string& name)
        : Scene(name) {
    }

    void SetTilemapSpec(const TilemapSpec& spec) { tilemapSpec = spec; }

protected:
    const TilemapSpec& GetTilemapSpec() const { return tilemapSpec; }

private:
    TilemapSpec tilemapSpec;
    friend class SceneManager;
};