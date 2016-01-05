#ifndef GRAPHICS_CONTEXT_HEADER
#define GRAPHICS_CONTEXT_HEADER

struct ppGraphicsContext {
	ppColor* color;
	SDL_BlendMode blendMode;
	int translation_x;
	int translation_y;
	float rotation;
};

#endif
