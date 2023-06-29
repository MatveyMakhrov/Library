add_library(interpolation interpolation.cpp include/interpolation/interpolation.hpp)
set_property(TARGET interpolation PROPERTY CXX_STANDARD 20)
target_link_libraries(interpolation ${OpenCV_LIBS})
target_include_directories(interpolation PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
