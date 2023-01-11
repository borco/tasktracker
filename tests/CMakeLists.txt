# test_foldercreator

qt_add_executable(test_foldercreator
    test_foldercreator.cpp
)

set_target_properties(test_foldercreator PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(test_foldercreator PUBLIC
    Qt::Test
    TaskTrackerLib
)
