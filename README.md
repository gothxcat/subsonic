# Subsonic

Subsonic is a command line tool for embedding and extracting data files split across the IDv3 tags of MP3 audio files, written in C++17.

## Runtime Dependencies

- `gettext`

## Documentation

See the files in [`doc`](doc) or the [Subsonic Wiki (TODO)](https://github.com/kxwiggins/subsonic/wiki).

Commands are written in POSIX shell syntax and prefixed with `$`.

## Build

Build Dependencies:
- `cmake` >=3.1
- `gcc` >=5
- `gettext`

`$ mkdir build`

`$ (cd build && cmake .. && cmake --build .)`

## Run

`$ ./build/subsonic`

## Platforms

Tested platforms:
- Arch Linux x86_64

## Licence

Released under the GNU GPLv3. See [`LICENCE`](LICENCE).