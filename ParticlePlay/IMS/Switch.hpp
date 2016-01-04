#ifndef SWITCH_HEADER
#define SWITCH_HEADER

#include <string>
#include <vector>
#include <map>
#include <ParticlePlay/IMS/Interfaces.hpp>
#include <ParticlePlay/IMS/Transition.hpp>
#include <ParticlePlay/IMS/Stinger.hpp>
#include <ParticlePlay/IMS/TimeListener.hpp>
#include <ParticlePlay/IMS/IMS.hpp>

class ppTransition;
class ppSwitch : public ppUpdatable, public ppControl, public ppTimeListenerCallback {
protected:
	bool isPlaying;
	bool isPause;
	ppIMS* ims;
	std::string stateName;
	std::vector<ppTransition*> transitions;
	std::map<std::string, ppStinger*> stingers;
	ppTransition* currentTransition;
	ppTransition* defaultTransition;
	ppGenericSound* lastPlay;
	ppTimeListener* timeListener;
	bool readyForTransition;
	static bool ppTransitionOrdering(ppTransition* a, ppTransition* b);
	ppTransition* FindTransition(const char *sourceName, const char *destName);
public:
	ppSwitch(const char *name, ppIMS* ims);
	~ppSwitch();
	std::string GetCurrentState();
	ppTransition* GetDefaultTransition();
	ppTransition* CreateTransition(int priority, ppGenericSound* sourceSound, ppGenericSound* destSound);
	ppStinger* CreateStinger(const char *stingerName, ppGenericSound* sound, ppStingerTriggerPosition position);
	ppStinger* GetStinger(const char *stingerName);
	void SwitchState(const char *stateName);
	void TriggerStinger(const char *stingerName);
	void Play();
	void Pause();
	void Stop();
	bool IsPlaying();
	bool IsPause();
	bool IsStop();
	bool IsStingerTrigger(const char *stingerName);
	bool IsTransitioning();
	void Render(ppGraphics* graphics);
	void Update();
	void Update(ppInput* input);
	void OnBar(ppGenericSound* source);
	void OnBeat(ppGenericSound* source);
	void OnEntryCue(ppGenericSound* source);
	void OnExitCue(ppGenericSound* source);
	ppControlType GetType();
};

#endif
