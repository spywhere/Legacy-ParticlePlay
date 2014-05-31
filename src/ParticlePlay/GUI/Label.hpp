#ifndef LABEL_HEADER
#define LABEL_HEADER

#include "../Includes.hpp"
#include "../Input.hpp"
#include "Control.hpp"
#include "ControlType.hpp"

class ppLabel : public ppControl{
protected:
	const char* text;
public:
	ppLabel(const char *name, int x, int y);
	ppLabel(const char *name) : ppLabel(name, 0, 0) {}
	const char* GetText();
	void SetText(const char *text);
	void Render(SDL_Renderer* renderer);
	ppControlType GetType();
};

#endif
