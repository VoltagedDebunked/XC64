#ifndef LIBLOADER_H
#define LIBLOADER_H

#include <windows.h>
#include <iostream>
#include <string>

class LibLoader {
public:
    ///
    /// Constructor that takes the names of two DLLs to load.
    ///
    LibLoader(const std::string& dll1, const std::string& dll2)
        : hDll1(nullptr), hDll2(nullptr), func1(nullptr), func2(nullptr) {
        ///
        /// Attempt to load the DLLs.
        ///
        if (!loadDll(dll1, dll2)) {
            return; /// Exit if DLLs could not be loaded.
        }

        ///
        /// Attempt to retrieve function pointers from the DLLs.
        ///
        if (!retrieveFunction("FunctionFromFirstDll", func1, hDll1, dll1)) {
            FreeLibrary(hDll1); /// Unload DLLs if function retrieval fails.
            FreeLibrary(hDll2);
            return; /// Exit if function retrieval fails.
        }
        if (!retrieveFunction("FunctionFromSecondDll", func2, hDll2, dll2)) {
            FreeLibrary(hDll1); /// Unload DLLs if function retrieval fails.
            FreeLibrary(hDll2);
            return; /// Exit if function retrieval fails.
        }
    }

    ///
    /// Destructor that ensures DLLs are unloaded.
    ///
    ~LibLoader() {
        if (hDll1) FreeLibrary(hDll1); /// Unload the first DLL if it was loaded.
        if (hDll2) FreeLibrary(hDll2); /// Unload the second DLL if it was loaded.
    }

    ///
    /// Method to call both functions from the loaded DLLs.
    ///
    void CombineFunctions() {
        if (func1) func1(); /// Call function from the first DLL if it's valid.
        if (func2) func2(); /// Call function from the second DLL if it's valid.
    }

private:
    typedef void (*FunctionType)(); /// Typedef for function pointer type.
    HMODULE hDll1; /// Handle to the first DLL.
    HMODULE hDll2; /// Handle to the second DLL.
    FunctionType func1; /// Function pointer to a function in the first DLL.
    FunctionType func2; /// Function pointer to a function in the second DLL.

    ///
    /// Attempts to load the DLLs and returns true if successful, false otherwise.
    ///
    bool loadDll(const std::string& dll1, const std::string& dll2) {
        hDll1 = LoadLibrary(dll1.c_str()); /// Load the first DLL.
        if (!hDll1) {
            std::cerr << "Failed to load " << dll1 << std::endl;
            return false; /// Return false if loading fails.
        }

        hDll2 = LoadLibrary(dll2.c_str()); /// Load the second DLL.
        if (!hDll2) {
            std::cerr << "Failed to load " << dll2 << std::endl;
            FreeLibrary(hDll1); /// Unload the first DLL if the second fails to load.
            return false; /// Return false if loading fails.
        }
        return true; /// Return true if both DLLs are loaded successfully.
    }

    ///
    /// Attempts to retrieve a function pointer from a DLL and returns true if successful, false otherwise.
    ///
    bool retrieveFunction(const char* functionName, FunctionType& func, HMODULE hDll, const std::string& dllName) {
        func = reinterpret_cast<FunctionType>(GetProcAddress(hDll, functionName)); /// Retrieve the function pointer.
        if (!func) {
            std::cerr << "Failed to get function " << functionName << " from " << dllName << std::endl;
            return false; /// Return false if retrieval fails.
        }
        return true; /// Return true if function pointer is retrieved successfully.
    }
};

#endif // LIBLOADER_H