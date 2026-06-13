#include <pcm.hpp>
#include <parser.hpp>
#include <memory>
#include <list>

uint64_t srate{44100};
static size_t sample = 0;

template <typename T>
void writeTo(std::ofstream& file, T byte) {
    std::string bytearr{};
    for (size_t i = 0; i < (sizeof byte); i++) {
        bytearr.push_back((byte & (0xff << (8 * i))) >> (i * 8));
    }
    file << bytearr;
}

void writeSheet(std::ofstream& file, std::vector<std::vector<note>>& notes) {
    std::shared_ptr<std::list<uint16_t>> data{std::make_shared<std::list<uint16_t>>()};
    for (auto chord : notes)
        writeChord(data, chord);
    file << "RIFF";
    writeTo(file, static_cast<uint32_t>((data->size() * 2) + 36));
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
    writeTo(file, static_cast<uint32_t>(data->size() * 2));
    for (uint16_t s : *data)
        writeTo(file, s);
}

void writeChord(std::shared_ptr<std::list<uint16_t>> data, std::vector<note>& chord) {
    for (size_t ssample = 0; ssample < (srate * chord[0].dur) / 1000; ssample++, sample++) {
        if (chord[0].rest) {
            data->push_back(static_cast<uint16_t>(0));
            continue;
        }
        uint16_t byte{0};
        for (note nt : chord)
            byte += (0x4000 / chord.size()) * nt.wave(static_cast<double>(sample * nt.freq) / srate);
        data->push_back(byte);
    }
}