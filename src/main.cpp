#include <file.hpp>
#include <pcm.hpp>
#include <wave.hpp>
#include <parser.hpp>

int main(int argc, char** argv) {
    auto file{initOut("test.wav")};
    auto sheet{parseFile("extra/test2.xmus")};
    writeSheet(file, *sheet);
    file.close();
    return 0;
}