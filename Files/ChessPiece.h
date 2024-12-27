#pragma once
#include "Board.h"
#include <string>

class Board;

class ChessPiece
{
private:
	char _symbol;
	std::string _kingCoords;

public:
	// constructors and destructors
	ChessPiece(char symbol, std::string kingCoords);
	virtual ~ChessPiece();

	// setters and getters
	void setSymbol(char symbol);
	char getSymbol() const;
	void setKingCoords(std::string kingCoords);
	std::string getKingCoords() const;


	// extras
	virtual int isValidMove(const std::string& coords, Board* board, bool turn) = 0;
	bool checkIfSameDestination(int srcX, int srcY, int dstX, int dstY) const;
	bool isKingInCheck(Board* board, int kingX, int kingY, bool turn) const;
	bool checkIfPieceCheck(Board* board, const std::string& coords, const std::string& kingCoords, bool turn);
};