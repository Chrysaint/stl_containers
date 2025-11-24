# CPP_containers

This project implements custom C++ container classes similar to those in the C++ Standard Template Library (STL). The implementation includes various containers with unit tests, build automation, and coverage reporting.

## Project Structure

```
.
├── src/
│ └── lib/
│ ├── containers/
│ │ ├── array/ - Array container implementation
│ │ ├── list/ - List container implementation
│ │ ├── map/ - Map container implementation
│ │ ├── multiset/ - Multiset container
│ │ ├── queue/ - Queue container implementation
│ │ ├── set/ - Set container implementation
│ │ ├── stack/ - Stack container implementation
│ │ ├── tree/ - Tree implementation (internal)
│ │ ├── vector/ - Vector container implementation
│ │ └── testing_include - Testing utilities
│ └── _containers.h - Main header including all containers
├── build/ - Default build directory
├── coverage_report_build/ - Coverage report build directory
├── Makefile - Top-level Makefile
└── CMakeLists.txt - Top-level CMake configuration
```

## Build System Overview

### Using CMake Directly

Configure and build with CMake commands:

```bash
# Standard build
cmake -B build -S .
cmake --build build

# Run all unit tests
make -C build test_units

# Coverage build and report generation
cmake -B coverage_report_build -S . -DCMAKE_BUILD_TYPE=Coverage
cmake --build coverage_report_build
make -C coverage_report_build test_coverage
```

### The main Makefile provides these targets:

    - make all           # Clean, format, test, install headers, create tar
    - make test          # Run all tests (units, memcheck, static, coverage)
    - make test_units    # Build and run unit tests
    - make test_coverage # Generate coverage report
    - make test_valgrind # Run tests with Valgrind
    - make test_sanitizer# Run tests with AddressSanitizer
    - make format_style  # Format code with clang-format
    - make install_headers # Install headers system-wide
    - make create_tar_headers # Create compressed tar of headers
    - make clean         # Clean build artifacts

Integration with CMake
CMake is used for actual building and testing. The Makefile delegates to CMake for:

#### Configuring different build types:

    - Debug: Standard debug build

    - Sanitizer: Build with AddressSanitizer

    - Coverage: Build with code coverage instrumentation

    - Generating build files in:
        - build/: Default build directory
        - coverage_report_build/: Special directory for coverage reports

    - Creating per-container test targets:
        - test_array_units,
        - test_vector_coverage,
        - etc.

    - test_units: Runs all container tests

    - Regular debug builds

    - Sanitizer builds

    - Valgrind test execution

    - coverage_report_build/ directory for:
        - Coverage-instrumented builds
        - HTML coverage reports
        - Prevents mixing coverage data with regular builds
        - Preserves coverage reports between builds

## Containers Documentation
Implemented Containers:

| Container name | About | Features |
|----------------|-------|----------|
| ::array | Fixed-size array container similar to std::array | at(), front(), back(), fill(), iterators |
| ::list | Doubly-linked list similar to std::list | push_back(), push_front(), insert(), splice(), sort() |
| ::vector | Dynamic array similar to std::vector | reserve(), shrink_to_fit(), insert_many(), element access |
| ::queue | FIFO queue adapter using list/vector | push(), pop(), front(), back() |
| ::stack | LIFO stack adapter using list/vector | push(), pop(), top() |
| ::map | (Partially implemented) | Key value pair container using Red-Black tree |
| ::set | Unique key container using Red-Black tree | insert(), find(), erase(), merge(), insert_many() |
| ::multiset | Multiple key container using Red-Black tree | insert(), count(), equal_range(), lower_bound(), upper_bound() |

## Installation and Packaging
### System-wide Installation:

```bash
make install_headers
```
Installs headers to /usr/local/include/_containers/

### Create Header Directory:

```bash
make ___create_bin_headers___
```
Creates bin/containers with organized headers
### Create Compressed Tar:

```bash
make create_tar_headers
```
Generates _containers_headers.tar containing:
bin/_containers.h

bin/containers/ with all container headers

## Container Implementation Details
All containers are header-only implementations following STL interfaces. Key implementation details:

    - Memory Management

    - Vector uses dynamic array with geometric resizing

    - List uses nodes with prev/next pointers

    - Queue/stack delegate to underlying container

## Iterator Support
All containers implement standard iterators:

| Method | Description |
|--------|-------------|
| begin() | Returns the iterator on a first elemenet |
| end() | Returns the iterator on the end of a container |
| cbegin() | Returns the const iterator on a first element |
| cend() | Returns the const iterator on the end of a container |

## Exception Safety
Basic exception guarantee for most operations

## Template Design
Containers are templated for any copyable type

## Special Methods

| Method | Description |
|--------|-------------|
| insert_many() | Insert multiple elements at once |
| insert_many_back() | Append multiple elements |

## Testing Framework
Each container has dedicated unit tests:

    - Google Test framework

    - Test executables per container

    - Memory leak checks

    - Valgrind/AddressSanitizer integration

### Run Tests:

```bash
make test_units      # Run all unit tests
make test_vector     # Run vector tests only
make test_coverage   # Generate coverage report
```
Coverage reports are generated in HTML format and stored in coverage_report_build/.

## Dependencies

1) Compiler: C++20 compatible (GCC/Clang)
2) Build: CMake ≥ 3.10, Make
3) Testing: Google Test, Valgrind, lcov
4) Formatting: clang-format ≥ 20
5) Static Analysis: cppcheck, clang-tidy

License
MIT License (see LICENSE file)

## Examples

1. List
    - Doubly-linked, circular sentinel node (m_end), iterator support.
    - Insert/remove at both ends, random-access via custom iterator, advanced splice/reverse/unique/sort/merge.
    - Robust iterator and exception safety checks.

2. Array:
    - Fixed-size at compile time, full random access, STL-style operations.

### Example Usage
```cpp
#include <_containers.h>

::vector<int> v = {1, 2, 3};
v.push_back(4);
for (auto x : v) std::cout << x << std::endl;
```

## Overview

This project implements a modern **C++ STL-like container library** called `_containers`. It includes classic container types such as array, list, vector, map, set, multiset, stack, queue, and tree with a focus on:

- Education and deep understanding of container internals
- Flexibility for modular use of individual containers
- Robust testing and coverage reporting
- Full system-wide installation support
- Advanced build and formatting options

The implementations closely follow the STL interface semantics while providing original container code that leverages C++20 features.

