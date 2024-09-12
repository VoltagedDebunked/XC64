#ifndef LIBLOADER_H
#define LIBLOADER_H

#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif

#include <iostream>
#include <string>

class LibLoader {
public:
    LibLoader(const std::string& lib1, const std::string& lib2)
        : handle1(nullptr), handle2(nullptr), func1(nullptr), func2(nullptr) {
        if (!loadLib(lib1, lib2)) {
            return;
        }

        if (!retrieveFunction("FunctionFromFirstLib", func1, handle1, lib1)) {
            unloadLib(handle1);
            unloadLib(handle2);
            return;
        }

        if (!retrieveFunction("FunctionFromSecondLib", func2, handle2, lib2)) {
            unloadLib(handle1);
            unloadLib(handle2);
            return;
        }
    }

    ~LibLoader() {
        if (handle1) unloadLib(handle1);
        if (handle2) unloadLib(handle2);
    }

    void CombineFunctions() {
        if (func1) func1();
        if (func2) func2();
    }

private:
    typedef void (*FunctionType)();

#ifdef _WIN32
    HMODULE handle1;
    HMODULE handle2;
#else
    void* handle1;
    void* handle2;
#endif

    FunctionType func1;
    FunctionType func2;

    bool loadLib(const std::string& lib1, const std::string& lib2) {
#ifdef _WIN32
        handle1 = LoadLibrary(lib1.c_str());
        if (!handle1) {
            std::cerr << "Failed to load " << lib1 << std::endl;
            return false;
        }

        handle2 = LoadLibrary(lib2.c_str());
        if (!handle2) {
            std::cerr << "Failed to load " << lib2 << std::endl;
            FreeLibrary(handle1);
            return false;
        }
#else
        handle1 = dlopen(lib1.c_str(), RTLD_LAZY);
        if (!handle1) {
            std::cerr << "Failed to load " << lib1 << ": " << dlerror() << std::endl;
            return false;
        }

        handle2 = dlopen(lib2.c_str(), RTLD_LAZY);
        if (!handle2) {
            std::cerr << "Failed to load " << lib2 << ": " << dlerror() << std::endl;
            dlclose(handle1);
            return false;
        }
#endif
        return true;
    }

    void unloadLib(void* handle) {
#ifdef _WIN32
        FreeLibrary(static_cast<HMODULE>(handle));
#else
        dlclose(handle);
#endif
    }

    bool retrieveFunction(const char* functionName, FunctionType& func, void* handle, const std::string& libName) {
#ifdef _WIN32
        func = reinterpret_cast<FunctionType>(GetProcAddress(static_cast<HMODULE>(handle), functionName));
#else
        func = reinterpret_cast<FunctionType>(dlsym(handle, functionName));
#endif
        if (!func) {
#ifdef _WIN32
            std::cerr << "Failed to get function " << functionName << " from " << libName << std::endl;
#else
            std::cerr << "Failed to get function " << functionName << " from " << libName << ": " << dlerror() << std::endl;
#endif
            return false;
        }
        return true;
    }
};

#endif // LIBLOADER_H