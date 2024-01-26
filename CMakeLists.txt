cmake_minimum_required(VERSION 3.0)
project(gui)
set(CMAKE_CXX_STANDARD 11)

# Raylib
set(RAYLIB_DIR "${CMAKE_CURRENT_LIST_DIR}/libs")

# Specify the include directories
include_directories("${CMAKE_CURRENT_LIST_DIR}/include")
include_directories("${RAYLIB_DIR}/raylib/src")

# Add the Raylib library
add_library(raylib STATIC IMPORTED)
set_target_properties(raylib PROPERTIES
  IMPORTED_LOCATION "${RAYLIB_DIR}/libraylib.a"
)

# Adding source files
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")

# Declare the executable
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

# Link the executable with Raylib
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# Platform-specific settings
if (WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE opengl32 gdi32)
elseif (APPLE)
    find_library(COCOA_LIBRARY Cocoa)
    find_library(OPENGL_LIBRARY OpenGL)
    find_library(IOKIT_LIBRARY IOKit)
    find_library(COREVIDEO_LIBRARY CoreVideo)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${COCOA_LIBRARY} ${OPENGL_LIBRARY} ${IOKIT_LIBRARY} ${COREVIDEO_LIBRARY})
endif ()
