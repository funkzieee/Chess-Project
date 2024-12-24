#pragma once
#include "ChessPiece.h"
#include "Board.h"
#include <string>

class Pawn : public ChessPiece
{
private:
    bool _First2Step;

public:
    Pawn(char symbol, std::string kingCoords);
    //virtual ~Pawn();
    int isValidMove(const std::string& coords, Board* board, bool turn) override;
    bool isFirst2Step() const;
    void setFirst2Step();
};