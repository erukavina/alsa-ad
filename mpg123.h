#ifndef MPG123_H
#define MPG123_H

#include <stdbool.h>
#include <mpg123.h>

#define MP3_BUFFER_SIZE 32768 // Buffer size for MP3 decoding

extern mpg123_handle *mpg123_handle;

bool init_mp3(const char *mp3_file);
bool play_mp3_chunk();
void cleanup_mp3();

#endif // MPG123_H

