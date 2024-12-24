#include "Pawn.h"
#include <cmath>

using std::string;

/*
The constructor for the pawn piece
input: symbol - char, kingCoords - string
output: none
*/
Pawn::Pawn(char symbol, string kingCoords)
	: ChessPiece(symbol, kingCoords), _First2Step(false)
{
}

/*
The function returns if the pawn made the first 2 step
input: none
output: bool
*/
bool Pawn::isFirst2Step() const
{
    return this->_First2Step;
}

/*
The function sets the first 2 step of the pawn
input: none
output: none
*/
void Pawn::setFirst2Step()
{
    this->_First2Step = true;
}

/*
The function checks if the pawn move is valid based on the coords it gets
input: coords - string, board - 2d array
output: a number based on the move
*/
int Pawn::isValidMove(const string& coords, Board* board, bool turn)
{
    int i = 0;
    bool inCheck = false;
    // Getting the indexes to check on the board
    int srcX = coords[0] - 'a', srcY = coords[1] - '1';
    int dstX = coords[2] - 'a', dstY = coords[3] - '1';

    if (turn == isupper(board->_chessBoard[srcY][srcX]->getSymbol()))
    {
        return 6;
    }

    // Check if source and destination are the same (code 7)
    if (checkIfSameDestination(srcX, srcY, dstX, dstY))
    {
        return 7;
    }

    // Check if the move is a valid capture move (diagonal move with a piece to capture)
    if (abs(dstY - srcY) == 1 && abs(dstX - srcX) == 1 && board->_chessBoard[dstY][dstX] != nullptr)
    {
        this->setFirst2Step();
        return 0;
    }

    // Check if the move violates pawn movement rules (code 6)
    if (abs(dstY - srcY) > 1 || (abs(dstY - srcY) == 1 && abs(dstX - srcX) == 1 && board->_chessBoard[dstY][dstX] == nullptr) || (abs(dstY - srcY) == 1 && abs(dstX - srcX) == 0 && board->_chessBoard[dstY][dstX] != nullptr))
    {
        if (!this->isFirst2Step() && abs(dstY - srcY) == 2 && abs(dstX - srcX) == 0)
        {
            int step = (dstY > srcY) ? 1 : -1;
            if (board->_chessBoard[srcY + step][srcX] != nullptr)
            {
                return 6;
            }
            this->setFirst2Step();
            return 0;
        }
        return 6;
    }

    // Check if destination has a piece of the same color (code 3)
    if (board->_chessBoard[dstY][dstX] != nullptr && isupper(board->_chessBoard[srcY][srcX]->getSymbol()) == isupper(board->_chessBoard[dstY][dstX]->getSymbol()))
    {
        return 3;
    }

    string kingCoords = this->getKingCoords();
    // check if the piece made a check
    if (checkIfPieceCheck(board, coords, kingCoords, turn))
    {
        return 1;
    }
    

    if (!this->isFirst2Step())
    {
        this->setFirst2Step();
    }
    return 0; // Valid move
}

