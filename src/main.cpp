#include "lib/library-loader.hpp"
#include <cstdio>

int main(int argc, char* argv[]) {
    if (argc != 4 || std::string(argv[1]) != "link") {
        printf("Usage: %s link <first.dll> <second.dll>\n", argv[0]);
        return 1;
    }

    LibLoader loader(argv[2], argv[3]);
    loader.CombineFunctions();

    return 0;
}