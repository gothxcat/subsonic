/* Command line options */
#ifndef _OPTIONS_HXX_
#define _OPTIONS_HXX_

#include <exception>
#include <vector>
#include <string>
#include "i18n.hxx"

using namespace std;

#define OPT_EMBED               _("-m")
#define OPT_EMBED_LONG          _("--embed")
#define OPT_EXTRACT             _("-x")
#define OPT_EXTRACT_LONG        _("--extract")
#define OPT_AUDIO_FILES         _("-a")
#define OPT_AUDIO_FILES_LONG    _("--audio-files")
#define OPT_OUTPUT              _("-o")
#define OPT_OUTPUT_LONG         _("--output")
#define OPT_OUTPUT_DIR          _("-d")
#define OPT_OUTPUT_DIR_LONG     _("--output-directory")
#define OPT_VERSION_LONG        _("--version")
#define OPT_HELP_LONG           _("--help")

struct Option
{
    const char *string;
    bool has_args;
};

struct OptionResult
{
    const char *option_string;
    vector<const char *> args;
};

class OptionException: public exception
{
public:
    enum Category
    {
        NO_ARGUMENT,
        INVALID_OPTION
    };

    const char *option_string;
    Category category;

    OptionException(const char *option_string, const OptionException::Category category);
};

Option opt(const char *s);
Option argopt(const char *s);

bool get_option(const vector<const char*> args, const vector<Option> options, int *index, OptionResult *result);

void show_help(const string basename);
void show_version();

#endif