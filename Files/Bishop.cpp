#include "Bishop.h"
#include <iostream>
#include <cmath>

using std::string;

/*
The constructor for the Bishop piece
input: symbol - char, kingCoords - string
output: none
*/
Bishop::Bishop(char symbol, std::string kingCoords)
	: ChessPiece(symbol, kingCoords)
{
}

/*
The function checks if the bishop move is valid based on the coords it gets
input: coords - string, board - 2d array, turn - bool
output: a number based on the move
*/
int Bishop::isValidMove(const std::string& coords, Board* board, bool turn)
{
    bool isCheck = false;
    // Getting the indexes to check on the board
    int srcX = coords[0] - 'a', srcY = coords[1] - '1';
    int dstX = coords[2] - 'a', dstY = coords[3] - '1';

    if (turn == isupper(board->_chessBoard[srcY][srcX]->getSymbol()))
    {
        return 6;
    }

    // Check if the move violates Bishop movement rules (code 6)
    if (abs(dstX - srcX) != abs(dstY - srcY))
    {
        return 6;
    }

    // Check if source and destination are the same (code 7)
    if (checkIfSameDestination(srcX, srcY, dstX, dstY))
    {
        return 7;
    }

    // Check if destination has a piece of the same color (code 3)
    if (board->_chessBoard[dstY][dstX] != nullptr && isupper(board->_chessBoard[srcY][srcX]->getSymbol()) == isupper(board->_chessBoard[dstY][dstX]->getSymbol()))
    {
        return 3;
    }

    if (abs(dstX - srcX) == abs(dstY - srcY))
    { // Check if the move is diagonal
        int stepX = (dstX > srcX) ? 1 : -1; // Direction for X
        int stepY = (dstY > srcY) ? 1 : -1; // Direction for Y

        int xs = srcX + stepX;
        int ys = srcY + stepY;
        // Initialize position to start checking from the next diagonal square

        while (xs != dstX && ys != dstY)
        {
            if (board->_chessBoard[ys][xs] != nullptr) // Check if the current block is blocked
            {
                return 6; // if so returing 6
            }
            xs += stepX;
            ys += stepY;
        }
    }

    string kingCoords = this->getKingCoords();
    // check if the piece made a check
    if (checkIfPieceCheck(board, coords, kingCoords, turn))
    {
        return 1;
    }

	return 0;
}
