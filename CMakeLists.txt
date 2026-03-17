cmake_minimum_required(VERSION 3.10)


project(
  minesweeper
  CXX
)

include(FetchContent)
set(FETCHCONTENT_QUIET TRUE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES OFF CACHE BOOL "" FORCE) # don't build the supplied example games

FetchContent_Declare(
  raylib
  GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
  GIT_TAG "master"
  GIT_PROGRESS FALSE
  GIT_SHALLOW 1
)

FetchContent_MakeAvailable(raylib)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared libraries" FORCE)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)
set(CMAKE_CXX_STANDARD 23)

add_compile_options(
  "-g"
)
add_executable(
  minesweeper
  src/main.cpp
)

target_link_libraries(
  minesweeper
  PRIVATE raylib
)

install(

)
