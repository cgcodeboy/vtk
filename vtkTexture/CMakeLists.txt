CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(vtkTexture)
FIND_PACKAGE(VTK REQUIRED)
INCLUDE(${VTK_USE_FILE})
ADD_EXECUTABLE(vtkTexture vtkTexture.cpp)
TARGET_LINK_LIBRARIES(vtkTexture ${VTK_LIBRARIES})