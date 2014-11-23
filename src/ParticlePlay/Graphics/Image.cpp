#include "Image.hpp"

#ifdef PPDEBUG
	#include <iostream>
#endif

static SDL_Point* MakePoint(int x, int y){
	SDL_Point* point = new SDL_Point();
	point->x = x;
	point->y = y;
	return point;
}

SDL_Point* ppImage::NO_CENTER = NULL;
SDL_RendererFlip ppImage::NO_FLIP = SDL_FLIP_NONE;
SDL_RendererFlip ppImage::FLIP_HORIZONTAL = SDL_FLIP_HORIZONTAL;
SDL_RendererFlip ppImage::FLIP_VERTICAL = SDL_FLIP_VERTICAL;
SDL_RendererFlip ppImage::FLIP_ALL = (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);

ppImage::ppImage(SDL_Surface *surface){
	this->surface = surface;
	this->texture = NULL;
	this->renderer = NULL;
}

ppImage::ppImage(const char *name){
	this->surface = IMG_Load(name);
	if(!this->surface){
		#ifdef PPDEBUG
		std::cout << "ppImage Error: " << IMG_GetError() << std::endl;
		#endif
		return;
	}
	this->texture = NULL;
	this->renderer = NULL;
}

void ppImage::Render(SDL_Renderer *renderer, int sx, int sy, int dx, int dy, int sw, int sh, int dw, int dh, double angle, SDL_Point* center, SDL_RendererFlip flip){
	if(sw < 0){
		sw = this->GetWidth();
	}
	if(sh < 0){
		sh = this->GetHeight();
	}
	if(dw < 0){
		dw = this->GetWidth();
	}
	if(dh < 0){
		dh = this->GetHeight();
	}
	if(sx+sw > this->GetWidth()){
		sw = this->GetWidth() - sx;
	}else if(sw > this->GetWidth()){
		sw = this->GetWidth();
	}
	if(sy+sh > this->GetHeight()){
		sh = this->GetHeight() - sy;
	}else if(sh > this->GetHeight()){
		sh = this->GetHeight();
	}
	SDL_Rect targetOffset;
	targetOffset.x = dx;
	targetOffset.y = dy;
	targetOffset.w = dw;
	targetOffset.h = dh;

	SDL_Rect sourceOffset;
	sourceOffset.x = sx;
	sourceOffset.y = sy;
	sourceOffset.w = sw;
	sourceOffset.h = sh;
	if(!this->texture || this->renderer != renderer){
		this->renderer = renderer;
		this->texture = SDL_CreateTextureFromSurface(renderer, this->surface);
	}
	SDL_RenderCopyEx(renderer, this->texture, &sourceOffset, &targetOffset, angle, center, flip);
}

void ppImage::Render(SDL_Renderer *renderer, int sx, int sy, int dx, int dy, int sw, int sh, int dw, int dh, double angle, SDL_RendererFlip flip){
	this->Render(renderer, sx, sy, dx, dy, sw, sh, dw, dh, angle, ppImage::NO_CENTER, flip);
}

void ppImage::Render(SDL_Renderer *renderer, int sx, int sy, int dx, int dy, int sw, int sh, int dw, int dh, double angle, SDL_Point* center){
	this->Render(renderer, sx, sy, dx, dy, sw, sh, dw, dh, angle, center, ppImage::NO_FLIP);
}

void ppImage::Render(SDL_Renderer *renderer, int sx, int sy, int dx, int dy, int sw, int sh, int dw, int dh, SDL_RendererFlip flip){
	this->Render(renderer, sx, sy, dx, dy, sw, sh, dw, dh, 0.0, ppImage::NO_CENTER, flip);
}

void ppImage::Render(SDL_Renderer *renderer, int sx, int sy, int dx, int dy, int sw, int sh, int dw, int dh, double angle){
	this->Render(renderer, sx, sy, dx, dy, sw, sh, dw, dh, angle, ppImage::NO_CENTER, ppImage::NO_FLIP);
}

void ppImage::Render(SDL_Renderer *renderer, int sx, int sy, int dx, int dy, int sw, int sh, int dw, int dh){
	this->Render(renderer, sx, sy, dx, dy, sw, sh, dw, dh, 0.0, ppImage::NO_CENTER, ppImage::NO_FLIP);
}

////
void ppImage::Render(SDL_Renderer *renderer, int sx, int sy, int dx, int dy, int width, int height, double angle, SDL_Point* center, SDL_RendererFlip flip){
	this->Render(renderer, sx, sy, dx, dy, -1, -1, width, height, angle, center, flip);
}

void ppImage::Render(SDL_Renderer *renderer, int sx, int sy, int dx, int dy, int width, int height, double angle, SDL_RendererFlip flip){
	this->Render(renderer, sx, sy, dx, dy, width, height, angle, ppImage::NO_CENTER, flip);
}

void ppImage::Render(SDL_Renderer *renderer, int sx, int sy, int dx, int dy, int width, int height, double angle, SDL_Point* center){
	this->Render(renderer, sx, sy, dx, dy, width, height, angle, center, ppImage::NO_FLIP);
}

void ppImage::Render(SDL_Renderer *renderer, int sx, int sy, int dx, int dy, int width, int height, SDL_RendererFlip flip){
	this->Render(renderer, sx, sy, dx, dy, width, height, 0.0, ppImage::NO_CENTER, flip);
}

void ppImage::Render(SDL_Renderer *renderer, int sx, int sy, int dx, int dy, int width, int height, double angle){
	this->Render(renderer, sx, sy, dx, dy, width, height, angle, ppImage::NO_CENTER, ppImage::NO_FLIP);
}

void ppImage::Render(SDL_Renderer *renderer, int sx, int sy, int dx, int dy, int width, int height){
	this->Render(renderer, sx, sy, dx, dy, width, height, 0.0, ppImage::NO_CENTER, ppImage::NO_FLIP);
}

////
void ppImage::Render(SDL_Renderer *renderer, int x, int y, int width, int height, double angle, SDL_Point* center, SDL_RendererFlip flip){
	this->Render(renderer, 0, 0, x, y, width, height, angle, center, flip);
}

void ppImage::Render(SDL_Renderer *renderer, int x, int y, int width, int height, double angle, SDL_RendererFlip flip){
	this->Render(renderer, x, y, width, height, angle, ppImage::NO_CENTER, flip);
}

void ppImage::Render(SDL_Renderer *renderer, int x, int y, int width, int height, double angle, SDL_Point* center){
	this->Render(renderer, x, y, width, height, angle, center, ppImage::NO_FLIP);
}

void ppImage::Render(SDL_Renderer *renderer, int x, int y, int width, int height, SDL_RendererFlip flip){
	this->Render(renderer, x, y, width, height, 0.0, ppImage::NO_CENTER, flip);
}

void ppImage::Render(SDL_Renderer *renderer, int x, int y, int width, int height, double angle){
	this->Render(renderer, x, y, width, height, angle, ppImage::NO_CENTER, ppImage::NO_FLIP);
}

void ppImage::Render(SDL_Renderer *renderer, int x, int y, int width, int height){
	this->Render(renderer, x, y, width, height, 0.0, ppImage::NO_CENTER, ppImage::NO_FLIP);
}

// FLOAT
void ppImage::Render(SDL_Renderer *renderer, int sx, int sy, int dx, int dy, float sw, float sh, float dw, float dh, double angle, SDL_Point* center, SDL_RendererFlip flip){
	this->Render(renderer, sx, sy, dx, dy, (int)(this->GetWidth()*sw), (int)(this->GetHeight()*sh), (int)(this->GetWidth()*dw), (int)(this->GetHeight()*dh), angle, center, flip);
}

void ppImage::Render(SDL_Renderer *renderer, int sx, int sy, int dx, int dy, float sw, float sh, float dw, float dh, double angle, SDL_RendererFlip flip){
	this->Render(renderer, sx, sy, dx, dy, sw, sh, dw, dh, angle, ppImage::NO_CENTER, flip);
}

void ppImage::Render(SDL_Renderer *renderer, int sx, int sy, int dx, int dy, float sw, float sh, float dw, float dh, double angle, SDL_Point* center){
	this->Render(renderer, sx, sy, dx, dy, sw, sh, dw, dh, angle, center, ppImage::NO_FLIP);
}

void ppImage::Render(SDL_Renderer *renderer, int sx, int sy, int dx, int dy, float sw, float sh, float dw, float dh, SDL_RendererFlip flip){
	this->Render(renderer, sx, sy, dx, dy, sw, sh, dw, dh, 0.0, ppImage::NO_CENTER, flip);
}

void ppImage::Render(SDL_Renderer *renderer, int sx, int sy, int dx, int dy, float sw, float sh, float dw, float dh, double angle){
	this->Render(renderer, sx, sy, dx, dy, sw, sh, dw, dh, angle, ppImage::NO_CENTER, ppImage::NO_FLIP);
}

void ppImage::Render(SDL_Renderer *renderer, int sx, int sy, int dx, int dy, float sw, float sh, float dw, float dh){
	this->Render(renderer, sx, sy, dx, dy, sw, sh, dw, dh, 0.0, ppImage::NO_CENTER, ppImage::NO_FLIP);
}

////
void ppImage::Render(SDL_Renderer *renderer, int sx, int sy, int dx, int dy, float width, float height, double angle, SDL_Point* center, SDL_RendererFlip flip){
	this->Render(renderer, sx, sy, dx, dy, 1.0f, 1.0f, width, height, angle, center, flip);
}

void ppImage::Render(SDL_Renderer *renderer, int sx, int sy, int dx, int dy, float width, float height, double angle, SDL_RendererFlip flip){
	this->Render(renderer, sx, sy, dx, dy, width, height, angle, ppImage::NO_CENTER, flip);
}

void ppImage::Render(SDL_Renderer *renderer, int sx, int sy, int dx, int dy, float width, float height, double angle, SDL_Point* center){
	this->Render(renderer, sx, sy, dx, dy, width, height, angle, center, ppImage::NO_FLIP);
}

void ppImage::Render(SDL_Renderer *renderer, int sx, int sy, int dx, int dy, float width, float height, SDL_RendererFlip flip){
	this->Render(renderer, sx, sy, dx, dy, width, height, 0.0, ppImage::NO_CENTER, flip);
}

void ppImage::Render(SDL_Renderer *renderer, int sx, int sy, int dx, int dy, float width, float height, double angle){
	this->Render(renderer, sx, sy, dx, dy, width, height, angle, ppImage::NO_CENTER, ppImage::NO_FLIP);
}

void ppImage::Render(SDL_Renderer *renderer, int sx, int sy, int dx, int dy, float width, float height){
	this->Render(renderer, sx, sy, dx, dy, width, height, 0.0, ppImage::NO_CENTER, ppImage::NO_FLIP);
}

////
void ppImage::Render(SDL_Renderer *renderer, int x, int y, float width, float height, double angle, SDL_Point* center, SDL_RendererFlip flip){
	this->Render(renderer, 0, 0, x, y, width, height, angle, center, flip);
}

void ppImage::Render(SDL_Renderer *renderer, int x, int y, float width, float height, double angle, SDL_RendererFlip flip){
	this->Render(renderer, x, y, width, height, angle, ppImage::NO_CENTER, flip);
}

void ppImage::Render(SDL_Renderer *renderer, int x, int y, float width, float height, double angle, SDL_Point* center){
	this->Render(renderer, x, y, width, height, angle, center, ppImage::NO_FLIP);
}

void ppImage::Render(SDL_Renderer *renderer, int x, int y, float width, float height, SDL_RendererFlip flip){
	this->Render(renderer, x, y, width, height, 0.0, ppImage::NO_CENTER, flip);
}

void ppImage::Render(SDL_Renderer *renderer, int x, int y, float width, float height, double angle){
	this->Render(renderer, x, y, width, height, angle, ppImage::NO_CENTER, ppImage::NO_FLIP);
}

void ppImage::Render(SDL_Renderer *renderer, int x, int y, float width, float height){
	this->Render(renderer, x, y, width, height, 0.0, ppImage::NO_CENTER, ppImage::NO_FLIP);
}

////
void ppImage::Render(SDL_Renderer *renderer, int x, int y, double angle, SDL_Point* center, SDL_RendererFlip flip){
	this->Render(renderer, x, y, -1, -1, angle, center, flip);
}

void ppImage::Render(SDL_Renderer *renderer, int x, int y, double angle, SDL_RendererFlip flip){
	this->Render(renderer, x, y, angle, ppImage::NO_CENTER, flip);
}

void ppImage::Render(SDL_Renderer *renderer, int x, int y, double angle, SDL_Point* center){
	this->Render(renderer, x, y, angle, center, ppImage::NO_FLIP);
}

void ppImage::Render(SDL_Renderer *renderer, int x, int y, SDL_RendererFlip flip){
	this->Render(renderer, x, y, 0.0, ppImage::NO_CENTER, flip);
}

void ppImage::Render(SDL_Renderer *renderer, int x, int y, double angle){
	this->Render(renderer, x, y, angle, ppImage::NO_CENTER, ppImage::NO_FLIP);
}

void ppImage::Render(SDL_Renderer *renderer, int x, int y){
	this->Render(renderer, x, y, 0.0, ppImage::NO_CENTER, ppImage::NO_FLIP);
}

int ppImage::GetWidth(){
	return this->surface->w;
}

int ppImage::GetHeight(){
	return this->surface->h;
}
