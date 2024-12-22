#include "Board.h"
#include "Rook.h"
#include "King.h"
#include "Bishop.h"
#include <cmath>
#include <string>


enum WhiteTypes { wROOK = 'R', wKNIGHT = 'N', wBISHOP = 'B', wQUEEN = 'Q', wKING = 'K', wPAWN = 'P' };
enum BlackTypes { bROOK = 'r', bKNIGHT = 'n', bBISHOP = 'b', bQUEEN = 'q', bKING = 'k', bPAWN = 'p' };
using std::string;
using std::pow;

/*
The constructor for the board
input: none
output: none
*/
Board::Board()
{
    // all the private variables
    this->_PlayerTurn = 1; // 1 = black

    int i = 0, j = 0;
    for (i = 0; i < BOARDSIZE; ++i) 
    {
        for (j = 0; j < BOARDSIZE; ++j) 
        {
            this->_chessBoard[i][j] = nullptr;
        }
    }
    // White side
	this->_chessBoard[0][0] = new Rook(wROOK, "e8");
    this->_chessBoard[0][7] = new Rook(wROOK, "e8");
    this->_chessBoard[0][2] = new Bishop(wBISHOP, "e8");
    this->_chessBoard[0][5] = new Bishop(wBISHOP, "e8");
    this->_chessBoard[0][4] = new King(wKING, "e8");
    //Black side
    this->_chessBoard[7][0] = new Rook(bROOK, "e1");
    this->_chessBoard[7][7] = new Rook(bROOK, "e1");
    this->_chessBoard[7][2] = new Bishop(bBISHOP, "e1");
    this->_chessBoard[7][5] = new Bishop(bBISHOP, "e1");
    this->_chessBoard[7][4] = new King(bKING, "e1");
}

/*
The destructor for the board
input: none
output: none
*/
Board::~Board()
{
    int i = 0, j = 0;
    for (i = 0; i < BOARDSIZE; i++) 
    {
        for (j = 0; j < BOARDSIZE; j++) 
        {
            delete _chessBoard[i][j];
        }
    }
}

/*
The function returns the board as a string
input: none
output: string
*/
string Board::getBoard() const
{
    string boardString = "";
    int i = 0, j = 0;
    for (i = 0; i < BOARDSIZE; i++)
    {
        for (j = 0; j < BOARDSIZE; j++)
        {
            if (this->_chessBoard[i][j] == nullptr)
            {
                boardString += "#";
            }
            else
            {
                boardString += this->_chessBoard[i][j]->getSymbol();
            }
        }
    }
    return boardString;
}

/*
The function moves the piece on the board
input: coords - string
output: 0 - the move is valid
*/
int Board::move(std::string coords)
{
    string newPos = "";
    int srcX = coords[0] - 'a', srcY = coords[1] - '1';
    int dstX = coords[2] - 'a', dstY = coords[3] - '1';

    // deleting the piece of the place we want to put the rook in
    if (this->_chessBoard[dstY][dstX] != nullptr)
    {
        delete this->_chessBoard[dstY][dstX];
    }
    this->_chessBoard[dstY][dstX] = this->_chessBoard[srcY][srcX]; // move
    newPos += (char)(dstX + 'a');
    newPos += (char)(dstY + '1');
    this->_chessBoard[srcY][srcX] = nullptr; // Clearing the old position

    return 0;
}

/*
The function changes the turn of the player
input: none
output: none
*/
void Board::changeTurn()
{
    this->_PlayerTurn = !(this->_PlayerTurn);
}

/*
The function returns the turn of the player
input: none
output: bool
*/
bool Board::getPlayerTurn() const
{
    return this->_PlayerTurn;
}

/*
The function update the opposite team king coords after a move
input: kingCoords - string, turn - bool
output: none
*/
void Board::updateKingCoords(const std::string& kingCoords, bool turn) 
{
	int i = 0, j = 0;
	// running over the board
    for (i = 0; i < BOARDSIZE; i++) 
    {
        for (j = 0; j < BOARDSIZE; j++) 
        {
			if (this->_chessBoard[i][j] != nullptr) // checking if its not a blank space
            {
                // Updating only the opposite team king
                if (turn && islower(this->_chessBoard[i][j]->getSymbol())) 
                {
                    this->_chessBoard[i][j]->setKingCoords(kingCoords);
                }
                else if (!turn && isupper(this->_chessBoard[i][j]->getSymbol())) 
                {
                    this->_chessBoard[i][j]->setKingCoords(kingCoords);
                }
            }
        }
    }
}
