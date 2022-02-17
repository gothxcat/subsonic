#include <string>
#include <filesystem>
#include "files.hxx"

using namespace std;

string Files::exec_basename;

void Files::set_exec_basename(const string basename)
{
    Files::exec_basename = basename;
}

const string Files::get_exec_basename()
{
    return Files::exec_basename;
}

string get_basename(const char *filename)
{
    return filesystem::path(filename).filename().string();
}