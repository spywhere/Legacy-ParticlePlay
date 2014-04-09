#ifndef UTILS_HEADER
#define UTILS_HEADER

struct Wav_Info{
	int chunkSize;
	int audioFormat;
	int channels;
	int sampleRate;
	int byteRate;
	int bitPerSample;
	int dataSize;
};

bool IsBigEndian();
int ConvertToInt(char* buffer, int len);

#endif
