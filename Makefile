CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
LIBS = -lmpg123 -lasound

SRCS = main.c alsa.c mpg123.c signals.c daemon.c logging.c
OBJS = $(SRCS:.c=.o)
DEPS = alsa.h mpg123.h signals.h daemon.h logging.h

TARGET = alsa-ad

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean

