# Subsonic

Subsonic is a command line tool for embedding and extracting data files split across the ID3v2 tags of MP3 audio files, written in C++17.

## Runtime Dependencies

- `gettext`

## Documentation

See the files in [`doc`](doc).

Commands are written in POSIX shell syntax and prefixed with `$`.

## Platforms

Tested platforms:
- Arch Linux x86_64

## Build

Build Dependencies:
- `cmake` >=3.1
- `gcc` >=5
- `gettext`

`$ git submodule init`

`$ mkdir build`

`$ (cd build && cmake .. && cmake --build .)`

## Run

`$ ./build/subsonic`

## Licence

Released under the GNU GPLv3. See [`LICENCE`](LICENCE).
