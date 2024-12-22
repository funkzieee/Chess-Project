#include "ChessPiece.h"
#include <string>

using std::string;

ChessPiece::ChessPiece(char symbol, string kingCoords)
	:_symbol(symbol), _kingCoords(kingCoords)
{

}

ChessPiece::~ChessPiece()
{
	this->_symbol = ' ';
	this->_kingCoords = "";
}

void ChessPiece::setSymbol(char symbol)
{
	this->_symbol = symbol;
}

char ChessPiece::getSymbol() const
{
	return this->_symbol;
}

void ChessPiece::setKingCoords(string kingCoords)
{
	this->_kingCoords = kingCoords;
}

string ChessPiece::getKingCoords() const
{
	return (string)this->_kingCoords;
}

bool ChessPiece::checkIfSameDestination(int srcX, int srcY, int dstX, int dstY) const
{
	// Check if source and destination are the same (code 7)
	if (srcX == dstX && srcY == dstY)
	{
		return true;
	}
	return false;
}

bool ChessPiece::isKingInCheck(Board* board, int dstX, int dstY, bool turn) const
{
    string coords = "";
    int i = 0, j = 0;
    // Check if any opponent piece can attack the king
    for (i = 0; i < BOARDSIZE; i++)
    {
        for (j = 0; j < BOARDSIZE; j++)
        {
            if (board->_chessBoard[i][j] && isupper(board->_chessBoard[i][j]->getSymbol()) == turn)
            {
                coords = ""; //reset coords
                coords += char('a' + j);
                coords += char('1' + i);
                coords += char('a' + dstX);
                coords += char('1' + dstY);

                if (board->_chessBoard[i][j]->isValidMove(coords, board, !turn) == 0) // fix here
                {
                    return true;
                }
            }
        }
    }
    return false;
}