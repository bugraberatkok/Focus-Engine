#include "InputManager.h"

/*****************************************************************************/

void InputManager::Update(void)
{
  mCurrentKeyStates = SDL_GetKeyboardState(NULL);
}
/*****************************************************************************/

bool InputManager::GetKey(int scanCode)
{
  return mCurrentKeyStates[scanCode] != 0;
}

/*****************************************************************************/

//SDL_SCANCODE_UP
//SDL_SCANCODE_DOWN
//SDL_SCANCODE_LEFT
//SDL_SCANCODE_RIGHT