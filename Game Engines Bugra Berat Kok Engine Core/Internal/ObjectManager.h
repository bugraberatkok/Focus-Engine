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
	SDL_Renderer* renderer = nullptr;

	ObjectManager() {
		objects = std::vector<BaseObject*>();
	}
	~ObjectManager() {
		for (size_t i = 0; i < objects.size(); i++)
		{
			delete(objects[i]);
			objects[i] = nullptr;
		}

		objects.clear();
	}
public:
	void Update();
	void RenderAll();
	void SetRenderer(SDL_Renderer* r);
	
	const std::vector<BaseObject*>& GetObjects() const { return objects; }



	void AddObject(BaseObject* newObject) {
		objects.push_back(newObject);
	}
	void RemoveObject(BaseObject* object) {
		int swapIndex = -1;

		for (size_t i = 0; i < objects.size(); i++)
		{
			if (objects[i] == object)
			{
				swapIndex = i;
			}
		}

		if (swapIndex != -1)
		{
			if (swapIndex != objects.size() - 1)
			{
				BaseObject* tmp = objects[swapIndex];

				objects[swapIndex] = objects[objects.size() - 1];

				delete (tmp);
				tmp = nullptr;
			}

			objects.pop_back();
		}
		else
		{
			printf(" Object to remove not found!");
		}

	}

};
