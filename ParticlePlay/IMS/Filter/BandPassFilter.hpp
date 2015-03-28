#ifndef BANDPASSFILTER_HEADER
#define BANDPASSFILTER_HEADER

#include <ParticlePlay/IMS/Filter.hpp>

class ppBandPassFilter : public ppFilter {
protected:
	float gain, gainhf, gainlf;
public:
	ppBandPassFilter();
	void InitFilter();
	float GetGain();
	float GetGainHF();
	float GetGainLF();
	void SetGain(float gain);
	void SetGainHF(float gainhf);
	void SetGainLF(float gainlf);
};

#endif
