#include "BitmapFont.hpp"

#ifdef PPDEBUG
	#include <iostream>
#endif

ppBitmapFont::ppBitmapFont(SDL_Surface* surface){
	this->bitmap = surface;
	this->spacing = 1;
	this->linespacing = 3;
	this->texture = NULL;
	this->renderer = NULL;
	if(!this->bitmap){
		#ifdef PPDEBUG
		std::cout << "BitmapFont Error: " << IMG_GetError() << std::endl;
		#endif
		return;
	}
	Uint32 bgColor = SDL_MapRGBA(bitmap->format, 0, 0, 0, 0);

	int cellW = bitmap->w/16;
	int cellH = bitmap->h/16;
	int top = cellH;
	int baseA = cellH;
	int currentChar = 0;
	for(int y=0;y<16;y++){
		for(int x=0;x<16;x++){
			chars[currentChar].x = x*cellW;
			chars[currentChar].y = y*cellH;
			chars[currentChar].w = cellW;
			chars[currentChar].h = cellH;

			for(int pCol=0;pCol<cellW;pCol++){
				for(int pRow=0;pRow<cellH;pRow++){
					int pX = (cellW*x)+pCol;
					int pY = (cellH*y)+pRow;
					if(this->GetPixel(pX, pY, bitmap)!=bgColor){
						chars[currentChar].x = pX;
						pCol = cellW;
						pRow = cellH;
					}
				}
			}

			for(int pCol_w=cellW-1;pCol_w >= 0;pCol_w--){
				for(int pRow_w=0;pRow_w<cellH;pRow_w++){
					int pX = (cellW*x)+pCol_w;
					int pY = (cellH*y)+pRow_w;
					if(this->GetPixel(pX, pY, bitmap)!=bgColor){
						chars[currentChar].w = (pX-chars[currentChar].x)+1;
						pCol_w = -1;
						pRow_w = cellH;
					}
				}
			}

			for(int pRow=0;pRow<cellH;pRow++){
				for(int pCol=0;pCol<cellW;pCol++){
					int pX = (cellW*x)+pCol;
					int pY = (cellH*y)+pRow;
					if(this->GetPixel(pX, pY, bitmap)!=bgColor){
						if( pRow < top ){
							top = pRow;
						}
						pCol = cellW;
						pRow = cellH;
					}
				}
			}

			if(currentChar=='A'){
				for(int pRow=cellH-1;pRow>=0;pRow--){
					for(int pCol=0;pCol<cellW;pCol++){
						int pX = (cellW*x)+pCol;
						int pY = (cellH*y)+pRow;
						if(this->GetPixel(pX, pY, bitmap)!=bgColor){
							baseA = pRow;
							pCol = cellW;
							pRow = -1;
						}
					}
				}
			}

			currentChar++;
		}
	}

	this->space = cellW / 3;
	this->line = baseA - top;

	for(int t=0;t<256;t++){
		chars[t].y += top;
		chars[t].h -= top;
	}
}

void ppBitmapFont::SetSpacing(int spacing){
	this->spacing = spacing;
}

void ppBitmapFont::SetLineSpacing(int spacing){
	this->linespacing = spacing;
}

Uint32 ppBitmapFont::GetPixel(int x, int y, SDL_Surface* surface){
	Uint32 *pixels = (Uint32 *)surface->pixels;
	return pixels[ ( y * surface->w ) + x ];
}

void ppBitmapFont::RenderSurface(int x, int y, SDL_Texture* texture, SDL_Rect* offset){
	SDL_Rect off;
	off.x = x;
	off.y = y;
	off.w = offset->w;
	off.h = offset->h;
	SDL_RenderCopy(this->renderer, texture, offset, &off);
}

void ppBitmapFont::Render(int x, int y, const char* text, SDL_Renderer *renderer){
	if(!this->bitmap){
		return;
	}
	if(!this->texture||this->renderer!=renderer){
		this->renderer = renderer;
		this->texture = SDL_CreateTextureFromSurface(this->renderer, this->bitmap);
	}
	int X = x, Y = y;
	if(bitmap!=NULL){
		for(int show=0;text[show]!='\0';show++){
			if(text[show]==' '){
				X+=this->space;
			}else if(text[show]=='\n'){
				Y+=this->line+this->linespacing;
				X=x;
			}else{
				int ascii = (unsigned char)text[show];
				this->RenderSurface(X, Y, this->texture, &chars[ascii]);
				X += chars[ ascii ].w + this->spacing;
			}
		}
	}
}
