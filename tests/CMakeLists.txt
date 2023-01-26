foreach(TEST_NAME IN ITEMS
        datesortedlist
        foldercreator
        task
        taskaggregate
        taskduration
        taskdurationsortedlist
        taskmodel
    )

    qt_add_executable(test_${TEST_NAME}
        test_${TEST_NAME}.cpp
    )

    set_target_properties(test_${TEST_NAME} PROPERTIES
        WIN32_EXECUTABLE TRUE
        MACOSX_BUNDLE TRUE
    )

    target_link_libraries(test_${TEST_NAME} PUBLIC
        Qt::Test
        TaskTrackerLib
    )

    target_compile_definitions(test_${TEST_NAME} PRIVATE
        TEST_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}"
    )

endforeach()
