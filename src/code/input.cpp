#include <input.hpp>
#include <iostream>
#include <print>

std::string inname;
std::string outname;

void processInput(int argc, char** argv) {
    if (argc != 3) {
        std::println(std::cerr, "USAGE: {} [in_file.xmus] [out_file.wav]", argv[0]);
        exit(1);
    }
    inname = argv[1];
    outname = argv[2];
}