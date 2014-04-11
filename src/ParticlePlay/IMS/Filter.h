#ifndef FILTER_HEADER
#define FILTER_HEADER

#include "../Includes.h"

class ppFilter {
protected:
	bool supported;
	ALuint filterID;
public:
	virtual ~ppFilter();
	ALuint GetFilterID();
	virtual void InitFilter()=0;
	bool IsSupported();
};

#endif
