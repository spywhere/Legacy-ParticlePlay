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
	virtual int Init(const char *filename, bool stereo);
	// virtual void Read(int position)=0;
	// virtual void Read(int position, int track)=0;
	virtual int GetPositionLength()=0;
	virtual float PositionToTime(int position)=0;
	virtual int TimeToPosition(float time)=0;
	virtual int GetSampleRate()=0;
	virtual ALuint GetFormat()=0;
	virtual int GetTotalTrack()=0;
	virtual bool IsStereo();
	virtual std::string GetFileName();
};

#endif
