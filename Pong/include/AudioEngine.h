
#pragma once

#include <alsa/asoundlib.h>
#include <thread>

#include <queue>
#include <string>
using std::string;

class AudioEngine {
	static AudioEngine* s_instance;
	snd_pcm_t* pcmHandle;
	
	bool audioThreadOn;
	std::queue<std::string> audioQueue;
	std::thread audioThread;

	struct WaveHeader {
		char riff[4];
		uint32_t chunk_size;
		char wave[4];
		char fmt[4];
		
		uint32_t subchunk1_size;
		uint16_t audio_format;
		uint16_t channel_number;
		uint32_t sample_rate;
		uint32_t byte_rate;
		uint16_t block_align;
		uint16_t bits_per_sample;
		char data[4];
		uint32_t data_size;
	};	
	
	AudioEngine();
	
	void monitorQueue();
	void playWavFile(string filename_string);

public:
	static AudioEngine* getInstance();
	void playWav(const char* filename);
};
