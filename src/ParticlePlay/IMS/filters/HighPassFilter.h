#ifndef HIGHPASSFILTER_HEADER
#define HIGHPASSFILTER_HEADER

#include "../Filter.h"

class ppHighPassFilter : public ppFilter{
private:
	float gain;
	float gainlf;
public:
	ppHighPassFilter();
	void InitFilter();
	void SetGain(float val);
	void SetGainLF(float val);
	float GetGainLF();
};

#endif
