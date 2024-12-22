#include "King.h"
#include <iostream>

using std::string;

King::King(char symbol, string kingCoords)
	:	ChessPiece(symbol, kingCoords)
{
}

int King::isValidMove(const string& coords, Board* board, bool turn)
{
    bool inCheck = false;
    // Getting the indexes to check on the board
    int srcX = coords[0] - 'a', srcY = coords[1] - '1';
    int dstX = coords[2] - 'a', dstY = coords[3] - '1';

    if (turn == isupper(board->_chessBoard[srcY][srcX]->getSymbol()))
    {
        return 6;
    }

    // Check if the move violates king movement rules (code 6)
    if (abs(dstX - srcX) > 1 || abs(dstY - srcY) > 1)
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

    inCheck = isKingInCheck(board, dstX, dstY, turn);

    // Restore the board
    board->_chessBoard[srcY][srcX] = board->_chessBoard[dstY][dstX];
    board->_chessBoard[dstY][dstX] = temp;

    if (inCheck)
    {
        return 4;
    }

	string kingCoords = coords.substr(2, 2);
    board->updateKingCoords(kingCoords, turn);
	return 0; // Move is valid
}
