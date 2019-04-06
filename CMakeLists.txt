cmake_minimum_required(VERSION 3.6)
project(SuperBernieBros)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Player/Player.cpp Player/Player.h BadGuys/BadGuy.cpp BadGuys/BadGuy.h Tiles/Tiles.cpp Tiles/Tiles.h Game/Game.cpp Game/Game.h Entities/Entity.cpp Entities/Entity.h MoneyBagsBro/MoneyBagsBro.cpp MoneyBagsBro/MoneyBagsBro.h MoneyBag/MoneyBag.cpp MoneyBag/MoneyBag.h Level/Level.cpp Level/Level.h coin/coin.cpp coin/coin.h ShermanAntiTrustActPowerup/ShermanAntiTrustPowerUp.cpp ShermanAntiTrustActPowerup/ShermanAntiTrustPowerUp.h JPMorgan/JPMorgan.cpp JPMorgan/JPMorgan.h)
add_executable(SuperBernieBros ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(SuperBernieBros ${SFML_LIBRARIES})
endif()