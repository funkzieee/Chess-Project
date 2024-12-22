#pragma once
#include "ChessPiece.h"
#include "Board.h"
#include <string>

//class Board;

class Rook : public ChessPiece
{
public:
    Rook(char symbol, std::string kingCoords);
    //virtual ~Rook();
    int isValidMove(const std::string& coords, Board* board, bool turn) override;
};