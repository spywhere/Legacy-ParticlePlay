#ifndef EMPTYFORMAT_HEADER
#define EMPTYFORMAT_HEADER

#include <string>
#include <ParticlePlay/IMS/Utils.hpp>
#include <ParticlePlay/IMS/Format/Format.hpp>

class ppEmptyFormat : public ppFormat {
protected:
	int audioChannels;
	int audioTracks;
	int bitPerSample;
	int sampleRate;
	Sint64 length;
	ALuint audioFormat;
	ppFormat* sourceAudioFormat;
public:
	ppEmptyFormat(ppIMS* ims, Sint64 length, ppFormat* audioFormat);
	virtual int Init(const char *filename, bool stereo);
	virtual Sint64 Read(char *bufferData, Sint64 position, Sint64 size, int track);
	virtual Sint64 ActualPosition(Sint64 relativePosition);
	virtual Sint64 RelativePosition(Sint64 actualPosition);
	virtual Sint64 GetPositionLength();
	virtual float PositionToTime(Sint64 position);
	virtual Sint64 TimeToPosition(float time);
	virtual int GetSampleRate();
	virtual ALuint GetFormat();
	virtual int GetTotalTrack();
};

#endif
