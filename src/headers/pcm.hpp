#pragma once
#include <parser.hpp>
#include <fstream>
#include <memory>
#include <list>

extern uint64_t srate;

template <typename T>
void writeTo(std::ofstream& file, T byte);
void writeSheet(std::ofstream& file, std::vector<std::vector<note>>& notes);
void writeChord(std::shared_ptr<std::list<uint16_t>> data, std::vector<note>& chord);