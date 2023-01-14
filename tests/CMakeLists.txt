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

target_compile_definitions(test_foldercreator PRIVATE
    TEST_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}"
)

# test_task

qt_add_executable(test_task
test_task.cpp
)

set_target_properties(test_task PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(test_task PUBLIC
    Qt::Test
    TaskTrackerLib
)

# test_tasklistmodel

qt_add_executable(test_tasklistmodel
    test_tasklistmodel.cpp
)

set_target_properties(test_tasklistmodel PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(test_tasklistmodel PUBLIC
    Qt::Test
    TaskTrackerLib
)
