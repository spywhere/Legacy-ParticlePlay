#ifndef INPUT_HEADER
#define INPUT_HEADER

#include <ParticlePlay/Includes.hpp>

class ppGame;
class ppInput{
protected:
	const Uint8 *keyState;
	SDL_KeyboardEvent* keyEvent;
	int keyCooldown;
	int mouseCooldown;
	bool keyDown;
	bool mouseDown;
	int mbtn;
	int clicks;
	int mx, my, rmx, rmy, mmx, mmy, dmx, dmy;
	ppGame* game;
public:
	ppInput(ppGame* game);
	ppGame* GetGame();
	int GetMouseX();
	int GetMouseY();
	int GetRelativeMouseX();
	int GetRelativeMouseY();
	int GetDeltaMouseX();
	int GetDeltaMouseY();
	int GetActualMouseX();
	int GetActualMouseY();
	int GetActualRelativeMouseX();
	int GetActualRelativeMouseY();
	int GetActualDeltaMouseX();
	int GetActualDeltaMouseY();
	int GetScrollX();
	int GetScrollY();
	int GetScrollX(bool once);
	int GetScrollY(bool once);
	SDL_Keysym* IsKeyDown();
	int IsMouseDown();
	// SDL_Keysym* IsKeyDown(int cooldown);
	bool IsKeyDown(SDL_Keycode key);
	bool IsKeyDown(SDL_Scancode key);
	bool IsKeyDown(SDL_Scancode key, int cooldown);
	bool IsMouseDown(int button);
	bool IsMouseDown(int button, int cooldown);
	bool IsKeyCoolDown(int cooldown);
	bool IsMouseCoolDown(int cooldown);
	void OnEvent(SDL_Event* event);
	void OnUpdate();
	int GetKeyCooldown();
	int GetMouseCooldown();
};

#endif
