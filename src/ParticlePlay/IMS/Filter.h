#ifndef FILTER_HEADER
#define FILTER_HEADER

#include "Includes.h"

class Filter {
protected:
	bool supported;
	ALuint filterID;
public:
	ALuint GetFilterID();
	virtual void InitFilter()=0;
	bool IsSupported();
};

#endif
