#ifndef BOARD_H_
#define BOARD_H_

#include <array>

#include "ChessBoard.h"
#include "pieces/PieceFactory.h"
#include "utility/TeamUtility.h"

class King;

class Board : public sf::Drawable
{
public:
	Board();
	~Board();

	void Init();
	void Reset();
	void Clear();
	void ClearHighlightedSquares();
	void ClearDangerSquares();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	std::shared_ptr<Piece> GetPiece(Position position) const;
	std::shared_ptr<King> GetKing(ISXChess::Team team) const;
	Position FindKingPosition(ISXChess::Team team) const;
	std::list<std::pair<std::shared_ptr<Piece>, Position>> GetPiecesPositions(ISXChess::Team team) const;

	const ISXChess::ChessBoard& get_chess_board() const;
	ISXChess::ChessBoard& get_chess_board();
	void set_chess_board(const ISXChess::ChessBoard& chess_board);

private:
	void InitPieces(ISXChess::Team team);

	ISXChess::ChessBoard m_chess_board;
};

#endif //BOARD_H_
