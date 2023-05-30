#include "utility/TeamUtility.h"

namespace ISXUtility
{

bool IsWhiteSide(ISXChess::Team team)
{
	return team == ISXChess::Team::WHITE;
}

ISXChess::Team EnemyTeam(ISXChess::Team ally_team)
{
	return (ally_team == ISXChess::Team::WHITE) ? ISXChess::Team::BLACK : ISXChess::Team::WHITE;
}

}
