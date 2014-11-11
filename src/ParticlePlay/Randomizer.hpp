#ifndef RANDOMIZER_HEADER
#define RANDOMIZER_HEADER

class ppRandomizer{
protected:
	unsigned seed;
public:
	ppRandomizer();
	void SetSeed(unsigned seed);
	void ResetSeed();
	unsigned GetSeed();
	float NextFloat();
	float NextFloat(float min, float max);
	float NextFloat(float max);
	int NextInt(int min, int max);
	int NextInt(int max);
};

#endif
