#ifndef ALSA_H
#define ALSA_H

#include <stdbool.h>
#include <alsa/asoundlib.h>

#define PCM_DEVICE "default"

extern snd_pcm_t *pcm_handle;

bool init_alsa();
void cleanup_alsa();

#endif // ALSA_H

