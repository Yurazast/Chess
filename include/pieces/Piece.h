#ifndef PIECE_H_
#define PIECE_H_

#include <string>
#include <list>
#include <map>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include "ChessBoard.h"
#include "Position.h"
#include "Team.h"
#include "utility/ResourcesFilepath.h"
#include "utility/ChessBoardUtility.h"
#include "utility/TeamUtility.h"

class Move;

class Piece : public sf::Drawable
{
public:
	enum class Type : char
	{
		PAWN = 'p',
		ROOK = 'r',
		KNIGHT = 'n',
		BISHOP = 'b',
		QUEEN = 'q',
		KING = 'k'
	};

	virtual ~Piece() = default;
	virtual std::list<Move> GeneratePossibleMoves(const ISXChess::ChessBoard& chess_board, Position position) const = 0;
	virtual bool IsMoveValid(Position src, Position dest, const ISXChess::ChessBoard& chess_board) const = 0;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	ISXChess::Team get_team() const;
	void set_team(ISXChess::Team team);
	Piece::Type get_type() const;
	void set_type(Piece::Type type);
	unsigned int get_value() const;
	void set_value(unsigned int value);
	bool is_first_move() const;
	void set_first_move(bool is_first_move);
	sf::Sprite& get_sprite();

protected:
	explicit Piece(ISXChess::Team team, Piece::Type type, unsigned int value);

	void LoadImageFromFile(const std::string& filepath);

	ISXChess::Team m_team;
	Piece::Type m_type;
	unsigned int m_value;
	bool m_first_move;
	sf::Sprite m_sprite;

private:
	static std::map<std::pair<ISXChess::Team, Piece::Type>, sf::Texture> s_textures;
};

#endif //PIECE_H_
