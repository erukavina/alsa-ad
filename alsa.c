#include "alsa.h"
#include "logging.h"

snd_pcm_t *pcm_handle = NULL;

bool init_alsa() {
    if (snd_pcm_open(&pcm_handle, PCM_DEVICE, SND_PCM_STREAM_PLAYBACK, 0) < 0) {
        log_error("Error opening PCM device %s", PCM_DEVICE);
        return false;
    }

    snd_pcm_hw_params_t *params;
    snd_pcm_hw_params_alloca(&params);
    snd_pcm_hw_params_any(pcm_handle, params);
    snd_pcm_hw_params_set_access(pcm_handle, params, SND_PCM_ACCESS_RW_INTERLEAVED);
    snd_pcm_hw_params_set_format(pcm_handle, params, SND_PCM_FORMAT_S16_LE);
    snd_pcm_hw_params_set_channels(pcm_handle, params, 2);
    unsigned int rate = 44100;
    snd_pcm_hw_params_set_rate_near(pcm_handle, params, &rate, 0);
    if (snd_pcm_hw_params(pcm_handle, params) < 0) {
        log_error("Error setting PCM HW params");
        return false;
    }

    return true;
}
