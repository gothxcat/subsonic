#include <cstdlib>
#include <vector>
#include <filesystem>
#include <taglib/taglib.h>
#include "embed.hxx"
#include "files.hxx"

using namespace std;
namespace fs = filesystem;

int embed(const char *data_file, vector<const char *> audio_files,
            const char *output_directory,
            bool show_errors, bool verbose = false)
{
    if (!fs::exists(data_file))
    {
        throw NoSuchFileException(string(data_file));
        return EXIT_FAILURE;
    }

    for (auto &filename : audio_files)
    {
        if (!fs::exists(filename))
        {
            throw NoSuchFileException(string(filename));
            return EXIT_FAILURE;
        }
    }

    if (!fs::exists(output_directory))
    {
        if (!fs::create_directories(output_directory))
        {
            throw CreateDirectoryException(string(output_directory));
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}