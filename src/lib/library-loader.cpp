#include "library-loader.hpp"

int main() {
    // Create an instance of LibLoader with the DLL filenames
    LibLoader loader("first.dll", "second.dll");

    // Call the CombineFunctions method to execute the functions from the DLLs
    loader.CombineFunctions();

    return 0;
}