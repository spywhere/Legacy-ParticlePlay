#ifndef HIGHPASSFILTER_HEADER
#define HIGHPASSFILTER_HEADER

#include <ParticlePlay/IMS/Filter.hpp>

class ppHighPassFilter : public ppFilter {
protected:
	float gainlf;
public:
	ppHighPassFilter(ppIMS* ims, ppFilterType type);
	void InitFilter();
	float GetGainLF();
	void SetGain(float gain);
	void SetGainLF(float gainlf);
};

#endif
