#ifndef SWITCH_HEADER
#define SWITCH_HEADER

#include "Interfaces.hpp"
#include "Transition.hpp"
#include "IMS.hpp"
#include <vector>

class ppTransition;
class ppSwitch : public ppUpdatable, public ppControl {
protected:
	ppIMS* ims;
	const char *stateName;
	std::vector<ppTransition*> transitions;
	ppTransition* currentTransition;
	ppTransition* defaultTransition;
	ppGenericSound* lastPlay;
	Uint32 triggerTime;
	bool readyForTransition;
	static bool ppTransitionOrdering(ppTransition* a, ppTransition* b);
	ppTransition* FindTransition(const char *sourceName, const char *destName);
public:
	ppSwitch(const char *name, ppIMS* ims);
	~ppSwitch();
	const char *GetCurrentState();
	ppTransition* GetDefaultTransition();
	ppTransition* CreateTransition(int priority, ppGenericSound* sourceSound, ppGenericSound* destSound);
	void SwitchState(const char *stateName);
	void Render(SDL_Renderer* renderer);
	void Update();
	void Update(ppInput* input);
	ppControlType GetType();
};

#endif
