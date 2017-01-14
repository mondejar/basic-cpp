#Find in all subdirectories for .cpp files 
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2")

file( GLOB APP_SOURCES */*.cpp )

#generate an executable for each file .cpp
foreach( testsourcefile ${APP_SOURCES} )
	get_filename_component( testname ${testsourcefile} NAME )
    string( REPLACE ".cpp" "" testname ${testname} )
	message("file = " ${testname}) 
    add_executable( ${testname} ${testsourcefile} )
endforeach( testsourcefile ${APP_SOURCES} )

