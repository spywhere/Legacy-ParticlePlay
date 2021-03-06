#ifndef GUI_HEADER
#define GUI_HEADER

#include <vector>
#include <ParticlePlay/Includes.hpp>
#include <ParticlePlay/Core/Input.hpp>
#include <ParticlePlay/Graphics/Font.hpp>
#include <ParticlePlay/GUI/Control.hpp>

class ppControl;
class ppGUI{
protected:
	ppFont* defaultFont;
	std::vector<ppControl*> controls;
	static bool ppControlOrdering(ppControl* a, ppControl* b);
public:
	ppGUI();
	void AddControl(ppControl* control);
	ppControl* GetControl(const char *name);
	ppFont* GetDefaultFont();
	void RemoveControl(const char *name);
	void ClearControl();
	void Render(ppGraphics* graphics);
	void Update(ppInput* input);
};

#endif
