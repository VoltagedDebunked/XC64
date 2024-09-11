# XC64

XC64 is a robust framework designed for developing dynamic applications using C and C++. It offers a core system that facilitates the creation, management, and execution of modular and scalable software components. The framework is built with performance and flexibility in mind, leveraging C++'s powerful features and CMake's build automation capabilities.

## Key Features

- **Dynamic Module Management**: Allows for the seamless integration and management of dynamic libraries and plugins.
- **Core System**: Provides a solid foundation for application development with essential services and abstractions.
- **CMake Integration**: Utilizes CMake for efficient build configuration and management, supporting complex project structures and dependencies.

## Getting Started

1. **Setup CMake**: Ensure that CMake is installed on your system. You can download it from the [CMake official website](https://cmake.org/download/).

2. **Clone the Repository**: Obtain the XC64 framework source code from its repository.

    ```bash
    git clone <repository-url>
    ```

3. **Configure the Project**: Navigate to the project directory and configure the build with CMake.

```bash
cd xc64
mkdir build
cd build
cmake ..
```

4. **Build the Project**: Compile the project using CMake.

```bash
cmake --build .
```

5. **Run the Application**: Execute your dynamic application built with XC64.

```bash
./your_application
```

## Contributing

If you'd like to contribute to the XC64 framework, please review our [contribution guidelines](CONTRIBUTING.md) and submit your pull requests.

## License

XC64 is licensed under the [Apache 2.0 License](LICENSE).