cmake_minimum_required(VERSION 2.8)

if(POLICY CMP0020)
  cmake_policy(SET CMP0020 NEW)
endif()

PROJECT(vtkSqltest)

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

set(CMAKE_AUTOMOC ON)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Sql REQUIRED)
find_package(Qt5Core REQUIRED)

#include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

#qt5_wrap_ui(UISrcs ${UI_FILES} )
add_executable(vtkSqltest vtkSqltest.cpp)
qt5_use_modules(vtkSqltest Core Gui Sql Widgets)
target_link_libraries(vtkSqltest ${VTK_LIBRARIES} ${QT_LIBRARIES})
