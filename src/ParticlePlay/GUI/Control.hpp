#ifndef CONTROL_HEADER
#define CONTROL_HEADER

#include <string>
#include "../Includes.hpp"
#include "../Input.hpp"
#include "GUI.hpp"
#include "ControlType.hpp"

class ppGUI;
class ppControl{
protected:
	int x, y, z;
	bool visible;
	ppControl* parent;
	ppGUI* gui;
	std::string name;
public:
	ppControl(const char *name, int x, int y);
	ppControl(const char *name) : ppControl(name, 0, 0) {}
	ppGUI* GetGUI();
	void SetGUI(ppGUI* gui);
	ppControl* GetParent();
	void SetParent(ppControl* parent);
	int GetX();
	int GetY();
	int GetZ();
	void SetX(int x);
	void SetY(int y);
	void SetZ(int z);
	std::string GetName();
	void SetName(const char *name);
	bool IsVisible();
	void SetVisible(bool visible);
	virtual void Render(SDL_Renderer* renderer);
	virtual void Update(ppInput* input);
	virtual ppControlType GetType()=0;
};
#endif
