#ifndef PIECEFACTORY_H_
#define PIECEFACTORY_H_

#include <memory>
#include <stdexcept>

#include "pieces/Piece.h"
#include "pieces/Pawn.h"
#include "pieces/Rook.h"
#include "pieces/Knight.h"
#include "pieces/Bishop.h"
#include "pieces/Queen.h"
#include "pieces/King.h"
#include "Team.h"

class PieceFactory
{
public:
	static std::shared_ptr<Piece> Create(Piece::Type piece_type, ISXChess::Team team);
	static std::shared_ptr<Piece> Create(char piece_character, ISXChess::Team team);
};

#endif //PIECEFACTORY_H_
