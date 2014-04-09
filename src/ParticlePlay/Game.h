#ifndef GAME_HEADER
#define GAME_HEADER

#include <map>
#include "Includes.h"
#include "IMS/IMS.h"
#include "Color.h"
#include "State.h"

class ppState;
class ppGame{
private:
	std::map<const char*, ppState*> states;
	SDL_Window* mainWindow;
	SDL_Renderer* renderer;
	SDL_GLContext glContext;
	ppColor* backgroundColor;
	ppInput* gameInput;
	ppIMS* ims;
	const char* title;
	ppState* currentState;
	int width, height;
	int targetFPS;
	int targetUPS;
	bool running;
	bool restarting;
	bool resizable;
	bool fullscreen;
	bool showFPS;
	bool vSync;
	int idleTime;
	int fps, ups, art, aut;
	bool init;
	int InitGame();
	void OnEvent(SDL_Event* event);
	void RestartGame();
public:
	ppGame();
	const char* GetTitle();
	void SetTitle(const char* title);
	int GetWidth();
	int GetHeight();
	void SetSize(int width, int height);
	bool IsResizable();
	void SetResizable(bool resizable);
	bool IsFullscreen();
	void SetFullscreen(bool fullscreen);
	int StartGame();
	void QuitGame();
	ppInput* GetGameInput();
	ppIMS* GetInteractiveMusicSystem();
	// GameIO* GetGameIO();
	// SoundPlayer* GetSoundPlayer();
	void AddState(const char* name, ppState* state);
	void EnterState(ppState* state);
	void EnterState(const char* name);
	void EnterState(const char* name, ppState* state);
	ppState* GetState(const char* name);
	bool HasState(const char* name);
	const char* GetCurrentStateName();
	void RemoveState(const char* name);
	ppColor* GetBackgroundColor();
	void SetBackgroundColor(ppColor* color);
	int GetFPS();
	int GetUPS();
	int GetAvgRenderTime();
	int GetAvgUpdateTime();
	int GetTargetFPS();
	void SetTargetFPS(int targetFPS);
	int GetTargetUPS();
	void SetTargetUPS(int targetUPS);
	int GetIdleTime();
	void SetIdleTime(int idleTime);
	bool IsShowFPS();
	void SetShowFPS(bool showFPS);
	bool IsVSync();
	void SetVSync(bool vSync);
	virtual ~ppGame();
};

#endif