#include <pcm.hpp>
#include <file.hpp>
#include <parser.hpp>

uint64_t srate{44100};
static size_t sample = 0;

void writeSheet(std::ofstream& file, std::vector<std::vector<note>>& notes) {
    for (auto chord : notes)
        writeChord(file, chord);
}

void writeChord(std::ofstream& file, std::vector<note>& chord) {
    for (size_t ssample = 0; ssample < (srate * chord[0].dur) / 1000; ssample++, sample++) {
        if (chord[0].rest) {
            writeTo(file, static_cast<uint16_t>(0));
            continue;
        }
        uint16_t byte{0};
        for (note nt : chord)
            byte += (0x4000 / chord.size()) * nt.wave(static_cast<double>(sample * nt.freq) / srate);
        writeTo(file, byte);
    }
}