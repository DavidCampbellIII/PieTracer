# CMakeList.txt : CMake project for PieTracer, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("PieTracer" VERSION 1.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SHARED_SOURCES "src/Shared/*.cpp")
file(GLOB_RECURSE TEST_SOURCES "Tests/*.cpp")

# Add source to this project's executable.
add_executable (PieTracer "src/Main.cpp")
target_sources(PieTracer PRIVATE ${SHARED_SOURCES})
target_include_directories(PieTracer PRIVATE "src/Shared")


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET PieTracer PROPERTY CXX_STANDARD 20)
endif()


Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0 # or a later release
)

FetchContent_MakeAvailable(Catch2)

add_executable(PieTracerTests ${TEST_SOURCES})
target_sources(PieTracerTests PRIVATE ${SHARED_SOURCES})

target_include_directories(PieTracerTests PRIVATE "src/Shared")
target_include_directories(PieTracerTests PRIVATE "Tests")
target_link_libraries(PieTracerTests PRIVATE Catch2::Catch2WithMain)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
catch_discover_tests(PieTracerTests)
