CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(vtkLogicImage)
FIND_PACKAGE(VTK REQUIRED)
INCLUDE (${VTK_USE_FILE})
ADD_EXECUTABLE(vtkLogicImage vtkLogicImage)
TARGET_LINK_LIBRARIES(vtkLogicImage ${VTK_LIBRARIES})
