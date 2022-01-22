cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

set(PROJECT_NAME SmartCheckers)
project(${PROJECT_NAME})

include(FetchContent)
set(BUILD_SHARED_LIBS OFF)
FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.5.1
)
FetchContent_MakeAvailable(SFML)

add_executable(${PROJECT_NAME} 
src/main.cpp

src/Graphics/blackpawn.cpp
    include/blackpawn.h
src/Graphics/whitepawn.cpp
    include/whitepawn.h
src/Graphics/cheesboard.cpp
    include/cheesboard.h
src/Graphics/cursor.cpp
    include/cursor.h
src/Graphics/figure.cpp
    include/figure.h
src/Graphics/gameboard.cpp
    include/gameboard.h
src/Players/al.cpp
    include/al.h
src/Players/player.cpp
    include/player.h
src/AbstractEntities/truthvaluefield.cpp
    include/truthvaluefield.h
) 

set_target_properties(
     ${PROJECT_NAME} PROPERTIES
     CXX_STANDARD 11
     CXX_STANDARD_REQUIRED ON
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        sfml-audio
        sfml-graphics
        sfml-system
        sfml-window
	sfml-network
)