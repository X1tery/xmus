#pragma once
#include <string>
#include <fstream>

std::ofstream initOut(std::string filename, const uint32_t srate = 44100);