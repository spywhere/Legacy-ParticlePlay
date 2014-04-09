#ifndef GAME_HEADER
#define GAME_HEADER

#include <map>
#include "Includes.h"
#include "IMS/IMS.h"
#include "Color.h"
#include "Scene.h"

class ppScene;
class ppGame{
private:
	std::map<const char*, ppScene*> scenes;
	SDL_Window* mainWindow;
	SDL_Renderer* renderer;
	SDL_GLContext glContext;
	ppColor* backgroundColor;
	ppInput* gameInput;
	ppIMS* ims;
	bool debug;
	const char* title;
	ppScene* currentScene;
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
	bool IsDebug();
	void SetDebug(bool debug);
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
	void AddScene(const char* name, ppScene* scene);
	void EnterScene(ppScene* scene);
	void EnterScene(const char* name);
	void EnterScene(const char* name, ppScene* scene);
	ppScene* GetScene(const char* name);
	bool HasScene(const char* name);
	const char* GetCurrentSceneName();
	void RemoveScene(const char* name);
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