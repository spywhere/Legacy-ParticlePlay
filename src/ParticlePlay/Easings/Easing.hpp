#ifndef EASINGS_HEADER
#define EASINGS_HEADER

class ppEasing {
public:
	virtual float GetValue(float time, float duration, float begin, float changes)=0;
};

#include "BackEasing.hpp"
#include "BackInEasing.hpp"
#include "BackOutEasing.hpp"
#include "BounceEasing.hpp"
#include "BounceInEasing.hpp"
#include "BounceOutEasing.hpp"
#include "CircEasing.hpp"
#include "CircInEasing.hpp"
#include "CircOutEasing.hpp"
#include "CubicEasing.hpp"
#include "CubicInEasing.hpp"
#include "CubicOutEasing.hpp"
#include "ElasticEasing.hpp"
#include "ElasticInEasing.hpp"
#include "ElasticOutEasing.hpp"
#include "ExpoEasing.hpp"
#include "ExpoInEasing.hpp"
#include "ExpoOutEasing.hpp"
#include "LinearEasing.hpp"
#include "QuadEasing.hpp"
#include "QuadInEasing.hpp"
#include "QuadOutEasing.hpp"
#include "QuartEasing.hpp"
#include "QuartInEasing.hpp"
#include "QuartOutEasing.hpp"
#include "QuintEasing.hpp"
#include "QuintInEasing.hpp"
#include "QuintOutEasing.hpp"
#include "SineEasing.hpp"
#include "SineInEasing.hpp"
#include "SineOutEasing.hpp"

#endif
