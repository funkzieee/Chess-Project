//#include "Bishop.h"
//#include <iostream>
//#include <cmath>
//
//using std::string;
//
//Bishop::Bishop(char symbol, std::string kingCoords)
//	: ChessPiece(symbol, kingCoords)
//{
//}
//
//int Bishop::isValidMove(const std::string& coords, Board* board, bool turn)
//{
//    bool isCheck = false;
//    int i = 0, step = 0;
//    // Getting the indexes to check on the board
//    int srcX = coords[0] - 'a', srcY = coords[1] - '1';
//    int dstX = coords[2] - 'a', dstY = coords[3] - '1';
//
//    if (turn == isupper(board->_chessBoard[srcY][srcX]->getSymbol()))
//    {
//        return 6;
//    }
//
//    // Check if the move violates Bishop movement rules (code 6)
//    if (abs(dstX - srcX) != abs(dstY - srcY))
//    {
//        return 6;
//    }
//
//    // Check if source and destination are the same (code 7)
//    if (checkIfSameDestination(srcX, srcY, dstX, dstY))
//    {
//        return 7;
//    }
//
//    // Check if destination has a piece of the same color (code 3)
//    if (board->_chessBoard[dstY][dstX] != nullptr && isupper(board->_chessBoard[srcY][srcX]->getSymbol()) == isupper(board->_chessBoard[dstY][dstX]->getSymbol()))
//    {
//        return 3;
//    }
//
//    if(dstX > srcX && dstY > srcY || dstX < srcX && dstY > srcY ) //diagnal right
//    {
//        step = (dstY > srcY) ? 1 : -1;
//        for (i = srcY + step; i != dstY; i += step)
//        { 
//            if (board->_chessBoard[i][srcX] != nullptr) // Check if the current block is blocked
//            {
//            return 6; // if so returing 6
//            }
//        }
//    }
//    if(dstX > srcX && dstY < srcY || dstX < srcX && dstY < srcY ) //diagnal left
//    {
//
//    }
//        
//
//    
//
//    ChessPiece* temp = board->_chessBoard[dstY][dstX];
//    board->_chessBoard[dstY][dstX] = board->_chessBoard[srcY][srcX];
//    board->_chessBoard[srcY][srcX] = nullptr;
//
//    string kingCoords = this->getKingCoords();
//    int coordX = kingCoords[0] - 'a';
//    int coordY = kingCoords[1] - '1';
//
//    isCheck = isKingInCheck(board, coordX, coordY, turn);
//
//    // Restore the board
//    board->_chessBoard[srcY][srcX] = board->_chessBoard[dstY][dstX];
//    board->_chessBoard[dstY][dstX] = temp;
//
//    if (isCheck)
//    {
//        return 1;
//    }
//
//	return 0;
//}
