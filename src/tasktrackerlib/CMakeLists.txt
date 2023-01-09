set(LIB_NAME TaskTrackerLib)

qt_add_library(${LIB_NAME}
    STATIC
)

qt_add_qml_module(${LIB_NAME}
    URI ${LIB_NAME}
    VERSION 1.0
    PLUGIN_TARGET ${LIB_NAME}Plugin
    SOURCES
        config.cpp
        config.h
        togglproxy.cpp
        togglproxy.h
)

target_link_libraries(${LIB_NAME} PUBLIC
    Qt6::Core
    Qt6::Qml
    Qt6::Quick
    Qt6::WebSockets
)

target_include_directories(${LIB_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)