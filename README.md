# Simple Library Template

A streamlined CMake template for single-library projects.

![GitHub Workflow Status](https://img.shields.io/github/actions/workflow/status/CMake-Blueprints/simple-library-template/build-and-test.yml)

- Compatible with CMake 3.5+\*
- Library export headers generated automatically
- Supports installing Debug and Release configuration to the same directory
- Will install PDBs for MSVC builds

\*This project actually supports CMake 3.4, but support for versions older than 3.5 is being phased out by Kitware.

## Caveats

This project has been trimmed down to the bare minimum still considered useful. As such, there are some caveats to be aware of:

- Tests cannot access non-exported symbols from the library
- The CMake config file generated does not support versioning, and will not handle `find_package()` calls for dependencies. A downstream project must call `find_package(<dependency>)` before calling `find_package(SimpleLibrary)`.
- The library name is not namespaced and may conflict if used in a superbuild. This can be avoided by naming the target `${PACKAGE_NAME}_SimpleLib` instead, or ensuring the name is sufficiently unique.

## Building and Testing

This project uses CTest to run tests regardless of the test framework used.

<details>
<summary>Linux (Ninja build system)</summary>

The following commands will build the project with the default compiler in both Debug and Release configurations, run the tests in Debug configuration, and install the library to the `install` directory.

```bash
# Optional: Install ninja-build (Debian/Ubuntu shown)
sudo apt install ninja-build

# Configure and build (Release)
cmake -S . -B build/ -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build/ --target install
rm -rf build/

# Configure amnd build (Debug)
cmake -S . -B build/ -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build/ --target install

# Test
cd build/
ctest --output-on-failure
cd ..
```

The `install` directory will contain CMake configuration files for both Debug and Release configurations and can be used by other CMake projects. Add a `find_package(SimpleLibrary)` statement to the consuming project and make sure that the install path is added to the `CMAKE_PREFIX_PATH` variable.

</details>

<details>
<summary>Windows (Visual Studio 2022)</summary>

The following commands will build the project with MSVC v143 in both Debug and Release configurations, run the tests in Debug configuration, and install the library to the `install` directory.

```powershell
# Configure
cmake -S . -B .\build\ -G "Visual Studio 17 2022" -A x64

# Build
cmake --build .\build\ --target install --config Debug
cmake --build .\build\ --target install --config Release

# Test
cd .\build\
ctest --output-on-failure -C Debug
cd ..
```

The `install` directory will contain CMake configuration files for both Debug and Release configurations and can be used by other CMake projects. Add a `find_package(SimpleLibrary)` statement to the consuming project and make sure that the install path is added to the `CMAKE_PREFIX_PATH` variable.

</details>

## Adapting This Template

This template is designed to be easily adapted to your needs. The following steps will help you get started:

1. Click on "Use this template" at the top of the repository page to create a copy of this repository with a clean history.
2. Replace the placeholder library names with your own library name. The following files and paths will need to be adjusted:

   - Top-level `CMakeLists.txt` file
      - Project name specified for the `project()` call
   - File paths in the `include/` directory
   - `src/CMakeLists.txt` file
      - `SimpleLibrary` target name
      - `simplelib_export.h` filename in `set(EXPORT_HEADER ...)`
      - `SIMPLELIB_EXPORT` macro name in the `generate_export_header()` call
      - The `simplelib` include directory suffix in the `install(TARGETS ...)` call
   - `tests/CMakeLists.txt` file
      - `SimpleLibrary` and `SimpleLibTest` target names

3. Update the `PUBLIC_HEADERS` list and `target_sources()` call in `src/CMakeLists.txt` as you replace the dummy sources with your own files.
4. (Optional) If you choose not to use a subdirectory for your include files (instead of the redundant `include/simplelib/simplelib.h`), be sure to remove the suffix from the `install(TARGETS ...)` call in `src/CMakeLists.txt`. 

## Contributing

If you have any suggestions or improvements, please open an issue or pull request.

## License

This is free and unencumbered software released into the public domain.

For more information, please refer to the LICENSE file or <https://unlicense.org>.
