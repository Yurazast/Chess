#include "players/Player.h"

Player::Player(ISXChess::Team team)
	: m_team(team)
{}

ISXChess::Team Player::get_team() const
{
	return this->m_team;
}

void Player::set_team(ISXChess::Team team)
{
	this->m_team = team;
}
