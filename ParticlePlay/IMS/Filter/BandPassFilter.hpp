#ifndef BANDPASSFILTER_HEADER
#define BANDPASSFILTER_HEADER

#include <ParticlePlay/IMS/Filter.hpp>

class ppBandPassFilter : public ppFilter {
protected:
	float gainhf, gainlf;
public:
	ppBandPassFilter(ppIMS* ims, ppFilterType type);
	void InitFilter();
	float GetGainHF();
	float GetGainLF();
	void SetGain(float gain);
	void SetGainHF(float gainhf);
	void SetGainLF(float gainlf);
};

#endif
