#ifndef FENPARSER_H_
#define FENPARSER_H_

#include <string>
#include <sstream>

#include "ChessBoard.h"
#include "Team.h"
#include "pieces/PieceFactory.h"
#include "players/Player.h"
#include "utility/PositionUtility.h"

constexpr char FEN_DELIMITER = ' ';

struct FENInfo
{
private:
	struct CastlingRights
	{
		bool black_king_side = false;
		bool black_queen_side = false;
		bool white_king_side = false;
		bool white_queen_side = false;
	};

public:
	ISXChess::ChessBoard chess_board;
	ISXChess::Team current_turn;
	CastlingRights castling_rights;
	Position en_passant_square;
	uint8_t halfmove_clock;
	uint8_t fullmove_counter;
};

class FENParser
{
public:
	FENParser(const std::string& fen);

	FENInfo Parse();

	const std::string& get_fen() const;
	void set_fen(const std::string& fen);

	static bool IsFENValid(const std::string& fen);

private:
	void ParseChessBoard(const std::string& fen_position);
	void ParseCurrentTurn(const std::string& fen_current_turn);
	void ParseCastlingRights(const std::string& fen_castling_rights);
	void ParseEnPassant(const std::string& fen_en_passant);
	void ParseCounters(const std::string& fen_halfmove, const std::string& fen_fullmove);

	std::string m_fen;
	FENInfo m_fen_info;
};

#endif //FENPARSER_H_
