cmake_minimum_required(VERSION 3.7)

project(SDL2Test)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} src)

add_executable(Asteroids src/main.cpp src/game.cpp src/controller.cpp src/renderer.cpp src/ship.cpp src/projectile.cpp src/TextureManager.cpp)
target_link_libraries(Asteroids ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
