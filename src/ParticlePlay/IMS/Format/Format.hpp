#ifndef FORMAT_HEADER
#define FORMAT_HEADER

#include <string>
#include "../../Includes.hpp"

class ppIMS;
class ppFormat {
protected:
	bool stereo;
	std::string filename;
	SDL_RWops* filePointer;
public:
	ppFormat(ppIMS* ims);
	virtual ~ppFormat();
	virtual int Init(const char *filename, bool stereo);
	virtual Sint64 Read(char *bufferData, Sint64 position, Sint64 size, int track)=0;
	virtual Sint64 Read(char *bufferData, Sint64 position, Sint64 size);
	virtual Sint64 ActualPosition(Sint64 relativePosition)=0;
	virtual Sint64 RelativePosition(Sint64 actualPosition)=0;
	virtual Sint64 GetPositionLength()=0;
	virtual float PositionToTime(Sint64 position)=0;
	virtual Sint64 TimeToPosition(float time)=0;
	virtual int GetSampleRate()=0;
	virtual ALuint GetFormat()=0;
	virtual int GetTotalTrack()=0;
	virtual bool IsStereo();
	virtual std::string GetFileName();
};

#endif
