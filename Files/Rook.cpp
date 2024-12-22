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

//Rook::~Rook()
//{
//}

/*
The function checks if the rook move is valid based on the coords it gets
input: coords - string, board - ChessPiece* [][] (2d array)
output: true (for valid move), false (for invalid move)
*/
int Rook::isValidMove(const string& coords, Board* board, bool turn)
{
	bool isCheck = false;
    // Note: Codes 1 (check), 4 (self-check), and 8 (checkmate) add later
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
    if (board->_chessBoard[srcY][srcX] != nullptr && (board->_chessBoard[srcY][srcX]->getSymbol() == this->getSymbol()))
    {
        return 3;
    }

    // Check path is clear
    if (srcX == dstX) // Vertical move
    {
        step = (dstY > srcY) ? 1 : -1;
        for (i = srcY + step; i != dstY; i += step)
        { 
            if (board->_chessBoard[i][srcX] != nullptr)
            {
                return 6;
            }
        }
    }
    else if (srcY == dstY) // Horizontal move
    {
        step = (dstX > srcX) ? 1 : -1;
        for (i = srcX + step; i != dstX; i += step)
        {
            if (board->_chessBoard[srcY][i] != nullptr)
            {
                return 6;
            }
        }
    }

	ChessPiece* temp = board->_chessBoard[dstY][dstX];
    board->_chessBoard[dstY][dstX] = board->_chessBoard[srcY][srcX];
    board->_chessBoard[srcY][srcX] = nullptr;

	string kingCoords = this->getKingCoords();
    int coordX = kingCoords[0] - 'a';
    int coordY = kingCoords[1] - '1';

    isCheck = isKingInCheck(board, coordX, coordY, turn);
     
    // Restore the board
    board->_chessBoard[srcY][srcX] = board->_chessBoard[dstY][dstX];
    board->_chessBoard[dstY][dstX] = temp;

    if (isCheck)
    {
        return 1;
    }

    return 0; // Valid move
}