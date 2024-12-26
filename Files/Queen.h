#pragma once
#include "ChessPiece.h"
#include "Board.h"
#include <string>

class Queen : public ChessPiece
{
public:
    Queen(char symbol, std::string kingCoords);
    //virtual ~Bishop();
    int isValidMove(const std::string& coords, Board* board, bool turn) override;
};