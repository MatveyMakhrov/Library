add_subdirectory(test_app)
add_subdirectory(include)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/examples
DESTINATION .)