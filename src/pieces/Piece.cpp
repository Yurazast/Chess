#include "pieces/Piece.h"

std::map<std::pair<ISXChess::Team, Piece::Type>, sf::Texture> Piece::s_textures;

Piece::Piece(ISXChess::Team team, Piece::Type type, unsigned int value)
	: m_team(team)
	, m_type(type)
	, m_value(value)
	, m_first_move(true)
{}

void Piece::draw(sf::RenderTarget& target, [[maybe_unused]] sf::RenderStates states) const
{
	target.draw(m_sprite);
}

ISXChess::Team Piece::get_team() const
{
	return this->m_team;
}

void Piece::set_team(ISXChess::Team team)
{
	this->m_team = team;
	m_sprite.setTexture(s_textures[{m_team, m_type}]);
}

Piece::Type Piece::get_type() const
{
	return this->m_type;
}

void Piece::set_type(Piece::Type type)
{
	this->m_type = type;
	m_sprite.setTexture(s_textures[{m_team, m_type}]);
}

unsigned int Piece::get_value() const
{
	return this->m_value;
}

void Piece::set_value(unsigned int value)
{
	this->m_value = value;
}

bool Piece::is_first_move() const
{
	return this->m_first_move;
}

void Piece::set_first_move(bool is_first_move)
{
	this->m_first_move = is_first_move;
}

sf::Sprite& Piece::get_sprite()
{
	return this->m_sprite;
}

void Piece::LoadImageFromFile(const std::string& filepath)
{
	if (s_textures.find({ m_team, m_type }) == s_textures.end())
	{
		s_textures[{ m_team, m_type }].loadFromFile(filepath);
	}

	m_sprite.setTexture(s_textures[{ m_team, m_type }]);
}
