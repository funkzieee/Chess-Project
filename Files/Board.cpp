#include "Board.h"
#include "Rook.h"
#include "King.h"
#include <cmath>
#include <string>


enum WhiteTypes { wROOK = 'R', wKNIGHT = 'N', wBISHOP = 'B', wQUEEN = 'Q', wKING = 'K', wPAWN = 'P' };
enum BlackTypes { bROOK = 'r', bKNIGHT = 'n', bBISHOP = 'b', bQUEEN = 'q', bKING = 'k', bPAWN = 'p' };
using std::string;
using std::pow;

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
    this->_chessBoard[0][4] = new King(wKING, "e8");
    //Black side
    this->_chessBoard[7][0] = new Rook(bROOK, "e1");
    this->_chessBoard[7][7] = new Rook(bROOK, "e1");
    this->_chessBoard[7][4] = new King(bKING, "e1");
}


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

void Board::changeTurn()
{
    this->_PlayerTurn = !(this->_PlayerTurn);
}

bool Board::getPlayerTurn() const
{
    return this->_PlayerTurn;
}

void Board::updateKingCoords(const std::string& kingCoords, bool turn) {
	int i = 0, j = 0;
    for (i = 0; i < BOARDSIZE; i++) 
    {
        for (j = 0; j < BOARDSIZE; j++) 
        {
            if (this->_chessBoard[i][j] != nullptr) 
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
