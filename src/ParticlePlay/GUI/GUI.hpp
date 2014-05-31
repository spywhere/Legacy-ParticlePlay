#ifndef GUI_HEADER
#define GUI_HEADER

#include <vector>
#include "../Includes.hpp"
#include "../Input.hpp"
#include "../BitmapFont.hpp"
#include "Control.hpp"

class ppControl;
class ppGUI{
protected:
	ppBitmapFont* defaultFont;
	std::vector<ppControl*> controls;
	static bool ppControlOrdering(ppControl* a, ppControl* b);
public:
	ppGUI();
	void AddControl(ppControl* control);
	ppControl* GetControl(const char *name);
	ppBitmapFont* GetDefaultFont();
	void RemoveControl(const char *name);
	void ClearControl();
	void Render(SDL_Renderer* renderer);
	void Update(ppInput* input);
};

#endif
