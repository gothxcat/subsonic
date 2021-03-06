# Internationalisation Using GNU gettext

Subsonic currently uses en_GB.UTF-8 strings and message identifiers by default. To add other languages, see the following steps.

## Generating the PO File Template

`$ mkdir build`

`$ (cd build && cmake .. && cmake --build . --target po-template)`

This will generate `po/subsonic.pot`.

## Generating PO Language Files

`$ msginit -i po/subsonic.pot -o po/<LANG>.po -l <LOCALE>`

(e.g.) `$ msginit -i po/subsonic.pot -o po/de.po -l de_DE.UTF-8`

Make edits to the output file as required.

(TODO) CMake will generate and distribute the `.mo` files upon installation.
