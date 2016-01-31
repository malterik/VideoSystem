cmake_minimum_required(VERSION 2.8.9)
project(VideoSystem)
find_package( OpenCV REQUIRED )
#Bring the headers, such as Student.h into the project
include_directories(src)

#Can manually add the sources using the set command as follows:
#set(SOURCES src/mainapp.cpp src/Student.cpp)

#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.cpp")

add_executable(main ${SOURCES})
target_link_libraries( main ${OpenCV_LIBS} )
