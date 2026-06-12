#include <file.hpp>
#include <fstream>

std::ofstream initOut(std::string filename, const uint32_t srate) {
    std::ofstream file{filename};
    file << "RIFF";
    writeTo(file, static_cast<uint32_t>(0));
    file << "WAVE";
    file << "fmt ";
    writeTo(file, static_cast<uint32_t>(16));
    writeTo(file, static_cast<uint16_t>(1));
    writeTo(file, static_cast<uint16_t>(1));
    writeTo(file, static_cast<uint32_t>(srate));
    writeTo(file, static_cast<uint32_t>((srate * 16) / 2));
    writeTo(file, static_cast<uint16_t>(2));
    writeTo(file, static_cast<uint16_t>(16));
    file << "data";
    writeTo(file, static_cast<uint32_t>(0));
    return file;
}

template <typename T>
void writeTo(std::ofstream& file, T byte) {
    std::string bytearr{};
    for (size_t i = 0; i < (sizeof byte); i++) {
        bytearr.push_back((byte & (0xff << (8 * i))) >> (i * 8));
    }
    file << bytearr;
}