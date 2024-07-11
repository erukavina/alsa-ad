#include "daemon.h"
#include "logging.h"

bool daemonize() {
    pid_t pid, sid;

    pid = fork();
    if (pid < 0) {
        log_error("Failed to fork: %s", strerror(errno));
        return false;
    }
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    umask(0);

    sid = setsid();
    if (sid < 0) {
        log_error("Failed to create new session: %s", strerror(errno));
        return false;
    }

    if ((chdir("/")) < 0) {
        log_error("Failed to change directory to /: %s", strerror(errno));
        return false;
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    open("/dev/null", O_RDONLY);
    open("/dev/null", O_RDWR);
    open("/dev/null", O_RDWR);

    log_info("Daemonized successfully");
    return true;
}

