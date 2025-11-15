#include "ObjectManager.h"
#include "BaseObject.h"

void ObjectManager::Update()
{
	for (size_t i = 0; i < objects.size(); i++)
		{
		if (objects[i] != nullptr)
			{
				objects[i]->Update();

			}
		}
  
}

void ObjectManager::SetRenderer(SDL_Renderer* r) {
    renderer = r;
}


void ObjectManager::RenderAll()
{
    if (!renderer) return; // if renderer is not initilazied exit!

    // clear the screen
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_RenderClear(renderer);

    // draw the objects
    for (auto* obj : objects)
    {
        if (obj)
            obj->Render(renderer);
    }

    SDL_RenderPresent(renderer);
}
