#ifndef EASINGS_HEADER
#define EASINGS_HEADER

class ppEasing {
public:
	virtual float GetValue(float time, float duration, float begin, float changes)=0;
};

#include <ParticlePlay/Easings/BackEasing.hpp>
#include <ParticlePlay/Easings/BackInEasing.hpp>
#include <ParticlePlay/Easings/BackOutEasing.hpp>
#include <ParticlePlay/Easings/BounceEasing.hpp>
#include <ParticlePlay/Easings/BounceInEasing.hpp>
#include <ParticlePlay/Easings/BounceOutEasing.hpp>
#include <ParticlePlay/Easings/CircEasing.hpp>
#include <ParticlePlay/Easings/CircInEasing.hpp>
#include <ParticlePlay/Easings/CircOutEasing.hpp>
#include <ParticlePlay/Easings/CubicEasing.hpp>
#include <ParticlePlay/Easings/CubicInEasing.hpp>
#include <ParticlePlay/Easings/CubicOutEasing.hpp>
#include <ParticlePlay/Easings/ElasticEasing.hpp>
#include <ParticlePlay/Easings/ElasticInEasing.hpp>
#include <ParticlePlay/Easings/ElasticOutEasing.hpp>
#include <ParticlePlay/Easings/ExpoEasing.hpp>
#include <ParticlePlay/Easings/ExpoInEasing.hpp>
#include <ParticlePlay/Easings/ExpoOutEasing.hpp>
#include <ParticlePlay/Easings/LinearEasing.hpp>
#include <ParticlePlay/Easings/QuadEasing.hpp>
#include <ParticlePlay/Easings/QuadInEasing.hpp>
#include <ParticlePlay/Easings/QuadOutEasing.hpp>
#include <ParticlePlay/Easings/QuartEasing.hpp>
#include <ParticlePlay/Easings/QuartInEasing.hpp>
#include <ParticlePlay/Easings/QuartOutEasing.hpp>
#include <ParticlePlay/Easings/QuintEasing.hpp>
#include <ParticlePlay/Easings/QuintInEasing.hpp>
#include <ParticlePlay/Easings/QuintOutEasing.hpp>
#include <ParticlePlay/Easings/SineEasing.hpp>
#include <ParticlePlay/Easings/SineInEasing.hpp>
#include <ParticlePlay/Easings/SineOutEasing.hpp>

#endif
