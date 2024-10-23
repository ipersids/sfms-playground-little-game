cmake_minimum_required(VERSION 3.28)
# project setup
project(LittleGame LANGUAGES CXX)

# use C++ standard version 17
set(CMAKE_CXX_STANDARD 17)
# produce non-optimized code with debug symbols
set(CMAKE_BUILD_TYPE Debug)

# binary output directory (executable)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# build static libraries (desable shared library)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# --------------------- LIBRARIES --------------------- #

# fetching SFML 2.6.x version from GitHub
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW TRUE
    EXCLUDE_FROM_ALL
    SYSTEM
)
FetchContent_MakeAvailable(SFML)

# fetching Box2D main version from GitHub
FetchContent_Declare(box2d
	GIT_REPOSITORY https://github.com/erincatto/box2d.git
	GIT_TAG main
	GIT_SHALLOW TRUE
	GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(box2d)

# ------------------------------------------------------ #

# add all .cpp, - files under src/ directory
file(GLOB SOURCES_CPP "src/*.cpp")
# add all .hpp files from multiple directories
set(SOURCES_HPP
    "${CMAKE_SOURCE_DIR}/build/_deps/sfml-src/include"          # SFML headers
    "${CMAKE_SOURCE_DIR}/include"                               # project headers
    "${CMAKE_SOURCE_DIR}/build/_deps/box2d-src/include/box2d"   # Box2D headers
    "build/_deps/box2d-src/src"
)

message(
    STATUS "SRC directory source code files: \n
    \t-- HEADERS: ${SOURCES_HPP}
    \t-- CPP SOURCE: ${SOURCES_CPP}\n"
)

add_executable(main)
target_sources(main PUBLIC ${SOURCES_CPP})
target_include_directories(main PRIVATE ${SOURCES_HPP})
target_link_libraries(main PRIVATE sfml-graphics sfml-window sfml-audio sfml-network box2d)
target_compile_features(main PRIVATE cxx_std_17)

# get a lot of warnings
if(MSVC)
    target_compile_options(main PRIVATE /Wall)
else()
    # gcc and clang
    target_compile_options(main PRIVATE -Wall -Wextra -pedantic -Wno-missing-field-initializers -Wno-c99-extensions)
endif()

if(WIN32)
    add_custom_command(
        TARGET main
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:main>
        VERBATIM)
endif()
