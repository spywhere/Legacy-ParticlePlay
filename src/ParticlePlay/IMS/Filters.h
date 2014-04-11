#include "filters/BandPassFilter.h"
#include "filters/HighPassFilter.h"
#include "filters/LowPassFilter.h"
#include "Filter.h"

#ifndef FILTERTYPE_HEADER
#define FILTERTYPE_HEADER
enum class ppFilterType{
	BAND_PASS, HIGH_PASS, LOW_PASS
};
#endif