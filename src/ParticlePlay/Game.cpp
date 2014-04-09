#include "Game.h"

#include <iostream>

ppGame::ppGame(){
	this->mainWindow = NULL;
	this->renderer = NULL;
	this->backgroundColor = new ppColor();
	this->gameInput = new ppInput();
	this->ims = new ppIMS();
	this->debug = false;
	this->title = "My Game";
	this->currentScene = NULL;
	this->width = 640;
	this->height = 480;
	this->targetFPS = 60;
	this->targetUPS = 60;
	this->running = false;
	this->restarting = false;
	this->resizable = false;
	this->fullscreen = false;
	this->showFPS = false;
	this->vSync = false;
	this->idleTime = 0;
	this->fps = 0;
	this->ups = 0;
	this->art = 0;
	this->aut = 0;
}

bool ppGame::IsDebug(){
	return this->debug;
}

void ppGame::SetDebug(bool debug){
	this->debug = debug;
}

const char* ppGame::GetTitle(){
	return this->title;
}

void ppGame::SetTitle(const char* title){
	this->title = title;
	if(this->mainWindow){
		SDL_SetWindowTitle(this->mainWindow, title);
	}
}

int ppGame::GetWidth(){
	return this->width;
}

int ppGame::GetHeight(){
	return this->height;
}

void ppGame::SetSize(int width, int height){
	this->width = width;
	this->height = height;
	this->RestartGame();
}

bool ppGame::IsResizable(){
	return this->resizable;
}

void ppGame::SetResizable(bool resizable){
	this->resizable = resizable;
	this->RestartGame();
}

bool ppGame::IsFullscreen(){
	return this->fullscreen;
}

void ppGame::SetFullscreen(bool fullscreen){
	this->fullscreen = fullscreen;
	this->RestartGame();
}

void ppGame::OnEvent(SDL_Event* event) {
	switch(event->type){
		case SDL_QUIT:
		if(!this->currentScene || !this->currentScene->OnEvent(event)){
			this->running = false;
		}
		break;
		case SDL_KEYDOWN:
		case SDL_KEYUP:
		case SDL_MOUSEMOTION:
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
		case SDL_MOUSEWHEEL:
		case SDL_JOYAXISMOTION:
		case SDL_JOYBALLMOTION:
		case SDL_JOYHATMOTION:
		case SDL_JOYBUTTONDOWN:
		case SDL_JOYBUTTONUP:
		case SDL_JOYDEVICEADDED:
		case SDL_JOYDEVICEREMOVED:
		case SDL_CONTROLLERAXISMOTION:
		case SDL_CONTROLLERBUTTONDOWN:
		case SDL_CONTROLLERBUTTONUP:
		case SDL_CONTROLLERDEVICEADDED:
		case SDL_CONTROLLERDEVICEREMOVED:
		case SDL_CONTROLLERDEVICEREMAPPED:
		case SDL_FINGERDOWN:
		case SDL_FINGERUP:
		case SDL_FINGERMOTION:
		case SDL_DOLLARGESTURE:
		case SDL_DOLLARRECORD:
		case SDL_MULTIGESTURE:
		if(!this->currentScene || !this->currentScene->OnEvent(event)){
			this->gameInput->OnEvent(event);
		}
		break;
		case SDL_APP_TERMINATING:
		if(this->debug){
			std::cout << "Getting force close..." << std::endl;
		}
		if(!this->currentScene || !this->currentScene->OnEvent(event)){
			this->running = false;
		}
		break;
		case SDL_APP_LOWMEMORY:
		if(this->debug){
			std::cout << "Low memory..." << std::endl;
		}
		if(this->currentScene){
			this->currentScene->OnEvent(event);
		}
		break;
		case SDL_WINDOWEVENT:
		if(event->window.event == SDL_WINDOWEVENT_RESIZED){
			this->SetSize(event->window.data1, event->window.data2);
		}
		if(this->currentScene){
			this->currentScene->OnEvent(event);
		}
		break;
		default:
		if(this->currentScene){
			this->currentScene->OnEvent(event);
		}
		break;
	}
}

int ppGame::StartGame(){
	if(this->IsDebug()){
		std::cout << "Initializing SDL..." << std::endl;
	}
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		return 1;
	}
	if(this->IsDebug()){
		std::cout << "Initializing SDL_image..." << std::endl;
	}
	int img_flags = IMG_INIT_JPG|IMG_INIT_PNG|IMG_INIT_TIF;
	if((IMG_Init(img_flags) & img_flags) != img_flags) {
		return 1;
	}
	if(this->IsDebug()){
		std::cout << "Initializing SDL_net..." << std::endl;
	}
	if(SDLNet_Init() < 0) {
		return 1;
	}
	do{
		Uint32 speedTimer = SDL_GetTicks();
		this->restarting = false;
		if(this->IsDebug()){
			std::cout << "Creating window... ";
		}
		Uint32 flags = 0;
		if(this->resizable){
			flags |= SDL_WINDOW_RESIZABLE;
		}
		if(this->fullscreen){
			flags |= SDL_WINDOW_FULLSCREEN;
		}
		if(!(this->mainWindow = SDL_CreateWindow(this->title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->width, this->height, flags))) {
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Unexpected error has occurred", "Cannot initialize window.", 0);
			return 1;
		}
		if(this->IsDebug()){
			std::cout << "in " << (SDL_GetTicks()-speedTimer) << "ms" << std::endl;
			speedTimer = SDL_GetTicks();
			std::cout << "Creating renderer... ";
		}
		if(!(this->renderer = SDL_CreateRenderer(this->mainWindow, -1, 0))) {
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Unexpected error has occurred", "Cannot initialize renderer.", 0);
			return 1;
		}

		if(this->renderer){
			if(this->IsDebug()){
				std::cout << "Initializing OpenGL..." << std::endl;
			}
			glClearColor(0, 0, 0, 0);
			glViewport(0, 0, this->width, this->height);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(0, this->width, this->height, 0, 1, -1);
			glMatrixMode(GL_MODELVIEW);
			glEnable(GL_TEXTURE_2D);
			glLoadIdentity();
			if(glGetError() != GL_NO_ERROR){
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Unexpected error has occurred", "Cannot initialize OpenGL.", 0);
				return 1;
			}
		}

		if(this->IsDebug()){
			std::cout << "Initializing OpenAL..." << std::endl;
		}
		if(this->ims->Init()){
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Unexpected error has occurred", "Cannot initialize OpenAL.", 0);
			return 1;
		}

		if(this->debug && !this->currentScene) {
			if(this->IsDebug()){
				std::cout << "No scene found..." << std::endl;
			}
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Warning!", "Scene not found.", 0);
		}
		if(this->IsDebug()){
			std::cout << "in " << (SDL_GetTicks()-speedTimer) << "ms" << std::endl;
			speedTimer = SDL_GetTicks();
			std::cout << "Preparing... ";
		}
		this->running = true;
		SDL_Event* event = new SDL_Event();

		SDL_SetRenderDrawBlendMode(this->renderer, SDL_BLENDMODE_BLEND);

		Uint32 lastTimer = SDL_GetTicks(), timeNow;
		Uint32 lastTime = lastTimer, avgRenderTime = 0, avgUpdateTime = 0;
		int renderDelta = 0, updateDelta = 0;
		int frames = 0, updates = 0;
		Uint32 msPerRender = 1000.0f / this->targetFPS;
		Uint32 msPerUpdate = 1000.0f / this->targetUPS;
		if(this->IsDebug()){
			std::cout << "in " << (SDL_GetTicks()-speedTimer) << "ms" << std::endl;
			speedTimer = SDL_GetTicks();
			std::cout << "Running... " << std::endl;
		}
		while(this->running) {
			timeNow = SDL_GetTicks();
			renderDelta += (timeNow - lastTime);
			updateDelta += (timeNow - lastTime);
			lastTime = timeNow;

			while(SDL_PollEvent(event)) {
				this->OnEvent(event);
			}

			if(updateDelta > msPerUpdate){
				speedTimer = SDL_GetTicks();
				updateDelta -= msPerUpdate;
				updates++;
				if(this->currentScene && this->currentScene->GetGame()){
					this->currentScene->OnUpdate(this->gameInput, updateDelta);
				}
				this->gameInput->OnUpdate();
				avgUpdateTime += SDL_GetTicks()-speedTimer;
			}

			if(!this->vSync || renderDelta > msPerRender){
				speedTimer = SDL_GetTicks();
				renderDelta -= msPerRender;
				frames++;

				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				glLoadIdentity();

				SDL_SetRenderDrawColor(this->renderer, this->backgroundColor->GetR(), this->backgroundColor->GetG(), this->backgroundColor->GetB(), this->backgroundColor->GetA());
				SDL_RenderClear(this->renderer);
				if(this->currentScene && this->currentScene->GetGame()){
					this->currentScene->OnRender(this->renderer, renderDelta);
				}

				if(this->showFPS){
					// BG
					SDL_Rect* rect = new SDL_Rect;
					rect->x = 0;
					rect->y = 0;
					rect->w = this->width;
					rect->h = 6;
					SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 127);
					SDL_RenderFillRect(this->renderer, rect);
					// FPS
					if(this->fps > 0){
						rect->x = 0;
						rect->y = 1;
						rect->w = this->fps % this->width;
						rect->h = 2;
						Uint8 delta = this->fps / this->width;
						SDL_SetRenderDrawColor(this->renderer, 0, 255-(delta*2), 0, 127);
						SDL_RenderFillRect(this->renderer, rect);
					}
					// UPS
					if(this->ups > 0){
						rect->x = 0;
						rect->y = 3;
						rect->w = this->ups % this->width;
						rect->h = 2;
						Uint8 delta = this->ups / this->width;
						SDL_SetRenderDrawColor(this->renderer, 0, 0, 255-(delta*2), 127);
						SDL_RenderFillRect(this->renderer, rect);
					}
				}
				SDL_RenderPresent(this->renderer);
				avgRenderTime += SDL_GetTicks()-speedTimer;
			}

			if(this->idleTime > 0){
				SDL_Delay(this->idleTime);
			}

			if(SDL_GetTicks() - lastTimer >= 1000){
				this->fps = frames;
				this->ups = updates;
				this->art = avgRenderTime/fps;
				this->aut = avgUpdateTime/ups;
				frames = 0;
				updates = 0;
				lastTimer = SDL_GetTicks();
				if(this->showFPS){
					std::cout << "FPS: " << fps << " [" << art <<"ms]   UPS: " << ups << " [" << aut <<"ms]" << std::endl;
				}
				avgRenderTime = 0;
				avgUpdateTime = 0;
			}
		}
		speedTimer = SDL_GetTicks();
		if(this->IsDebug()){
			std::cout << "Destroying... ";
		}
		SDL_DestroyRenderer(this->renderer);
		SDL_DestroyWindow(this->mainWindow);
		if(this->IsDebug()){
			std::cout << "in " << (SDL_GetTicks()-speedTimer) << "ms" << std::endl;
			speedTimer = SDL_GetTicks();
			if(this->restarting){
				std::cout << "Restarting..." << std::endl;
			}
		}
	} while(this->restarting);
	this->ims->Quit();
	IMG_Quit();
	SDLNet_Quit();
	SDL_Quit();
	if(this->IsDebug()){
		std::cout << "Quitting..." << std::endl;
	}
	return 0;
}

void ppGame::RestartGame(){
	this->running = false;
	this->restarting = true;
}

void ppGame::QuitGame(){
	this->running = false;
}

ppInput* ppGame::GetGameInput(){
	return this->gameInput;
}

ppIMS* ppGame::GetInteractiveMusicSystem(){
	return this->ims;
}

// GameIO* ppGame::getGameIO(){

// }

// SoundPlayer* ppGame::getSoundPlayer(){

// }

void ppGame::AddScene(const char* name, ppScene* scene){
	if(this->IsDebug()){
		std::cout << "Add a new scene \"" << name << "\"..." << std::endl;
	}
	scene->SetName(name);
	this->scenes.insert(std::pair<const char*, ppScene*>(name, scene));
}

void ppGame::EnterScene(ppScene* scene){
	if(!scene->GetGame()){
		scene->SetGame(this);
		scene->OnInit();
	}else if(scene->IsNeedInit()){
		scene->OnInit();
	}
	if(this->IsDebug()){
		std::cout << "Enter a scene \"" << scene->GetName() << "\"..." << std::endl;
	}
	this->currentScene = scene;
}

void ppGame::EnterScene(const char* name){
	ppScene* scene = this->GetScene(name);
	if(scene){
		if(!scene->GetGame()){
			scene->SetGame(this);
			scene->OnInit();
		}else if(scene->IsNeedInit()){
			scene->OnInit();
		}
		if(this->IsDebug()){
			std::cout << "Enter a scene \"" << scene->GetName() << "\"..." << std::endl;
		}
		this->currentScene = scene;
	}
}

void ppGame::EnterScene(const char* name, ppScene* scene){
	this->AddScene(name, scene);
	this->EnterScene(scene);
}

ppScene* ppGame::GetScene(const char* name){
	if(this->scenes.empty()){
		return NULL;
	}
	std::map<const char*, ppScene*>::iterator it;
	it = this->scenes.find(name);
	if(it != this->scenes.end()){
		return it->second;
	}
	return NULL;
}

bool ppGame::HasScene(const char* name){
	return false;
}

const char* ppGame::GetCurrentSceneName(){
	return this->currentScene->GetName();
}

void ppGame::RemoveScene(const char* name){
	if(this->scenes.empty()){
		return;
	}
	std::map<const char*, ppScene*>::iterator it;
	it = this->scenes.find(name);
	if(it != this->scenes.end()){
		this->scenes.erase(it);
	}
}

ppColor* ppGame::GetBackgroundColor(){
	return this->backgroundColor;
}

void ppGame::SetBackgroundColor(ppColor* color){
	this->backgroundColor = color;
}

int ppGame::GetFPS(){
	return this->fps;
}

int ppGame::GetUPS(){
	return this->ups;
}

int ppGame::GetAvgRenderTime(){
	return this->art;
}

int ppGame::GetAvgUpdateTime(){
	return this->aut;
}

int ppGame::GetTargetFPS(){
	return this->targetFPS;
}

void ppGame::SetTargetFPS(int targetFPS){
	this->targetFPS = targetFPS;
}

int ppGame::GetTargetUPS(){
	return this->targetUPS;
}

void ppGame::SetTargetUPS(int targetUPS){
	this->targetUPS = targetUPS;
}

int ppGame::GetIdleTime(){
	return this->idleTime;
}

void ppGame::SetIdleTime(int idleTime){
	this->idleTime = idleTime;
}

bool ppGame::IsShowFPS(){
	return this->showFPS;
}

void ppGame::SetShowFPS(bool showFPS){
	this->showFPS = showFPS;
}

bool ppGame::IsVSync(){
	return this->vSync;
}

void ppGame::SetVSync(bool vSync){
	this->vSync = vSync;
}

ppGame::~ppGame(){
	// Pure virtual
	// Will run on destroy only
	free(this->gameInput);
	free(this->backgroundColor);
}