#ifndef LOWPASSFILTER_HEADER
#define LOWPASSFILTER_HEADER

#include "../Filter.h"

class ppLowPassFilter : public ppFilter{
private:
	float gain;
	float gainhf;
public:
	ppLowPassFilter();
	void InitFilter();
	void SetGain(float val);
	void SetGainHF(float val);
	float GetGainHF();
};

#endif
