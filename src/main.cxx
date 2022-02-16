#include <cstdlib>
#include <clocale>
#include <string>
#include <vector>
#include <iostream>
#include <libintl.h>

#include "config.hxx"
#include "files.hxx"
#include "options.hxx"
#include "i18n.hxx"

using namespace std;

int main(int argc, char **argv)
{
    const string basename = get_basename(argv[0]);

    /* Initialise locale */

    setlocale(LC_ALL, NULL);
    textdomain(PROJECT_NAME);

    /* Parse command line arguments */

    vector<const char *> args;
    for (int i=1; i<argc; ++i)
    {
        args.push_back(argv[i]);
    }

    vector<Option> options = {
        argopt(OPT_EMBED),
        argopt(OPT_EMBED_LONG),
        argopt(OPT_AUDIO_FILES),
        argopt(OPT_AUDIO_FILES_LONG),
        argopt(OPT_OUTPUT),
        argopt(OPT_OUTPUT_LONG),
        argopt(OPT_OUTPUT_DIR),
        argopt(OPT_OUTPUT_DIR_LONG),
        opt(OPT_EXTRACT),
        opt(OPT_EXTRACT_LONG),
        opt(OPT_VERSION_LONG),
        opt(OPT_HELP_LONG)
    };

    enum Action
    {
        NONE,
        EMBED,
        EXTRACT
    };

    Action action = NONE;
    vector<const char *> data_input;
    vector<const char *> audio_input;
    vector<const char *> output;
    const char *output_directory;

    try
    {
        int index = 0;
        OptionResult result;
        while (index != -1)
        {
            if (get_option(args, options, &index, &result))
            {
                const char *optstr = result.option_string;
                if (optstr == OPT_EMBED || optstr == OPT_EMBED_LONG)
                {
                    action = Action::EMBED;
                    data_input = result.args;
                }
                else if (optstr == OPT_EXTRACT || optstr == OPT_EXTRACT_LONG)
                {
                    action = Action::EXTRACT;
                }
                else if (optstr == OPT_AUDIO_FILES || optstr == OPT_AUDIO_FILES_LONG)
                {
                    audio_input = result.args;
                }
                else if (optstr == OPT_OUTPUT || optstr == OPT_OUTPUT_LONG)
                {
                    output = result.args;
                }
                else if (optstr == OPT_VERSION_LONG)
                {
                    show_version();
                    return EXIT_SUCCESS;
                }
                else if (optstr == OPT_HELP_LONG)
                {
                    show_help(basename);
                    return EXIT_SUCCESS;
                }
            }
        }
    }
    catch (const OptionException& e)
    {
        switch (e.category)
        {
            case OptionException::Category::INVALID_OPTION:
                cerr << basename << _(": unrecognised option \'") << e.option_string << _("\'") << endl;
                break;
            case OptionException::Category::NO_ARGUMENT:
                cerr << basename << _(": option \'") << e.option_string << _("\' requires an argument") << endl;
                break;
        }

        cerr << _("Try \'") << basename << " " << OPT_HELP_LONG << _("\' for more information.") << endl;
        return 2;
    }

    switch (action)
    {
        case Action::EMBED: // TODO
            break;
        case Action::EXTRACT: // TODO
            break;
        default:
            show_help(basename);
            break;
    }

    return EXIT_SUCCESS;
}