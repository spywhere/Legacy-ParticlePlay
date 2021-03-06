#ifndef LABEL_HEADER
#define LABEL_HEADER

#include <string>
#include <ParticlePlay/GUI/Control.hpp>

class ppLabel : public ppControl {
protected:
	std::string text;
public:
	ppLabel(const char *name, int x, int y);
	ppLabel(const char *name) : ppLabel(name, 0, 0) {};
	std::string GetText();
	void SetText(std::string text);
	void Render(ppGraphics* graphics);
	ppControlType GetType();
};

#endif
