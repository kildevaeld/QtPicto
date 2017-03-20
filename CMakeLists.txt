cmake_minimum_required(VERSION 3.1)
project(QtPicto)

option(PICTO_BUILD_DEMOS "build demos" off)

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Qml REQUIRED)
find_package(Qt5Quick REQUIRED)

add_subdirectory(QtPicto)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(QmlPicto)

if(PICTO_BUILD_DEMOS)
	add_subdirectory(QmlPictoDemo)
endif(PICTO_BUILD_DEMOS)
