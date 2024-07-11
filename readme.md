# ALSA Audio Driver

This project is a simple MP3 player daemon that uses ALSA for audio playback and libmpg123 for MP3 decoding. The player runs as a daemon process and handles termination signals gracefully.

## Features

- Plays MP3 files using ALSA and libmpg123
- Runs as a daemon in the background
- Graceful handling of termination signals (SIGTERM, SIGINT)
- Logging of informational messages and errors

## Prerequisites

- ALSA development libraries
- libmpg123 development libraries
- Doxygen for documentation generation

Install the required libraries on Debian-based systems:
```bash
sudo apt-get install libasound2-dev libmpg123-dev doxygen
```

## Building 
Use the provided Makefile to build the project:
```bash
make 
```
This will compile the source files and generate the alsa-ad executable.

## Running
To run as a daemon, execute:
```bash
./alsa-ad <file> &
```

## Documentation
To generate the project documentation using Doxygen, run:
```
doxygen Doxyfile
```
The documentation will be generated in the docs directory.

## License
This project is licensed under the MIT License. See the LICENSE file for details.



