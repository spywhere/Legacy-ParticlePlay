#ifndef STATE_HEADER
#define STATE_HEADER

#include <ParticlePlay/Includes.hpp>
#include <ParticlePlay/Core/Input.hpp>
#include <ParticlePlay/Core/Game.hpp>
#include <ParticlePlay/Graphics/Graphics.hpp>

class ppGame;
class ppState{
private:
	ppGame* game;
	const char* name;
	void* customData;
protected:
	bool needInit;
public:
	ppState();
	bool IsNeedInit();
	void SetNeedInit(bool needInit);
	const char* GetName();
	void SetName(const char* name);
	void SetCustomData(void* customData);
	template<typename ppType> ppType GetCustomData(){
		return static_cast<ppType>(this->customData);
	};
	ppGame* GetGame();
	void SetGame(ppGame* game);
	virtual void OnInit()=0;
	virtual void OnRender(ppGraphics* graphics, int delta)=0;
	virtual void OnUpdate(ppInput* input, int delta)=0;
	virtual void OnExit();
	virtual void OnRestart();
	virtual void OnRestore();
	virtual bool OnEvent(SDL_Event* event);
	virtual ~ppState();
};

#endif
