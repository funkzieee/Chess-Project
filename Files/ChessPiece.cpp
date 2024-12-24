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
    int checkValid = 0;
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

                checkValid = board->_chessBoard[i][j]->isValidMove(coords, board, turn);
                // Check if the other team piece can move to the king position
                if (checkValid == 0 || checkValid == 1 || checkValid == 8)
                {
                    return true; // means king is in check
                }
            }
        }
    }
    return false; // means king is not in check
}

/*
The function checks if the king is in check after a move of a piece
input: board - 2d array, kingX - int, kingY - int, turn - bool
output: true (for king in check), false (for king not in check)
*/
bool ChessPiece::checkIfPieceCheck(Board* board, const string& coords, const string& kingCoords, bool turn)
{
	int srcX = coords[0] - 'a', srcY = coords[1] - '1';
	int dstX = coords[2] - 'a', dstY = coords[3] - '1';

    int coordX = kingCoords[0] - 'a';
    int coordY = kingCoords[1] - '1';

	bool inCheck = false;
    ChessPiece* temp = board->_chessBoard[dstY][dstX];

	// Move the piece
    board->_chessBoard[dstY][dstX] = board->_chessBoard[srcY][srcX];
	board->_chessBoard[srcY][srcX] = nullptr; // Set the source to nullptr
	// Check if the king is in check after the move
    inCheck = isKingInCheck(board, coordX, coordY, turn);

    // Restore the board
    board->_chessBoard[srcY][srcX] = board->_chessBoard[dstY][dstX];
    board->_chessBoard[dstY][dstX] = temp;
	return inCheck; // return in check (true/false)
}