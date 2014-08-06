#ifndef WAVEFORMAT_HEADER
#define WAVEFORMAT_HEADER

#include <string>
#include "../Utils.hpp"
#include "Format.hpp"

class ppWaveFormat : public ppFormat {
protected:
	int audioChannels;
	int audioTracks;
	int bitPerSample;
	int sampleRate;
	int audioDataSize;
	ALuint audioFormat;
	Sint64 startReadPosition;
	void GetWaveChunkInfo(SDL_RWops *filePointer, char *chunkName, int &chunkSize);
public:
	ppWaveFormat(ppIMS* ims);
	virtual int Init(const char *filename, bool stereo);
	virtual Sint64 Read(char *bufferData, Sint64 position, Sint64 size, int track);
	virtual Sint64 ActualPosition(Sint64 relativePosition);
	virtual Sint64 GetPositionLength();
	virtual float PositionToTime(Sint64 position);
	virtual Sint64 TimeToPosition(float time);
	virtual int GetSampleRate();
	virtual ALuint GetFormat();
	virtual int GetTotalTrack();
};

#endif
