#ifndef BANDPASSFILTER_HEADER
#define BANDPASSFILTER_HEADER

#include "../Filter.h"

class BandPassFilter : public Filter{
private:
	float gain;
	float gainlf;
	float gainhf;
public:
	BandPassFilter();
	void InitFilter();
	void SetGain(float val);
	void SetGainLF(float val);
	void SetGainHF(float val);
	float GetGainLF();
	float GetGainHF();
};

#endif
