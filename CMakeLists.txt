cmake_minimum_required(VERSION 3.10)

project(Asteroids VERSION 1.0)

add_executable(Asteroids WIN32
  Asteroids/AsterModel.cpp
  Asteroids/BulletModel.cpp
  Asteroids/Game.cpp
  Asteroids/main.cpp
  Asteroids/Model.cpp
  Asteroids/ShipModel.cpp)

target_include_directories(Asteroids PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Asteroids)

add_subdirectory(SoftwareRender)

target_link_libraries(Asteroids SoftwareRender)