cmake_minimum_required(VERSION 3.0.0)
project(WhaleMarket VERSION 0.1.0)



set(SOURCES
    src/Date.cpp
    src/User.cpp
    src/Good.cpp
    src/Order.cpp
    src/DataManager.cpp
    test/test.cpp)

add_executable(${PROJECT_NAME} 
    ${SOURCES}
)

target_include_directories(${PROJECT_NAME}
PUBLIC 
include

)