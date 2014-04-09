#ifndef SOUND_HEADER
#define SOUND_HEADER

#include <fstream>
#include <string>
#include "Includes.h"
#include "IMS.h"
#include "Filter.h"
#include "Utils.h"

class IMS;
class Sound {
private:
	bool justLoop;
	bool preload;
	bool loop;
	float speed;
	float volumn;
	int bufferSize;
	int totalTrack;
	int track;
	ALuint sourceID;
	Filter* filter;
	ALuint bufferSet[2];
	int bufferProcessed;
	std::string filename;
	int dataReadPosition;
	int dataStartPosition;
	int dataPositionOffset;

	std::string errorMsg;

	ALuint format;
	int audioFormat;
	int channels;
	int targetChannels;
	int sampleRate;
	int byteRate;
	int bitPerSample;
	int dataSize;
	std::ifstream filePointer;
	float ByteToSecond(int byte);
	int SecondToByte(float sec);
	void ReadData(std::ifstream &filePointer, char *dataBuffer, int bufferSize, ALuint &bufferID);
	void GetWaveChunkInfo(std::ifstream &filePointer, char *chunkName, int &chunkSize);
	int GetTotalBuffer(int dataSize, bool countCurrent);
public:
	Sound(IMS* ims);
	~Sound();
	int LoadWaveFile(const char *filename, bool stereo);
	void Preload();
	void Preload(int track);
	void Preload(int track, bool skip);
	void ApplyFilter(Filter* filter);
	void Play();
	void Play(int track);
	void Pause();
	void Stop();
	void SeekPosition(int targetPosition);
	void SeekPosition(int targetPosition, int track);
	void SeekTime(float targetTime);
	void SeekTime(float targetTime, int track);
	void SetSpeed(float speed);
	void SetVolumn(float vol);
	void SetLoop(bool loop);
	bool IsPlaying();
	bool IsPause();
	bool IsStop();
	bool IsLoop();
	bool IsJustLoop();
	float GetCurrentTime();
	float GetTimeLength();
	int GetCurrentPosition();
	int GetPositionLength();
	int GetAudioFormat();
	int GetChannels();
	int GetTargetChannels();
	int GetSampleRate();
	int GetByteRate();
	int GetBitPerSample();
	int GetCurrentTrack();
	int GetTotalTrack();
	float GetSpeed();
	float GetVolumn();
	std::string GetFileName();
	void Update();
};

#endif
