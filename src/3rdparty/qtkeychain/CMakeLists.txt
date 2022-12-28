set(LIB_NAME keychain)

set(LIB_SOURCES
    qtkeychain/keychain.cpp
    qtkeychain/keychain.h
    keychainclass.cpp
    keychainclass.h
)

if(APPLE)
    list(APPEND LIB_SOURCES qtkeychain/keychain_apple.mm)
    list(APPEND LIB_LIBRARIES "-framework Foundation" "-framework Security")
endif()

qt_add_library(${LIB_NAME} STATIC
    MANUAL_FINALIZATION
    ${LIB_SOURCES}
)

target_link_libraries(${LIB_NAME} PUBLIC
    Qt6::Core
    ${LIB_LIBRARIES}
)

target_include_directories(${LIB_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/qtkeychain
    ${CMAKE_CURRENT_SOURCE_DIR}/
    ${CMAKE_CURRENT_BINARY_DIR}/qtkeychain
)

qt_finalize_target(${LIB_NAME})
