#ifndef GAME_HEADER
#define GAME_HEADER

#include <map>
#include <ParticlePlay/Includes.hpp>
#include <ParticlePlay/Core/Color.hpp>
#include <ParticlePlay/Core/IO.hpp>
#include <ParticlePlay/Core/Input.hpp>
#include <ParticlePlay/Core/Randomizer.hpp>
#include <ParticlePlay/Core/State.hpp>
#include <ParticlePlay/IMS/IMS.hpp>

class ppInput;
class ppState;
class ppGame{
private:
	std::map<const char*, ppState*> states;
	SDL_Window* mainWindow;
	SDL_Renderer* renderer;
	SDL_GLContext glContext;
	ppColor* backgroundColor;
	ppInput* gameInput;
	ppIO* gameIO;
	ppIMS* ims;
	ppRandomizer* randomizer;
	const char* title;
	ppState* currentState;
	int screenWidth, screenHeight;
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
	int GetScreenWidth();
	int GetScreenHeight();
	void SetScreenSize(int width, int height);
	void SetSize(int width, int height);
	bool IsResizable();
	void SetResizable(bool resizable);
	bool IsFullscreen();
	void SetFullscreen(bool fullscreen);
	int StartGame();
	void QuitGame();
	ppInput* GetGameInput();
	ppIO* GetGameIO();
	ppIMS* GetInteractiveMusicSystem();
	// SoundPlayer* GetSoundPlayer();
	ppRandomizer* GetRandomizer();
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
