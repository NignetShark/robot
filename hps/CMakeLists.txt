cmake_minimum_required(VERSION 3.10)

project(Robot)

set(SRC_DIR "src/robot")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_COMPILER   arm-linux-gnueabihf-gcc)
set(CMAKE_CXX_COMPILER arm-linux-gnueabihf-g++)

include_directories(/usr/local/include/)
link_directories(/usr/local/lib)

add_executable(Robot
    "${SRC_DIR}/robot.cpp"
    "${SRC_DIR}/motor.cpp"
    "${SRC_DIR}/radio.cpp"
    "${SRC_DIR}/sonar.cpp"
    )
target_link_libraries(Robot rf24)
target_include_directories(Robot
    PRIVATE include
    )

add_custom_target(upload
    COMMAND scp ${CMAKE_CURRENT_SOURCE_DIR}/build/Robot root@10.0.0.2:~/robot/
    COMMENT "Upload Robot file to DE10-Nano"
    )
