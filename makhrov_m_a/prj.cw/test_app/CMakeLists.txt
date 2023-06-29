add_executable(test_app test_interpolation.cpp)
target_link_libraries(test_app interpolation ${OpenCV_LIBS})
install (TARGETS test_app)