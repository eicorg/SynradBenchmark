cmake_minimum_required (VERSION 3.5 FATAL_ERROR)
project (ANA C CXX)

#----------------------------------------------------------------------------
# Find ROOT
find_package(ROOT 6.24 REQUIRED)

#----------------------------------------------------------------------------
# Compile definitions (see https://cmake.org/cmake/help/v3.0/command/execute_process.html)
execute_process(COMMAND root-config --cflags OUTPUT_VARIABLE ROOT_CXX_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND root-config --libs OUTPUT_VARIABLE ROOT_LD_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ROOT_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS ${ROOT_LD_FLAGS})

#----------------------------------------------------------------------------
# Locate sources and headers for this project (see https://cmake.org/cmake/help/latest/command/include_directories.html)
include_directories(${PROJECT_SOURCE_DIR}/src 
                    ${ROOT_INCLUDE_DIR})
                    
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/src/*.hh)

#----------------------------------------------------------------------------
# Add the executable, and link it to ROOT libraries (see https://cmake.org/cmake/help/latest/command/add_executable.html)
add_executable(exe ana.cc ${sources} ${headers})
target_link_libraries(exe ${ROOT_LIBRARIES})

#----------------------------------------------------------------------------
# Install the executable (see https://cmake.org/cmake/help/latest/command/install.html)
install(TARGETS exe)
