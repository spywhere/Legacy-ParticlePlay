#include "Graphics.hpp"

#include <cmath>
const double PI = std::acos(-1);

ppGraphics::ppGraphics(SDL_Renderer* renderer){
	this->renderer = renderer;
}

void ppGraphics::Arc(int x, int y, int w, int h, int start, int end, bool filled){
	start %= 360;
	end %= 360;
	if(start >= end){
		end += 360;
	}
	float cx = x+w/2.0f;
	float cy = y+h/2.0f;
	float doublePi = 2.0f*PI;
	float maxSegment = ((w>h)?w:h) * doublePi;
	float deg2rad = doublePi / 360.0f;
	float halfPi = PI / 2.0f;
	for (float i = start; i < end; i+=1.0f/maxSegment){
		float px = w*cosf(i * deg2rad - halfPi)/2.0f;
		float py = h*sinf(i * deg2rad - halfPi)/2.0f;
		if (filled) {
			this->DrawLine((int)cx, (int)cy, (int)(cx + px), (int)(cy + py));
		} else {
			this->DrawPoint((int)(cx + px), (int)(cy + py));
		}
	}
}

void ppGraphics::DrawArc(int x, int y, int w, int h, int start, int end){
	this->Arc(x, y, w, h, start, end, false);
}

void ppGraphics::DrawImage(int x, int y, ppImage* image){
	image->Render(this->renderer, x, y);
}

void ppGraphics::DrawLine(int x1, int y1, int x2, int y2){
	SDL_RenderDrawLine(this->renderer, x1, y1, x2, y2);
}

void ppGraphics::Oval(int x, int y, int w, int h, bool filled){
	float hw = w / 2.0f;
	float hh = h / 2.0f;
	float cx = x + hw;
	for (float i=0; i<h; i++){
		float angle = acosf((i - hh) / hh);
		float val = sinf(angle) * hw;
		if (filled) {
			this->DrawLine((int)(cx - val), (int)(y + i), (int)(cx + val), (int)(y + i));
		} else {
			this->DrawPoint((int)(cx - val), (int)(y + i));
			this->DrawPoint((int)(cx + val), (int)(y + i));
		}
	}
}

void ppGraphics::DrawOval(int x, int y, int w, int h){
	this->Oval(x, y, w, h, false);
}

void ppGraphics::DrawPoint(int x, int y){
	SDL_RenderDrawPoint(this->renderer, x, y);
}

void ppGraphics::DrawRect(int x, int y, int w, int h){
	SDL_Rect* rect = new SDL_Rect;
	rect->x = x;
	rect->y = y;
	rect->w = w;
	rect->h = h;
	SDL_RenderDrawRect(this->renderer, rect);
}

void ppGraphics::DrawRoundRect(int x, int y, int w, int h, int roundness){
	this->DrawArc(x, y, roundness * 2, roundness * 2, -90, 0);
	this->DrawArc(x, y + h - roundness * 2, roundness * 2, roundness * 2, 180, 270);
	this->DrawArc(x + w - roundness * 2, y, roundness * 2, roundness * 2, 0, 90);
	this->DrawArc(x + w - roundness * 2, y + h - roundness * 2, roundness * 2, roundness * 2, 90, 180);
	this->DrawLine(x + roundness, y, x + w - roundness, y);
	this->DrawLine(x + w, y + roundness, x + w, y + h - roundness);
	this->DrawLine(x + roundness, y + h, x + w - roundness, y + h);
	this->DrawLine(x, y + roundness, x, y + h - roundness);
}

void ppGraphics::FillArc(int x, int y, int w, int h, int start, int end){
	this->Arc(x, y, w, h, start, end, true);
}

void ppGraphics::FillOval(int x, int y, int w, int h){
	this->Oval(x, y, w, h, true);
}

void ppGraphics::FillRect(int x, int y, int w, int h){
	SDL_Rect* rect = new SDL_Rect;
	rect->x = x;
	rect->y = y;
	rect->w = w;
	rect->h = h;
	SDL_RenderFillRect(this->renderer, rect);
}

void ppGraphics::FillRoundRect(int x, int y, int w, int h, int roundness){
	this->FillArc(x, y, roundness * 2, roundness * 2, -90, 0);
	this->FillArc(x, y + h - roundness * 2, roundness * 2, roundness * 2, 180, 270);
	this->FillArc(x + w - roundness * 2, y, roundness * 2, roundness * 2, 0, 90);
	this->FillArc(x + w - roundness * 2, y + h - roundness * 2, roundness * 2, roundness * 2, 90, 180);
	this->FillRect(x + roundness, y, w - roundness * 2, roundness);
	this->FillRect(x + w - roundness, y + roundness, roundness, h - roundness * 2);
	this->FillRect(x + roundness, y + h - roundness, w - roundness * 2, roundness);
	this->FillRect(x, y + roundness, w - roundness, h - roundness * 2);
}

void ppGraphics::SetBlendMode(SDL_BlendMode blendMode){
	SDL_SetRenderDrawBlendMode(this->renderer, blendMode);
}

void ppGraphics::SetColor(ppColor* color){
	SDL_SetRenderDrawColor(this->renderer, color->GetR(), color->GetG(), color->GetB(), color->GetA());
}

SDL_BlendMode ppGraphics::GetBlendMode(){
	SDL_BlendMode blendMode;
	SDL_GetRenderDrawBlendMode(this->renderer, &blendMode);
	return blendMode;
}

SDL_Renderer* ppGraphics::GetRenderer(){
	return this->renderer;
}
