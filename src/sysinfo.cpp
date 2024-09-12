#include <iostream>
#include <vector>
#include <string>

// Forward declarations
void windows_specific_function();
void unix_specific_function();
std::vector<std::string> get_system_info();

// Platform-specific function implementations
#ifdef _WIN32
    #include <windows.h>
    #define OS_WINDOWS
#elif defined(__unix__) || defined(__APPLE__)
    #include <unistd.h>
    #include <sys/utsname.h>
    #include <sys/sysctl.h>
    #define OS_UNIX
#else
    #error "Unsupported operating system"
#endif

typedef void (*SystemFunction)();
SystemFunction get_system_function();

int main() {
    std::cout << "OS Detection and System Information" << std::endl;
    std::cout << "-----------------------------------" << std::endl;

    #ifdef OS_WINDOWS
        std::cout << "Running on Windows" << std::endl;
    #elif defined(OS_UNIX)
        std::cout << "Running on Unix-like system" << std::endl;
    #endif

    // Simulated dynamic linking
    SystemFunction sys_func = get_system_function();
    sys_func();

    // Get additional system info
    std::vector<std::string> sys_info = get_system_info();
    std::cout << "\nAdditional System Information:" << std::endl;
    for (const auto& info : sys_info) {
        std::cout << info << std::endl;
    }

    return 0;
}

#ifdef OS_WINDOWS
void windows_specific_function() {
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    std::cout << "Windows-specific function:" << std::endl;
    std::cout << "Number of processors: " << sysInfo.dwNumberOfProcessors << std::endl;

    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);
    DWORDLONG totalVirtualMem = memInfo.ullTotalPageFile;

    std::cout << "Total virtual memory: " << totalVirtualMem / (1024 * 1024) << " MB" << std::endl;
}

std::vector<std::string> get_system_info() {
    std::vector<std::string> info;
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);

    info.push_back("Processor architecture: " + std::to_string(sysInfo.wProcessorArchitecture));
    info.push_back("Page size: " + std::to_string(sysInfo.dwPageSize) + " bytes");

    return info;
}
#elif defined(OS_UNIX)
void unix_specific_function() {
    long numCPU = sysconf(_SC_NPROCESSORS_ONLN);
    std::cout << "Unix-specific function:" << std::endl;
    std::cout << "Number of processors: " << numCPU << std::endl;

    // Use sysctl for macOS to get memory information
    int mib[2] = { CTL_HW, HW_PHYSMEM };
    uint64_t memSize;
    size_t len = sizeof(memSize);
    sysctl(mib, 2, &memSize, &len, NULL, 0);

    std::cout << "Total virtual memory: " << memSize / (1024 * 1024) << " MB" << std::endl;
}

std::vector<std::string> get_system_info() {
    std::vector<std::string> info;
    struct utsname unameData;
    uname(&unameData);

    info.push_back("System name: " + std::string(unameData.sysname));
    info.push_back("Node name: " + std::string(unameData.nodename));
    info.push_back("Release: " + std::string(unameData.release));
    info.push_back("Version: " + std::string(unameData.version));
    info.push_back("Machine: " + std::string(unameData.machine));

    return info;
}
#endif

SystemFunction get_system_function() {
    #ifdef OS_WINDOWS
        return windows_specific_function;
    #else
        return unix_specific_function;
    #endif
}