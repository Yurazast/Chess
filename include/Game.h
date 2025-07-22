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
#include "Move.h"
#include "audio/SoundPlayer.h"
#include "parsers/FENParser.h"
#include "players/Player.h"
#include "utility/TeamUtility.h"

constexpr auto PAWN_PROMOTION_PIECES_COUNT = 4;

class Game
{
private:
	enum class Status { ACTIVE, WHITE_WIN, BLACK_WIN, STALEMATE, DRAW };

public:
	Game(sf::RenderWindow& window,
		 const std::string& fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
		 PlayerArray players = std::array<std::shared_ptr<Player>, PLAYER_COUNT>{
			std::make_shared<Player>(ISXChess::Team::WHITE),
			std::make_shared<Player>(ISXChess::Team::BLACK)
		 });

	void Run();
	void Reset(const std::string& fen = "", const PlayerArray* const players = nullptr);

	bool MakeMove(Position src, Position dest);
	void UndoMove();
	void RedoMove();

	void SwitchTurn();
	bool IsGameOver();

private:
	void Init();

	void OnMouseClick(const sf::Vector2i& mouse_position);
	void OnPawnPromotion(const sf::Vector2i& mouse_position);

	void CheckSpecialMoves(const Move& move);
	void UndoSpecialMoves(const Move& move);
	void RedoSpecialMoves(const Move& move);

	void CheckKingStatus();
	void RemoveMovesLeadingToCheck(std::list<Move>& moves);
	sf::String GetGameResults() const;
	std::list<Move> GeneratePossibleMoves();
	bool CanMove();
	bool IsInCheck() const;

	sf::RenderWindow& m_window;

	Board m_board;
	std::string m_fen;
	PlayerArray m_players;
	ISXChess::Team m_current_turn;
	Status m_status;

	std::list<Move> m_possible_moves;
	std::list<Move> m_undo_moves;
	std::list<Move> m_redo_moves;

	Position m_selected_piece_position;
	std::array<std::shared_ptr<Piece>, PAWN_PROMOTION_PIECES_COUNT> m_pawn_promotion_pieces;

	uint8_t m_halfmove_clock;
	uint8_t m_fullmove_counter;
};

#endif //GAME_H_
