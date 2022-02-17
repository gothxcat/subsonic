#ifndef _EMBED_HXX_
#define _EMBED_HXX_

#include <vector>

using namespace std;

int embed(vector<const char *> data_input, vector<const char *> audio_input,
            vector<const char *> output, const char *output_directory,
            bool show_errors, bool verbose);

#endif