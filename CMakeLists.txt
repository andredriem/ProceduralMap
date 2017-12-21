cmake_minimum_required(VERSION 3.7)
project(untitled)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(SOURCE_FILES main.cpp GameObjects/MapObject.cpp GameObjects/MapObject.h Camera/Camera.cpp Camera/Camera.h game_constants.h GameObjects/Tile.cpp GameObjects/Tile.h BitmapPair.cpp BitmapPair.h GameObjects/TileBlock.cpp GameObjects/TileBlock.h GameObjects/Tree.cpp GameObjects/Tree.h)

INCLUDE_DIRECTORIES(  /usr/local/Cellar/allegro/5.2.3.0/include )
LINK_DIRECTORIES(  /usr/local/Cellar/allegro/5.2.3.0/lib )

file(GLOB LIBRARIES "/usr/local/Cellar/allegro/5.2.3.0/lib/*.dylib")
message("LIBRARIES = ${LIBRARIES}")

add_executable(untitled ${SOURCE_FILES})

configure_file(assets/grass.png assets/grass.png COPYONLY)
configure_file(assets/water.png assets/water.png COPYONLY)
configure_file(assets/tree.png assets/tree.png COPYONLY)



TARGET_LINK_LIBRARIES(untitled  ${LIBRARIES})