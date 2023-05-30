#ifndef TEAMUTILITY_H_
#define TEAMUTILITY_H_

#include <array>
#include <memory>

#include "Team.h"
#include "players/Player.h"

namespace ISXUtility
{

bool IsWhiteSide(ISXChess::Team team);
ISXChess::Team EnemyTeam(ISXChess::Team ally_team);

}

#endif //TEAMUTILITY_H_
