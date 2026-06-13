#include <file.hpp>
#include <fstream>

std::ofstream initOut(std::string filename, const uint32_t srate) {
    std::ofstream file{filename};
    return file;
}