#ifndef BUTTON_HEADER
#define BUTTON_HEADER

#include <string>
#include <ParticlePlay/GUI/Control.hpp>

class ppButton;
class ppButtonListener {
public:
	virtual void OnClick(ppButton* button){};
	virtual void OnMouseOver(ppButton* button){};
};

class ppButton : public ppControl {
protected:
	int backgroundColor;
	int highlightColor;
	int foregroundColor;
	bool highlight;
	ppButtonListener* listener;
	std::string text;
public:
	ppButton(const char *name, int x, int y, int w, int h);
	ppButton(const char *name, int x, int y) : ppButton(name, x, y, 0, 0) {};
	ppButton(const char *name) : ppButton(name, 0, 0) {};
	std::string GetText();
	bool IsHighlight();
	void SetListener(ppButtonListener* listener);
	void SetText(std::string text);
	void SetBackgroundColor(int color);
	void SetHighlightColor(int color);
	void SetForegroundColor(int color);
	void Render(ppGraphics* graphics);
	void Update(ppInput* input);
	ppControlType GetType();
};

#endif
