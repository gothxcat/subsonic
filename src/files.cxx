#include <cerrno>
#include <string>
#include <filesystem>
#include "files.hxx"

using namespace std;
namespace fs = filesystem;

string Files::exec_basename;

void Files::set_exec_basename(const string basename)
{
    Files::exec_basename = basename;
}

const string Files::get_exec_basename()
{
    return Files::exec_basename;
}

NoSuchFileException::NoSuchFileException(string filename)
{
    this->code = ENOENT;
    this->filename = filename;
}

CreateDirectoryException::CreateDirectoryException(string filename)
{
    this->code = EIO;
    this->filename = filename;
}

string get_basename(const char *filename)
{
    return fs::path(filename).filename().string();
}