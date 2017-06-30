project (locality_sensitive_hashing)

cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
find_package(OpenCV REQUIRED)

add_executable(lsh main_cosine.cpp lshcosine.h lshcosine.cpp)
target_link_libraries(lsh ${OpenCV_LIBS})
