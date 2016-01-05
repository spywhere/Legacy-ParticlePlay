#ifndef GRAPHICS_HEADER
#define GRAPHICS_HEADER

#include <stack>
#include <ParticlePlay/Includes.hpp>
#include <ParticlePlay/Core/Color.hpp>
#include <ParticlePlay/Graphics/GraphicsContext.hpp>
#include <ParticlePlay/Graphics/Image.hpp>

class ppGraphics{
protected:
	std::stack<ppGraphicsContext> contexts;
	int translation_x;
	int translation_y;
	float rotation;
	SDL_Renderer* renderer;
	void Arc(int x, int y, int w, int h, int start, int end, bool filled);
	void Oval(int x, int y, int w, int h, bool filled);
public:
	ppGraphics(SDL_Renderer* renderer);
	void DrawArc(int x, int y, int w, int h, int start, int end);
	void DrawTexture(SDL_Texture* texture, SDL_Rect sourceOffset, SDL_Rect targetOffset, double angle, SDL_Point* center, SDL_RendererFlip flip);
	SDL_Texture* CreateTextureFromSurface(SDL_Surface* surface);
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

	void PushContext();
	void PopContext();

	void Translate(int x, int y);
	// void Rotate(int degree);
	// void Rotate(float radian);
	void SetBlendMode(SDL_BlendMode blendMode);
	void SetColor(ppColor* color);

	SDL_Renderer* GetRenderer();
};

#endif
