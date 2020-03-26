cmake_minimum_required(VERSION 3.15)
project(tile-map-manager)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/modules)

list(APPEND COMPILER_FLAGS_DEBUG "-O0" "-g" "-Wall" "-Wextra" "-pedantic")

find_package(TinyXML2 REQUIRED)
if(TINYXML2_FOUND)
    set( ${TINYXML2_LIBRARIES})
    include_directories(${TINYXML2_INCLUDE_DIR})
else()
    message(STATUS "TinyXml2 not found")
endif()

find_package(tmxparser REQUIRED)

find_package(SFML COMPONENTS graphics window system audio REQUIRED)


add_executable(tile-map-manager
        main.cpp
        Game.hpp
        Game.cpp
        TileMapManager.cpp
        TileMapManager.hpp
        TileMap.cpp
        TileMap.hpp
        TileLayer.cpp
        TileLayer.hpp
        Tileset.cpp
        Tileset.hpp
        Tile.cpp
        Tile.hpp
        AnimatedTile.cpp
        AnimatedTile.hpp
        PropertyTile.cpp
        PropertyTile.hpp
        TileAnimation.cpp
        TileAnimation.hpp
        )
set_target_properties(tile-map-manager PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set_target_properties(tile-map-manager PROPERTIES OUTPUT_NAME tile-map-manager-bin)
target_compile_options( tile-map-manager
        PRIVATE
        ${COMPILER_FLAGS}
        "$<$<CONFIG:Debug>:${COMPILER_FLAGS_DEBUG}>"
        "$<$<CONFIG:Release>:${COMPILER_FLAGS_RELEASE}>")

target_link_libraries(tile-map-manager sfml-graphics sfml-window sfml-system sfml-audio tmxparser ${TINYXML2_LIBRARIES} )