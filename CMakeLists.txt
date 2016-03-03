cmake_minimum_required(VERSION 2.8.9)
project (VideoSystem)
find_package( OpenCV REQUIRED )


file(GLOB_RECURSE Foo_SOURCES "src/*.cpp")
file(GLOB_RECURSE Foo_HEADERS "src/*.h")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set (Foo_INCLUDE_DIRS "")
foreach (_headerFile ${Foo_HEADERS})
	get_filename_component(_dir ${_headerFile} PATH)
        list (APPEND Foo_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES Foo_INCLUDE_DIRS)

include_directories(${Foo_INCLUDE_DIRS})
add_executable (main  ${Foo_SOURCES})
target_link_libraries( main ${OpenCV_LIBS} )
