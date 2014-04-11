#ifndef LABEL_HEADER
#define LABEL_HEADER

#include "../Includes.h"
#include "../Input.h"
#include "Control.h"
#include "ControlType.h"

class ppLabel : public ppControl{
private:
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