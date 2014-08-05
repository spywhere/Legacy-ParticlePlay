#ifndef LABEL_HEADER
#define LABEL_HEADER

#include <string>
#include "../Control.hpp"

class ppLabel : public ppControl {
protected:
	std::string text;
public:
	ppLabel(const char *name, int x, int y);
	ppLabel(const char *name) : ppLabel(name, 0, 0) {}
	std::string GetText();
	void SetText(std::string text);
	void Render(SDL_Renderer* renderer);
	ppControlType GetType();
};

#endif
