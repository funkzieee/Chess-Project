#include "Bishop.h"
#include <iostream>

using std::string;

Bishop::Bishop(char symbol, std::string kingCoords)
	: ChessPiece(symbol, kingCoords)
{
}

int Bishop::isValidMove(const std::string& coords, Board* board, bool turn)
{
    bool isCheck = false;
    int i = 0;
    // Getting the indexes to check on the board
    int srcX = coords[0] - 'a', srcY = coords[1] - '1';
    int dstX = coords[2] - 'a', dstY = coords[3] - '1';

    if (turn == isupper(board->_chessBoard[srcY][srcX]->getSymbol()))
    {
        return 6;
    }

    // Check if the move violates Bishop movement rules (code 6)
    if (dstX - srcX != dstY - srcY)
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

	return 0;
}
