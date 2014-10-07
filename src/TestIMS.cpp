#include "TestIMS.hpp"

#include <iostream>
#include <cmath>
#include <sstream>

void TestIMS::OnInit(){
	this->gui = new ppGUI();
	this->gui->AddControl(new ppLabel("text", 10, 50));
	this->test = 0;
}

void TestIMS::OnRender(SDL_Renderer* renderer, int delta){
	std::stringstream ss;
	ss << "FPS: " << this->GetGame()->GetFPS() << " [" << this->GetGame()->GetAvgRenderTime() << "ms]\n";
	ss << "UPS: " << this->GetGame()->GetUPS() << " [" << this->GetGame()->GetAvgUpdateTime() << "ms]\n";
	if(this->gui->GetDefaultFont()){
		glColor3f(1 ,1 ,1);
		this->gui->GetDefaultFont()->Render(10, 10, ss.str().c_str(), renderer);
	}
	this->gui->Render(renderer);
}

void TestIMS::OnUpdate(ppInput* input, int delta){
	this->ims = this->GetGame()->GetInteractiveMusicSystem();
	ppLabel* label = (ppLabel*)this->gui->GetControl("text");
	if(!label || !ims){
		this->gui->Update(input);
		return;
	}
	std::stringstream msg;
	if(this->test == 0){
		msg << "1 = Sound Test\n";
		msg << "2 = Segment Test\n";
		msg << "3 = Playlist Test";

		if(input->IsKeyDown(SDL_SCANCODE_1, 10)){
			this->test = 1;
		}else if(input->IsKeyDown(SDL_SCANCODE_2, 10)){
			this->test = 2;
		}else if(input->IsKeyDown(SDL_SCANCODE_3, 10)){
			this->test = 3;
		}
	}else if(this->test == 1){
		msg << "Sound Test\n";
	}else if(this->test == 2){
		msg << "Segment Test\n";
	}else if(this->test == 3){
		msg << "Playlist Test\n";
	}
	if(this->test != 0){
		msg << "Press 'R' to select a new test";
		if(input->IsKeyDown(SDL_SCANCODE_R, 10)){
			this->test = 0;
			//Clear Test 1
			this->gui->RemoveControl("sound");
			//Clear Test 2
			this->gui->RemoveControl("segment");
			//Clear Test 3
			this->gui->RemoveControl("playlist");
			//Clear all sounds
			this->ims->ClearSound();
		}
	}

	if(this->test == 1){
		////////////////
		//   TEST 1   //
		// SOUND TEST //
		////////////////
		if(!this->ims->GetSound("sound")){
			ppFormat* soundFormat = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/MusicGameplay/Music_Gameplay.wav");
			ppSound* sound = this->ims->CreateSound("sound", soundFormat);
			sound->SetSize(300, 30);
			sound->SetLocation(10, 200);
			this->gui->AddControl(sound);
		}else{
			ppSound* sound = (ppSound*)this->ims->GetSound("sound");

			msg << "\n\nLoop: ";
			if(sound->IsLoop()){
				if(sound->GetLoop() < 0){
					msg << "Infinite";
				}else{
					msg << sound->GetLoop();
				}
			}else{
				msg << "No Loop";
			}
			if(sound->IsStop()){
				msg << " ('Left' or 'Right' to change)";
			}
			msg << "\nPlay Order: ";
			ppSoundPlayOrder currentPlayOrder = sound->GetPlayOrder();
			if(currentPlayOrder == ppSoundPlayOrder::LOOP){
				msg << "Loop";
			}else if(currentPlayOrder == ppSoundPlayOrder::SEQUENCE){
				msg << "Sequence";
			}else if(currentPlayOrder == ppSoundPlayOrder::RANDOM){
				msg << "Random";
			}else if(currentPlayOrder == ppSoundPlayOrder::SHUFFLE){
				msg << "Shuffle";
			}
			if(sound->IsStop()){
				msg << " ('Up' or 'Down' to change)";
			}
			msg << "\n\nPress 'P' to ";

			if(sound){
				if(sound->IsPlaying()){
					msg << "pause";
				}else{
					msg << "play";
				}
				if(sound->IsStop()){
					int currentLoop = sound->GetLoop();
					if(input->IsKeyDown(SDL_SCANCODE_LEFT, 10)){
						if(currentLoop >= 0){
							currentLoop--;
						}
						sound->SetLoop(currentLoop);
					}else if(input->IsKeyDown(SDL_SCANCODE_RIGHT, 10)){
						sound->SetLoop(currentLoop+1);
					}
					ppSoundPlayOrder currentPlayOrder = sound->GetPlayOrder();
					if(input->IsKeyDown(SDL_SCANCODE_UP, 10)){
						if(currentPlayOrder == ppSoundPlayOrder::LOOP){
							currentPlayOrder = ppSoundPlayOrder::SEQUENCE;
						}else if(currentPlayOrder == ppSoundPlayOrder::SEQUENCE){
							currentPlayOrder = ppSoundPlayOrder::RANDOM;
						}else if(currentPlayOrder == ppSoundPlayOrder::RANDOM){
							currentPlayOrder = ppSoundPlayOrder::SHUFFLE;
						}else if(currentPlayOrder == ppSoundPlayOrder::SHUFFLE){
							currentPlayOrder = ppSoundPlayOrder::LOOP;
						}
						sound->SetPlayOrder(currentPlayOrder);
					}else if(input->IsKeyDown(SDL_SCANCODE_DOWN, 10)){
						if(currentPlayOrder == ppSoundPlayOrder::LOOP){
							currentPlayOrder = ppSoundPlayOrder::SHUFFLE;
						}else if(currentPlayOrder == ppSoundPlayOrder::SEQUENCE){
							currentPlayOrder = ppSoundPlayOrder::LOOP;
						}else if(currentPlayOrder == ppSoundPlayOrder::RANDOM){
							currentPlayOrder = ppSoundPlayOrder::SEQUENCE;
						}else if(currentPlayOrder == ppSoundPlayOrder::SHUFFLE){
							currentPlayOrder = ppSoundPlayOrder::RANDOM;
						}
						sound->SetPlayOrder(currentPlayOrder);
					}
					if(input->IsKeyDown(SDL_SCANCODE_P, 10)){
						sound->Play();
					}
				}else{
					msg << "\nPress 'S' to stop\n\n";
					if(input->IsKeyDown(SDL_SCANCODE_P, 10)){
						if(sound->IsPause()){
							sound->Play();
						}else{
							sound->Pause();
						}
					}
					if(input->IsKeyDown(SDL_SCANCODE_S, 10)){
						sound->Stop();
					}

					msg << sound->GetAudioFormat()->GetFileName() << "\n";
					msg << "Track " << sound->GetTrack() << "/" << sound->GetAudioFormat()->GetTotalTrack() << " " << sound->GetCurrentTime() << "/" << sound->GetTotalTime();
				}
			}
		}
	}else if(this->test == 2){
		//////////////////
		//    TEST 2    //
		// SEGMENT TEST //
		//////////////////
		if(!this->ims->GetSound("segment")){
			ppFormat* soundFormat = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/MusicGameplay/Music_Gameplay.wav");
			ppSound* melody = this->ims->CreateSound("melody", soundFormat, 1);
			ppSound* critical = this->ims->CreateSound("critical", soundFormat, 2);
			ppSound* drum = this->ims->CreateSound("drum", soundFormat, 3);

			critical->SetOffset(soundFormat->TimeToPosition(5));

			ppSegment* segment = this->ims->CreateSegment("segment");
			segment->AddSound(melody);
			segment->AddSound(critical);
			segment->AddSound(drum);
			segment->SetLoop(-1);
			segment->SetSize(300, 30);
			segment->SetLocation(10, 200);
			this->gui->AddControl(segment);
		}else{
			ppSegment* segment = (ppSegment*)this->ims->GetSound("segment");

			msg << "\n\nLoop: ";
			if(segment->IsLoop()){
				if(segment->GetLoop() < 0){
					msg << "Infinite";
				}else{
					msg << segment->GetLoop();
				}
			}else{
				msg << "No Loop";
			}
			if(segment->IsStop()){
				msg << " ('Left' or 'Right' to change)";
			}
			msg << "\n\nPress 'P' to ";

			if(segment){
				if(segment->IsPlaying()){
					msg << "pause";
				}else{
					msg << "play";
				}
				if(segment->IsStop()){
					int currentLoop = segment->GetLoop();
					if(input->IsKeyDown(SDL_SCANCODE_LEFT, 10)){
						if(currentLoop >= 0){
							currentLoop--;
						}
						segment->SetLoop(currentLoop);
					}else if(input->IsKeyDown(SDL_SCANCODE_RIGHT, 10)){
						segment->SetLoop(currentLoop+1);
					}
					if(input->IsKeyDown(SDL_SCANCODE_P, 10)){
						segment->Play();
					}
				}else{
					msg << "\nPress 'S' to stop\n\n";
					if(input->IsKeyDown(SDL_SCANCODE_P, 10)){
						if(segment->IsPause()){
							segment->Play();
						}else{
							segment->Pause();
						}
					}
					if(input->IsKeyDown(SDL_SCANCODE_S, 10)){
						segment->Stop();
					}

					msg << segment->GetCurrentTime() << "/" << segment->GetTotalTime();
				}
			}
		}
	}else if(this->test == 3){
		///////////////////
		//    TEST 3     //
		// PLAYLIST TEST //
		///////////////////
		if(!this->ims->GetSound("playlist")){
			this->playlist_track = 0;

			ppFormat* seg1format = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/kameleon/l4_a1-01.wav");
			ppFormat* seg2format = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/kameleon/l4_a1-02.wav");
			ppFormat* seg3format = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/kameleon/l4_a1-03.wav");
			ppFormat* seg4format = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/kameleon/l4_a1-04.wav");
			ppFormat* seg5format = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/kameleon/l4_a1-05.wav");
			ppFormat* seg6format = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/kameleon/l4_a1-06.wav");
			ppFormat* seg7format = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/kameleon/l4_a1-07.wav");
			ppFormat* seg8format = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/kameleon/l4_a1-08.wav");
			ppFormat* seg9format = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/kameleon/l4_a1-09.wav");
			ppFormat* seg10format = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/kameleon/l4_a1-10.wav");
			ppFormat* seg11format = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/kameleon/l4_a1-11.wav");
			ppFormat* seg12format = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/kameleon/l4_a1-12.wav");

			ppSound* seg1 = this->ims->CreateSound("seg1sound", seg1format);
			ppSound* seg2 = this->ims->CreateSound("seg2sound", seg2format);
			ppSound* seg3 = this->ims->CreateSound("seg3sound", seg3format);
			ppSound* seg4 = this->ims->CreateSound("seg4sound", seg4format);
			ppSound* seg5 = this->ims->CreateSound("seg5sound", seg5format);
			ppSound* seg6 = this->ims->CreateSound("seg6sound", seg6format);
			ppSound* seg7 = this->ims->CreateSound("seg7sound", seg7format);
			ppSound* seg8 = this->ims->CreateSound("seg8sound", seg8format);
			ppSound* seg9 = this->ims->CreateSound("seg9sound", seg9format);
			ppSound* seg10 = this->ims->CreateSound("seg10sound", seg10format);
			ppSound* seg11 = this->ims->CreateSound("seg11sound", seg11format);
			ppSound* seg12 = this->ims->CreateSound("seg12sound", seg12format);
			// ppSound* seg1sound = this->ims->CreateSound("seg1sound", seg1format);
			// ppSound* seg2sound = this->ims->CreateSound("seg2sound", seg2format);
			// ppSound* seg3sound = this->ims->CreateSound("seg3sound", seg3format);
			// ppSound* seg4sound = this->ims->CreateSound("seg4sound", seg4format);
			// ppSound* seg5sound = this->ims->CreateSound("seg5sound", seg5format);
			// ppSound* seg6sound = this->ims->CreateSound("seg6sound", seg6format);
			// ppSound* seg7sound = this->ims->CreateSound("seg7sound", seg7format);
			// ppSound* seg8sound = this->ims->CreateSound("seg8sound", seg8format);
			// ppSound* seg9sound = this->ims->CreateSound("seg9sound", seg9format);
			// ppSound* seg10sound = this->ims->CreateSound("seg10sound", seg10format);
			// ppSound* seg11sound = this->ims->CreateSound("seg11sound", seg11format);
			// ppSound* seg12sound = this->ims->CreateSound("seg12sound", seg12format);

			// ppSegment* seg1 = this->ims->CreateSegment("seg1");
			seg1->SetEntryCue(seg1format->TimeToPosition(1.5f));
			seg1->SetExitCue(seg1format->TimeToPosition(4.5f));
			// ppSegment* seg2 = this->ims->CreateSegment("seg2");
			seg2->SetEntryCue(seg1format->TimeToPosition(1.125f));
			seg2->SetExitCue(seg1format->TimeToPosition(4.5f));
			// ppSegment* seg3 = this->ims->CreateSegment("seg3");
			seg3->SetEntryCue(seg1format->TimeToPosition(1.5f));
			seg3->SetExitCue(seg1format->TimeToPosition(4.5f));
			// ppSegment* seg4 = this->ims->CreateSegment("seg4");
			seg4->SetEntryCue(seg1format->TimeToPosition(1.125f));
			seg4->SetExitCue(seg1format->TimeToPosition(4.5f));
			// ppSegment* seg5 = this->ims->CreateSegment("seg5");
			seg5->SetEntryCue(seg1format->TimeToPosition(1.5f));
			seg5->SetExitCue(seg1format->TimeToPosition(4.5f));
			// ppSegment* seg6 = this->ims->CreateSegment("seg6");
			seg6->SetEntryCue(seg1format->TimeToPosition(1.125f));
			seg6->SetExitCue(seg1format->TimeToPosition(4.5f));
			// ppSegment* seg7 = this->ims->CreateSegment("seg7");
			seg7->SetEntryCue(seg1format->TimeToPosition(1.125f));
			seg7->SetExitCue(seg1format->TimeToPosition(4.5f));
			// ppSegment* seg8 = this->ims->CreateSegment("seg8");
			seg8->SetEntryCue(seg1format->TimeToPosition(1.125f));
			seg8->SetExitCue(seg1format->TimeToPosition(4.5f));
			// ppSegment* seg9 = this->ims->CreateSegment("seg9");
			seg9->SetEntryCue(seg1format->TimeToPosition(1.875f));
			seg9->SetExitCue(seg1format->TimeToPosition(4.5f));
			// ppSegment* seg10 = this->ims->CreateSegment("seg10");
			seg10->SetEntryCue(seg1format->TimeToPosition(1.5f));
			seg10->SetExitCue(seg1format->TimeToPosition(4.5f));
			// ppSegment* seg11 = this->ims->CreateSegment("seg11");
			seg11->SetEntryCue(seg1format->TimeToPosition(1.125f));
			seg11->SetExitCue(seg1format->TimeToPosition(5.625f));
			// ppSegment* seg12 = this->ims->CreateSegment("seg12");
			seg12->SetEntryCue(seg1format->TimeToPosition(2.625f));
			seg12->SetExitCue(seg1format->TimeToPosition(4.5f));

			// seg1->AddSound(seg1sound);
			// seg2->AddSound(seg2sound);
			// seg3->AddSound(seg3sound);
			// seg4->AddSound(seg4sound);
			// seg5->AddSound(seg5sound);
			// seg6->AddSound(seg6sound);
			// seg7->AddSound(seg7sound);
			// seg8->AddSound(seg8sound);
			// seg9->AddSound(seg9sound);
			// seg10->AddSound(seg10sound);
			// seg11->AddSound(seg11sound);
			// seg12->AddSound(seg12sound);

			ppPlaylist* playlist = this->ims->CreatePlaylist("playlist");
			playlist->AddSound(seg1);
			playlist->AddSound(seg2);
			playlist->AddSound(seg3);
			playlist->AddSound(seg4);
			playlist->AddSound(seg5);
			playlist->AddSound(seg6);
			playlist->AddSound(seg7);
			playlist->AddSound(seg8);
			playlist->AddSound(seg9);
			playlist->AddSound(seg10);
			playlist->AddSound(seg11);
			playlist->AddSound(seg12);

			// ppPlaylist* playlist2 = this->ims->CreatePlaylist("playlist2");
			// playlist2->AddSound(seg7);
			// playlist2->AddSound(seg8);
			// playlist2->AddSound(seg9);
			// playlist2->AddSound(seg10);
			// playlist2->AddSound(seg11);
			// playlist2->AddSound(seg12);

			// playlist->AddSound(playlist2);

			playlist->SetSize(300, 250);
			playlist->SetLocation(10, 100);
			this->gui->AddControl(playlist);
		}else{
			ppPlaylist* playlist = (ppPlaylist*)this->ims->GetSound("playlist");

			msg << "\n\nPress 'P' to ";

			if(playlist){
				if(playlist->IsPlaying()){
					msg << "pause";
				}else{
					msg << "play";
				}
				msg << " playlist";
				if(playlist->IsStop()){
					ppGenericSound* sound = playlist->GetSoundAtIndex(this->playlist_track);
					msg << "\nPress 'Space' to ";
					if(sound->IsPlaying()){
						msg << "stop";
					}else {
						msg << "preview";
					}
					msg << " sound ";
					msg << "\"" << sound->GetName() << "\"";
					if(input->IsKeyDown(SDL_SCANCODE_UP, 10)){
						// sound->Stop();
						if(this->playlist_track == 0){
							this->playlist_track = playlist->GetTotalSound();
						}
						this->playlist_track--;
					}else if(input->IsKeyDown(SDL_SCANCODE_DOWN, 10)){
						// sound->Stop();
						this->playlist_track++;
						this->playlist_track %= playlist->GetTotalSound();
					}else if(input->IsKeyDown(SDL_SCANCODE_SPACE, 10)){
						if(sound->IsPlaying()){
							sound->Stop();
						}else{
							sound->Play();
						}
					}
					if(input->IsKeyDown(SDL_SCANCODE_P, 10)){
						playlist->GetSoundAtIndex(this->playlist_track)->Stop();
						playlist->Play();
					}
				}else{
					msg << "\nPress 'S' to stop\n\n";
					if(input->IsKeyDown(SDL_SCANCODE_P, 10)){
						if(playlist->IsPause()){
							playlist->Play();
						}else{
							playlist->Pause();
						}
					}
					if(input->IsKeyDown(SDL_SCANCODE_S, 10)){
						playlist->Stop();
					}
				}
			}
		}
	}
	label->SetText(msg.str());
	this->gui->Update(input);
}
