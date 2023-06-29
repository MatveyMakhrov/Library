add_executable(rational_test rational_test.cpp)
target_link_libraries(rational_test rational doctest::doctest)
add_test(NAME rational_test COMMAND rational_test)

add_executable(arrayd_test arrayd_test.cpp)
target_link_libraries(arrayd_test arrayd doctest::doctest)
add_test(NAME array_test COMMAND arrayd_test)