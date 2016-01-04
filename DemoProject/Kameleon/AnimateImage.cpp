#include "AnimateImage.hpp"

AnimateImage::AnimateImage(int delay){
	this->delay = delay;
	this->currentFrame = 0;
	this->currentTime = 0;
	this->width = 0;
	this->height = 0;
}

void AnimateImage::AddImage(ppImage* image, int offsetX, int offsetY){
	this->frames.push_back(image);
	this->offsetX.push_back(offsetX);
	this->offsetY.push_back(offsetY);
}

void AnimateImage::AddImage(ppImage* image){
	this->AddImage(image, 0, 0);
}

void AnimateImage::SetDelay(int delay){
	this->delay = delay;
}

void AnimateImage::SetCurrentFrame(int currentFrame){
	if(this->frames.size() <= 0){
		this->currentFrame = 0;
	}else{
		this->currentFrame = currentFrame % this->frames.size();
	}
}

int AnimateImage::GetDelay(){
	return this->delay;
}

int AnimateImage::GetCurrentFrame(){
	if(this->frames.size() <= 0){
		return -1;
	}
	return this->currentFrame;
}

int AnimateImage::GetCurrentWidth(){
	if(this->frames.size() <= 0){
		return 0;
	}
	return (*std::next(this->frames.begin(), 0))->GetWidth();
}

int AnimateImage::GetCurrentHeight(){
	if(this->frames.size() <= 0){
		return 0;
	}
	return (*std::next(this->frames.begin(), 0))->GetHeight();
}

int AnimateImage::GetWidth(){
	return this->width;
}

int AnimateImage::GetHeight(){
	return this->height;
}

void AnimateImage::Render(ppGraphics* graphics, int x, int y, SDL_RendererFlip flip){
	if(this->frames.size() <= 0){
		return;
	}
	ppImage* image = (*std::next(this->frames.begin(), this->currentFrame));
	int offsetX = (*std::next(this->offsetX.begin(), this->currentFrame));
	int offsetY = (*std::next(this->offsetY.begin(), this->currentFrame));
	image->Render(graphics->GetRenderer(), x-image->GetWidth()/2+offsetX, y-image->GetWidth()/2+offsetY, flip);
}

void AnimateImage::Update(int delta){
	if(this->frames.size() <= 0){
		return;
	}
	if(this->delay >= 0){
		this->currentTime += delta;
		if(this->currentTime >= this->delay){
			this->currentTime %= this->delay;
			this->currentFrame++;
		}
	}
	this->currentFrame %= this->frames.size();
}
