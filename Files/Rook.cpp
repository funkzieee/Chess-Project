#include "Rook.h"
#include <iostream>

using std::string;

/*
The constractor for the rook
input: position - string, color - string, symbol - char
output: none
*/
Rook::Rook(char symbol, string kingCoords)
    : ChessPiece(symbol, kingCoords)
{
}

/*
The function checks if the rook move is valid based on the coords it gets
input: coords - string, board - ChessPiece* [][] (2d array)
output: true (for valid move), false (for invalid move)
*/
int Rook::isValidMove(const string& coords, Board* board, bool turn)
{
	bool isCheck = false;
    // 4 (self-check), and 8 (checkmate) add later
    int i = 0, step = 0;
    // getting the indexes to check on the board
    int srcX = coords[0] - 'a', srcY = coords[1] - '1';
    int dstX = coords[2] - 'a', dstY = coords[3] - '1';

    if (turn == isupper(board->_chessBoard[srcY][srcX]->getSymbol()))
    {
        return 6;
    }

    // Check if the move violates rook movement rules (code 6)
    if (srcX != dstX && srcY != dstY)
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

    // Check path is clear
    if (srcX == dstX) // Vertical move
    {
        step = (dstY > srcY) ? 1 : -1; // here we checking the direction of the move
        for (i = srcY + step; i != dstY; i += step)
        { 
            if (board->_chessBoard[i][srcX] != nullptr) // Check if the current block is blocked
            {
                return 6; // if so returing 6
            }
        }
    }
    else if (srcY == dstY) // Horizontal move
    {
        step = (dstX > srcX) ? 1 : -1; // here we checking the direction of the move
        for (i = srcX + step; i != dstX; i += step)
        {
            if (board->_chessBoard[srcY][i] != nullptr) // Check if the current block is blocked
            {
                return 6; // if so returing 6
            }
        }
    }

    string kingCoords = this->getKingCoords();
    // check if the piece made a check
    if (checkIfPieceCheck(board, coords, kingCoords, turn))
    {
        return 1;
    }

    return 0; // Valid move
}