#ifndef GRAPHICS_HEADER
#define GRAPHICS_HEADER

#include <ParticlePlay/Includes.hpp>
#include <ParticlePlay/Core/Color.hpp>
#include <ParticlePlay/Graphics/Image.hpp>

class ppGraphics{
protected:
	SDL_Renderer* renderer;
	void DrawArc(int x, int y, int w, int h, int start, int end, GLenum mode);
public:
	ppGraphics(SDL_Renderer *renderer);
	void DrawArc(int x, int y, int w, int h, int start, int end);
	void DrawImage(int x, int y, ppImage* image);
	void DrawLine(int x1, int y1, int x2, int y2);
	void DrawOval(int x, int y, int w, int h);
	void DrawPoint(int x, int y);
	//DrawPolygon
	void DrawRect(int x, int y, int w, int h);
	void DrawRoundRect(int x, int y, int w, int h, int roundness);
	void FillArc(int x, int y, int w, int h, int start, int end);
	void FillOval(int x, int y, int w, int h);
	//FillPolygon
	void FillRect(int x, int y, int w, int h);
	void FillRoundRect(int x, int y, int w, int h, int roundness);

	// void Rotate(int degree);
	// void Rotate(float radian);
	void SetForeground(ppColor* color);
	void SetBackground(ppColor* color);
};

#endif
