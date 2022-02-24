
cmake_minimum_required(VERSION 3.1.0)
project(usbrelay)


include_directories(include)
include_directories(thirdparty/CppLinuxSerial/include)
add_subdirectory(thirdparty/CppLinuxSerial)
file(GLOB_RECURSE USBRELAY
        "src/*.cpp")

add_executable(${PROJECT_NAME} ${USBRELAY})
target_link_libraries(${PROJECT_NAME} CppLinuxSerial)

