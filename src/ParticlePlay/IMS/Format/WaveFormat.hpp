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
	void GetWaveChunkInfo(SDL_RWops *filePointer, char *chunkName, int &chunkSize);
public:
	ppWaveFormat(ppIMS* ims);
	virtual int Init(const char *filename, bool stereo);
	// virtual void Read(int position);
	// virtual void Read(int position, int track);
	virtual int GetPositionLength();
	virtual float PositionToTime(int position);
	virtual int TimeToPosition(float time);
	virtual int GetSampleRate();
	virtual ALuint GetFormat();
	virtual int GetTotalTrack();
};

#endif
