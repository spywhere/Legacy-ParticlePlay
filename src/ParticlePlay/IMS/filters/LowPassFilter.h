#ifndef LOWPASSFILTER_HEADER
#define LOWPASSFILTER_HEADER

#include "../Filter.h"

class LowPassFilter : public Filter{
private:
	float gain;
	float gainhf;
public:
	LowPassFilter();
	void InitFilter();
	void SetGain(float val);
	void SetGainHF(float val);
	float GetGainHF();
};

#endif
