#ifndef LIBLOADER_H
#define LIBLOADER_H

#include <windows.h>
#include <iostream>

class LibLoader {
public:
    LibLoader(const std::string& dll1, const std::string& dll2)
        : hDll1(nullptr), hDll2(nullptr) {
        hDll1 = LoadLibrary(dll1.c_str());
        if (!hDll1) {
            std::cerr << "Failed to load " << dll1 << std::endl;
            return;
        }

        hDll2 = LoadLibrary(dll2.c_str());
        if (!hDll2) {
            std::cerr << "Failed to load " << dll2 << std::endl;
            FreeLibrary(hDll1);
            return;
        }

        func1 = (FunctionType)GetProcAddress(hDll1, "FunctionFromFirstDll");
        if (!func1) {
            std::cerr << "Failed to get function from " << dll1 << std::endl;
            FreeLibrary(hDll1);
            FreeLibrary(hDll2);
            return;
        }

        func2 = (FunctionType)GetProcAddress(hDll2, "FunctionFromSecondDll");
        if (!func2) {
            std::cerr << "Failed to get function from " << dll2 << std::endl;
            FreeLibrary(hDll1);
            FreeLibrary(hDll2);
            return;
        }
    }

    ~LibLoader() {
        if (hDll1) FreeLibrary(hDll1);
        if (hDll2) FreeLibrary(hDll2);
    }

    void CombineFunctions() {
        if (func1) func1();
        if (func2) func2();
    }

private:
    typedef void (*FunctionType)();
    HMODULE hDll1;
    HMODULE hDll2;
    FunctionType func1;
    FunctionType func2;
};

#endif // LIBLOADER_H