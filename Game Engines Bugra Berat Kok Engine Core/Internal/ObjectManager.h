#pragma once
#include <vector>
#include <SDL.h>
#include "Singleton.h"

class BaseObject;

class ObjectManager : public Singleton<ObjectManager>
{
    friend class Singleton<ObjectManager>;

private:
    static const int MAX_OBJECT_SIZE = 100;

    std::vector<BaseObject*> objects;
    std::vector<BaseObject*> destroyQueue;

    SDL_Renderer* renderer = nullptr;

    void RequestDestroy(BaseObject* obj);
    void FlushDestroyQueue();

    ObjectManager() = default;
    ~ObjectManager();

public:
    void Update();
    void RenderAll();
    void SetRenderer(SDL_Renderer* r);

    const std::vector<BaseObject*>& GetObjects() const { return objects; }

    void AddObject(BaseObject* newObject);
    void RemoveObject(BaseObject* object);

    // ✅ Oyun tarafının kullanacağı tek güvenli API
    void DestroyObject(BaseObject* object);
    void ClearAll();

};
