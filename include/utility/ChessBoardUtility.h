#ifndef CHESSBOARDUTILITY_H_
#define CHESSBOARDUTILITY_H_

#include "ChessBoard.h"
#include "Position.h"
#include "Team.h"

namespace ISXUtility
{

std::shared_ptr<Piece> GetPiece(const ISXChess::ChessBoard& chess_board, Position position);

bool IsValidBorders(Position position);
bool IsPositionAvailable(const ISXChess::ChessBoard& chess_board, Position position);
bool HasEnemyPiece(const ISXChess::ChessBoard& chess_board, Position position, ISXChess::Team enemy_team);
bool IsObstacleBetween(const ISXChess::ChessBoard& chess_board, Position src, Position dest);

void InitSquares(ISXChess::ChessBoard& chess_board);
void ClearSquaresStates(ISXChess::ChessBoard& chess_board, uint8_t state_to_clear = BoardSquare::State::NONE);

}

#endif //CHESSBOARDUTILITY_H_
