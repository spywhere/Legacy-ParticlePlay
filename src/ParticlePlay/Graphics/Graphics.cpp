#include "Graphics.hpp"

ppGraphics::ppGraphics(SDL_Renderer* renderer){
	this->renderer = renderer;
}

void ppGraphics::DrawArc(int x, int y, int w, int h, int start, int end, GLenum mode){
	start %= 360;
	end %= 360;
	if(start >= end){
		end += 360;
	}
	float cx = x+w/2.0f;
	float cy = y+h/2.0f;
	float doublePi = 6.28318f;
	float maxSegment = ((w>h)?w:h) * doublePi;
	glBegin(mode);
	if(mode == GL_TRIANGLE_FAN){
		glVertex2f(cx, cy);
	}
	for (float i = 1.0f*start; i < end; i+=1.0f/maxSegment){
		float px = w/2.0f*cosf(i / 360.0f * doublePi - doublePi / 4.0f);
		float py = h/2.0f*sinf(i / 360.0f * doublePi - doublePi / 4.0f);
		glVertex2f(cx+px, cy+py);
	}
	glEnd();
}

void ppGraphics::DrawArc(int x, int y, int w, int h, int start, int end){
	this->DrawArc(x, y, w, h, start, end, GL_LINE_STRIP);
}

void ppGraphics::DrawImage(int x, int y, ppImage* image){
	image->Render(this->renderer, x, y);
}

void ppGraphics::DrawLine(int x1, int y1, int x2, int y2){
	glBegin(GL_LINES);
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
	glEnd();
}

void ppGraphics::DrawOval(int x, int y, int w, int h){
	this->DrawArc(x, y, w, h, 0, 360, GL_LINE_LOOP);
}

void ppGraphics::DrawPoint(int x, int y){
	glBegin(GL_POINTS);
		glVertex2f(x, y);
	glEnd();
}

void ppGraphics::DrawRect(int x, int y, int w, int h){
	glBegin(GL_LINE_LOOP);
		glVertex2f(x, y);
		glVertex2f(x+w, y);
		glVertex2f(x+w, y+h);
		glVertex2f(x, y+h);
	glEnd();
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
	this->DrawArc(x, y, w, h, start, end, GL_TRIANGLE_FAN);
}

void ppGraphics::FillOval(int x, int y, int w, int h){
	this->FillArc(x, y, w, h, 0, 360);
}

void ppGraphics::FillRect(int x, int y, int w, int h){
	glBegin(GL_QUADS);
		glVertex2f(x, y);
		glVertex2f(x+w, y);
		glVertex2f(x+w, y+h);
		glVertex2f(x, y+h);
	glEnd();
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
