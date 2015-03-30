#ifndef FILTER_HEADER
#define FILTER_HEADER

#include <map>
#include <ParticlePlay/Includes.hpp>
#include <ParticlePlay/IMS/RTPC.hpp>

enum class ppFilterType {
	LOW_PASS, BAND_PASS, HIGH_PASS
};

class ppIMS;
class ppFilter {
protected:
	bool init;
	bool supported;
	float gain;
	ALuint filterID;
	ppFilterType type;
	std::map<ppRTPC*, ppEffectInfo*> rtpcs;
public:
	ppFilter(ppIMS* ims, ppFilterType type);
	virtual ~ppFilter();
	virtual void InitFilter();
	virtual void SetGain(float gain);
	virtual float GetGain();
	virtual bool IsSupported();
	virtual ppFilterType GetFilterType();
	virtual ALuint GetFilterID();
	virtual void AddRTPC(ppRTPC* rtpc, ppRTPCEffect effect, ppEasing* easing);
	virtual void RemoveRTPC(ppRTPC* rtpc);
	virtual std::map<ppRTPC*, ppEffectInfo*> GetRTPCs();
};

#endif
