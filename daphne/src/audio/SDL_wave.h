/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2016 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/
#include <stdint.h>
#include "../SDL_internal.h"

/* WAVE files are little-endian */

/*******************************************/
/* Define values for Microsoft WAVE format */
/*******************************************/
#define RIFF            0x46464952      /* "RIFF" */
#define WAVE            0x45564157      /* "WAVE" */
#define FACT            0x74636166      /* "fact" */
#define LIST            0x5453494c      /* "LIST" */
#define BEXT            0x74786562      /* "bext" */
#define JUNK            0x4B4E554A      /* "JUNK" */
#define FMT             0x20746D66      /* "fmt " */
#define DATA            0x61746164      /* "data" */
#define PCM_CODE        0x0001
#define MS_ADPCM_CODE   0x0002
#define IEEE_FLOAT_CODE 0x0003
#define IMA_ADPCM_CODE  0x0011
#define MP3_CODE        0x0055
#define WAVE_MONO       1
#define WAVE_STEREO     2

/* Normally, these three chunks come consecutively in a WAVE file */
typedef struct WaveFMT
{
/* Not saved in the chunk we read:
    uint32_t  FMTchunk;
    uint32_t  fmtlen;
*/
    uint16_t encoding;
    uint16_t channels;            /* 1 = mono, 2 = stereo */
    uint32_t frequency;           /* One of 11025, 22050, or 44100 Hz */
    uint32_t byterate;            /* Average bytes per second */
    uint16_t blockalign;          /* Bytes per sample block */
    uint16_t bitspersample;       /* One of 8, 12, 16, or 4 for ADPCM */
} WaveFMT;

/* The general chunk found in the WAVE file */
typedef struct Chunk
{
    uint32_t magic;
    uint32_t length;
    uint8_t *data;
} Chunk;

/* vi: set ts=4 sw=4 expandtab: */
