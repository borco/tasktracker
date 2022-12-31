set(QML_MODULE_NAME TogglTrackTasks)
set(LIB_NAME "${QML_MODULE_NAME}Lib")

qt_add_library(${LIB_NAME} STATIC
    messagehandler.cpp
    messagehandler.h
)

#qt_add_qml_module(${LIB_NAME}
#    URI ${QML_MODULE_NAME}
#    VERSION 1.0
#    SOURCES
#)

target_link_libraries(${LIB_NAME} PUBLIC
    Qt6::Core
)

target_include_directories(${LIB_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
