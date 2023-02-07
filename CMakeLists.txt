cmake_minimum_required(VERSION 3.0.0)
project(WhaleMarket VERSION 0.1.0)



set(SOURCES
    src/Date.cpp
    src/User.cpp
    src/UserManager.cpp
    src/Good.cpp
    src/GoodManager.cpp
    # test/testUser.cpp
    # test/testUserManager.cpp
    test/test.cpp
)

add_executable(${PROJECT_NAME} 
    ${SOURCES}
)

target_include_directories(${PROJECT_NAME}
PRIVATE 
include
)