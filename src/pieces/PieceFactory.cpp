#include "pieces/PieceFactory.h"

std::shared_ptr<Piece> PieceFactory::Create(Piece::Type piece_type, ISXChess::Team team)
{
	return Create(static_cast<char>(piece_type), team);
}

std::shared_ptr<Piece> PieceFactory::Create(char piece_character, ISXChess::Team team)
{
	switch (piece_character)
	{
		case 'p': return std::make_shared<Pawn>(team);
		case 'r': return std::make_shared<Rook>(team);
		case 'n': return std::make_shared<Knight>(team);
		case 'b': return std::make_shared<Bishop>(team);
		case 'q': return std::make_shared<Queen>(team);
		case 'k': return std::make_shared<King>(team);
		default: throw std::runtime_error("No such piece by character: " + std::to_string(piece_character));
	}
}
