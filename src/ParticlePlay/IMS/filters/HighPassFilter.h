#ifndef HIGHPASSFILTER_HEADER
#define HIGHPASSFILTER_HEADER

#include "../IMS.h"
#include "../Filter.h"

class ppIMS;
class ppHighPassFilter : public ppFilter{
private:
	float gain;
	float gainlf;
public:
	ppHighPassFilter(ppIMS* ims);
	void InitFilter();
	void SetGain(float val);
	void SetGainLF(float val);
	float GetGainLF();
};

#endif
