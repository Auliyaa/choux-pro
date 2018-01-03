cmake_minimum_required(VERSION 3.0.0)

# ===========================================
# Project definition
# ===========================================
project(choux VERSION 12.2.24)

# ===========================================
# Compiler & CMake options
# ===========================================

# ===========================================
# Dependencies
# ===========================================
find_package(Qt5Core    REQUIRED)
find_package(Qt5Widgets REQUIRED)

# ===========================================
# Main target
# ===========================================
include_directories(
  include
  ${CMAKE_BINARY_DIR}
)

qt5_add_resources(RCC_OUT
  res/choux.qrc
)

qt5_wrap_cpp(MOC_OUT
  include/choux_window.h
)

qt5_wrap_ui(UIC_OUT
  ui/choux_window.ui
)

add_executable(choux WIN32
  ${MOC_OUT}
  ${RCC_OUT}
  ${UIC_OUT}

  src/choux.cpp
  src/choux_window.cpp
)

target_link_libraries(choux
  Qt5::Core
  Qt5::Widgets
)

install(TARGETS choux
  DESTINATION bin
)

add_custom_target(redist ALL
  COMMAND windeployqt.exe --dir ${CMAKE_BINARY_DIR}/redist $<TARGET_FILE:choux>
  DEPENDS choux
)

install(DIRECTORY ${CMAKE_BINARY_DIR}/redist/ DESTINATION bin)
