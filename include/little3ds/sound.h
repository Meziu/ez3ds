#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <tremor/ivorbiscodec.h>
#include <tremor/ivorbisfile.h>
#include <3ds.h>

#define BUFF_SIZE 8 * 4096
typedef struct {
	float rate;
	u32 channels;
	u32 encoding;
	u32 nsamples;
	u32 size;
	char* data1;
	char* data2;
	bool loop;
	int audiochannel;
	float mix[12];
	ndspInterpType interp;
	OggVorbis_File ovf;
} Audio;

Audio music;
ndspWaveBuf waveBuf[2];

uint64_t fillVorbisBuffer(OggVorbis_File ovf, char* buffer) {	
	uint64_t samplesRead = 0;
	int samplesToRead = BUFF_SIZE;
	while (samplesToRead > 0) {
		static int current_section;
		int samplesJustRead =
			ov_read(&ovf,
				buffer,
				samplesToRead > 4096 ? 4096 : samplesToRead,
				&current_section);

		if (samplesJustRead < 0) {
			return samplesJustRead;
		}else if (samplesJustRead == 0){
			break;
		}
		samplesRead += samplesJustRead;
		samplesToRead -= samplesJustRead;
		buffer += samplesJustRead;
	}
	return samplesRead / sizeof(int16_t);
}


int load() {
	memset(&music, 0, sizeof(music));
	music.mix[0] = 1.0f;
	music.mix[1] = 1.0f;
	FILE * file = fopen("example.ogg", "rb");
	if (file == 0) {
		printf("no file\n");
		while (1);
	}
	if (ov_open(file, &music.ovf, NULL, 0) < 0) {
		printf("ogg vorbis file error\n");
		while (1);
	}
	vorbis_info * vorbisInfo = ov_info(&music.ovf, -1);
	if (vorbisInfo == NULL) {
		printf("could not retrieve ogg audio stream information\n");
		while (1);
	}
	music.rate = (float)vorbisInfo->rate;
	music.channels = (u32)vorbisInfo->channels;
	music.encoding = NDSP_ENCODING_PCM16;
	//music.nsamples = (u32)ov_pcm_total(&music.ovf, -1);
	music.size = music.nsamples * music.channels * 2;
	music.audiochannel = 0;
	music.interp = NDSP_INTERP_NONE;
	music.loop = false;
	if (linearSpaceFree() < music.size) {
		printf("not enough linear memory available %ld\n", music.size);
	}
	music.data1 = (char *)linearAlloc(BUFF_SIZE * sizeof(int16_t));
	music.data2 = (char *)linearAlloc(BUFF_SIZE * sizeof(int16_t));
	if (music.audiochannel == -1) {
		printf("No available audio channel\n");
		return -1;
	}
		ndspChnWaveBufClear(music.audiochannel);
		ndspChnReset(music.audiochannel);
		ndspChnInitParams(music.audiochannel);
		ndspChnSetMix(music.audiochannel, music.mix);
		ndspChnSetInterp(music.audiochannel, music.interp);
		ndspChnSetRate(music.audiochannel, music.rate);
		ndspChnSetFormat(music.audiochannel, NDSP_CHANNELS(music.channels) | NDSP_ENCODING(music.encoding));

	memset(&waveBuf, 0, sizeof(WaveBuf));
	waveBuf[0].data_vaddr = &music.data1[0];
	waveBuf[0].nsamples = fillVorbisBuffer(music.ovf, &music.data1[0]) / music.channels;
	waveBuf[0].looping = music.loop;
	ndspChnWaveBufAdd(music.audiochannel, &waveBuf[0]);
	waveBuf[1].data_vaddr = &music.data2[0];
	waveBuf[1].nsamples = fillVorbisBuffer(music.ovf, &music.data2[0]) / music.channels;
	waveBuf[1].looping = music.loop;
	ndspChnWaveBufAdd(music.audiochannel, &waveBuf[1]);
	return 0;
}

int run(int argc, char **argv) {
	ndspInit();
	ndspSetOutputMode(NDSP_OUTPUT_STEREO);
	ndspSetOutputCount(1);

	load();
    
	bool lastbuf = false;
	//while (ndspChnIsPlaying(music.audiochannel) == false);
	while (aptMainLoop()) {
		hidScanInput();
		u32 keys = hidKeysDown();
		if (keys & KEY_START)
			break;
		if (lastbuf == true) {
			continue;
		}
			if (waveBuf[0].status == NDSP_WBUF_DONE) {
				size_t read = fillVorbisBuffer(music.ovf, &music.data1[0]);
				if (read <= 0) {
					lastbuf = true;
					printf("END\n");
					continue;
				}
				else if (read < BUFF_SIZE) {
					waveBuf[0].nsamples = read / music.channels;
				}
				ndspChnWaveBufAdd(music.audiochannel, &waveBuf[0]);
			}

			if (waveBuf[1].status == NDSP_WBUF_DONE) {
				size_t read = fillVorbisBuffer(music.ovf, &music.data2[0]);
				if (read <= 0) {
					lastbuf = true;
					printf("END\n");
					continue;
				}
				else if (read < BUFF_SIZE) {
					waveBuf[1].nsamples = read / music.channels;
				}
				ndspChnWaveBufAdd(music.audiochannel, &waveBuf[1]);
			}
		DSP_FlushDataCache(music.data1, BUFF_SIZE * sizeof(int16_t));
		DSP_FlushDataCache(music.data2, BUFF_SIZE * sizeof(int16_t));
		gfxFlushBuffers();
		gfxSwapBuffers();
		gspWaitForVBlank();
	}
	ndspChnWaveBufClear(music.audiochannel);
	ndspExit();
	gfxExit();
	return 0;
}