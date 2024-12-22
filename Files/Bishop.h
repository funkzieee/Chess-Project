#pragma once
#include "ChessPiece.h"
#include "Board.h"
#include <string>

//class Board;

class Bishop : public ChessPiece
{
public:
    Bishop(char symbol, std::string kingCoords);
    //virtual ~BIshop();
    int isValidMove(const std::string& coords, Board* board, bool turn) override;
};