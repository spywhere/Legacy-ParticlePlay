#include "Graphics.hpp"

#include <cmath>
const double PI = std::acos(-1);

ppGraphics::ppGraphics(SDL_Renderer* renderer){
	this->renderer = renderer;
	this->translationX = 0;
	this->translationY = 0;
	this->rotation = 0;
	this->drawn = true;
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

void ppGraphics::DrawPolygon(){
	if(this->verts.size() == 0){
		this->drawn = true;
		return;
	}else if(this->verts.size() == 1){
		this->DrawPoint(this->verts[0].x, this->verts[0].y);
		this->drawn = true;
		return;
	}

	int numVerts = this->verts.size();
	int prevVert = numVerts - 1;
	for(int i=0;i<numVerts;i++){
		this->DrawLine(this->verts[prevVert].x, this->verts[prevVert].y, this->verts[i].x, this->verts[i].y);
		prevVert = (prevVert + 1) % numVerts;
	}
	this->drawn = true;
}

void ppGraphics::FillPolygon(){
	if(this->verts.size() == 0){
		this->drawn = true;
		return;
	}else if(this->verts.size() == 1){
		this->DrawPoint(this->verts[0].x, this->verts[0].y);
		this->drawn = true;
		return;
	}

	for(int y=this->minYVert;y<this->maxYVert;y++){
		int n = this->verts.size();
		int prevVert = n - 1;
		std::deque<int> scanXPoints;
		for(int curVert=0;curVert<n;curVert++){
			if((this->verts[curVert].y < y && y <= this->verts[prevVert].y) || (this->verts[prevVert].y < y && y <= this->verts[curVert].y)){
				int diffX = this->verts[prevVert].x - this->verts[curVert].x;
				int diffY = this->verts[prevVert].y - this->verts[curVert].y;
				scanXPoints.push_back(rint(this->verts[curVert].x + (y - verts[curVert].y) * diffX / diffY));
			}
			for(int k=scanXPoints.size() - 1; k > 0 && scanXPoints[k-1] > scanXPoints[k]; k--){
				int tmp = scanXPoints[k-1];
				scanXPoints[k-1] = scanXPoints[k];
				scanXPoints[k] = tmp;
			}
			prevVert = (prevVert + 1) % n;
		}

		int numScanXPoints = scanXPoints.size();
		for(int i=0;i<numScanXPoints;i+=2){
			this->DrawLine(scanXPoints[i], y, scanXPoints[i+1], y);
		}
	}

	this->drawn = true;
}

void ppGraphics::DrawArc(int x, int y, int w, int h, int start, int end){
	this->Arc(x, y, w, h, start, end, false);
}

void ppGraphics::DrawTexture(SDL_Texture* texture, SDL_Rect sourceOffset, SDL_Rect targetOffset, double angle, SDL_Point* center, SDL_RendererFlip flip){
	targetOffset.x += this->translationX;
	targetOffset.y += this->translationY;
	SDL_RenderCopyEx(this->renderer, texture, &sourceOffset, &targetOffset, angle, center, flip);
}

SDL_Texture* ppGraphics::CreateTextureFromSurface(SDL_Surface* surface){
	return SDL_CreateTextureFromSurface(this->renderer, surface);
}

void ppGraphics::DrawLine(int x1, int y1, int x2, int y2){
	SDL_RenderDrawLine(this->renderer, this->translationX+x1, this->translationY+y1, this->translationX+x2, this->translationY+y2);
}

void ppGraphics::DrawOval(int x, int y, int w, int h){
	this->Oval(x, y, w, h, false);
}

void ppGraphics::DrawPoint(int x, int y){
	SDL_RenderDrawPoint(this->renderer, this->translationX+x, this->translationY+y);
}

void ppGraphics::DrawRect(int x, int y, int w, int h){
	SDL_Rect* rect = new SDL_Rect;
	rect->x = this->translationX+x;
	rect->y = this->translationY+y;
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
	rect->x = this->translationX+x;
	rect->y = this->translationY+y;
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

void ppGraphics::PushContext(){
	ppGraphicsContext context;
	uint8 r, g, b, a;
	SDL_GetRenderDrawColor(this->renderer, &r, &g, &b, &a);
	context.color = new ppColor(r, g, b, a);
	SDL_GetRenderDrawBlendMode(this->renderer, &context.blendMode);
	context.translationX = this->translationX;
	context.translationY = this->translationY;
	context.rotation = this->rotation;
	this->contexts.push_back(context);
}

void ppGraphics::PopContext(){
	if(this->contexts.empty()){
		return;
	}
	ppGraphicsContext context = this->contexts.back();
	this->contexts.pop_back();
	this->SetColor(context.color);
	this->SetBlendMode(context.blendMode);
	this->translationX = context.translationX;
	this->translationY = context.translationY;
	this->rotation = context.rotation;
}

void ppGraphics::SetVertex(int x, int y){
	if(this->drawn){
		this->verts.clear();
		this->drawn = false;
	}
	ppPoint point;
	point.x = x;
	point.y = y;
	if(this->verts.empty()){
		this->minYVert = y;
		this->maxYVert = y;
	}else{
		if(y < this->minYVert){
			this->minYVert = y;
		}
		if(y > this->maxYVert){
			this->maxYVert = y;
		}
	}
	this->verts.push_back(point);
}

void ppGraphics::Translate(int x, int y){
	this->translationX = x;
	this->translationY = y;
}

void ppGraphics::SetBlendMode(SDL_BlendMode blendMode){
	SDL_SetRenderDrawBlendMode(this->renderer, blendMode);
}

void ppGraphics::SetColor(ppColor* color){
	SDL_SetRenderDrawColor(this->renderer, color->GetR(), color->GetG(), color->GetB(), color->GetA());
}

SDL_Renderer* ppGraphics::GetRenderer(){
	return this->renderer;
}
