#ifndef HIGHPASSFILTER_HEADER
#define HIGHPASSFILTER_HEADER

#include "../Filter.h"

class HighPassFilter : public Filter{
private:
	float gain;
	float gainlf;
public:
	HighPassFilter();
	void InitFilter();
	void SetGain(float val);
	void SetGainLF(float val);
	float GetGainLF();
};

#endif
