#include "signals.h"
#include "logging.h"

volatile sig_atomic_t stop_flag = 0;

void sigterm_handler(int signum) {
    stop_flag = 1;
    log_info("Received termination signal");
}

bool setup_signal_handlers() {
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = sigterm_handler;
    if (sigaction(SIGTERM, &sa, NULL) < 0 || sigaction(SIGINT, &sa, NULL) < 0) {
        log_error("Failed to set up signal handlers: %s", strerror(errno));
        return false;
    }
    return true;
}

