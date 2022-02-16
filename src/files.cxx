#include <string>
#include <filesystem>
using namespace std;

const string get_basename(const char *filename)
{
    return (const string)filesystem::path(filename).filename().string();
}