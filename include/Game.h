#ifndef GAME_H_
#define GAME_H_

#include <array>
#include <list>
#include <thread>
#include <chrono>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

#include "Board.h"
#include "FENParser.h"
#include "Move.h"
#include "audio/SoundPlayer.h"
#include "players/Player.h"
#include "utility/TeamUtility.h"

constexpr auto PAWN_PROMOTION_PIECES_COUNT = 4;

class Game
{
private:
	enum class Status { ACTIVE, WHITE_WIN, BLACK_WIN, STALEMATE, DRAW };

public:
	Game(sf::RenderWindow& window, PlayerArray players = std::array<std::shared_ptr<Player>, PLAYER_COUNT>{ std::make_shared<Player>(ISXChess::Team::WHITE), std::make_shared<Player>(ISXChess::Team::BLACK) });

	void Init(const std::string& fen = "");
	void Run();
	void Reset(const PlayerArray* const players = nullptr);

	void SwitchTurn();
	bool MakeMove(Position src, Position dest);
	bool IsGameOver();

private:
	void OnMouseClick(const sf::Vector2i& mouse_position);
	void OnPawnPromotion(const sf::Vector2i& mouse_position);

	sf::String GetGameResults() const;

	void CheckSpecialMoves(const Move& move);
	std::list<Move> GeneratePossibleMoves();
	void RemoveMovesLeadingToCheck(std::list<Move>& moves);
	bool CanMove();
	bool IsInCheck() const;

	Board m_board;
	sf::RenderWindow& m_window;

	PlayerArray m_players;
	ISXChess::Team m_current_turn;
	std::list<Move> m_played_moves;
	std::list<Move> m_possible_moves;
	Status m_status;

	Position m_selected_piece_position;
	std::array<std::shared_ptr<Piece>, PAWN_PROMOTION_PIECES_COUNT> m_pawn_promotion_pieces;

	uint8_t m_halfmove_clock;
	uint8_t m_fullmove_counter;

	float m_board_square_size_x = BOARD_SQUARE_INIT_SIZE;
	float m_board_square_size_y = BOARD_SQUARE_INIT_SIZE;
};

#endif //GAME_H_
