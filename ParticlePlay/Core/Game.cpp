#include "Game.hpp"

#ifdef PPDEBUG
	#include <iostream>
#endif

ppGame::ppGame(){
	this->mainWindow = NULL;
	this->renderer = NULL;
	this->graphics = NULL;
	this->backgroundColor = new ppColor();
	this->gameInput = new ppInput(this);
	this->gameIO = new ppIO();
	this->randomizer = new ppRandomizer();
	this->ims = NULL;
	this->title = "My Game";
	this->currentState = NULL;
	this->screenWidth = 640;
	this->width = 640;
	this->screenHeight = 480;
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

const char* ppGame::GetTitle(){
	return this->title;
}

void ppGame::SetTitle(const char* title){
	this->title = title;
	if(this->mainWindow){
		SDL_SetWindowTitle(this->mainWindow, title);
	}
}

int ppGame::GetScreenWidth(){
	return this->screenWidth;
}

int ppGame::GetScreenHeight(){
	return this->screenHeight;
}

int ppGame::GetWidth(){
	return this->width;
}

int ppGame::GetHeight(){
	return this->height;
}

ppRandomizer* ppGame::GetRandomizer(){
	return this->randomizer;
}

void ppGame::SetScreenSize(int width, int height){
	this->screenWidth = width;
	this->screenHeight = height;
	this->SetSize(width, height);
	this->RestartGame();
}

void ppGame::SetSize(int width, int height){
	this->width = width;
	this->height = height;
	if(this->renderer){
		SDL_RenderSetLogicalSize(this->renderer, this->width, this->height);
	}
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
		if(!this->currentState || !this->currentState->OnEvent(event)){
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
		if(!this->currentState || !this->currentState->OnEvent(event)){
			this->gameInput->OnEvent(event);
		}
		break;
		case SDL_APP_TERMINATING:
		#ifdef PPDEBUG
			std::cout << "Getting force close..." << std::endl;
		#endif
		if(!this->currentState || !this->currentState->OnEvent(event)){
			this->running = false;
		}
		break;
		case SDL_APP_LOWMEMORY:
		#ifdef PPDEBUG
			std::cout << "Low memory..." << std::endl;
		#endif
		if(this->currentState){
			this->currentState->OnEvent(event);
		}
		break;
		case SDL_WINDOWEVENT:
		if(event->window.event == SDL_WINDOWEVENT_RESIZED){
			this->SetScreenSize(event->window.data1, event->window.data2);
		}
		if(this->currentState){
			this->currentState->OnEvent(event);
		}
		break;
		default:
		if(this->currentState){
			this->currentState->OnEvent(event);
		}
		break;
	}
}

int ppGame::StartGame(){
	#ifdef PPDEBUG
		std::cout << "Initializing SDL... ";
	#endif
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		#ifndef PPDEBUG
			std::cout << "Error: ";
		#endif
		std::cout << SDL_GetError() << std::endl;
		return 1;
	}
	SDL_version sdlCompiledVersion;
	SDL_version sdlLinkedVersion;
	SDL_VERSION(&sdlCompiledVersion);
	SDL_GetVersion(&sdlLinkedVersion);
	if(SDL_VERSION_NUMBER(&sdlLinkedVersion) < SDL_VERSION_NUMBER(&sdlCompiledVersion)){
		std::cout << "The installed SDL is not compatible. [" << SDL_VERSION_CONCAT(&sdlLinkedVersion) << "<" << SDL_VERSION_CONCAT(&sdlCompiledVersion) << "]" << std::endl;
		return 1;
	}
	#ifdef PPDEBUG
		std::cout << "v" << SDL_VERSION_CONCAT(&sdlLinkedVersion) << std::endl;
		std::cout << "Initializing SDL_image... ";
	#endif
	int imgFlags = IMG_INIT_JPG|IMG_INIT_PNG|IMG_INIT_TIF;
	if((IMG_Init(imgFlags) & imgFlags) != imgFlags) {
		#ifndef PPDEBUG
			std::cout << "Error: ";
		#endif
		std::cout << IMG_GetError() << std::endl;
		return 1;
	}
	SDL_version imgCompiledVersion;
	SDL_IMAGE_VERSION(&imgCompiledVersion);
	const SDL_version *imgLinkedVersion = IMG_Linked_Version();
	if(SDL_VERSION_NUMBER(imgLinkedVersion) < SDL_VERSION_NUMBER(&imgCompiledVersion)){
		std::cout << "The installed SDL_image is not compatible. [" << SDL_VERSION_CONCAT(imgLinkedVersion) << "<" << SDL_VERSION_CONCAT(&imgCompiledVersion) << "]" << std::endl;
		return 1;
	}
	#ifdef PPDEBUG
		std::cout << "v" << SDL_VERSION_CONCAT(imgLinkedVersion) << std::endl;
		std::cout << "Initializing SDL_net... ";
	#endif
	if(SDLNet_Init() < 0) {
		#ifndef PPDEBUG
			std::cout << "Error: ";
		#endif
		std::cout << SDLNet_GetError() << std::endl;
		return 1;
	}
	SDL_version netCompiledVersion;
	SDL_NET_VERSION(&netCompiledVersion);
	const SDL_version *netLinkedVersion = SDLNet_Linked_Version();
	if(SDL_VERSION_NUMBER(netLinkedVersion) < SDL_VERSION_NUMBER(&netCompiledVersion)){
		std::cout << "The installed SDL_net is not compatible. [" << SDL_VERSION_CONCAT(netLinkedVersion) << "<" << SDL_VERSION_CONCAT(&netCompiledVersion) << "]" << std::endl;
		return 1;
	}
	#ifdef PPDEBUG
		std::cout << "v" << SDL_VERSION_CONCAT(netLinkedVersion) << std::endl;
	#endif
	do{
		Uint32 speedTimer = SDL_GetTicks();
		#ifdef PPDEBUG
			std::cout << "Creating window... ";
		#endif
		Uint32 flags = 0;
		if(this->resizable){
			flags |= SDL_WINDOW_RESIZABLE;
		}
		if(this->fullscreen){
			flags |= SDL_WINDOW_FULLSCREEN;
		}
		if(!(this->mainWindow = SDL_CreateWindow(this->title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->screenWidth, this->screenHeight, flags))) {
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Unexpected error has occurred", "Cannot initialize window.", 0);
			return 1;
		}
		#ifdef PPDEBUG
			std::cout << "in " << (SDL_GetTicks()-speedTimer) << "ms" << std::endl;
			speedTimer = SDL_GetTicks();
			std::cout << "Creating renderer... ";
		#endif
		if(!(this->renderer = SDL_CreateRenderer(this->mainWindow, -1, 0))) {
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Unexpected error has occurred", "Cannot initialize renderer.", 0);
			return 1;
		}
		this->graphics = new ppGraphics(this->renderer);

		if(this->renderer){
			#ifdef PPDEBUG
				std::cout << "in " << (SDL_GetTicks()-speedTimer) << "ms" << std::endl;

				SDL_RendererInfo rendererInfo;
				SDL_GetRendererInfo(this->renderer, &rendererInfo);
				std::cout << "Using \"" << rendererInfo.name << "\" as rendering engine..." << std::endl;

				speedTimer = SDL_GetTicks();
				std::cout << "Configuring renderer... ";
			#endif

			SDL_Rect* rect = new SDL_Rect;
			rect->x = 0;
			rect->y = 0;
			rect->w = this->screenWidth;
			rect->h = this->screenHeight;
			SDL_RenderSetViewport(this->renderer, rect);
			SDL_RenderSetLogicalSize(this->renderer, this->width, this->height);
		}

		if(!this->restarting){
			#ifdef PPDEBUG
				std::cout << "in " << (SDL_GetTicks()-speedTimer) << "ms" << std::endl;
				speedTimer = SDL_GetTicks();
				std::cout << "Initializing Adaptive Music System... ";
			#endif
			this->ims = new ppIMS(this, this->randomizer);
			if(this->ims->Init()){
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Unexpected error has occurred", "Cannot initialize Adaptive Music System.", 0);
				return 1;
			}
		}

		#ifdef PPDEBUG
			std::cout << "in " << (SDL_GetTicks()-speedTimer) << "ms" << std::endl;
			if(!this->currentState) {
				std::cout << "No state found..." << std::endl;
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Warning!", "State not found.", 0);
			}
			speedTimer = SDL_GetTicks();
			std::cout << "Preparing... ";
		#endif
		this->running = true;
		if(this->currentState && this->currentState->GetGame()){
			this->currentState->OnInit();
		}
		SDL_Event* event = new SDL_Event();

		Uint32 lastTimer = SDL_GetTicks(), timeNow;
		Uint32 lastTime = lastTimer, avgRenderTime = 0, avgUpdateTime = 0;
		int renderDelta = 0, updateDelta = 0, renderDeltaTime=0, updateDeltaTime=0;
		int frames = 0, updates = 0;
		Uint32 msPerRender = 1000.0f / this->targetFPS;
		Uint32 msPerUpdate = 1000.0f / this->targetUPS;
		#ifdef PPDEBUG
			std::cout << "in " << (SDL_GetTicks()-speedTimer) << "ms" << std::endl;
			speedTimer = SDL_GetTicks();
			std::cout << "Running... " << std::endl;
		#endif
		if(this->restarting){
			this->restarting = false;
			if(this->currentState && this->currentState->GetGame()){
				this->currentState->OnRestore();
			}
		}
		while(this->running) {
			timeNow = SDL_GetTicks();
			renderDelta += (timeNow - lastTime);
			renderDeltaTime += (timeNow - lastTime);
			updateDelta += (timeNow - lastTime);
			updateDeltaTime += (timeNow - lastTime);
			lastTime = timeNow;

			while(SDL_PollEvent(event)) {
				this->OnEvent(event);
			}

			if(updateDelta > msPerUpdate){
				speedTimer = SDL_GetTicks();
				updateDelta -= msPerUpdate;
				updates++;
				if(this->currentState && this->currentState->GetGame()){
					this->currentState->OnUpdate(this->gameInput, updateDeltaTime);
				}
				updateDeltaTime = 0;
				this->ims->Update();
				this->gameInput->OnUpdate();
				avgUpdateTime += SDL_GetTicks()-speedTimer;
			}

			if(!this->vSync || renderDelta > msPerRender){
				speedTimer = SDL_GetTicks();
				renderDelta -= msPerRender;
				frames++;

				SDL_SetRenderDrawColor(this->renderer, this->backgroundColor->GetR(), this->backgroundColor->GetG(), this->backgroundColor->GetB(), this->backgroundColor->GetA());
				SDL_RenderClear(this->renderer);

				if(this->currentState && this->currentState->GetGame()){
					SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
					SDL_SetRenderDrawBlendMode(this->renderer, SDL_BLENDMODE_BLEND);
					this->currentState->OnRender(this->graphics, renderDeltaTime);
				}
				renderDeltaTime = 0;

				if(this->showFPS){
					SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 127);
					SDL_Rect* rect = new SDL_Rect;
					rect->x = 0;
					rect->y = 0;
					rect->w = this->width;
					rect->h = 6;
					SDL_RenderFillRect(this->renderer, rect);

					// FPS
					if(this->fps > 0){
						Uint8 delta = this->fps / this->width;
						SDL_SetRenderDrawColor(this->renderer, 0, (255-(delta*2)), 0, 127);
						SDL_Rect* rect = new SDL_Rect;
						rect->x = 0;
						rect->y = 1;
						rect->w = this->fps % this->width;
						rect->h = 2;
						SDL_RenderFillRect(this->renderer, rect);
					}
					// UPS
					if(this->ups > 0){
						Uint8 delta = this->ups / this->width;
						SDL_SetRenderDrawColor(this->renderer, 0, 0, (255-(delta*2)), 127);
						SDL_Rect* rect = new SDL_Rect;
						rect->x = 0;
						rect->y = 3;
						rect->w = this->ups % this->width;
						rect->h = 2;
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
				#ifdef PPDEBUG
					if(this->showFPS){
						std::cout << "FPS: " << fps << " [" << art <<"ms]   UPS: " << ups << " [" << aut << "ms]" << std::endl;
					}
				#endif
				avgRenderTime = 0;
				avgUpdateTime = 0;
			}
		}
		if(this->currentState){
			this->currentState->OnExit();
		}
		#ifdef PPDEBUG
			speedTimer = SDL_GetTicks();
			std::cout << "Destroying... ";
		#endif
		if(!this->restarting){
			this->ims->Quit();
		}
		SDL_DestroyRenderer(this->renderer);
		SDL_DestroyWindow(this->mainWindow);
		#ifdef PPDEBUG
			std::cout << "in " << (SDL_GetTicks()-speedTimer) << "ms" << std::endl;
			speedTimer = SDL_GetTicks();
			if(this->restarting){
				std::cout << "Restarting..." << std::endl;
			}
		#endif
	} while(this->restarting);
	IMG_Quit();
	SDLNet_Quit();
	SDL_Quit();
	#ifdef PPDEBUG
		std::cout << "Quitting..." << std::endl;
	#endif
	return 0;
}

void ppGame::RestartGame(){
	if(!this->running){
		return;
	}
	if(this->currentState && this->currentState->GetGame()){
		this->currentState->OnRestart();
	}
	this->running = false;
	this->restarting = true;
}

void ppGame::QuitGame(){
	this->running = false;
}

ppInput* ppGame::GetGameInput(){
	return this->gameInput;
}

ppIO* ppGame::GetGameIO(){
	return this->gameIO;
}

ppIMS* ppGame::GetInteractiveMusicSystem(){
	return this->ims;
}

// GameIO* ppGame::getGameIO(){

// }

// SoundPlayer* ppGame::getSoundPlayer(){

// }

void ppGame::AddState(const char* name, ppState* state){
	#ifdef PPDEBUG
		std::cout << "Add a new state \"" << name << "\"..." << std::endl;
	#endif
	state->SetName(name);
	this->states.insert(std::pair<const char*, ppState*>(name, state));
}

void ppGame::EnterState(ppState* state){
	if(!state->GetGame()){
		state->SetGame(this);
		if(this->running){
			state->OnInit();
		}
	}else if(state->IsNeedInit() && this->running){
		state->OnInit();
	}
	if(this->currentState){
		this->currentState->OnExit();
	}
	#ifdef PPDEBUG
		std::cout << "Enter a state \"" << state->GetName() << "\"..." << std::endl;
	#endif
	this->currentState = state;
}

void ppGame::EnterState(const char* name){
	ppState* state = this->GetState(name);
	if(state){
		if(!state->GetGame()){
			state->SetGame(this);
			if(this->running){
				state->OnInit();
			}
		}else if(state->IsNeedInit() && this->running){
			state->OnInit();
		}
		if(this->currentState){
			this->currentState->OnExit();
		}
		#ifdef PPDEBUG
			std::cout << "Enter a state \"" << state->GetName() << "\"..." << std::endl;
		#endif
		this->currentState = state;
	}
}

void ppGame::EnterState(const char* name, ppState* state){
	this->AddState(name, state);
	this->EnterState(state);
}

ppState* ppGame::GetState(const char* name){
	if(this->states.empty()){
		return NULL;
	}
	std::map<const char*, ppState*>::iterator it;
	it = this->states.find(name);
	if(it != this->states.end()){
		return it->second;
	}
	return NULL;
}

bool ppGame::HasState(const char* name){
	return false;
}

const char* ppGame::GetCurrentStateName(){
	return this->currentState->GetName();
}

void ppGame::RemoveState(const char* name){
	if(this->states.empty()){
		return;
	}
	std::map<const char*, ppState*>::iterator it;
	it = this->states.find(name);
	if(it != this->states.end()){
		this->states.erase(it);
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
