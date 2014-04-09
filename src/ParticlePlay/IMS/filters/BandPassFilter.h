#ifndef BANDPASSFILTER_HEADER
#define BANDPASSFILTER_HEADER

#include "../Filter.h"

class ppBandPassFilter : public ppFilter{
private:
	float gain;
	float gainlf;
	float gainhf;
public:
	ppBandPassFilter();
	void InitFilter();
	void SetGain(float val);
	void SetGainLF(float val);
	void SetGainHF(float val);
	float GetGainLF();
	float GetGainHF();
};

#endif
