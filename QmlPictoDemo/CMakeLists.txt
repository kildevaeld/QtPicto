

qt5_add_resources(RES qml.qrc)

add_executable(qmlpictodemo main.cpp ${RES})
target_link_libraries(qmlpictodemo Qt5::Qml qmlpicto)
target_compile_definitions(qmlpictodemo PUBLIC QPM_INIT)
