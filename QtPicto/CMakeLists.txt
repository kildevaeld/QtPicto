
qt5_wrap_cpp(MOC
	awesome.h
	material.h
)

qt5_add_resources(RES qtpicto.qrc)

set(SOURCES
	${MOC}
	${RES}
	awesome.cpp
	material.cpp
	qtpicto.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/patternscpp)

add_library(qtpicto ${SOURCES})
target_link_libraries(qtpicto Qt5::Gui)
target_include_directories(qtpicto PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/patternscpp)