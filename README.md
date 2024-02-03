# CPP_containers 

![_containers](misc/gifs/IMG_9775.gif)

This project implements custom C++ container classes similar to those in the C++ Standard Template Library (STL). The implementation includes various containers with unit tests, build automation, and coverage reporting.

## Project Structure

.
├── src/
│ └── lib/
│ ├── containers/
│ │ ├── array/ - Array container implementation
│ │ ├── list/ - List container implementation
│ │ ├── map/ - Map container implementation
│ │ ├── multiset/ - Multiset container (not implemented)
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

text

## Build System Overview

### Using Make with Top-Level Makefile

The main Makefile provides these targets:

```bash
make all           # Clean, format, test, install headers, create tar
make test          # Run all tests (units, memcheck, static, coverage)
make test_units    # Build and run unit tests
make test_coverage # Generate coverage report
make test_valgrind # Run tests with Valgrind
make test_sanitizer# Run tests with AddressSanitizer
make format_style  # Format code with clang-format
make install_headers # Install headers system-wide
make create_tar_headers # Create compressed tar of headers
make clean         # Clean build artifacts
Integration with CMake
CMake is used for actual building and testing. The Makefile delegates to CMake for:

Configuring different build types:

Debug: Standard debug build

Sanitizer: Build with AddressSanitizer

Coverage: Build with code coverage instrumentation

Generating build files in:

build/: Default build directory

coverage_report_build/: Special directory for coverage reports

Creating per-container test targets:

test_array_units, test_vector_coverage, etc.

test_units: Runs all container tests

Build Directories Purpose
build/ directory
Default directory for:

Regular debug builds

Sanitizer builds

Valgrind test execution

Contains compiled objects and test binaries

coverage_report_build/ directory
Dedicated directory for:

Coverage-instrumented builds

HTML coverage reports

Prevents mixing coverage data with regular builds

Preserves coverage reports between builds

Containers Documentation
Implemented Containers
::array
Fixed-size array container similar to std::array
Features: at(), front(), back(), fill(), iterators

::list
Doubly-linked list similar to std::list
Features: push_back(), push_front(), insert(), splice(), sort()

::vector
Dynamic array similar to std::vector
Features: reserve(), shrink_to_fit(), insert_many(), element access

::queue
FIFO queue adapter using list/vector
Features: push(), pop(), front(), back()

::stack
LIFO stack adapter using list/vector
Features: push(), pop(), top()

::map
(Partially implemented)
Key-value pair container using Red-Black tree

::set
(Not implemented - skeleton only)
Unique key container

::multiset
(Not implemented - skeleton only)
Multiple key container

Installation and Packaging
System-wide Installation:

bash
make install_headers
Installs headers to /usr/local/include/_containers/

Create Header Directory:

bash
make ___create_bin_headers___
Creates bin/containers with organized headers

Create Compressed Tar:

bash
make create_tar_headers
Generates _containers_headers.tar containing:

bin/_containers.h

bin/containers/ with all container headers

Container Implementation Details
All containers are header-only implementations following STL interfaces. Key implementation details:

Memory Management

Vector uses dynamic array with geometric resizing

List uses nodes with prev/next pointers

Queue/stack delegate to underlying container

Iterator Support
All containers implement standard iterators:

begin(), end()

cbegin(), cend() for const access

Exception Safety
Basic exception guarantee for most operations

Template Design
Containers are templated for any copyable type

Special Methods

insert_many(): Insert multiple elements at once

insert_many_back(): Append multiple elements

Testing Framework
Each container has dedicated unit tests:

Google Test framework

Test executables per container

Memory leak checks

Valgrind/AddressSanitizer integration

Run Tests:

bash
make test_units      # Run all unit tests
make test_vector     # Run vector tests only
make test_coverage   # Generate coverage report
Coverage reports are generated in HTML format and stored in coverage_report_build/.

Dependencies
Compiler: C++20 compatible (GCC/Clang)

Build: CMake ≥ 3.10, Make

Testing: Google Test, Valgrind, lcov

Formatting: clang-format ≥ 20

Static Analysis: cppcheck, clang-tidy

License
MIT License (see LICENSE file)

text

This README covers:
1. Project structure overview
2. Makefile usage with CMake integration
3. Build directories explanation
4. Container implementation status
5. Installation and packaging instructions
6. Testing methodology
7. Dependencies and licensing

The documentation clearly indicates which containers are fully implemented (array, list, vector, queue, stack), partially implemented (map), and not implemented (set, multiset). It also explains the purpose of both build directories and provides comprehensive usage instructions.


your readme file:
CPP2__containers Project
Overview
This project is a modern C++ implementation of key STL-like container classes—including array, list, vector, map, set, multiset, stack, queue, and tree—designed for learning, flexibility and robust testing. It offers deep modularity, advanced build options, and full system-wide installation capabilities.

Project Structure
text
.
├── Makefile
├── CMakeLists.txt
├── src/
│   └── lib/
│       ├── _containers.h
│       └── containers/
│           ├── array/
│           ├── list/
│           ├── vector/
│           ├── map/
│           ├── set/
│           ├── multiset/
│           ├── queue/
│           ├── stack/
│           └── tree/
├── build/
├── coverage_report_build/
├── materials/
│   └── containers_info.md
└── ...
src/lib/containers contains directories for each container, with implementations and unit tests.

materials/ includes documentation in multiple languages.

The build/ and coverage_report_build/ directories are created automatically for builds and code coverage reports (see below).

How to Build and Use
Using the Top-Level Makefile
The Makefile at the project root simplifies building, formatting, installing, and testing.

Typical Commands
make all
Clean, format, build, and run all tests and header installation.

make test
Runs unit tests, memory checks, static analysis, and code coverage.

make install_headers
Installs all headers system-wide (see below).

make create_tar_headers
Creates a compressed tarball of all exported headers.

Advanced Targets
make format_google_style
Runs Clang-Format according to Google style.

make test_valgrind and make test_sanitizer
Run memory checks with Valgrind or AddressSanitizer.

make clean
Remove build artifacts.

make uninstall_headers
Remove system-installed headers.

Directory Usage
build/
Used for standard debug/release/sanitizer builds and tests.
Keep this directory to separate object files/binaries from sources.

coverage_report_build/
Used exclusively for coverage builds (with coverage flags enabled).
Preserves the ability to analyze code coverage independently without polluting standard builds.
Retain this directory for preserving and serving HTML code coverage reports.

Using CMake Directly
Standard build:

text
cmake -B build -S .
cmake --build build
Run all unit tests:

text
make -C build test_units
Coverage build:

text
cmake -B coverage_report_build -S . -DCMAKE_BUILD_TYPE=Coverage
cmake --build coverage_report_build
make -C coverage_report_build test_coverage
System-Wide Header Installation
1. How to Install System-Wide
Install headers into /usr/local/include/_containers (by default) with:

text
sudo make install_headers
You may override the installation prefix:
make install_headers PREFIX=/custom/prefix

This copies all public headers into the appropriate system include folder for easy integration with other projects.

2. How to Create Directory with Headers
The process creates a bin/ directory containing hierarchical containers/ folders, reflecting all public headers.
These headers are then copied to the system include path or packaged as required.

3. How to Create Compressed Tar File with Headers
After building, run:

text
make create_tar_headers
This generates _containers_headers.tar in the project root, containing all public headers for distribution or backup.

The containers Directory: Full Description
Each subdirectory inside src/lib/containers/ implements a specific STL-like container.

Each container directory (e.g., array/, list/, etc.) contains:

The main header (e.g., _array.h)—the full container implementation (template/inline code).

unit_tests/tests.cpp—extensive GoogleTest-based C++ unit tests for that container.

A simple CMakeLists.txt for building and test target registration.

The modularity allows you to use any container independently (by including only its header) or as a full suite by including _containers.h.

Documentation: Containers Implementation
General Container Design
All containers are organized under the namespace .

Interface, behavior, and template argument semantics closely follow the C++ STL, but are original implementations.

Many containers enable advanced operations like move construction/assignment, in-place variadic insertion (insert_many, insert_many_back).

Individual Container Summaries
NameStatusFeatures
arrayFully implementedFixed-capacity, C++20-compliant, iterator support.
listFully implementedDoubly-linked, STL-compatible, advanced algorithms.
vectorFully implementedDynamic, custom memory resizing, all STL methods.
mapPartialCustom red-black tree logic, insert/search, in progress.
setNot implementedReserved for future.
multisetNot implementedReserved for future.
stackFully implementedContainer-adapter over list, full functionality.
queueFully implementedContainer-adapter over list, full functionality.
treePartially prototypedRed-black logic initial; not fully stable/covered.
Example: vector
Dynamic buffer, custom memory management, explicit array resizing and reserve, shrink_to_fit methods.

Methods: at, operator[], front, back, begin, end, insert, erase, push_back, pop_back, swap, clear, insert_many, insert_many_back, etc.

reserve and shrink_to_fit use manual memory (no realloc, only C++ semantics).

Example: list
Doubly-linked, circular sentinel node (m_end), iterator support.

Insert/remove at both ends, random-access via custom iterator, advanced splice/reverse/unique/sort/merge.

Robust iterator and exception safety checks.

Example: array
Fixed-size at compile time, full random access, STL-style operations.

Not-Yet-Implemented
set and multiset are declared/prototyped, not yet implemented. Methods may throw or be missing.

map and tree under development:
Custom red-black tree with basic iterator and insert support. Not fully completed as of this release.

Example Usage
cpp
#include <_containers.h>

::vector<int> v = {1, 2, 3};
v.push_back(4);
for (auto x : v) std::cout << x << std::endl;
Contributors & License
See LICENSE for legal information.

See CHANGELOG for feature progress.

Extensive multilingual information under materials/.

Notes on Code Coverage and Reports
coverage_report_build/ serves as a separate, clean build for generating and preserving code coverage reports (HTML and summary). Always build coverage targets here to keep artifacts and normal build outputs isolated.

You can view reports directly after build completion.

Future Work
Finish and stabilize map, set, multiset, and tree containers.

Expand performance benchmarks and examples.

Possibly add C bindings or Python integrations.

For full API reference, see header files and run make test to verify functionality.

Here is the combined and expanded README file in valid Markdown plain text format, merging your provided content with my earlier detailed version. It integrates your structure and phrasing with additional clarifications, examples, and explanations to create a more comprehensive and informative README for your project:

# CPP2__containers Project

## Overview

This project implements a modern **C++ STL-like container library** called `_containers`. It includes classic container types such as array, list, vector, map, set, multiset, stack, queue, and tree with a focus on:

- Education and deep understanding of container internals
- Flexibility for modular use of individual containers
- Robust testing and coverage reporting
- Full system-wide installation support
- Advanced build and formatting options

The implementations closely follow the STL interface semantics while providing original container code that leverages C++20 features.

## Project Structure

```

.
├── Makefile                  \# Top-level Makefile for building, testing, formatting
├── CMakeLists.txt            \# Project-wide CMake configuration
├── src/
│   └── lib/
│       ├── _containers.h  \# Master header including all containers
│       └── containers/       \# Source headers and implementation directories
│           ├── array/        \# Array container implementation
│           ├── list/         \# List container implementation
│           ├── vector/       \# Vector container implementation
│           ├── map/          \# Map container implementation (partial)
│           ├── set/          \# Set container (not implemented)
│           ├── multiset/     \# Multiset container (not implemented)
│           ├── queue/        \# Queue container implementation
│           ├── stack/        \# Stack container implementation
│           ├── tree/         \# Tree (red-black) implementation (partial)
│           └── testing_include/ \# Testing utilities and mocks
├── build/                    \# Default build directory for debug, release builds
├── coverage_report_build/    \# Dedicated coverage build directory
├── materials/                \# Documentation and materials
│   └── containers_info.md    \# Container descriptions and learning resources
└── LICENSE, CHANGELOG, README.md

```

- Each container is a header-only template implementation with comprehensive unit tests in their directories.
- `materials/` provides multilingual documentation and learning guides.
- `build/` and `coverage_report_build/` keep build artifacts and coverage reports separate for clarity.

## Build System Overview

### Using the Top-Level Makefile

You can build, test, format, install headers, and create header packages using simple Makefile targets:

| Target                | Description                                              |
|-----------------------|----------------------------------------------------------|
| `make all`            | Clean, format code, build library, run all tests, install headers, create tar archive |
| `make test`           | Run full suite of unit tests, memory checks, static analysis, coverage |
| `make test_units`     | Build and run only unit tests                             |
| `make test_coverage`  | Generate code coverage reports                            |
| `make test_valgrind`  | Run tests under Valgrind to detect memory issues         |
| `make test_sanitizer` | Run tests with AddressSanitizer enabled                   |
| `make format_style`   | Format all source files using clang-format (Google style)|
| `make install_headers`| Copy headers to system include directory                  |
| `make create_tar_headers` | Pack public headers into a `tar` archive                |
| `make clean`          | Remove all build artifacts and intermediate files         |
| `make uninstall_headers` | Remove installed headers from system directory           |

### Build Directories

- **`build/`**: Default directory for debug, release, and sanitizer builds with compiled objects and test binaries.
- **`coverage_report_build/`**: Dedicated for code coverage builds with instrumentation and HTML coverage reports. Keeps coverage results isolated from normal builds.

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


## Containers Overview

All containers are implemented under the `` namespace and are modeled on their STL counterparts, with original code focused on learning and experimentation.

### Container Status and Features

| Container | Status | Summary |
| :--: | :-- | :-- |
| `array` | Fully implemented | Fixed-size, C++20-compliant, supports iterators, element access (`at()`, `front()`, `back()`) |
| `list` | Fully implemented | Doubly-linked list with STL-like interface, advanced operations like `splice()`, `sort()`, `unique()` |
| `vector` | Fully implemented | Dynamic array with explicit memory management (`reserve()`, `shrink_to_fit()`, `insert_many()`) |
| `queue` | Fully implemented | FIFO container adapter using `list` or `vector` |
| `stack` | Fully implemented | LIFO container adapter using `list` or `vector` |
| `map` | Partially implemented | Red-black tree based key-value store, insertion and search mostly working |
| `set` | Not implemented | Placeholder/skeleton |
| `multiset` | Not implemented | Placeholder/skeleton |
| `tree` | Partially prototyped | Basic red-black tree logic under development |

### Selected Container Details

#### Vector

- Provides dynamic contiguous storage.
- Methods: `push_back()`, `pop_back()`, `insert()`, `erase()`, `reserve()`, `shrink_to_fit()`.
- Uses manual memory management with `new`/`delete` (no `realloc`), copying or moving elements on resize.
- Supports advanced insertion with `insert_many()` and `insert_many_back()` to add multiple elements at once.


#### List

- Doubly-linked circular list using sentinel node (`m_end`).
- Provides bidirectional iterator support.
- Supports typical list operations plus splice, reverse, sort, and unique with strong exception safety.


#### Array

- Fixed-size array container templated on size.
- Supports STL-style access and operations, providing a lightweight alternative to dynamic containers.


## Installation and Packaging

### System-Wide Header Installation

Install headers to the default system include directory:

```bash
sudo make install_headers
```

Override default prefix if desired:

```bash
make install_headers PREFIX=/custom/install/path
```

This installs headers into `/usr/local/include/_containers` or your specified prefix.

### Creating Header Packages

Create an organized directory tree of headers:

```bash
make ___create_bin_headers___
```

Create a compressed tarball of all public headers:

```bash
make create_tar_headers
```

You get `_containers_headers.tar` at the project root with all container headers in a `bin/containers` hierarchy.

## Testing Framework

- Each container has dedicated GoogleTest-based unit tests under its own directory.
- Tests cover functionality, boundary conditions, performance, and exception safety.
- Memory checks are integrated using Valgrind and AddressSanitizer via CI and `make test_valgrind`, `make test_sanitizer`.
- Code coverage generated and viewable from `coverage_report_build/` directory as HTML.

Run all tests simply with:

```bash
make test_units
```

Or test an individual container, for example:

```bash
make test_vector
```

Generate a coverage report:

```bash
make test_coverage
```


## Dependencies

- Compiler: C++20-compatible compiler (GCC, Clang)
- Build system: CMake (≥3.10), Make
- Testing: GoogleTest, Valgrind (optional memory checks), lcov (coverage)
- Formatting: clang-format (Google style)
- Static analysis: cppcheck, clang-tidy


## Example Usage

```cpp
#include <_containers.h>
#include <iostream>

int main() {
    ::vector<int> v = {1, 2, 3};
    v.push_back(4);

    for (auto x : v) {
        std::cout << x << '\n';
    }

    return 0;
}
```


## Contributing \& License

- Contributions are welcome! Please see the `CONTRIBUTING.md` (if present) or contact maintainers.
- Licensed under the **MIT License** (see LICENSE file for details).
- Development and change history tracked in `CHANGELOG`.


## Notes on Future Work

- Stabilize and fully implement the `map`, `set`, `multiset`, and `tree` containers.
- Expand benchmarking and usage examples.
- Possibly introduce C bindings or language bindings (e.g., Python).


## Summary

This README covers:

1. Comprehensive overview of project purpose and design
2. Detailed directory structure and build system usage
3. Clear instructions for building, testing, and packaging
4. Detailed container status with features and implementation notes
5. Usage examples and contribution/licensing info
6. Future plans and further enhancements

For full API documentation, consult the individual headers and run the test suite to verify functionality.