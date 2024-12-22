#pragma once
#include "ChessPiece.h"
#include <string>

#define BOARDSIZE 8
class ChessPiece;

class Board
{
private:
	bool _PlayerTurn; // 0 - white, other - black
public:
	ChessPiece* _chessBoard[BOARDSIZE][BOARDSIZE];
	// constructors and destructors
	Board();	
	virtual ~Board();

	// getters and setters
	bool getPlayerTurn() const;

	// extras
	int move(std::string coords);
	std::string getBoard() const;
	void changeTurn();
	void updateKingCoords(const std::string& kingCoords, bool turn);
};