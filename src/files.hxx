/* Filesystem functions */
#ifndef _FILES_HXX_
#define _FILES_HXX_

#include <string>

using namespace std;

class Files
{
public:
    static void set_exec_basename(const string basename);
    static const string get_exec_basename();

private:
    static string exec_basename;
};

string get_basename(const char *filename);

#endif