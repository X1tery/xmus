#pragma once
#include <cstdint>
#include <utility>
#include <string>
#include <vector>
#include <functional>
#include <memory>

extern uint16_t bpm;
extern std::pair<uint8_t, uint8_t> signature;

struct note {
    note(uint32_t duration, uint16_t frequency, std::function<double(double)> wave_function, bool is_rest = false, bool is_trans = false);
    uint32_t dur;
    uint16_t freq;
    std::function<double(double)> wave;
    bool rest;
    bool trans;
};

uint32_t parseDuration(std::string sdur);
uint16_t parseFrequency(std::string sfreq);
std::vector<note> parseChord(std::string line);
void handleChords(std::unique_ptr<std::vector<std::vector<note>>>& chords);
std::unique_ptr<std::vector<std::vector<note>>> parseFile(std::string filename);