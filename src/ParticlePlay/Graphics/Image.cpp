#include "Image.hpp"

#ifdef PPDEBUG
	#include <iostream>
#endif

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

void ppImage::Render(SDL_Renderer *renderer, int x, int y, int xOffset, int yOffset, int width, int height){
	if(width + xOffset > this->GetWidth()){
		width = this->GetWidth() - xOffset;
	}else if(width > this->GetWidth()){
		width = this->GetWidth();
	}
	if(height + yOffset > this->GetHeight()){
		height = this->GetHeight() - yOffset;
	}else if(height > this->GetHeight()){
		height = this->GetHeight();
	}
	SDL_Rect targetOffset;
	targetOffset.x = x;
	targetOffset.y = y;
	targetOffset.w = width;
	targetOffset.h = height;

	SDL_Rect sourceOffset;
	sourceOffset.x = xOffset;
	sourceOffset.y = yOffset;
	sourceOffset.w = width;
	sourceOffset.h = height;
	if(!this->texture || this->renderer != renderer){
		this->renderer = renderer;
		this->texture = SDL_CreateTextureFromSurface(renderer, this->surface);
	}
	SDL_RenderCopy(renderer, this->texture, &sourceOffset, &targetOffset);
}

void ppImage::Render(SDL_Renderer *renderer, int x, int y, int width, int height){
	this->Render(renderer, x, y, 0, 0, width, height);
}

void ppImage::Render(SDL_Renderer *renderer, int x, int y){
	this->Render(renderer, x, y, this->GetWidth(), this->GetHeight());
}

int ppImage::GetWidth(){
	return this->surface->w;
}

int ppImage::GetHeight(){
	return this->surface->h;
}
