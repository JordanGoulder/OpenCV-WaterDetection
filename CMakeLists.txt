cmake_minimum_required(VERSION 2.8)

set ( ProjName "WaterDetection" )

project( ${ProjName} )

find_package( OpenCV REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable( ${ProjName} main.cpp )

target_link_libraries( ${ProjName} ${OpenCV_LIBS} )
