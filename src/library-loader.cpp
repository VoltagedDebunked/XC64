#include "lib/library-loader.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <first.dll> <second.dll>\n";
        return 1;
    }

    LibLoader loader(argv[1], argv[2]);
    loader.CombineFunctions();

    return 0;
}