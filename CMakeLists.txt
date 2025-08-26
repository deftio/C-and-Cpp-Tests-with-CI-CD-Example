# CMakeLists.txt for C/C++ Testing with CI/CD Example
# 
# CMake is a cross-platform build system generator that creates native build files
# (Makefiles on Unix, Visual Studio projects on Windows, etc.) from this configuration.
# 
# Author: M A Chatterjee <deftio [at] deftio [dot] com>
# 
# Usage:
#   mkdir build           # Create a build directory (out-of-source build)
#   cd build             # Enter the build directory
#   cmake ..             # Generate build files
#   make                 # Build the project
#   make test           # Run tests
#   make coverage       # Generate coverage report (if enabled)

# Minimum CMake version required
# Version 3.10 is widely available and supports modern CMake features
cmake_minimum_required(VERSION 3.10)

# Project definition
# This sets the project name and specifies we're using C language
# VERSION follows semantic versioning (major.minor.patch)
project(CTestingExample 
    VERSION 1.0.4
    DESCRIPTION "Simple C library with unit testing and code coverage"
    LANGUAGES C)

# Set C standard
# C99 is the minimum required, but the code is compatible with all later standards
# Users can override with: cmake -DCMAKE_C_STANDARD=11 (or 17, 23, etc.)
if(NOT CMAKE_C_STANDARD)
    set(CMAKE_C_STANDARD 99)
endif()
set(CMAKE_C_STANDARD_REQUIRED ON)
# Allow newer standards if available
set(CMAKE_C_EXTENSIONS OFF)

# Compiler flags for all builds
# -Wall: Enable all common warnings
# -Wextra: Enable extra warning flags
add_compile_options(-Wall -Wextra)

# Option to enable code coverage (default: ON)
# Users can disable with: cmake -DENABLE_COVERAGE=OFF ..
option(ENABLE_COVERAGE "Enable code coverage reporting" ON)

# Coverage configuration
# Code coverage requires special compiler flags to instrument the code
if(ENABLE_COVERAGE)
    # Check if we're using GCC or Clang (both support gcov-style coverage)
    if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
        message(STATUS "Code coverage enabled")
        
        # Add coverage flags to both compilation and linking
        # -fprofile-arcs: Insert arc-based program flow instrumentation
        # -ftest-coverage: Produce .gcno files for gcov
        # --coverage: Shorthand that enables both flags above (alternative)
        add_compile_options(-fprofile-arcs -ftest-coverage)
        add_link_options(-fprofile-arcs -ftest-coverage)
        
        # Use -O0 (no optimization) for accurate coverage data
        # Optimizations can eliminate code paths and skew coverage metrics
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
    else()
        message(WARNING "Code coverage requested but compiler ${CMAKE_C_COMPILER_ID} is not supported")
        set(ENABLE_COVERAGE OFF)
    endif()
endif()

# Library definition
# Create a static library from our source files
# STATIC means the library will be linked statically (included in the executable)
add_library(testlib STATIC
    lib.c
    lib.h
)

# Include directories for the library
# PUBLIC means these includes are needed by both the library and its users
target_include_directories(testlib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Test executable
# This creates the test program that will exercise our library
add_executable(test-library
    test-library.c
)

# Link the test executable with our library
# Also link with math library (m) and ncurses for demonstration
target_link_libraries(test-library
    testlib      # Our library
    m           # Math library (for mathematical functions)
    ncurses     # NCurses library (for terminal UI, if needed)
)

# Enable testing support
# This must be called to use CTest (CMake's testing framework)
enable_testing()

# Register our test executable with CTest
# NAME: How the test appears in test reports
# COMMAND: What to run (our test executable)
add_test(
    NAME LibraryTests
    COMMAND test-library
)

# Custom target for coverage report
# This creates a 'make coverage' command that runs tests and generates reports
if(ENABLE_COVERAGE)
    # Find required coverage tools
    find_program(GCOV_EXECUTABLE gcov)
    find_program(LCOV_EXECUTABLE lcov)
    find_program(GENHTML_EXECUTABLE genhtml)
    
    if(GCOV_EXECUTABLE)
        # Create custom target for coverage
        add_custom_target(coverage
            # First, clean any existing coverage data
            COMMAND ${CMAKE_COMMAND} -E remove_directory coverage
            COMMAND ${CMAKE_COMMAND} -E make_directory coverage
            
            # Run the tests to generate coverage data
            COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
            
            # Process coverage data with gcov
            COMMAND ${GCOV_EXECUTABLE} -b -c lib.c
            
            # Optional: If lcov is available, generate HTML report
            COMMAND ${CMAKE_COMMAND} -E echo "Coverage report generated in *.gcov files"
            
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            DEPENDS test-library
            COMMENT "Generating code coverage report..."
        )
        
        # If lcov is available, add HTML report generation
        if(LCOV_EXECUTABLE AND GENHTML_EXECUTABLE)
            add_custom_command(TARGET coverage POST_BUILD
                COMMAND ${LCOV_EXECUTABLE} --capture --directory . --output-file coverage.info --ignore-errors unused,unsupported
                COMMAND ${LCOV_EXECUTABLE} --remove coverage.info '*/test-library.c' --output-file coverage.info --ignore-errors unused,unsupported
                COMMAND ${GENHTML_EXECUTABLE} coverage.info --output-directory coverage --ignore-errors unused,unsupported
                COMMAND ${CMAKE_COMMAND} -E echo "HTML coverage report generated in coverage/index.html"
                WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            )
        endif()
    else()
        message(STATUS "gcov not found - coverage target will not be available")
    endif()
endif()

# Installation rules (optional)
# These define how to install the library for system-wide use
install(TARGETS testlib
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(FILES lib.h
    DESTINATION include
)

# Print configuration summary
message(STATUS "")
message(STATUS "Configuration Summary:")
message(STATUS "  C Compiler: ${CMAKE_C_COMPILER}")
message(STATUS "  Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  Coverage Enabled: ${ENABLE_COVERAGE}")
message(STATUS "")
message(STATUS "Build with:")
message(STATUS "  mkdir build && cd build")
message(STATUS "  cmake ..")
message(STATUS "  make")
message(STATUS "  make test")
if(ENABLE_COVERAGE)
    message(STATUS "  make coverage  # Generate coverage report")
endif()
message(STATUS "")