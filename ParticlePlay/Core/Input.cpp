#include "Input.hpp"
#include <ParticlePlay/Core/Game.hpp>

ppInput::ppInput(ppGame* game){
	this->game = game;
	this->keyCooldown = 0;
	this->keyDown = false;
	this->mouseCooldown = 0;
	this->mouseDown = false;
	this->clicks = 0;
	this->mbtn = 0;
	this->mx = -1;
	this->my = -1;
	this->rmx = -1;
	this->rmy = -1;
	this->mmx = 0;
	this->mmy = 0;
	this->dmx = 0;
	this->dmy = 0;
}

ppGame* ppInput::GetGame(){
	return this->game;
}

int ppInput::GetMouseX(){
	return this->GetActualMouseX();
}

int ppInput::GetMouseY(){
	return this->GetActualMouseY();
}

int ppInput::GetRelativeMouseX(){
	return this->GetActualRelativeMouseX();
}

int ppInput::GetRelativeMouseY(){
	return this->GetActualRelativeMouseY();
}

int ppInput::GetDeltaMouseX(){
	return this->GetActualDeltaMouseX();
}

int ppInput::GetDeltaMouseY(){
	return this->GetActualDeltaMouseY();
}

int ppInput::GetActualMouseX(){
	return this->mx;
}

int ppInput::GetActualMouseY(){
	return this->my;
}

int ppInput::GetActualRelativeMouseX(){
	return this->rmx;
}

int ppInput::GetActualRelativeMouseY(){
	return this->rmy;
}

int ppInput::GetActualDeltaMouseX(){
	int dmx = this->dmx;
	this->dmx = 0;
	return dmx;
}

int ppInput::GetActualDeltaMouseY(){
	int dmy = this->dmy;
	this->dmy = 0;
	return dmy;
}

int ppInput::GetScrollX(){
	return this->GetScrollX(true);
}

int ppInput::GetScrollY(){
	return this->GetScrollY(true);
}

int ppInput::GetScrollX(bool once){
	if(once){
		int mm = this->mmx;
		this->mmx = 0;
		return mm;
	}else{
		return this->mmx;
	}
}

int ppInput::GetScrollY(bool once){
	if(once){
		int mm = this->mmy;
		this->mmy = 0;
		return mm;
	}else{
		return this->mmy;
	}
}

SDL_Keysym* ppInput::IsKeyDown(){
	if(this->keyDown){
		return &this->keyEvent->keysym;
	}
	return NULL;
}

int ppInput::IsMouseDown(){
	if(this->mouseDown){
		return this->mbtn;
	}
	return 0;
}

// SDL_Keysym* ppInput::isKeyDown(int cooldown){
// 	if(this->keyCooldown <= 0 && this->keyDown){
// 		this->keyCooldown = cooldown;
// 		return &this->keyEvent->keysym;
// 	}
// 	return NULL;
// }

bool ppInput::IsKeyDown(SDL_Keycode key){
	SDL_Keysym* keysym;
	if((keysym = this->IsKeyDown())){
		if(keysym->sym == key){
			return true;
		}
	}
	return false;
}

// bool ppInput::isKeyDown(SDL_Keycode key, int cooldown){
// 	if(this->keyCooldown > 0){
// 		return false;
// 	}
// 	bool down = false;
// 	SDL_Keysym* keysym;
// 	if((keysym = this->isKeyDown())){
// 		if(keysym->sym == key){
// 			down = true;
// 		}
// 	}
// 	if(down){
// 		this->keyCooldown = cooldown;
// 	}
// 	return down;
// }

bool ppInput::IsKeyDown(SDL_Scancode key){
	this->keyState = SDL_GetKeyboardState(NULL);
	return this->keyState[key];
}

bool ppInput::IsKeyDown(SDL_Scancode key, int cooldown){
	if(this->keyCooldown > 0){
		return false;
	}
	this->keyState = SDL_GetKeyboardState(NULL);
	if(this->keyState[key]){
		this->keyCooldown = cooldown;
	}
	return this->keyState[key];
}

bool ppInput::IsMouseDown(int button){
	int btn = this->IsMouseDown();
	return btn>0&&btn==button;
}

bool ppInput::IsMouseDown(int button, int cooldown){
	if(this->mouseCooldown > 0){
		return false;
	}
	int btn = this->IsMouseDown();
	if(btn>0&&btn==button){
		this->mouseCooldown = cooldown;
	}
	return btn>0&&btn==button;
}

bool ppInput::IsKeyCoolDown(int cooldown){
	if(this->keyCooldown > 0){
		return false;
	}
	this->keyCooldown = cooldown;
	return true;
}

bool ppInput::IsMouseCoolDown(int cooldown){
	if(this->mouseCooldown > 0){
		return false;
	}
	this->mouseCooldown = cooldown;
	return true;
}

void ppInput::OnEvent(SDL_Event* event){
	if(event->type == SDL_KEYUP){
		this->keyDown = false;
		this->keyEvent = &event->key;
	}else if(event->type == SDL_KEYDOWN){
		this->keyDown = true;
		this->keyEvent = &event->key;
	}else if(event->type == SDL_MOUSEMOTION){
		this->dmx = event->motion.x-this->mx;
		this->dmy = event->motion.y-this->my;
		this->mx = event->motion.x;
		this->my = event->motion.y;
		this->rmx = event->motion.xrel;
		this->rmy = event->motion.xrel;
	}else if(event->type == SDL_MOUSEBUTTONUP || event->type == SDL_MOUSEBUTTONDOWN){
		this->mx = event->button.x;
		this->my = event->button.y;
		this->clicks = event->button.clicks;
		this->mbtn = event->button.button;
		this->mouseDown = event->type == SDL_MOUSEBUTTONDOWN;
	}else if(event->type == SDL_MOUSEWHEEL){
		this->mmx = event->wheel.x;
		this->mmy = event->wheel.y;
	}
}

void ppInput::OnUpdate(){
	if(this->keyCooldown > 0){
		this->keyCooldown--;
	}
	if(this->mouseCooldown > 0){
		this->mouseCooldown--;
	}
}

int ppInput::GetKeyCooldown(){
	return this->keyCooldown;
}

int ppInput::GetMouseCooldown(){
	return this->mouseCooldown;
}
