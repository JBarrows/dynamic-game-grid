cmake_minimum_required(VERSION 3.15)

set(Headers
    cellcomponent.h
    gamegrid.h
    gridcell.h
)

add_library(GameGrid
    cellcomponent.cpp
    gamegrid.cpp
    gridcell.cpp
    ${Headers}
)

install(FILES ${Headers} TYPE INCLUDE)
