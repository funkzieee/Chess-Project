#include "Knight.h"

using std::string;

/*
The constructor for the knight piece
input: symbol - char, kingCoords - string
output: none
*/
Knight::Knight(char symbol, string kingCoords)
	: ChessPiece(symbol, kingCoords)
{
}

/*
The function checks if the knight move is valid based on the coords it gets
input: coords - string, board - 2d array
output: a number based on the move
*/
int Knight::isValidMove(const string& coords, Board* board, bool turn)
{
    bool inCheck = false;
    // Getting the indexes to check on the board
    int srcX = coords[0] - 'a', srcY = coords[1] - '1';
    int dstX = coords[2] - 'a', dstY = coords[3] - '1';

    if (turn == isupper(board->_chessBoard[srcY][srcX]->getSymbol()))
    {
        return 6;
    }

    // Check if the move violates knight movement rules (code 6)
    if (!((abs(dstX - srcX) == 2 && abs(dstY - srcY) == 1) || (abs(dstX - srcX) == 1 && abs(dstY - srcY) == 2)))
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

    string kingCoords = this->getKingCoords();
    // check if the piece made a check
    if (checkIfPieceCheck(board, coords, kingCoords, turn))
    {
        return 1;
    }

    return 0; // Valid move

}
