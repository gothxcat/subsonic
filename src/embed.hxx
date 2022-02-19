#ifndef _EMBED_HXX_
#define _EMBED_HXX_

#include <vector>

using namespace std;

int embed(const char *data_file, vector<const char *> audio_files,
            const char *output_directory,
            bool show_errors, bool verbose);

#endif