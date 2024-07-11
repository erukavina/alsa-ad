#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "alsa.h"
#include "mpg123.h"
#include "signals.h"
#include "daemon.h"
#include "logging.h"

#define MP3_FILE "audiofile.mp3"

int main() {
    init_logging();

    if (!daemonize()) {
        log_error("Failed to daemonize the process");
        return 1;
    }

    if (!init_alsa()) {
        log_error("Failed to initialize ALSA");
        return 1;
    }

    if (!init_mp3(MP3_FILE)) {
        log_error("Failed to initialize MPG123");
        cleanup();
        return 1;
    }

    if (!setup_signal_handlers()) {
        log_error("Failed to set up signal handlers");
        cleanup();
        return 1;
    }

    while (!stop_flag) {
        if (!play_mp3_chunk()) {
            log_error("Error while playing MP3");
            break;
        }
    }

    cleanup();
    log_info("MP3 player stopped");

    return 0;
}

