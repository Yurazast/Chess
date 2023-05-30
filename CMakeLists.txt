cmake_minimum_required(VERSION 3.12)
project(Chess)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)

include_directories(include)
set(PROJECT_SOURCE_FILES
    src/Main.cpp
    src/Board.cpp
    src/FENParser.cpp
    src/Game.cpp
    src/Move.cpp
    src/Position.cpp
    src/audio/SoundPlayer.cpp
    src/pieces/Piece.cpp
    src/pieces/Pawn.cpp
    src/pieces/Rook.cpp
    src/pieces/Knight.cpp
    src/pieces/Bishop.cpp
    src/pieces/Queen.cpp
    src/pieces/King.cpp
    src/pieces/PieceFactory.cpp
    src/players/Player.cpp
    src/utility/ChessBoardUtility.cpp
    src/utility/PositionUtility.cpp
    src/utility/SoundPlayerUtility.cpp
    src/utility/TeamUtility.cpp
)

add_executable(${CMAKE_PROJECT_NAME} ${PROJECT_SOURCE_FILES})
target_link_libraries(${CMAKE_PROJECT_NAME} sfml-system sfml-window sfml-graphics sfml-audio)
