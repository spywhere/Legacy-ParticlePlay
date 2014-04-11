#ifndef BANDPASSFILTER_HEADER
#define BANDPASSFILTER_HEADER

#include "../IMS.h"
#include "../Filter.h"

class ppIMS;
class ppBandPassFilter : public ppFilter{
private:
	float gain;
	float gainlf;
	float gainhf;
public:
	ppBandPassFilter(ppIMS* ims);
	void InitFilter();
	void SetGain(float val);
	void SetGainLF(float val);
	void SetGainHF(float val);
	float GetGainLF();
	float GetGainHF();
};

#endif
