#ifndef CONTROL_HEADER
#define CONTROL_HEADER

#include "../Includes.h"
#include "../Input.h"
#include "GUI.h"
#include "GUIType.h"

class ppGUI;
class ppControl{
private:
	int x, y;
	ppControl* parent;
	ppGUI* gui;
public:
	ppControl();
	ppControl(int x, int y);
	ppGUI* GetGUI();
	void SetGUI(ppGUI* gui);
	ppControl* GetParent();
	void SetParent(ppControl* parent);
	int GetX();
	int GetY();
	void SetX(int x);
	void SetY(int y);
	virtual void Render(SDL_Renderer* renderer);
	virtual void Update(ppInput* input);
	virtual ppGUIType GetType()=0;
};
#endif