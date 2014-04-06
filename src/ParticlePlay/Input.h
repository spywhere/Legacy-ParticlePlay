#ifndef INPUT_HEADER
#define INPUT_HEADER

#include "Includes.h"

class ppInput{
private:
	const Uint8 *keyState;
	SDL_KeyboardEvent* keyEvent;
	int keyCooldown;
	int mouseCooldown;
	bool keyDown;
public:
	ppInput();
	SDL_Keysym* IsKeyDown();
	// SDL_Keysym* IsKeyDown(int cooldown);
	bool IsKeyDown(SDL_Keycode key);
	bool IsKeyDown(SDL_Scancode key);
	bool IsKeyDown(SDL_Scancode key, int cooldown);
	void OnEvent(SDL_Event* event);
	void OnUpdate();
	int GetKeyCooldown();
};

#endif