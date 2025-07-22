#include "utility/ChessBoardUtility.h"
#include "pieces/Piece.h"

namespace ISXUtility
{

std::shared_ptr<Piece> GetPiece(const ISXChess::ChessBoard& chess_board, Position position)
{
	return chess_board.at(position.y).at(position.x).piece;
}

bool IsValidBorders(Position position)
{
	return position.x >= 0 && position.y >= 0 && position.x < BOARD_WIDTH && position.y < BOARD_HEIGHT;
}

bool IsPositionAvailable(const ISXChess::ChessBoard& chess_board, Position position)
{
	return IsValidBorders(position) && GetPiece(chess_board, position) == nullptr;
}

bool HasEnemyPiece(const ISXChess::ChessBoard& chess_board, Position position, ISXChess::Team enemy_team)
{
	if (!IsValidBorders(position))
	{
		return false;
	}

	std::shared_ptr<Piece> piece = GetPiece(chess_board, position);

	return piece && piece->get_team() == enemy_team;
}

bool IsObstacleBetween(const ISXChess::ChessBoard& chess_board, Position src, Position dest)
{
	int8_t shift_x = dest.x > src.x ? 1
				   : dest.x == src.x ? 0
				   : -1;
	int8_t shift_y = dest.y > src.y ? 1
				   : dest.y == src.y ? 0
				   : -1;

	uint8_t max_distance = std::max(abs(dest.x - src.x), abs(dest.y - src.y));

	for (uint8_t i = 1; i < max_distance; ++i)
	{
		int8_t x = src.x + (i * shift_x);
		int8_t y = src.y + (i * shift_y);
		Position pos = { x, y };

		if (dest != pos && !IsPositionAvailable(chess_board, pos))
		{
			return true;
		}
	}

	return false;
}

void InitSquares(ISXChess::ChessBoard& chess_board)
{
	for (uint8_t y = 0; y < BOARD_HEIGHT; ++y)
	{
		for (uint8_t x = 0; x < BOARD_WIDTH; ++x)
		{
			sf::RectangleShape& square = chess_board.at(y).at(x).square;
			sf::Color& init_color = chess_board.at(y).at(x).init_color;

			square.setSize(sf::Vector2f(ISXChess::g_board_square_size_x, ISXChess::g_board_square_size_y));
			square.setPosition(sf::Vector2f(x * ISXChess::g_board_square_size_x, y * ISXChess::g_board_square_size_y));
			init_color = (!(y % 2 == 0) != !(x % 2 == 0)) ? BOARD_SQUARE_BLACK_COLOR : BOARD_SQUARE_WHITE_COLOR;
		}
	}
}

void ClearSquaresStates(ISXChess::ChessBoard& chess_board, uint8_t state_to_clear)
{
	for (uint8_t y = 0; y < BOARD_HEIGHT; ++y)
	{
		for (uint8_t x = 0; x < BOARD_WIDTH; ++x)
		{
			uint8_t& board_square_state = chess_board.at(y).at(x).state;

			if (state_to_clear == BoardSquare::State::NONE)
			{
				board_square_state = BoardSquare::State::NONE;
			}
			else if (board_square_state & state_to_clear)
			{
				board_square_state ^= board_square_state & state_to_clear;
			}
		}
	}
}

}
