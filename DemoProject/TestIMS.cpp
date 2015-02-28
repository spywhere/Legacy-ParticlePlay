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
	if(this->test==0){
		ppEasing* easing = new ppLinearEasing();
		glColor3f(1, 1, 1);
		for(int i=0;i<=100;i++){
			glBegin(GL_POINTS);
				glVertex2f(50+i, 300-easing->GetValue(i, 100, 0, 100));
			glEnd();
		}
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
		msg << "3 = Playlist Test\n";
		msg << "4 = Complex Playlist Test\n";
		msg << "5 = Playlist Play Order Test\n";
		msg << "6 = Music Notation\n";
		msg << "7 = Music Transition\n";
		msg << "8 = Demo Game";

		if(input->IsKeyDown(SDL_SCANCODE_1, 10)){
			this->test = 1;
		}else if(input->IsKeyDown(SDL_SCANCODE_2, 10)){
			this->test = 2;
		}else if(input->IsKeyDown(SDL_SCANCODE_3, 10)){
			this->test = 3;
		}else if(input->IsKeyDown(SDL_SCANCODE_4, 10)){
			this->test = 4;
		}else if(input->IsKeyDown(SDL_SCANCODE_5, 10)){
			this->test = 5;
		}else if(input->IsKeyDown(SDL_SCANCODE_6, 10)){
			this->test = 6;
		}else if(input->IsKeyDown(SDL_SCANCODE_7, 10)){
			this->test = 7;
		}else if(input->IsKeyDown(SDL_SCANCODE_8, 10)){
			this->GetGame()->EnterState("farmstate");
		}
	}else if(this->test == 1){
		msg << "Sound Test\n";
	}else if(this->test == 2){
		msg << "Segment Test\n";
	}else if(this->test == 3){
		msg << "Playlist Test\n";
	}else if(this->test == 4){
		msg << "Complex Playlist Test\n";
	}else if(this->test == 5){
		msg << "Playlist Play Order Test\n";
	}else if(this->test == 6){
		msg << "Music Notation\n";
	}else if(this->test == 7){
		msg << "Music Transition\n";
	}
	if(this->test != 0){
		msg << "Press 'R' to select a new test";
		if(input->IsKeyDown(SDL_SCANCODE_R, 10)){
			this->test = 0;
			//Clear Test 1
			this->gui->RemoveControl("sound");
			//Clear Test 2
			this->gui->RemoveControl("segment");
			this->gui->RemoveControl("seg1");
			this->gui->RemoveControl("seg2");
			this->gui->RemoveControl("seg3");
			//Clear Test 5
			this->gui->RemoveControl("seg1playlist");
			this->gui->RemoveControl("seg2playlist");
			this->gui->RemoveControl("seg3playlist");
			this->gui->RemoveControl("seg4playlist");
			this->gui->RemoveControl("seg5playlist");
			this->gui->RemoveControl("seg6playlist");
			this->gui->RemoveControl("seg7playlist");
			//Clear Test 3 & 4
			this->gui->RemoveControl("playlist");
			this->gui->RemoveControl("playlist2");
			//Clear Test 7
			this->gui->RemoveControl("level");
			this->gui->RemoveControl("stress");
			this->gui->RemoveControl("fight");
			this->gui->RemoveControl("bonus");
			//Clear all sounds
			this->ims->ClearSound();
			this->ims->ClearSwitch();
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
			segment->SetSize(300, 100);
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

			ppSound* seg1sound = this->ims->CreateSound("seg1sound", seg1format);
			ppSound* seg2sound = this->ims->CreateSound("seg2sound", seg2format);
			ppSound* seg3sound = this->ims->CreateSound("seg3sound", seg3format);
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

			ppSegment* seg1 = this->ims->CreateSegment("seg1");
			seg1->SetEntryCue(seg1format->TimeToPosition(1.5f));
			seg1->SetExitCue(seg1format->TimeToPosition(4.5f));
			ppSegment* seg2 = this->ims->CreateSegment("seg2");
			seg2->SetEntryCue(seg1format->TimeToPosition(1.125f));
			seg2->SetExitCue(seg1format->TimeToPosition(4.5f));
			ppSegment* seg3 = this->ims->CreateSegment("seg3");
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

			seg1->AddSound(seg1sound);
			seg2->AddSound(seg2sound);
			seg3->AddSound(seg3sound);
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
			// playlist->AddSound(seg7);
			// playlist->AddSound(seg8);
			// playlist->AddSound(seg9);
			// playlist->AddSound(seg10);
			// playlist->AddSound(seg11);
			// playlist->AddSound(seg12);

			ppPlaylist* playlist2 = this->ims->CreatePlaylist("playlist2");
			playlist2->AddSound(seg7);
			playlist2->AddSound(seg8);
			playlist2->AddSound(seg9);
			playlist2->AddSound(seg10);
			playlist2->AddSound(seg11);
			playlist2->AddSound(seg12);

			playlist->AddSound(playlist2);

			playlist2->SetLoop(1);
			playlist->SetLoop(1);

			playlist->SetSize(300, 250);
			playlist->SetLocation(10, 150);
			playlist2->SetSize(300, 250);
			playlist2->SetLocation(330, 150);
			this->gui->AddControl(playlist);
			this->gui->AddControl(playlist2);
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
						if(this->playlist_track == 0){
							this->playlist_track = playlist->GetTotalSound();
						}
						this->playlist_track--;
					}else if(input->IsKeyDown(SDL_SCANCODE_DOWN, 10)){
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
	}else if(this->test == 4){
		///////////////////////////
		//        TEST 4         //
		// COMPLEX PLAYLIST TEST //
		///////////////////////////
		if(!this->ims->GetSound("playlist")){
			this->playlist_track = 0;
			// Segment 1 Formats
			ppFormat* drumSeg1Format = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/SampleProject/Stealth_Drums_AmbientDrum&Ride1_Seg1_01.wav");
			ppFormat* bassSeg1Format = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/SampleProject/Stress_Bass_MainBassMelody_Seg1_01.wav");
			ppFormat* stringSeg1Format = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/SampleProject/Stress_Orchestra_StringMelody_Seg1_01.wav");
			ppFormat* percussionSeg1Format = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/SampleProject/Stress_Percussion_BigDrums&Cymbals_Seg1_01.wav");
			ppFormat* variousSeg1Format = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/SampleProject/Stress_Various_DoubleTimeElements_Seg1_01.wav");

			// Segment 2 Formats
			ppFormat* brassSeg2Format = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/SampleProject/Stealth_Orchestra_BrassPiano&Ride1_Seg2_01.wav");
			ppFormat* bassSeg2Format = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/SampleProject/Stress_Bass_MainBassMelody_Seg2_01.wav");
			ppFormat* stringSeg2Format = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/SampleProject/Stress_Orchestra_StringMelody_Seg2_01.wav");
			ppFormat* percussionSeg2Format = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/SampleProject/Stress_Percussion_BigDrums&Cymbals_Seg2_01.wav");
			ppFormat* variousSeg2Format = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/SampleProject/Stress_Various_DoubleTimeElements_Seg2_01.wav");

			// Segment 3 Formats
			ppFormat* drumSeg3Format = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/SampleProject/Stealth_Drums_AmbientDrum&Ride1_Seg3_01.wav");
			ppFormat* bassSeg3Format = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/SampleProject/Stress_Bass_MainBassMelody_Seg3_01.wav");
			ppFormat* stringSeg3Format = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/SampleProject/Stress_Orchestra_StringMelody_Seg3_01.wav");
			ppFormat* percussionSeg3Format = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/SampleProject/Stress_Percussion_BigDrums&Cymbals_Seg3_01.wav");
			ppFormat* variousSeg3Format = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/SampleProject/Stress_Various_DoubleTimeElements_Seg3_01.wav");

			// Segment 1 Sounds
			ppSound* drumSeg1Sound = this->ims->CreateSound("drumSeg1Sound", drumSeg1Format);
			ppSound* bassSeg1Sound = this->ims->CreateSound("bassSeg1Sound", bassSeg1Format);
			ppSound* stringSeg1Sound = this->ims->CreateSound("stringSeg1Sound", stringSeg1Format);
			ppSound* percussionSeg1Sound = this->ims->CreateSound("percussionSeg1Sound", percussionSeg1Format);
			ppSound* variousSeg1Sound = this->ims->CreateSound("variousSeg1Sound", variousSeg1Format);

			drumSeg1Sound->SetOffset(drumSeg1Format->TimeToPosition(1.29f));
			bassSeg1Sound->SetOffset(bassSeg1Format->TimeToPosition(1.29f));
			stringSeg1Sound->SetOffset(stringSeg1Format->TimeToPosition(1.29f));
			variousSeg1Sound->SetOffset(variousSeg1Format->TimeToPosition(1.29f));

			// Segment 2 Sounds
			ppSound* brassSeg2Sound = this->ims->CreateSound("brassSeg2Sound", brassSeg2Format);
			ppSound* bassSeg2Sound = this->ims->CreateSound("bassSeg2Sound", bassSeg2Format);
			ppSound* stringSeg2Sound = this->ims->CreateSound("stringSeg2Sound", stringSeg2Format);
			ppSound* percussionSeg2Sound = this->ims->CreateSound("percussionSeg2Sound", percussionSeg2Format);
			ppSound* variousSeg2Sound = this->ims->CreateSound("variousSeg2Sound", variousSeg2Format);

			brassSeg2Sound->SetOffset(brassSeg2Format->TimeToPosition(1.325f));
			brassSeg2Sound->SetClipStart(brassSeg2Format->TimeToPosition(2.6f));
			bassSeg2Sound->SetOffset(bassSeg2Format->TimeToPosition(1.325f));
			stringSeg2Sound->SetOffset(stringSeg2Format->TimeToPosition(1.325f));
			variousSeg2Sound->SetOffset(variousSeg2Format->TimeToPosition(1.325f));

			// Segment 3 Sounds
			ppSound* drumSeg3Sound = this->ims->CreateSound("drumSeg3Sound", drumSeg3Format);
			ppSound* bassSeg3Sound = this->ims->CreateSound("bassSeg3Sound", bassSeg3Format);
			ppSound* stringSeg3Sound = this->ims->CreateSound("stringSeg3Sound", stringSeg3Format);
			ppSound* percussionSeg3Sound = this->ims->CreateSound("percussionSeg3Sound", percussionSeg3Format);
			ppSound* variousSeg3Sound = this->ims->CreateSound("variousSeg3Sound", variousSeg3Format);

			drumSeg3Sound->SetOffset(drumSeg3Format->TimeToPosition(1.29f));
			drumSeg3Sound->SetClipStart(drumSeg3Format->TimeToPosition(2.6f));
			bassSeg3Sound->SetOffset(bassSeg3Format->TimeToPosition(1.29f));
			stringSeg3Sound->SetOffset(stringSeg3Format->TimeToPosition(1.29f));
			variousSeg3Sound->SetOffset(variousSeg3Format->TimeToPosition(1.29f));

			// Segment Setups
			ppSegment* seg1 = this->ims->CreateSegment("seg1");
			seg1->SetEntryCue(percussionSeg1Format->TimeToPosition(1.29f));
			seg1->SetExitCue(percussionSeg1Format->TimeToPosition(21.31f));
			ppSegment* seg2 = this->ims->CreateSegment("seg2");
			seg2->SetEntryCue(percussionSeg2Format->TimeToPosition(1.325f));
			seg2->SetExitCue(percussionSeg2Format->TimeToPosition(21.325f));
			ppSegment* seg3 = this->ims->CreateSegment("seg3");
			seg3->SetEntryCue(percussionSeg3Format->TimeToPosition(1.29f));
			seg3->SetExitCue(percussionSeg3Format->TimeToPosition(21.31f));

			//Segment 1
			seg1->AddSound(drumSeg1Sound);
			seg1->AddSound(bassSeg1Sound);
			seg1->AddSound(stringSeg1Sound);
			seg1->AddSound(percussionSeg1Sound);
			seg1->AddSound(variousSeg1Sound);
			//Segment 2
			seg2->AddSound(brassSeg2Sound);
			seg2->AddSound(bassSeg2Sound);
			seg2->AddSound(stringSeg2Sound);
			seg2->AddSound(percussionSeg2Sound);
			seg2->AddSound(variousSeg2Sound);
			//Segment 3
			seg3->AddSound(drumSeg3Sound);
			seg3->AddSound(bassSeg3Sound);
			seg3->AddSound(stringSeg3Sound);
			seg3->AddSound(percussionSeg3Sound);
			seg3->AddSound(variousSeg3Sound);

			ppPlaylist* playlist = this->ims->CreatePlaylist("playlist");
			playlist->AddSound(seg1);
			playlist->AddSound(seg2);
			playlist->AddSound(seg3);

			playlist->SetLoop(-1);

			playlist->SetSize(300, 250);
			playlist->SetLocation(10, 150);
			seg1->SetSize(300, 150);
			seg1->SetLocation(330, 150);
			seg2->SetSize(300, 150);
			seg2->SetLocation(330, 150);
			seg3->SetSize(300, 150);
			seg3->SetLocation(330, 150);
			this->gui->AddControl(playlist);
			this->gui->AddControl(seg1);
			this->gui->AddControl(seg2);
			this->gui->AddControl(seg3);
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
						if(this->playlist_track == 0){
							this->playlist_track = playlist->GetTotalSound();
						}
						this->playlist_track--;
					}else if(input->IsKeyDown(SDL_SCANCODE_DOWN, 10)){
						this->playlist_track++;
						this->playlist_track %= playlist->GetTotalSound();
					}else if(input->IsKeyDown(SDL_SCANCODE_SPACE, 10)){
						if(sound->IsPlaying()){
							sound->Stop();
						}else{
							sound->Play();
						}
					}
					for(int i=0;i<playlist->GetTotalSound();i++){
						ppGenericSound* sound = playlist->GetSoundAtIndex(i);
						sound->SetVisible(i==this->playlist_track);
					}
					if(input->IsKeyDown(SDL_SCANCODE_P, 10)){
						playlist->GetSoundAtIndex(this->playlist_track)->Stop();
						playlist->Play();
					}
				}else{
					for(int i=playlist->GetTotalSound()-1;i>=0;i--){
						ppGenericSound* sound = playlist->GetSoundAtIndex(i);
						sound->SetVisible(false);
					}
					playlist->GetPlayingSound()->SetVisible(true);
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
	}else if(this->test == 5){
		//////////////////////////////
		//          TEST 5          //
		// PLAYLIST PLAY ORDER TEST //
		//////////////////////////////
		if(!this->ims->GetSound("playlist")){
			this->playlist_track = 0;
			// Formats
			ppFormat* seg1AFormat = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/SampleProject/Attack01_Seg 01a (A) [light groove].wav");
			ppFormat* seg1BFormat = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/SampleProject/Attack02_Seg 01b (B) [light groove].wav");

			ppFormat* seg2AFormat = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/SampleProject/Attack03_Seg 01c (A) [light groove].wav");
			ppFormat* seg2BFormat = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/SampleProject/Attack04_Seg 01d (B) [light groove].wav");

			ppFormat* seg3AFormat = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/SampleProject/Attack05_Seg 02a (A) [medium groove + bass].wav");
			ppFormat* seg3BFormat = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/SampleProject/Attack06_Seg 02b (B) [medium groove + bass].wav");

			ppFormat* seg4AFormat = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/SampleProject/Attack07_Seg 02c (A) [medium groove + bass].wav");
			ppFormat* seg4BFormat = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/SampleProject/Attack08_Seg 02d (B) [medium groove + bass].wav");

			ppFormat* seg5AFormat = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/SampleProject/Attack09_Seg 03a (A) [full groove + horns].wav");
			ppFormat* seg5BFormat = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/SampleProject/Attack10_Seg 03b (B) [full groove + horns].wav");

			ppFormat* seg6AFormat = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/SampleProject/Attack11_Seg 03c (A) [full groove + horns].wav");
			ppFormat* seg6BFormat = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/SampleProject/Attack12_Seg 03d (B) [full groove + horns].wav");

			ppFormat* seg7AFormat = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/SampleProject/Attack18_Seg 04e [break - full].wav");
			ppFormat* seg7BFormat = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/SampleProject/Attack19_Seg 04f [break - full].wav");

			// Sounds
			ppSound* seg1ASound = this->ims->CreateSound("seg1ASound", seg1AFormat);
			ppSound* seg1BSound = this->ims->CreateSound("seg1BSound", seg1BFormat);
			ppSound* seg2ASound = this->ims->CreateSound("seg2ASound", seg2AFormat);
			ppSound* seg2BSound = this->ims->CreateSound("seg2BSound", seg2BFormat);
			ppSound* seg3ASound = this->ims->CreateSound("seg3ASound", seg3AFormat);
			ppSound* seg3BSound = this->ims->CreateSound("seg3BSound", seg3BFormat);
			ppSound* seg4ASound = this->ims->CreateSound("seg4ASound", seg4AFormat);
			ppSound* seg4BSound = this->ims->CreateSound("seg4BSound", seg4BFormat);
			ppSound* seg5ASound = this->ims->CreateSound("seg5ASound", seg5AFormat);
			ppSound* seg5BSound = this->ims->CreateSound("seg5BSound", seg5BFormat);
			ppSound* seg6ASound = this->ims->CreateSound("seg6ASound", seg6AFormat);
			ppSound* seg6BSound = this->ims->CreateSound("seg6BSound", seg6BFormat);
			ppSound* seg7ASound = this->ims->CreateSound("seg7ASound", seg7AFormat);
			ppSound* seg7BSound = this->ims->CreateSound("seg7BSound", seg7BFormat);

			// Segment Setups
			ppSegment* seg1a = this->ims->CreateSegment("seg1a");
			seg1a->SetEntryCue(seg1AFormat->TimeToPosition(2.0f));
			seg1a->SetExitCue(seg1AFormat->TimeToPosition(4.0f));
			ppSegment* seg1b = this->ims->CreateSegment("seg1b");
			seg1b->SetEntryCue(seg1BFormat->TimeToPosition(0.0f));
			seg1b->SetExitCue(seg1BFormat->TimeToPosition(4.0f));
			ppSegment* seg2a = this->ims->CreateSegment("seg2a");
			seg2a->SetEntryCue(seg2AFormat->TimeToPosition(2.0f));
			seg2a->SetExitCue(seg2AFormat->TimeToPosition(4.0f));
			ppSegment* seg2b = this->ims->CreateSegment("seg2b");
			seg2b->SetEntryCue(seg2BFormat->TimeToPosition(0.0f));
			seg2b->SetExitCue(seg2BFormat->TimeToPosition(4.0f));
			ppSegment* seg3a = this->ims->CreateSegment("seg3a");
			seg3a->SetEntryCue(seg3AFormat->TimeToPosition(2.0f));
			seg3a->SetExitCue(seg3AFormat->TimeToPosition(4.0f));
			ppSegment* seg3b = this->ims->CreateSegment("seg3b");
			seg3b->SetEntryCue(seg3BFormat->TimeToPosition(0.0f));
			seg3b->SetExitCue(seg3BFormat->TimeToPosition(4.0f));
			ppSegment* seg4a = this->ims->CreateSegment("seg4a");
			seg4a->SetEntryCue(seg4AFormat->TimeToPosition(2.0f));
			seg4a->SetExitCue(seg4AFormat->TimeToPosition(4.0f));
			ppSegment* seg4b = this->ims->CreateSegment("seg4b");
			seg4b->SetEntryCue(seg4BFormat->TimeToPosition(0.0f));
			seg4b->SetExitCue(seg4BFormat->TimeToPosition(4.0f));
			ppSegment* seg5a = this->ims->CreateSegment("seg5a");
			seg5a->SetEntryCue(seg5AFormat->TimeToPosition(2.0f));
			seg5a->SetExitCue(seg5AFormat->TimeToPosition(4.0f));
			ppSegment* seg5b = this->ims->CreateSegment("seg5b");
			seg5b->SetEntryCue(seg5BFormat->TimeToPosition(0.0f));
			seg5b->SetExitCue(seg5BFormat->TimeToPosition(4.0f));
			ppSegment* seg6a = this->ims->CreateSegment("seg6a");
			seg6a->SetEntryCue(seg6AFormat->TimeToPosition(2.0f));
			seg6a->SetExitCue(seg6AFormat->TimeToPosition(4.0f));
			ppSegment* seg6b = this->ims->CreateSegment("seg6b");
			seg6b->SetEntryCue(seg6BFormat->TimeToPosition(0.0f));
			seg6b->SetExitCue(seg6BFormat->TimeToPosition(4.0f));
			ppSegment* seg7a = this->ims->CreateSegment("seg7a");
			seg7a->SetEntryCue(seg7AFormat->TimeToPosition(0.0f));
			seg7a->SetExitCue(seg7AFormat->TimeToPosition(4.0f));
			ppSegment* seg7b = this->ims->CreateSegment("seg7b");
			seg7b->SetEntryCue(seg7BFormat->TimeToPosition(0.0f));
			seg7b->SetExitCue(seg7BFormat->TimeToPosition(4.0f));

			//Segment 1
			seg1a->AddSound(seg1ASound);
			seg1b->AddSound(seg1BSound);
			//Segment 2
			seg2a->AddSound(seg2ASound);
			seg2b->AddSound(seg2BSound);
			//Segment 3
			seg3a->AddSound(seg3ASound);
			seg3b->AddSound(seg3BSound);
			//Segment 4
			seg4a->AddSound(seg4ASound);
			seg4b->AddSound(seg4BSound);
			//Segment 5
			seg5a->AddSound(seg5ASound);
			seg5b->AddSound(seg5BSound);
			//Segment 6
			seg6a->AddSound(seg6ASound);
			seg6b->AddSound(seg6BSound);
			//Segment 7
			seg7a->AddSound(seg7ASound);
			seg7b->AddSound(seg7BSound);

			ppPlaylist* seg1playlist = this->ims->CreatePlaylist("seg1playlist");
			seg1playlist->AddSound(seg1a);
			seg1playlist->AddSound(seg1b);
			seg1playlist->SetPlayOrder(ppPlaylistPlayOrder::SHUFFLE_STEP);
			ppPlaylist* seg2playlist = this->ims->CreatePlaylist("seg2playlist");
			seg2playlist->AddSound(seg2a);
			seg2playlist->AddSound(seg2b);
			seg2playlist->SetPlayOrder(ppPlaylistPlayOrder::SHUFFLE_STEP);
			ppPlaylist* seg3playlist = this->ims->CreatePlaylist("seg3playlist");
			seg3playlist->AddSound(seg3a);
			seg3playlist->AddSound(seg3b);
			seg3playlist->SetPlayOrder(ppPlaylistPlayOrder::SEQUENCE_STEP);
			ppPlaylist* seg4playlist = this->ims->CreatePlaylist("seg4playlist");
			seg4playlist->AddSound(seg4a);
			seg4playlist->AddSound(seg4b);
			seg4playlist->SetPlayOrder(ppPlaylistPlayOrder::SEQUENCE_STEP);
			ppPlaylist* seg5playlist = this->ims->CreatePlaylist("seg5playlist");
			seg5playlist->AddSound(seg5a);
			seg5playlist->AddSound(seg5b);
			seg5playlist->SetPlayOrder(ppPlaylistPlayOrder::SHUFFLE_CONTINUOUS);
			ppPlaylist* seg6playlist = this->ims->CreatePlaylist("seg6playlist");
			seg6playlist->AddSound(seg6a);
			seg6playlist->AddSound(seg6b);
			seg6playlist->SetPlayOrder(ppPlaylistPlayOrder::SHUFFLE_CONTINUOUS);
			ppPlaylist* seg7playlist = this->ims->CreatePlaylist("seg7playlist");
			seg7playlist->AddSound(seg7a);
			seg7playlist->AddSound(seg7b);

			ppPlaylist* playlist = this->ims->CreatePlaylist("playlist");
			playlist->AddSound(seg1playlist);
			playlist->AddSound(seg2playlist);
			playlist->AddSound(seg3playlist);
			playlist->AddSound(seg4playlist);
			playlist->AddSound(seg5playlist);
			playlist->AddSound(seg6playlist);
			playlist->AddSound(seg7playlist);

			playlist->SetLoop(-1);

			playlist->SetSize(300, 250);
			playlist->SetLocation(10, 150);
			seg1playlist->SetSize(300, 250);
			seg1playlist->SetLocation(330, 150);
			seg2playlist->SetSize(300, 250);
			seg2playlist->SetLocation(330, 150);
			seg3playlist->SetSize(300, 250);
			seg3playlist->SetLocation(330, 150);
			seg4playlist->SetSize(300, 250);
			seg4playlist->SetLocation(330, 150);
			seg5playlist->SetSize(300, 250);
			seg5playlist->SetLocation(330, 150);
			seg6playlist->SetSize(300, 250);
			seg6playlist->SetLocation(330, 150);
			seg7playlist->SetSize(300, 250);
			seg7playlist->SetLocation(330, 150);
			this->gui->AddControl(playlist);
			this->gui->AddControl(seg1playlist);
			this->gui->AddControl(seg2playlist);
			this->gui->AddControl(seg3playlist);
			this->gui->AddControl(seg4playlist);
			this->gui->AddControl(seg5playlist);
			this->gui->AddControl(seg6playlist);
			this->gui->AddControl(seg7playlist);
		}else{
			ppPlaylist* playlist = (ppPlaylist*)this->ims->GetSound("playlist");

			msg << "\n\nPress 'P' to ";

			if(playlist){
				if(playlist->IsPlaying()){
					msg << "pause";
				}else{
					msg << "play";
				}
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
						if(this->playlist_track == 0){
							this->playlist_track = playlist->GetTotalSound();
						}
						this->playlist_track--;
					}else if(input->IsKeyDown(SDL_SCANCODE_DOWN, 10)){
						this->playlist_track++;
						this->playlist_track %= playlist->GetTotalSound();
					}else if(input->IsKeyDown(SDL_SCANCODE_SPACE, 10)){
						if(sound->IsPlaying()){
							sound->Stop();
						}else{
							sound->Play();
						}
					}
					for(int i=0;i<playlist->GetTotalSound();i++){
						ppGenericSound* sound = playlist->GetSoundAtIndex(i);
						sound->SetVisible(i==this->playlist_track);
					}
					if(input->IsKeyDown(SDL_SCANCODE_P, 10)){
						playlist->GetSoundAtIndex(this->playlist_track)->Stop();
						playlist->Play();
					}
				}else{
					for(int i=playlist->GetTotalSound()-1;i>=0;i--){
						ppGenericSound* sound = playlist->GetSoundAtIndex(i);
						sound->SetVisible(false);
					}
					playlist->GetPlayingSound()->SetVisible(true);
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
	}else if(this->test == 6){
		////////////////////
		//     TEST 6     //
		// MUSIC NOTATION //
		////////////////////
		if(!this->ims->GetSound("sound")){
			ppFormat* soundFormat = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/MusicGameplay/Music_Gameplay.wav");
			ppSound* sound = this->ims->CreateSound("sound", soundFormat);
			sound->SetLoop(-1);
			sound->SetSize(300, 30);
			sound->SetLocation(10, 200);
			this->gui->AddControl(sound);
		}else{
			ppSound* sound = (ppSound*)this->ims->GetSound("sound");

			msg << "\nTempo: " << sound->GetTempo() << " BPM";
			msg << "\nTime Signature: " << sound->GetBeatPerBar() << "/" << sound->GetNoteValue();
			msg << "\n\nPress 'P' to ";

			if(sound){
				if(sound->IsPlaying()){
					msg << "pause";
				}else{
					msg << "play";
				}
				if(sound->IsStop()){
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
					msg << "Beat " << (sound->GetCurrentBar()+1) << "-" << (sound->GetCurrentBeat()+1) << " [" << sound->GetTotalBeat() << "]";
				}
			}
		}
	}else if(this->test == 7){
		//////////////////////
		//      TEST 7      //
		// MUSIC TRANSITION //
		//////////////////////
		if(!this->ims->GetSwitch("level")){
			this->playlist_track = 0;

			/////////////////
			// Fight Music //
			/////////////////
			ppFormat* seg1AFormat = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/SampleProject/Attack01_Seg 01a (A) [light groove].wav");
			ppFormat* seg1BFormat = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/SampleProject/Attack02_Seg 01b (B) [light groove].wav");

			ppFormat* seg2AFormat = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/SampleProject/Attack03_Seg 01c (A) [light groove].wav");
			ppFormat* seg2BFormat = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/SampleProject/Attack04_Seg 01d (B) [light groove].wav");

			ppFormat* seg3AFormat = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/SampleProject/Attack05_Seg 02a (A) [medium groove + bass].wav");
			ppFormat* seg3BFormat = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/SampleProject/Attack06_Seg 02b (B) [medium groove + bass].wav");

			ppFormat* seg4AFormat = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/SampleProject/Attack07_Seg 02c (A) [medium groove + bass].wav");
			ppFormat* seg4BFormat = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/SampleProject/Attack08_Seg 02d (B) [medium groove + bass].wav");

			ppFormat* seg5AFormat = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/SampleProject/Attack09_Seg 03a (A) [full groove + horns].wav");
			ppFormat* seg5BFormat = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/SampleProject/Attack10_Seg 03b (B) [full groove + horns].wav");

			ppFormat* seg6AFormat = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/SampleProject/Attack11_Seg 03c (A) [full groove + horns].wav");
			ppFormat* seg6BFormat = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/SampleProject/Attack12_Seg 03d (B) [full groove + horns].wav");

			ppFormat* seg7AFormat = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/SampleProject/Attack18_Seg 04e [break - full].wav");
			ppFormat* seg7BFormat = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/SampleProject/Attack19_Seg 04f [break - full].wav");

			// Sounds
			ppSound* seg1ASound = this->ims->CreateSound("seg1ASound", seg1AFormat);
			ppSound* seg1BSound = this->ims->CreateSound("seg1BSound", seg1BFormat);
			ppSound* seg2ASound = this->ims->CreateSound("seg2ASound", seg2AFormat);
			ppSound* seg2BSound = this->ims->CreateSound("seg2BSound", seg2BFormat);
			ppSound* seg3ASound = this->ims->CreateSound("seg3ASound", seg3AFormat);
			ppSound* seg3BSound = this->ims->CreateSound("seg3BSound", seg3BFormat);
			ppSound* seg4ASound = this->ims->CreateSound("seg4ASound", seg4AFormat);
			ppSound* seg4BSound = this->ims->CreateSound("seg4BSound", seg4BFormat);
			ppSound* seg5ASound = this->ims->CreateSound("seg5ASound", seg5AFormat);
			ppSound* seg5BSound = this->ims->CreateSound("seg5BSound", seg5BFormat);
			ppSound* seg6ASound = this->ims->CreateSound("seg6ASound", seg6AFormat);
			ppSound* seg6BSound = this->ims->CreateSound("seg6BSound", seg6BFormat);
			ppSound* seg7ASound = this->ims->CreateSound("seg7ASound", seg7AFormat);
			ppSound* seg7BSound = this->ims->CreateSound("seg7BSound", seg7BFormat);

			// Segment Setups
			ppSegment* seg1a = this->ims->CreateSegment("seg1a");
			seg1a->SetEntryCue(seg1AFormat->TimeToPosition(2.0f));
			seg1a->SetExitCue(seg1AFormat->TimeToPosition(4.0f));
			ppSegment* seg1b = this->ims->CreateSegment("seg1b");
			seg1b->SetEntryCue(seg1BFormat->TimeToPosition(0.0f));
			seg1b->SetExitCue(seg1BFormat->TimeToPosition(4.0f));
			ppSegment* seg2a = this->ims->CreateSegment("seg2a");
			seg2a->SetEntryCue(seg2AFormat->TimeToPosition(2.0f));
			seg2a->SetExitCue(seg2AFormat->TimeToPosition(4.0f));
			ppSegment* seg2b = this->ims->CreateSegment("seg2b");
			seg2b->SetEntryCue(seg2BFormat->TimeToPosition(0.0f));
			seg2b->SetExitCue(seg2BFormat->TimeToPosition(4.0f));
			ppSegment* seg3a = this->ims->CreateSegment("seg3a");
			seg3a->SetEntryCue(seg3AFormat->TimeToPosition(2.0f));
			seg3a->SetExitCue(seg3AFormat->TimeToPosition(4.0f));
			ppSegment* seg3b = this->ims->CreateSegment("seg3b");
			seg3b->SetEntryCue(seg3BFormat->TimeToPosition(0.0f));
			seg3b->SetExitCue(seg3BFormat->TimeToPosition(4.0f));
			ppSegment* seg4a = this->ims->CreateSegment("seg4a");
			seg4a->SetEntryCue(seg4AFormat->TimeToPosition(2.0f));
			seg4a->SetExitCue(seg4AFormat->TimeToPosition(4.0f));
			ppSegment* seg4b = this->ims->CreateSegment("seg4b");
			seg4b->SetEntryCue(seg4BFormat->TimeToPosition(0.0f));
			seg4b->SetExitCue(seg4BFormat->TimeToPosition(4.0f));
			ppSegment* seg5a = this->ims->CreateSegment("seg5a");
			seg5a->SetEntryCue(seg5AFormat->TimeToPosition(2.0f));
			seg5a->SetExitCue(seg5AFormat->TimeToPosition(4.0f));
			ppSegment* seg5b = this->ims->CreateSegment("seg5b");
			seg5b->SetEntryCue(seg5BFormat->TimeToPosition(0.0f));
			seg5b->SetExitCue(seg5BFormat->TimeToPosition(4.0f));
			ppSegment* seg6a = this->ims->CreateSegment("seg6a");
			seg6a->SetEntryCue(seg6AFormat->TimeToPosition(2.0f));
			seg6a->SetExitCue(seg6AFormat->TimeToPosition(4.0f));
			ppSegment* seg6b = this->ims->CreateSegment("seg6b");
			seg6b->SetEntryCue(seg6BFormat->TimeToPosition(0.0f));
			seg6b->SetExitCue(seg6BFormat->TimeToPosition(4.0f));
			ppSegment* seg7a = this->ims->CreateSegment("seg7a");
			seg7a->SetEntryCue(seg7AFormat->TimeToPosition(0.0f));
			seg7a->SetExitCue(seg7AFormat->TimeToPosition(4.0f));
			ppSegment* seg7b = this->ims->CreateSegment("seg7b");
			seg7b->SetEntryCue(seg7BFormat->TimeToPosition(0.0f));
			seg7b->SetExitCue(seg7BFormat->TimeToPosition(4.0f));

			//Segment 1
			seg1a->AddSound(seg1ASound);
			seg1b->AddSound(seg1BSound);
			//Segment 2
			seg2a->AddSound(seg2ASound);
			seg2b->AddSound(seg2BSound);
			//Segment 3
			seg3a->AddSound(seg3ASound);
			seg3b->AddSound(seg3BSound);
			//Segment 4
			seg4a->AddSound(seg4ASound);
			seg4b->AddSound(seg4BSound);
			//Segment 5
			seg5a->AddSound(seg5ASound);
			seg5b->AddSound(seg5BSound);
			//Segment 6
			seg6a->AddSound(seg6ASound);
			seg6b->AddSound(seg6BSound);
			//Segment 7
			seg7a->AddSound(seg7ASound);
			seg7b->AddSound(seg7BSound);

			ppPlaylist* seg1playlist = this->ims->CreatePlaylist("seg1playlist");
			seg1playlist->AddSound(seg1a);
			seg1playlist->AddSound(seg1b);
			ppPlaylist* seg2playlist = this->ims->CreatePlaylist("seg2playlist");
			seg2playlist->AddSound(seg2a);
			seg2playlist->AddSound(seg2b);
			ppPlaylist* seg3playlist = this->ims->CreatePlaylist("seg3playlist");
			seg3playlist->AddSound(seg3a);
			seg3playlist->AddSound(seg3b);
			ppPlaylist* seg4playlist = this->ims->CreatePlaylist("seg4playlist");
			seg4playlist->AddSound(seg4a);
			seg4playlist->AddSound(seg4b);
			ppPlaylist* seg5playlist = this->ims->CreatePlaylist("seg5playlist");
			seg5playlist->AddSound(seg5a);
			seg5playlist->AddSound(seg5b);
			ppPlaylist* seg6playlist = this->ims->CreatePlaylist("seg6playlist");
			seg6playlist->AddSound(seg6a);
			seg6playlist->AddSound(seg6b);
			ppPlaylist* seg7playlist = this->ims->CreatePlaylist("seg7playlist");
			seg7playlist->AddSound(seg7a);
			seg7playlist->AddSound(seg7b);

			ppPlaylist* fightPlaylist = this->ims->CreatePlaylist("fight");
			fightPlaylist->AddSound(seg1playlist);
			fightPlaylist->AddSound(seg2playlist);
			fightPlaylist->AddSound(seg3playlist);
			fightPlaylist->AddSound(seg4playlist);
			fightPlaylist->AddSound(seg5playlist);
			fightPlaylist->AddSound(seg6playlist);
			fightPlaylist->AddSound(seg7playlist);

			fightPlaylist->SetLoop(-1);
			fightPlaylist->SetLocation(10, 150);
			fightPlaylist->SetSize(300, 300);

			//////////////////
			// Stress Music //
			//////////////////
			// Segment 1 Formats
			ppFormat* drumSeg1Format = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/SampleProject/Stealth_Drums_AmbientDrum&Ride1_Seg1_01.wav");
			ppFormat* bassSeg1Format = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/SampleProject/Stress_Bass_MainBassMelody_Seg1_01.wav");
			ppFormat* stringSeg1Format = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/SampleProject/Stress_Orchestra_StringMelody_Seg1_01.wav");
			ppFormat* percussionSeg1Format = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/SampleProject/Stress_Percussion_BigDrums&Cymbals_Seg1_01.wav");
			ppFormat* variousSeg1Format = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/SampleProject/Stress_Various_DoubleTimeElements_Seg1_01.wav");

			// Segment 2 Formats
			ppFormat* brassSeg2Format = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/SampleProject/Stealth_Orchestra_BrassPiano&Ride1_Seg2_01.wav");
			ppFormat* bassSeg2Format = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/SampleProject/Stress_Bass_MainBassMelody_Seg2_01.wav");
			ppFormat* stringSeg2Format = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/SampleProject/Stress_Orchestra_StringMelody_Seg2_01.wav");
			ppFormat* percussionSeg2Format = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/SampleProject/Stress_Percussion_BigDrums&Cymbals_Seg2_01.wav");
			ppFormat* variousSeg2Format = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/SampleProject/Stress_Various_DoubleTimeElements_Seg2_01.wav");

			// Segment 3 Formats
			ppFormat* drumSeg3Format = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/SampleProject/Stealth_Drums_AmbientDrum&Ride1_Seg3_01.wav");
			ppFormat* bassSeg3Format = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/SampleProject/Stress_Bass_MainBassMelody_Seg3_01.wav");
			ppFormat* stringSeg3Format = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/SampleProject/Stress_Orchestra_StringMelody_Seg3_01.wav");
			ppFormat* percussionSeg3Format = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/SampleProject/Stress_Percussion_BigDrums&Cymbals_Seg3_01.wav");
			ppFormat* variousSeg3Format = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/SampleProject/Stress_Various_DoubleTimeElements_Seg3_01.wav");

			// Segment 1 Sounds
			ppSound* drumSeg1Sound = this->ims->CreateSound("drumSeg1Sound", drumSeg1Format);
			ppSound* bassSeg1Sound = this->ims->CreateSound("bassSeg1Sound", bassSeg1Format);
			ppSound* stringSeg1Sound = this->ims->CreateSound("stringSeg1Sound", stringSeg1Format);
			ppSound* percussionSeg1Sound = this->ims->CreateSound("percussionSeg1Sound", percussionSeg1Format);
			ppSound* variousSeg1Sound = this->ims->CreateSound("variousSeg1Sound", variousSeg1Format);

			drumSeg1Sound->SetOffset(drumSeg1Format->TimeToPosition(1.29f));
			bassSeg1Sound->SetOffset(bassSeg1Format->TimeToPosition(1.29f));
			stringSeg1Sound->SetOffset(stringSeg1Format->TimeToPosition(1.29f));
			variousSeg1Sound->SetOffset(variousSeg1Format->TimeToPosition(1.29f));

			// Segment 2 Sounds
			ppSound* brassSeg2Sound = this->ims->CreateSound("brassSeg2Sound", brassSeg2Format);
			ppSound* bassSeg2Sound = this->ims->CreateSound("bassSeg2Sound", bassSeg2Format);
			ppSound* stringSeg2Sound = this->ims->CreateSound("stringSeg2Sound", stringSeg2Format);
			ppSound* percussionSeg2Sound = this->ims->CreateSound("percussionSeg2Sound", percussionSeg2Format);
			ppSound* variousSeg2Sound = this->ims->CreateSound("variousSeg2Sound", variousSeg2Format);

			brassSeg2Sound->SetOffset(brassSeg2Format->TimeToPosition(1.325f));
			brassSeg2Sound->SetClipStart(brassSeg2Format->TimeToPosition(2.6f));
			bassSeg2Sound->SetOffset(bassSeg2Format->TimeToPosition(1.325f));
			stringSeg2Sound->SetOffset(stringSeg2Format->TimeToPosition(1.325f));
			variousSeg2Sound->SetOffset(variousSeg2Format->TimeToPosition(1.325f));

			// Segment 3 Sounds
			ppSound* drumSeg3Sound = this->ims->CreateSound("drumSeg3Sound", drumSeg3Format);
			ppSound* bassSeg3Sound = this->ims->CreateSound("bassSeg3Sound", bassSeg3Format);
			ppSound* stringSeg3Sound = this->ims->CreateSound("stringSeg3Sound", stringSeg3Format);
			ppSound* percussionSeg3Sound = this->ims->CreateSound("percussionSeg3Sound", percussionSeg3Format);
			ppSound* variousSeg3Sound = this->ims->CreateSound("variousSeg3Sound", variousSeg3Format);

			drumSeg3Sound->SetOffset(drumSeg3Format->TimeToPosition(1.29f));
			drumSeg3Sound->SetClipStart(drumSeg3Format->TimeToPosition(2.6f));
			bassSeg3Sound->SetOffset(bassSeg3Format->TimeToPosition(1.29f));
			stringSeg3Sound->SetOffset(stringSeg3Format->TimeToPosition(1.29f));
			variousSeg3Sound->SetOffset(variousSeg3Format->TimeToPosition(1.29f));

			// Segment Setups
			ppSegment* seg1 = this->ims->CreateSegment("seg1");
			seg1->SetEntryCue(percussionSeg1Format->TimeToPosition(1.29f));
			seg1->SetExitCue(percussionSeg1Format->TimeToPosition(21.31f));
			ppSegment* seg2 = this->ims->CreateSegment("seg2");
			seg2->SetEntryCue(percussionSeg2Format->TimeToPosition(1.325f));
			seg2->SetExitCue(percussionSeg2Format->TimeToPosition(21.325f));
			ppSegment* seg3 = this->ims->CreateSegment("seg3");
			seg3->SetEntryCue(percussionSeg3Format->TimeToPosition(1.29f));
			seg3->SetExitCue(percussionSeg3Format->TimeToPosition(21.31f));

			//Segment 1
			seg1->AddSound(drumSeg1Sound);
			seg1->AddSound(bassSeg1Sound);
			seg1->AddSound(stringSeg1Sound);
			seg1->AddSound(percussionSeg1Sound);
			seg1->AddSound(variousSeg1Sound);
			//Segment 2
			seg2->AddSound(brassSeg2Sound);
			seg2->AddSound(bassSeg2Sound);
			seg2->AddSound(stringSeg2Sound);
			seg2->AddSound(percussionSeg2Sound);
			seg2->AddSound(variousSeg2Sound);
			//Segment 3
			seg3->AddSound(drumSeg3Sound);
			seg3->AddSound(bassSeg3Sound);
			seg3->AddSound(stringSeg3Sound);
			seg3->AddSound(percussionSeg3Sound);
			seg3->AddSound(variousSeg3Sound);

			ppPlaylist* stressPlaylist = this->ims->CreatePlaylist("stress");
			stressPlaylist->AddSound(seg1);
			stressPlaylist->AddSound(seg2);
			stressPlaylist->AddSound(seg3);

			stressPlaylist->SetLoop(-1);
			stressPlaylist->SetLocation(310, 150);
			stressPlaylist->SetSize(300, 300);
			stressPlaylist->SetTempo(90);

			//////////////////////
			// Transition Music //
			//////////////////////
			ppFormat* transitionFormat = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/SampleProject/Fight to Stress Transition.wav");
			ppSound* transitionSound = this->ims->CreateSound("transitionSound", transitionFormat);
			ppSegment* transitionSeg = this->ims->CreateSegment("transitionTrack");
			transitionSeg->AddSound(transitionSound);
			// transitionSeg->SetEntryCue(transitionFormat->TimeToPosition(0.0f));
			transitionSeg->SetExitCue(transitionFormat->TimeToPosition(14.15f));

			///////////////////
			// Stinger Music //
			///////////////////
			ppFormat* stingerFormat = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/SampleProject/Interlude_Theme_01.wav");
			ppSound* stingerSound = this->ims->CreateSound("stingerSound", stingerFormat);
			ppSegment* stingerSeg = this->ims->CreateSegment("stingerTrack");
			stingerSeg->AddSound(stingerSound);
			stingerSeg->SetLocation(100, 420);
			stingerSeg->SetSize(300, 30);

			//////////////////////

			ppSwitch* sw = this->ims->CreateSwitch("level");
			sw->SetLocation(10, 100);
			sw->SetSize(300, 30);

			ppTransition* fightToStress = sw->CreateTransition(0, fightPlaylist, stressPlaylist);
			fightToStress->SetSourceCurve(NULL); // No Fade
			fightToStress->SetDestinationCurve(NULL); // No Fade
			fightToStress->SetTransitionTrack(transitionSeg);
			fightToStress->SetSourcePosition(ppTransitionSourcePosition::NEXT_BAR);

			ppTransition* stressToFight = sw->CreateTransition(0, stressPlaylist, fightPlaylist);
			// stressToFight->SetSourceOffset(2.5f);
			// stressToFight->SetDestinationOffset(2.5f);
			stressToFight->SetDestinationPosition(ppTransitionDestinationPosition::SAME_TIME);

			sw->CreateStinger("bonus", stingerSeg, ppStingerTriggerPosition::NEXT_BAR);

			this->gui->AddControl(sw);
			this->gui->AddControl(stressPlaylist);
			this->gui->AddControl(fightPlaylist);
			this->gui->AddControl(stingerSeg);
		}else{
			ppSwitch* sw = this->ims->GetSwitch("level");

			if(sw){
				ppStinger* stinger = sw->GetStinger("bonus");
				ppGenericSound* stingerSeg = this->ims->GetSound("stingerTrack");
				if(stinger && stingerSeg){
					stingerSeg->SetVisible(stinger->IsPreparing() || stinger->IsTriggering());
				}
				if(this->playlist_track == 0){
					msg << "\nCurrent State: -Stop-";
				}else{
					msg << "\nCurrent State: " << sw->GetCurrentState();
				}
				if(input->IsKeyDown(SDL_SCANCODE_SPACE, 10)){
					sw->TriggerStinger("bonus");
				}
				if(input->IsKeyDown(SDL_SCANCODE_UP, 10)){
					if(this->playlist_track == 0){
						this->playlist_track = 2;
						sw->SwitchState("stress");
					}else if(this->playlist_track == 1){
						this->playlist_track = 0;
						sw->SwitchState("");
					}else if(this->playlist_track == 2){
						this->playlist_track = 1;
						sw->SwitchState("fight");
					}
				}else if(input->IsKeyDown(SDL_SCANCODE_DOWN, 10)){
					if(this->playlist_track == 0){
						this->playlist_track = 1;
						sw->SwitchState("fight");
					}else if(this->playlist_track == 1){
						this->playlist_track = 2;
						sw->SwitchState("stress");
					}else if(this->playlist_track == 2){
						this->playlist_track = 0;
						sw->SwitchState("");
					}
				}
			}
		}
	}
	label->SetText(msg.str());
	this->gui->Update(input);
}
