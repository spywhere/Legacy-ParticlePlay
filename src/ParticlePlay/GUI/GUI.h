#ifndef GUI_HEADER
#define GUI_HEADER

#include <map>
#include "../Includes.h"
#include "../Input.h"
#include "../BitmapFont.h"
#include "Control.h"

class ppControl;
class ppGUI{
private:
	ppBitmapFont* defaultFont;
	std::map<const char*, ppControl*> controls;
public:
	ppGUI();
	void AddControl(const char *name, ppControl* control);
	ppControl* GetControl(const char *name);
	ppBitmapFont* GetDefaultFont();
	void RemoveControl(const char *name);
	void ClearControl();
	void Render(SDL_Renderer* renderer);
	void Update(ppInput* input);
};

#endif