#include "ObjectManager.h"
#include "BaseObject.h"
#include <algorithm>

ObjectManager::~ObjectManager()
{
    // Engine kapanırken de leak olmasın:
    // Kalan tüm objeleri güvenli şekilde sil.
    for (BaseObject* obj : objects)
        delete obj;

    objects.clear();
    destroyQueue.clear();
}

void ObjectManager::SetRenderer(SDL_Renderer* r)
{
    renderer = r;
}

void ObjectManager::AddObject(BaseObject* newObject)
{
    if (!newObject) return;

    // Basit dupe koruması (isteğe bağlı)
    if (std::find(objects.begin(), objects.end(), newObject) != objects.end())
        return;

    objects.push_back(newObject);
}

void ObjectManager::RemoveObject(BaseObject* object)
{
    if (!object) return;

    auto it = std::find(objects.begin(), objects.end(), object);
    if (it != objects.end())
        objects.erase(it);
}

void ObjectManager::DestroyObject(BaseObject* object)
{
    // Oyun bunu çağıracak. Delete yok.
    RequestDestroy(object);
}

void ObjectManager::RequestDestroy(BaseObject* obj)
{
    if (!obj) return;

    // Zaten destroyQueue'da mı?
    if (std::find(destroyQueue.begin(), destroyQueue.end(), obj) != destroyQueue.end())
        return;

    destroyQueue.push_back(obj);
}

void ObjectManager::FlushDestroyQueue()
{
    if (destroyQueue.empty()) return;

    // 1) objects listesinden çıkar
    for (BaseObject* obj : destroyQueue)
        RemoveObject(obj);

    // 2) delete et
    for (BaseObject* obj : destroyQueue)
        delete obj;

    destroyQueue.clear();
}

void ObjectManager::Update()
{
    // ✅ Kopya almaya gerek yok; silmeler queue’da
    for (BaseObject* obj : objects)
    {
        if (obj)
            obj->Update();
    }

    // ✅ frame sonunda güvenli destroy
    FlushDestroyQueue();
}

// ObjectManager.cpp
void ObjectManager::ClearAll() // <--- DOĞRU! ObjectManager'a ait olduğunu belirttik.
{
    for (BaseObject* obj : objects)
    {
        if (obj) delete obj;
    }
    objects.clear();
    destroyQueue.clear();
}

void ObjectManager::RenderAll()
{
    if (!renderer) return;

    for (BaseObject* obj : objects)
    {
        if (obj)
            obj->Render(renderer);
    }
}


