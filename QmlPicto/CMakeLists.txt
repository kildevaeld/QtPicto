
qt5_wrap_cpp(MOC
	qmlpicto_plugin.h
	qmlpictoview.h
)

qt5_add_resources(RES qmlpicto.qrc)

set(SOURCES
	${MOC}
	${RES}
	pictoimageprovider.cpp
	qmlpicto.cpp
	qmlpicto_plugin.cpp
	qmlpictoview.cpp
)

add_library(qmlpicto ${SOURCES})
target_link_libraries(qmlpicto Qt5::Qml Qt5::Quick qtpicto)