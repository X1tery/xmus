#include <parser.hpp>
#include <wave.hpp>
#include <cwctype>
#include <cmath>
#include <utility>
#include <fstream>
#include <iostream>
#include <functional>
#include <memory>
#include <unordered_map>
#include <print>

uint16_t bpm;
std::pair<uint8_t, uint8_t> signature;

const std::unordered_map<std::string, double> NOTE_MAP {
    {"c", 16.35},
    {"c#", 17.32},
    {"db", 17.32},
    {"d", 18.35},
    {"d#", 19.45},
    {"eb", 19.45},
    {"e", 20.60},
    {"f", 21.83},
    {"f#", 23.12},
    {"gb", 23.12},
    {"g", 24.50},
    {"g#", 25.96},
    {"ab", 25.96},
    {"a", 27.50},
    {"a#", 29.14},
    {"bb", 29.14},
    {"b", 30.87}
};

note::note(uint32_t duration, uint16_t frequency, std::function<double(double)> wave_function, bool is_rest, bool is_trans) : dur(duration), freq(frequency), wave(wave_function), rest(is_rest), trans(is_trans) {}

uint32_t parseDuration(std::string sdur) {
    double dur{static_cast<double>(signature.second) / (std::stoul(sdur) * bpm)};
    if (sdur.contains('.'))
        dur += dur / 2;
    return dur * 60 * 1000;
}

uint16_t parseFrequency(std::string sfreq) {
    uint16_t freq;
    if (std::isalpha(sfreq[0])) {
        switch (sfreq.size()) {
            case 2:
                freq = std::round(std::pow(2, std::stoul(sfreq.substr(1))) * NOTE_MAP.at(sfreq.substr(0, 1)));
                break;
            case 3:
                freq = std::round(std::pow(2, std::stoul(sfreq.substr(2))) * NOTE_MAP.at(sfreq.substr(0, 2)));
                break;
            default:
                throw;
        }
    } else
        freq = std::stoul(sfreq);
    return freq;
}

std::vector<note> parseChord(std::string line) {
    size_t n = line.find_last_of(',');
    if (n == line.npos) {
        const uint32_t dur{parseDuration(line.substr(line.find('[') + 1, line.find(']') - line.find('[') - 1))};
        const uint16_t freq{parseFrequency(line.substr(line.find('(') + 1, line.find(')') - line.find('(') - 1))};
        const std::function<double(double)> wave{wave::map.at(line.substr(line.find('{') + 1, line.find('}') - line.find('{') - 1))};
        return {{dur, freq, wave}};
    }
    std::vector<note> chord = parseChord(line.substr(0, n));
    chord.push_back(parseChord(line.substr(n + 1)).at(0));
    return chord;
}

void handleChords(std::unique_ptr<std::vector<std::vector<note>>>& chords) {
    for (size_t i = 0; i < chords->size(); i++) {
        if ((*chords)[i].size() > 1) {
            uint32_t min_dur{std::min_element((*chords)[i].cbegin(), (*chords)[i].cend(), [](note a, note b) {
                if (b.trans)
                    return true;
                else
                    return a.dur < b.dur;
            })->dur};
            for (note& nt : (*chords)[i]) {
                if (nt.dur < min_dur) {
                    std::vector<note> fchord{(*chords)[i]};
                    std::transform((*chords)[i].begin(), (*chords)[i].end(), fchord.begin(), [&](note a) {
                        a.dur = nt.dur;
                        return a;
                    });
                    std::vector<note> lchord{(*chords)[i]};
                    std::transform((*chords)[i].begin(), (*chords)[i].end(), lchord.begin(), [&](note a) {
                        a.dur -= nt.dur;
                        return a;
                    });
                    (*chords)[i] = lchord;
                    chords->insert(chords->cbegin() + i, fchord);
                    break;
                } else if (nt.dur > min_dur) {
                    note newnt{nt};
                    newnt.trans = true;
                    newnt.dur = nt.dur - min_dur;
                    nt.dur = min_dur;
                    if (i + 1 >= chords->size())
                        chords->push_back({newnt});
                    else
                        (*chords)[i + 1].push_back(newnt);
                }
            }
        }
    }
}

std::unique_ptr<std::vector<std::vector<note>>> parseFile(std::string filename) {
    std::ifstream file{filename, std::ios::app};
    if (!file.good()) {
        std::println(std::cerr, "{} doesn't exist", filename);
        exit(1);
    }
    std::unique_ptr<std::vector<std::vector<note>>> content{std::make_unique<std::vector<std::vector<note>>>()};
    std::string line;
    try {
        std::getline(file, line);
        bpm = static_cast<uint16_t>(std::stoul(line));
        std::getline(file, line);
        signature.first = static_cast<uint8_t>(std::stoul(line.substr(0, line.find('/'))));
        signature.second = static_cast<uint8_t>(std::stoul(line.substr(line.find('/') + 1)));
        while (std::getline(file, line)) {
            if (line.size() == 0 || line.substr(0, 2) == "//")
                continue;
            else if (line.contains("rest"))
                content->push_back({{parseDuration(line.substr(line.find('(') + 1, line.find(')') - line.find('(') - 1)), 0, nullptr, true}});
            else
                content->push_back(parseChord(line));
        }
        handleChords(content);
    } catch (...) {
        std::println(std::cerr, "failed to parse file");
        exit(1);
    }
    return content;
}