#include "Input.h"

ppInput::ppInput(){
	this->keyCooldown = 0;
	this->mouseCooldown = 0;
	this->keyDown = false;
}

SDL_Keysym* ppInput::IsKeyDown(){
	if(this->keyDown){
		return &this->keyEvent->keysym;
	}
	return NULL;
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

void ppInput::OnEvent(SDL_Event* event){
	if(event->type == SDL_KEYUP){
		this->keyDown = false;
		this->keyEvent = &event->key;
	}else if(event->type == SDL_KEYDOWN){
		this->keyDown = true;
		this->keyEvent = &event->key;
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