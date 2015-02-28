#ifndef CONTROL_HEADER
#define CONTROL_HEADER

#include <string>
#include <ParticlePlay/Includes.hpp>
#include <ParticlePlay/Core/Input.hpp>
#include <ParticlePlay/GUI/GUI.hpp>
#include <ParticlePlay/GUI/ControlType.hpp>

class ppGUI;
class ppControl{
protected:
	int x, y, z, width, height;
	bool visible;
	ppControl* parent;
	ppGUI* gui;
	std::string name;
public:
	ppControl(const char *name, int x, int y, int w, int h);
	ppControl(const char *name, int x, int y) : ppControl(name, x, y, 0 ,0) {};
	ppControl(const char *name) : ppControl(name, 0, 0) {}
	virtual ~ppControl();
	ppGUI* GetGUI();
	void SetGUI(ppGUI* gui);
	ppControl* GetParent();
	void SetParent(ppControl* parent);
	int GetX();
	int GetY();
	int GetZ();
	int GetWidth();
	int GetHeight();
	virtual void SetX(int x);
	virtual void SetY(int y);
	void SetZ(int z);
	virtual void SetWidth(int width);
	virtual void SetHeight(int height);
	virtual void SetLocation(int x, int y);
	virtual void SetSize(int width, int height);
	std::string GetName();
	void SetName(const char *name);
	virtual bool IsVisible();
	virtual void SetVisible(bool visible);
	virtual void Render(SDL_Renderer* renderer);
	virtual void Update(ppInput* input);
	virtual ppControlType GetType()=0;
};
#endif
