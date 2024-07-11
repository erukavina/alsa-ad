#include "mpg123.h"
#include "logging.h"

mpg123_handle *mpg123_handle = NULL;

bool init_mp3(const char *mp3_file) {
    int err;
    mpg123_handle = mpg123_new(NULL, &err);
    if (mpg123_handle == NULL) {
        log_error("Failed to initialize MPG123: %s", mpg123_plain_strerror(err));
        return false;
    }

    if (mpg123_open(mpg123_handle, mp3_file) != MPG123_OK) {
        log_error("Failed to open MP3 file: %s", mpg123_strerror(mpg123_handle));
        mpg123_delete(mpg123_handle);
        return false;
    }

    return true;
}

bool play_mp3_chunk() {
    int err;
    off_t frame_offset;
    size_t buffer_size = MP3_BUFFER_SIZE;
    unsigned char *buffer = (unsigned char *)malloc(buffer_size * sizeof(unsigned char));

    size_t bytes_to_write;
    err = mpg123_read(mpg123_handle, buffer, buffer_size, &bytes_to_write);
    if (err == MPG123_OK) {
        err = snd_pcm_writei(pcm_handle, buffer, bytes_to_write / sizeof(short));
        if (err < 0) {
            log_error("Error writing to PCM device: %s", snd_strerror(err));
            free(buffer);
            return false;
        }
    } else if (err == MPG123_NEW_FORMAT) {
        long rate;
        int channels, encoding;
        mpg123_getformat(mpg123_handle, &rate, &channels, &encoding);
        log_info("New format: rate %ld Hz, %d channels, encoding 0x%x", rate, channels, encoding);
    } else {
        log_error("Error decoding MP3: %s", mpg123_strerror(mpg123_handle));
        free(buffer);
        return false;
    }

    free(buffer);
    return true;
}
// Add cleanup
void cleanup_mp3() {
    if (mpg123_handle) {
        mpg123_close(mpg123_handle);
        mpg123_delete(mpg123_handle);
    }
    mpg123_exit();
}
