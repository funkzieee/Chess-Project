#include "ChessPiece.h"
#include <string>

using std::string;

/*
The constructor for the chess piece
input: symbol - char, kingCoords - string
output: none
*/
ChessPiece::ChessPiece(char symbol, string kingCoords)
	:_symbol(symbol), _kingCoords(kingCoords)
{

}

/*
The destructor for the chess piece
input: none
output: none
*/
ChessPiece::~ChessPiece()
{
	this->_symbol = ' ';
	this->_kingCoords = "";
}

/*
The function sets the symbol of the piece
input: symbol - char
output: none
*/
void ChessPiece::setSymbol(char symbol)
{
	this->_symbol = symbol;
}

/*
The function returns the symbol of the piece
input: none
output: char
*/
char ChessPiece::getSymbol() const
{
	return this->_symbol;
}

/*
The function sets the king coords
input: kingCoords - string
output: none
*/
void ChessPiece::setKingCoords(string kingCoords)
{
	this->_kingCoords = kingCoords;
}

/*
The function returns the king coords
input: none
output: string
*/
string ChessPiece::getKingCoords() const
{
	return (string)this->_kingCoords;
}

/*
The function checks if the source and destination are the same
input: srcX - int, srcY - int, dstX - int, dstY - int
output: true / false
*/
bool ChessPiece::checkIfSameDestination(int srcX, int srcY, int dstX, int dstY) const
{
	// Check if source and destination are the same (code 7)
	if (srcX == dstX && srcY == dstY)
	{
		return true;
	}
	return false;
}

/*
The function checks if the king is in check
input: board - 2d array, dstX - int, dstY - int, turn - bool
output: true (for king in check), false (for king not in check)
*/
bool ChessPiece::isKingInCheck(Board* board, int kingX, int kingY, bool turn) const
{
    string coords = "";
    int i = 0, j = 0;
    // Check if any opponent piece can attack the king
    for (i = 0; i < BOARDSIZE; i++)
    {
        for (j = 0; j < BOARDSIZE; j++)
        {
            // Check if there is a piece on the board and if its the other team piece
            if (board->_chessBoard[i][j] && isupper(board->_chessBoard[i][j]->getSymbol()) != turn)
            {
                coords = "";
                coords += char('a' + j);
                coords += char('1' + i);
                coords += char('a' + kingX);
                coords += char('1' + kingY);

                // Check if the other team piece can move to the king position
                if (board->_chessBoard[i][j]->isValidMove(coords, board, turn) == 0)
                {
                    return true; // means king is in check
                }
            }
        }
    }
    return false; // means king is not in check
}