#pragma once
#include <parser.hpp>
#include <fstream>

extern uint64_t srate;

void writeSheet(std::ofstream& file, std::vector<std::vector<note>>& notes);
void writeChord(std::ofstream& file, std::vector<note>& chord);