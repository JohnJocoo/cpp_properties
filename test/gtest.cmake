# We need thread support
find_package(Threads REQUIRED)

# Enable ExternalProject CMake module
include(ExternalProject)

# Download and install GoogleTest
ExternalProject_Add(
    gtest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.8.0
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
    CMAKE_ARGS
        "-G" "${CMAKE_GENERATOR}"
        "-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}"
        "-DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}"
        "-DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}"
        "-DCMAKE_CONFIGURATION_TYPES=${CMAKE_CONFIGURATION_TYPES}"
        "-DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}"
    # Disable install step
    INSTALL_COMMAND ""
)

# Get GTest source and binary directories from CMake project
ExternalProject_Get_Property(gtest source_dir binary_dir)

if (MSVC)
    set(GTEST_LIB_PATH "Debug/")
    set(GTEST_LIB_NAME "gtest.lib")
    set(GTEST_MAIN_LIB_NAME "gtest_main.lib")
    set(GMOCK_LIB_NAME "gmock.lib")
elseif (CMAKE_GENERATOR STREQUAL Xcode)
    set(GTEST_LIB_PATH "Debug/")
    set(GTEST_LIB_NAME "libgtestd.a")
    set(GTEST_MAIN_LIB_NAME "libgtest_maind.a")
    set(GMOCK_LIB_NAME "libgmockd.a")
else (MSVC)
    set(GTEST_LIB_PATH "")
    set(GTEST_LIB_NAME "libgtest.a")
    set(GTEST_MAIN_LIB_NAME "libgtest_main.a")
    set(GMOCK_LIB_NAME "libgmock.a")
endif (MSVC)

# Create a libgtest target to be used as a dependency by test programs
add_library(libgtest IMPORTED STATIC GLOBAL)
add_dependencies(libgtest gtest)

# Set libgtest properties
set_target_properties(libgtest PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/googlemock/gtest/${GTEST_LIB_PATH}${GTEST_LIB_NAME}"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

add_library(libgtest_main IMPORTED STATIC GLOBAL)
add_dependencies(libgtest_main libgtest)

set_target_properties(libgtest_main PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/googlemock/gtest/${GTEST_LIB_PATH}${GTEST_MAIN_LIB_NAME}"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

# Create a libgmock target to be used as a dependency by test programs
add_library(libgmock IMPORTED STATIC GLOBAL)
add_dependencies(libgmock gtest)

# Set libgmock properties
set_target_properties(libgmock PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/googlemock/${GTEST_LIB_PATH}${GMOCK_LIB_NAME}"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

# I couldn't make it work with INTERFACE_INCLUDE_DIRECTORIES
include_directories("${source_dir}/googletest/include"
                    "${source_dir}/googlemock/include")
                    
