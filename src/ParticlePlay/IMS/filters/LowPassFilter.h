#ifndef LOWPASSFILTER_HEADER
#define LOWPASSFILTER_HEADER

#include "../IMS.h"
#include "../Filter.h"

class ppIMS;
class ppLowPassFilter : public ppFilter{
private:
	float gain;
	float gainhf;
public:
	ppLowPassFilter(ppIMS* ims);
	void InitFilter();
	void SetGain(float val);
	void SetGainHF(float val);
	float GetGainHF();
};

#endif
