#include "Graphics.hpp"

#include <cmath>
#include <list>

const double PI = std::acos(-1);

ppGraphics::ppGraphics(SDL_Renderer* renderer){
	this->renderer = renderer;
	this->translationX = 0;
	this->translationY = 0;
	this->rotation = 0;
	this->drawn = true;
}

ppPoint ppGraphics::TransformPoint(ppPoint point){
	if(this->rotation != 0){
		int rx = point.x * cosf(this->rotation) - point.y * sinf(this->rotation);
		int ry = point.x * sinf(this->rotation) + point.y * cosf(this->rotation);
		return ppPoint(this->translationX + rx, this->translationY + ry);
	}else{
		return ppPoint(this->translationX + point.x, this->translationY + point.y);
	}
}

void ppGraphics::Arc(int x, int y, int w, int h, int start, int end, uint8 mode){
	start %= 360;
	end %= 360;
	if(start >= end){
		end += 360;
	}
	float hw = w/2.0f;
	float hh = h/2.0f;
	float cx = x+hw;
	float cy = y+hh;

	float halfPi = PI / 2.0f;
	float deg2rad = PI / 180.0f;

	float segmentSize = 1.0f / sqrtf(w * h) * (end-start) * deg2rad;
	this->PushContext();
	this->verts.clear();
	for (float i = start; i < end; i += segmentSize){
		float angle = i * deg2rad - halfPi;
		float px = hw * cosf(angle);
		float py = hh * sinf(angle);
		this->SetVertex((int)(cx + px), (int)(cy + py));
	}
	if(mode == 0){
		this->DrawStrip();
	}else if(mode == 1){
		this->FillPolygon();
	}else{
		this->DrawPolygon();
	}
	this->PopContext();
}

void ppGraphics::Oval(int x, int y, int w, int h, bool filled){
	float hw = w / 2.0f;
	float hh = h / 2.0f;
	float cx = x + hw;
	std::list<ppPoint> verts;
	for (float i=0; i<=h; i++){
		float angle = acosf((i - hh) / hh);
		float val = sinf(angle) * hw;
		verts.push_front(ppPoint((int)(cx - val), (int)(y + i)));
		verts.push_back(ppPoint((int)(cx + val), (int)(y + i)));
	}
	this->PushContext();
	this->verts.clear();
	for(auto v : verts){
		this->SetVertex(v.x, v.y);
	}
	if(filled){
		this->FillPolygon();
	}else{
		this->DrawPolygon();
	}
	this->PopContext();
}

void ppGraphics::DrawPolygon(){
	if(this->verts.size() <= 1){
		this->DrawPoints();
		return;
	}

	int numVerts = this->verts.size();
	int prevVert = numVerts - 1;
	for(int i=0;i<numVerts;i++){
		this->DrawLine(this->verts[prevVert].x, this->verts[prevVert].y, this->verts[i].x, this->verts[i].y, false);
		prevVert = (prevVert + 1) % numVerts;
	}
	this->drawn = true;
}

void ppGraphics::FillPolygon(){
	if(this->verts.size() <= 2){
		this->DrawPolygon();
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
			this->DrawLine(scanXPoints[i], y, scanXPoints[i+1], y, false);
		}
	}

	this->drawn = true;
}

void ppGraphics::DrawArc(int x, int y, int w, int h, int start, int end){
	this->Arc(x, y, w, h, start, end, 0);
}

void ppGraphics::DrawLoopArc(int x, int y, int w, int h, int start, int end){
	this->Arc(x, y, w, h, start, end, 2);
}

void ppGraphics::DrawTexture(SDL_Texture* texture, SDL_Rect sourceOffset, SDL_Rect targetOffset, double angle, SDL_Point* center, SDL_RendererFlip flip){
	ppPoint p = this->TransformPoint(ppPoint(targetOffset.x, targetOffset.y));
	targetOffset.x = p.x;
	targetOffset.y = p.y;
	SDL_RenderCopyEx(this->renderer, texture, &sourceOffset, &targetOffset, (this->rotation * 180 / PI) + angle, center, flip);
}

SDL_Texture* ppGraphics::CreateTextureFromSurface(SDL_Surface* surface){
	return SDL_CreateTextureFromSurface(this->renderer, surface);
}

void ppGraphics::DrawLine(int x1, int y1, int x2, int y2, bool transform){
	if(transform){
		ppPoint p1 = this->TransformPoint(ppPoint(x1, y1));
		ppPoint p2 = this->TransformPoint(ppPoint(x2, y2));
		SDL_RenderDrawLine(this->renderer, p1.x, p1.y, p2.x, p2.y);
	}else{
		SDL_RenderDrawLine(this->renderer, x1, y1, x2, y2);
	}
}

void ppGraphics::DrawLine(int x1, int y1, int x2, int y2){
	this->DrawLine(x1, y1, x2, y2, true);
}

void ppGraphics::DrawOval(int x, int y, int w, int h){
	this->Oval(x, y, w, h, false);
}

void ppGraphics::DrawPoint(int x, int y, bool transform){
	if(transform){
		ppPoint p = this->TransformPoint(ppPoint(x, y));
		SDL_RenderDrawPoint(this->renderer, p.x, p.y);
	}else{
		SDL_RenderDrawPoint(this->renderer, x, y);
	}
}

void ppGraphics::DrawPoint(int x, int y){
	this->DrawPoint(x, y, true);
}

void ppGraphics::DrawRect(int x, int y, int w, int h){
	SDL_Rect* rect = new SDL_Rect;
	ppPoint p = this->TransformPoint(ppPoint(x, y));
	rect->x = p.x;
	rect->y = p.y;
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
	this->Arc(x, y, w, h, start, end, 1);
}

void ppGraphics::FillOval(int x, int y, int w, int h){
	this->Oval(x, y, w, h, true);
}

void ppGraphics::FillRect(int x, int y, int w, int h){
	SDL_Rect* rect = new SDL_Rect;
	ppPoint p = this->TransformPoint(ppPoint(x, y));
	rect->x = p.x;
	rect->y = p.y;
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

void ppGraphics::DrawPoints(){
	if(this->verts.size() == 0){
		this->drawn = true;
		return;
	}
	for(auto v : this->verts){
		this->DrawPoint(v.x, v.y, false);
	}
	this->drawn = true;
}

void ppGraphics::DrawLines(){
	if(this->verts.size() <= 1){
		this->DrawPoints();
		return;
	}
	bool gotPos = false;
	ppPoint lastPos;
	for(auto v : this->verts){
		if(gotPos){
			this->DrawLine(lastPos.x, lastPos.y, v.x, v.y, false);
		}else{
			lastPos = v;
		}
		gotPos = !gotPos;
	}
	if(gotPos){
		this->DrawPoint(lastPos.x, lastPos.y, false);
	}
	this->drawn = true;
}

void ppGraphics::DrawStrip(){
	if(this->verts.size() <= 1){
		this->DrawPoints();
		return;
	}
	bool gotPos = false;
	ppPoint lastPos;
	for(auto v : this->verts){
		if(gotPos){
			this->DrawLine(lastPos.x, lastPos.y, v.x, v.y, false);
		}
		lastPos = v;
		gotPos = true;
	}
	this->drawn = true;
}

void ppGraphics::IdentityContext(){
	this->SetColor(new ppColor(1.0f, 1.0f, 1.0f));
	this->translationX = 0;
	this->translationY = 0;
	this->rotation = 0;
	this->drawn = true;
	this->verts.clear();
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
	context.verts = this->verts;
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
	this->verts = context.verts;
}

void ppGraphics::SetVertex(int x, int y){
	if(this->drawn){
		this->verts.clear();
		this->drawn = false;
	}
	ppPoint point = this->TransformPoint(ppPoint(x, y));
	if(this->verts.empty()){
		this->minYVert = point.y;
		this->maxYVert = point.y;
	}else{
		if(point.y < this->minYVert){
			this->minYVert = point.y;
		}
		if(point.y > this->maxYVert){
			this->maxYVert = point.y;
		}
	}
	this->verts.push_back(point);
}

void ppGraphics::SetTranslate(int x, int y){
	this->translationX = x;
	this->translationY = y;
}

void ppGraphics::Translate(int x, int y){
	this->translationX += x;
	this->translationY += y;
}

void ppGraphics::SetRotate(float radian){
	this->rotation = radian;
}

void ppGraphics::Rotate(float radian){
	this->rotation += radian;
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
