#ifndef TYPES_HEADER
#define TYPES_HEADER

#include <deque>
#include <ParticlePlay/Includes.hpp>
#include <ParticlePlay/Core/Color.hpp>

struct ppPoint {
	int x;
	int y;

	ppPoint(){
		this->x = 0;
		this->y = 0;
	};

	ppPoint(int x, int y){
		this->x = x;
		this->y = y;
	};
};

struct ppSize {
	int width;
	int height;

	ppSize(){
		this->width = 0;
		this->height = 0;
	};

	ppSize(int width, int height){
		this->width = width;
		this->height = height;
	};
};

struct ppGraphicsContext {
	ppColor* color;
	SDL_BlendMode blendMode;
	int translationX;
	int translationY;
	float rotation;
	std::deque<ppPoint> verts;
};

#endif
