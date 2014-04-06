#ifndef LABEL_HEADER
#define LABEL_HEADER

#include "../Includes.h"
#include "../Input.h"
#include "Control.h"
#include "GUIType.h"

class ppLabel : public ppControl{
private:
	const char* text;
public:
	ppLabel();
	ppLabel(int x, int y);
	const char* GetText();
	void SetText(const char *text);
	void Render(SDL_Renderer* renderer);
	ppGUIType GetType();
};

#endif