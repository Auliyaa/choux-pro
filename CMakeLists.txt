cmake_minimum_required(VERSION 3.0.0)

# ===========================================
# Project definition
# ===========================================
project(choux VERSION 12.2.24)

# ===========================================
# Compiler & CMake options
# ===========================================
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

# ===========================================
# Dependencies
# ===========================================
find_package(Qt5Core    REQUIRED)
find_package(Qt5Widgets REQUIRED)

# ===========================================
# Main target
# ===========================================
add_executable(choux WIN32
  src/choux.cpp
)

target_link_libraries(choux
  Qt5::Core
  Qt5::Widgets
)

# ===========================================
# Installer
# ===========================================
include(CPack)
