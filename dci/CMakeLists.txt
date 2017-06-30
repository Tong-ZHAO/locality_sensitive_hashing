project (locality_sensitive_hashing)

cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
find_package(OpenCV REQUIRED)

#ImagineAddExecutable(test_zipimage example.cpp ../quadtree/quadtree.h)
add_executable(lsh main_dci.cpp lshdci.h lshdci.cpp)
target_link_libraries(lsh ${OpenCV_LIBS})
