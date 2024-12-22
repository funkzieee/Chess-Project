#pragma once
#include "ChessPiece.h"
#include "Board.h"
#include <string>

//class Board;

class King : public ChessPiece
{
public:
    King(char symbol, std::string kingCoords);
    //virtual ~King();
    int isValidMove(const std::string& coords, Board* board, bool turn) override;
};