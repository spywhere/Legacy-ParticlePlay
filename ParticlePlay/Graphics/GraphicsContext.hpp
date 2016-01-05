#ifndef GRAPHICS_CONTEXT_HEADER
#define GRAPHICS_CONTEXT_HEADER

struct ppGraphicsContext {
	ppColor* color;
	SDL_BlendMode blendMode;
	int translationX;
	int translationY;
	float rotation;
};

#endif
