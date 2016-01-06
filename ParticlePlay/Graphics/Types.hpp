#ifndef TYPES_HEADER
#define TYPES_HEADER

#include <ParticlePlay/Includes.hpp>
#include <ParticlePlay/Core/Color.hpp>

struct ppPoint {
	int x;
	int y;
};

struct ppSize {
	int width;
	int height;
};

struct ppRect {
	ppPoint origin;
	ppSize size;

	ppRect(int x, int y, int width, int height){
		this->origin.x = x;
		this->origin.y = y;
		this->size.width = width;
		this->size.height = height;
	};

	ppRect(ppPoint origin, int width, int height){
		this->origin = origin;
		this->size.width = width;
		this->size.height = height;
	};

	ppRect(int x, int y, ppSize size){
		this->origin.x = x;
		this->origin.y = y;
		this->size = size;
	};

	ppRect(ppPoint origin, ppSize size){
		this->origin = origin;
		this->size = size;
	};
};

struct ppGraphicsContext {
	ppColor* color;
	SDL_BlendMode blendMode;
	int translationX;
	int translationY;
	float rotation;
};

#endif
