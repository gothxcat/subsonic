#include <cstdlib>
#include <clocale>
#include <cerrno>
#include <string>
#include <vector>
#include <iostream>
#include <filesystem>
#include <libintl.h>

#include "config.hxx"
#include "files.hxx"
#include "options.hxx"
#include "i18n.hxx"
#include "embed.hxx"

using namespace std;
namespace fs = filesystem;

int main(int argc, char **argv)
{
    Files::set_exec_basename(get_basename(argv[0]));

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
        argopt(OPT_OUTPUT_DIR),
        argopt(OPT_OUTPUT_DIR_LONG),
        opt(OPT_EXTRACT),
        opt(OPT_EXTRACT_LONG),
        opt(OPT_VERBOSE),
        opt(OPT_VERBOSE_LONG),
        opt(OPT_VERSION),
        opt(OPT_VERSION_LONG),
        opt(OPT_HELP),
        opt(OPT_HELP_LONG)
    };

    enum Action
    {
        NONE,
        EMBED,
        EXTRACT
    };

    string current_path = fs::current_path().string();

    Action action = NONE;
    const char *data_file_input;
    vector<const char *> audio_file_input;
    vector<const char *> file_output;
    const char *output_directory = current_path.c_str();
    bool verbose = false;

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
                    data_file_input = result.args.at(0);
                }
                else if (optstr == OPT_EXTRACT || optstr == OPT_EXTRACT_LONG)
                {
                    action = Action::EXTRACT;
                }
                else if (optstr == OPT_AUDIO_FILES || optstr == OPT_AUDIO_FILES_LONG)
                {
                    audio_file_input = result.args;
                }
                else if (optstr == OPT_OUTPUT_DIR || optstr == OPT_OUTPUT_DIR_LONG)
                {
                    output_directory = result.args.at(0);
                }
                else if (optstr == OPT_VERBOSE || optstr == OPT_VERBOSE_LONG)
                {
                    verbose = true;
                }
                else if (optstr == OPT_VERSION || optstr == OPT_VERSION_LONG)
                {
                    show_version();
                    return EXIT_SUCCESS;
                }
                else if (optstr == OPT_HELP || optstr == OPT_HELP_LONG)
                {
                    show_help();
                    return EXIT_SUCCESS;
                }
            }
        }
    }
    catch (const OptionException &e)
    {
        switch (e.category)
        {
            case OptionException::Category::INVALID_OPTION:
                cerr << Files::get_exec_basename() << _(": unrecognised option '") << e.option_string << _("'") << endl;
                break;
            case OptionException::Category::NO_ARGUMENT:
                cerr << Files::get_exec_basename() << _(": option '") << e.option_string << _("' requires an argument") << endl;
                break;
        }

        cerr << _("Try '") << Files::get_exec_basename() << " " << OPT_HELP_LONG << _("' for more information.") << endl;
        return ENOENT;
    }

    string target_name;
    try
    {
        switch (action)
        {
            case Action::EMBED:
                target_name = _("embed");

                if (audio_file_input.size() == 0)
                {
                    cerr << Files::get_exec_basename() << _(": embed: no audio files specified") << endl;
                    return ENOENT;
                }

                return embed(data_file_input, audio_file_input, output_directory, true, verbose);

                break;
            case Action::EXTRACT: // TODO
                target_name = _("extract");
                break;
            default:
                show_help();
                break;
        }
    }
    catch (const NoSuchFileException &e)
    {
        cerr << Files::get_exec_basename() << _(": ") << target_name << _(": file '") << e.filename << _("' not found") << endl;
        return e.code;
    }
    catch (const CreateDirectoryException &e)
    {
        cerr << Files::get_exec_basename() << _(": ") << target_name << _(": unable to create directory'") << e.filename << _("'") << endl;
        return e.code;
    }

    return EXIT_SUCCESS;
}