#include "Randomizer.hpp"

#include <ctime>
#include <cstdlib>

ppRandomizer::ppRandomizer(){
	this->SetSeed(std::time(0));
}

void ppRandomizer::SetSeed(unsigned seed){
	this->seed = seed;
	this->ResetSeed();
}

void ppRandomizer::ResetSeed(){
	std::srand(this->GetSeed());
}

unsigned ppRandomizer::GetSeed(){
	return this->seed;
}

float ppRandomizer::NextFloat(){
	return (float)std::rand()/(float)RAND_MAX;
}

float ppRandomizer::NextFloat(float min, float max){
	return min+this->NextFloat()*(max-min);
}

float ppRandomizer::NextFloat(float max){
	return this->NextFloat(0, max);
}

int ppRandomizer::NextInt(int min, int max){
	return min+std::rand()%(max-min);
}

int ppRandomizer::NextInt(int max){
	return this->NextInt(0, max);
}

bool ppRandomizer::NextBool(){
	return this->NextFloat() < 0.5f;
}
