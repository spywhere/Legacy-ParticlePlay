#ifndef ANIMATEIMAGE_HEADER
#define ANIMATEIMAGE_HEADER

#include <ParticlePlay/ParticlePlay.hpp>

class AnimateImage {
protected:
	std::list<ppImage*> frames;
	std::list<int> offsetX;
	std::list<int> offsetY;
	int currentFrame;
	int delay;
	int currentTime;
	int width, height;
public:
	AnimateImage(int delay);
	void AddImage(ppImage* image, int offsetX, int offsetY);
	void AddImage(ppImage* image);
	void SetDelay(int delay);
	void SetCurrentFrame(int currentFrame);
	int GetDelay();
	int GetCurrentFrame();
	int GetCurrentWidth();
	int GetCurrentHeight();
	int GetWidth();
	int GetHeight();
	void Render(SDL_Renderer *renderer, int x, int y, SDL_RendererFlip flip);
	void Update(int delta);
};

#endif
