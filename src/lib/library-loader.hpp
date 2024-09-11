#ifndef LIBLOADER_H
#define LIBLOADER_H

#include <windows.h>
#include <iostream>

// Class to manage loading and unloading of DLLs
class LibLoader {
public:
    // Constructor that takes names of two DLLs to load
    LibLoader(const std::string& dll1, const std::string& dll2)
        : hDll1(nullptr), hDll2(nullptr) {
        // Load the first DLL
        hDll1 = LoadLibrary(dll1.c_str());
        if (!hDll1) {
            std::cerr << "Failed to load " << dll1 << std::endl;
            return;
        }

        // Load the second DLL
        hDll2 = LoadLibrary(dll2.c_str());
        if (!hDll2) {
            std::cerr << "Failed to load " << dll2 << std::endl;
            FreeLibrary(hDll1); // Free the first DLL if the second fails to load
            return;
        }

        // Retrieve a function pointer from the first DLL
        func1 = (FunctionType)GetProcAddress(hDll1, "FunctionFromFirstDll");
        if (!func1) {
            std::cerr << "Failed to get function from " << dll1 << std::endl;
            FreeLibrary(hDll1); // Free the first DLL
            FreeLibrary(hDll2); // Free the second DLL
            return;
        }

        // Retrieve a function pointer from the second DLL
        func2 = (FunctionType)GetProcAddress(hDll2, "FunctionFromSecondDll");
        if (!func2) {
            std::cerr << "Failed to get function from " << dll2 << std::endl;
            FreeLibrary(hDll1); // Free the first DLL
            FreeLibrary(hDll2); // Free the second DLL
            return;
        }
    }

    // Destructor that ensures DLLs are unloaded
    ~LibLoader() {
        if (hDll1) FreeLibrary(hDll1); // Unload the first DLL if it was loaded
        if (hDll2) FreeLibrary(hDll2); // Unload the second DLL if it was loaded
    }

    // Method to call both functions from the loaded DLLs
    void CombineFunctions() {
        if (func1) func1(); // Call function from the first DLL if it's valid
        if (func2) func2(); // Call function from the second DLL if it's valid
    }

private:
    typedef void (*FunctionType)(); // Typedef for function pointer type
    HMODULE hDll1; // Handle to the first DLL
    HMODULE hDll2; // Handle to the second DLL
    FunctionType func1; // Function pointer to a function in the first DLL
    FunctionType func2; // Function pointer to a function in the second DLL
};

#endif // LIBLOADER_H