#include <input.hpp>
#include <file.hpp>
#include <pcm.hpp>
#include <wave.hpp>
#include <parser.hpp>

int main(int argc, char** argv) {
    processInput(argc, argv);
    auto sheet{parseFile(inname)};
    auto file{initOut(outname)};
    writeSheet(file, *sheet);
    file.close();
    return 0;
}