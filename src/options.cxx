#include <cstring>
#include <cstddef>
#include <cstdarg>
#include <exception>
#include <string>
#include <vector>
#include <iostream>

#include "options.hxx"
#include "i18n.hxx"
#include "config.hxx"

using namespace std;

OptionException::OptionException(const char *option_string, const OptionException::Category category)
{
    this->option_string = option_string;
    this->category = category;
}

/* Create option with no required arguments */
Option opt(const char *s)
{
    Option option = {
        .string = s,
        .has_args = false
    };

    return option;
}

/* Create option with required arguments */
Option argopt(const char *s)
{
    Option option = {
        .string = s,
        .has_args = true
    };

    return option;
}

/*
* Returns true and sets object at pointer `result` if valid option from `options` is found at the value at pointer `index` in `args`.
* Throws an OptionException if an argument was invalid or a required argument was not found.
* Increments value at pointer `index` after parsing an option;
* sets value at `index` to -1 when all arguements have been parsed.
*/
bool get_option(const vector<const char*> args, const vector<Option> options, int *index, OptionResult *result)
{
    if (*index > -1 && *index < args.size())
    {
        /* Check current argument against each available option */
        for (size_t i=0; i<options.size(); ++i)
        {
            Option option = options.at(i);
            if (strcmp(args.at(*index), option.string) == 0)
            {
                if (option.has_args)
                {
                    size_t optarg_index = *index + 1;
                    while (true)
                    {
                        if (optarg_index >= args.size()
                            || strlen(args.at(optarg_index)) == 0
                            || args.at(optarg_index)[0] == '-')
                        {
                            break;
                        }
                        else
                        {
                            const char *optarg = args.at(optarg_index);
                            result->args.push_back(optarg);
                            ++optarg_index;
                        }
                    }
                    
                    if (result->args.size() > 0)
                    {
                        result->option_string = option.string;
                        ++*index;
                        return true;
                    }
                    else
                    {
                        throw OptionException(option.string, OptionException::Category::NO_ARGUMENT);
                        return false;
                    }
                }
                else
                {
                    *result = {
                        .option_string = option.string
                    };

                    ++*index;
                    return true;
                }
            }
        }
    }
    else
    {
        *index = -1;
        *result = {};
        return false;
    }
    
    throw OptionException(args.at(*index), OptionException::Category::INVALID_OPTION);
    *result = {};
    ++*index;
    return false;
}

void show_help(const string basename)
{
    cout << _("Usage: ") << basename << _(" [OPTION]...") << endl
            << _("Embed and extract data files split across IDv3 MP3 audio tags.") << endl
            << endl
            << _("Mandatory arguments for long options are also mandatory for short options.") << endl
            << _("Options:") << endl
            << _("  -m, --embed [FILE]...                   embed data from the specified data file(s)") << endl
            << _("                                              (requires \'--audio-files\' and \'--output\')") << endl
            << _("  -x, --extract                           extract data") << endl
            << _("                                              (requires \'--audio-files\')") << endl
            << _("  -a, --audio-files [FILE]...             specify input MP3 file(s)") << endl
            << _("  -o, --output [FILE]...                  specify output MP3 file(s)") << endl
            << _("  -d, --output-directory [DIRECTORY]...   specify output directory") << endl
            << _("      --version                           display version information and exit") << endl
            << _("      --help                              display this help and exit") << endl;
}

void show_version()
{
    cout << PROJECT_NAME << " " << PROJECT_VERSION_MAJOR << "." << PROJECT_VERSION_MINOR << endl;
}