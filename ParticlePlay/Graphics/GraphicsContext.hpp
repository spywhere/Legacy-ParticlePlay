/*
* Copyright (c) Digital Particle. All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Sirisak Lueangsaksri <spywhere@digitalparticle.com>
*
* File: GraphicsContext.hpp
* Created on: 2016-01-05 10:16:45
* Last modified on: 2016-01-05 10:34:37
* Last modified by: Sirisak Lueangsaksri
*/

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
