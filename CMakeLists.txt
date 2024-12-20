cmake_minimum_required(VERSION 3.10)

# Project name and version
project(BaseDefense VERSION 0.1)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Define the sources
set(SOURCES
    src/Game.cpp
    src/Utils.cpp
    src/Entities/Player.cpp
    src/Entities/Bullet.cpp
    main.cpp
)

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

# Add the executable
add_executable(BaseDefense ${SOURCES})

# Link libraries (if any)
target_link_libraries(BaseDefense sfml-graphics)
