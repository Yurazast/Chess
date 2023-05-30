#ifndef PLAYER_H_
#define PLAYER_H_

#include <array>
#include <memory>

#include "Team.h"

constexpr auto PLAYER_COUNT = 2;

class Player
{
public:
	explicit Player(ISXChess::Team team);

	ISXChess::Team get_team() const;
	void set_team(ISXChess::Team team);

protected:
	ISXChess::Team m_team;
};

using PlayerArray = std::array<std::shared_ptr<Player>, PLAYER_COUNT>;

#endif //PLAYER_H_
