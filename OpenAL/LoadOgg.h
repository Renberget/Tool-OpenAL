#pragma once
#include "Framework/Framework.h"
#include <Vorbis/vorbisfile.h>
#include <stdio.h>
#include <vector>

using namespace System::Diagnostics;

size_t ov_read_func(void* ptr, size_t size, size_t nmemb, void* datasource)
{
	return fread(ptr, size, nmemb, (FILE*)datasource);
}

int ov_seek_func(void* datasource, ogg_int64_t offset, int whence)
{
	return fseek((FILE*)datasource, (long)offset, whence);
}

int ov_close_func(void* datasource)
{
	return fclose((FILE*)datasource);
}

long ov_tell_func(void* datasource)
{
	return ftell((FILE*)datasource);
}

unsigned long decodeOgg(OggVorbis_File* psOggVorbisFile, char* pDecodeBuffer, unsigned long ulBufferSize, unsigned long ulChannels)
{
	int current_section;
	long lDecodeSize;
	unsigned long ulSamples;
	short* pSamples;

	unsigned long ulBytesDone = 0;
	while (1)
	{
		lDecodeSize = ov_read(psOggVorbisFile, pDecodeBuffer + ulBytesDone, ulBufferSize - ulBytesDone, 0, 2, 1, &current_section);
		if (lDecodeSize > 0)
		{
			ulBytesDone += lDecodeSize;

			if (ulBytesDone >= ulBufferSize)
				break;
		}
		else
		{
			break;
		}
	}

	// Mono, Stereo and 4-Channel files decode into the same channel order as WAVEFORMATEXTENSIBLE,
	// however 6-Channels files need to be re-ordered
	if (ulChannels == 6)
	{
		pSamples = (short*)pDecodeBuffer;
		for (ulSamples = 0; ulSamples < (ulBufferSize >> 1); ulSamples += 6)
		{
			// WAVEFORMATEXTENSIBLE Order : FL, FR, FC, LFE, RL, RR
			// OggVorbis Order            : FL, FC, FR,  RL, RR, LFE
			std::swap(pSamples[ulSamples + 1], pSamples[ulSamples + 2]);
			std::swap(pSamples[ulSamples + 3], pSamples[ulSamples + 5]);
			std::swap(pSamples[ulSamples + 4], pSamples[ulSamples + 5]);
		}
	}

	return ulBytesDone;
}

void loadOgg(ALuint alBufferId, FILE* file)
{
	ov_callbacks callbacks;
	callbacks.read_func = ov_read_func;
	callbacks.seek_func = ov_seek_func;
	callbacks.close_func = NULL;
	callbacks.tell_func = ov_tell_func;

	OggVorbis_File oggFile;
	if (int error = ov_open_callbacks(file, &oggFile, NULL, 0, callbacks))
	{
		Debug::WriteLine("Could not open ogg with callbacks. Error " + error.ToString());
		return;
	}
	
	vorbis_info* info = ov_info(&oggFile, -1);
	if (!info)
	{
		Debug::WriteLine("Could not retreive info from ogg");
		return;
	}
	
	unsigned long ulBufferSize;
	unsigned long ulFrequency = info->rate;
	unsigned long ulFormat = 0;
	unsigned long ulChannels = info->channels;
	
	if (ulChannels == 1)
	{
		ulFormat = AL_FORMAT_MONO16;
		// Set BufferSize to 250ms (Frequency * 2 (16bit) divided by 4 (quarter of a second))
		ulBufferSize = ulFrequency >> 1;
		// IMPORTANT : The Buffer Size must be an exact multiple of the BlockAlignment ...
		ulBufferSize -= (ulBufferSize % 2);
	}
	else if (ulChannels == 2)
	{
		ulFormat = AL_FORMAT_STEREO16;
		// Set BufferSize to 250ms (Frequency * 4 (16bit stereo) divided by 4 (quarter of a second))
		ulBufferSize = ulFrequency;
		// IMPORTANT : The Buffer Size must be an exact multiple of the BlockAlignment ...
		ulBufferSize -= (ulBufferSize % 4);
	}
	else if (ulChannels == 4)
	{
		ulFormat = alGetEnumValue("AL_FORMAT_QUAD16");
		// Set BufferSize to 250ms (Frequency * 8 (16bit 4-channel) divided by 4 (quarter of a second))
		ulBufferSize = ulFrequency * 2;
		// IMPORTANT : The Buffer Size must be an exact multiple of the BlockAlignment ...
		ulBufferSize -= (ulBufferSize % 8);
	}
	else if (ulChannels == 6)
	{
		ulFormat = alGetEnumValue("AL_FORMAT_51CHN16");
		// Set BufferSize to 250ms (Frequency * 12 (16bit 6-channel) divided by 4 (quarter of a second))
		ulBufferSize = ulFrequency * 3;
		// IMPORTANT : The Buffer Size must be an exact multiple of the BlockAlignment ...
		ulBufferSize -= (ulBufferSize % 12);
	}
	else
		return;
	
	std::vector<char> buffer(ulBufferSize);
	unsigned int ulWrittenBytes;
	unsigned int ulTotalWrittenBytes = 0;
	do
	{
		buffer.resize(buffer.size() + ulBufferSize);
		ulWrittenBytes = decodeOgg(&oggFile, buffer.data(), ulBufferSize, ulChannels);
		ulTotalWrittenBytes += ulWrittenBytes;
	} while (ulWrittenBytes);
	Debug::WriteLine(ulTotalWrittenBytes);
	alBufferData(alBufferId, ulFormat, buffer.data(), ulTotalWrittenBytes, ulFrequency);

	ov_clear(&oggFile);
}