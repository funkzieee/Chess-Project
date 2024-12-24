#pragma once
#include "ChessPiece.h"
#include "Board.h"
#include <string>

class Knight : public ChessPiece
{
public:
    Knight(char symbol, std::string kingCoords);
    //virtual ~Knight();
    int isValidMove(const std::string& coords, Board* board, bool turn) override;
};