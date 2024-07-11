#ifndef SIGNALS_H
#define SIGNALS_H

#include <stdbool.h>
#include <signal.h>

extern volatile sig_atomic_t stop_flag;

bool setup_signal_handlers();
void sigterm_handler(int signum);

#endif // SIGNALS_H

