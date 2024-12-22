/*
This file servers as an example of how to use Pipe.h file.
It is recommended to use the following code in your project, 
in order to read and write information from and to the Backend
*/

#include "Pipe.h"
#include <iostream>
#include <thread>
#include "Board.h"

using std::cout;
using std::endl;
using std::string;


void main()
{
	srand(time_t(NULL));

	Pipe p;
	bool isConnect = p.connect();
	
	string ans;
	while (!isConnect)
	{
		cout << "cant connect to graphics" << endl;
		cout << "Do you try to connect again or exit? (0-try again, 1-exit)" << endl;
		std::cin >> ans;

		if (ans == "0")
		{
			cout << "trying connect again.." << endl;
			Sleep(5000);
			isConnect = p.connect();
		}
		else 
		{
			p.close();
			return;
		}
	}
	

	char msgToGraphics[1024];
	// msgToGraphics should contain the board string accord the protocol
	// YOUR CODE
	Board* gameBoard = new Board(); // creating a new board
	strcpy_s(msgToGraphics, "rnbqkbnrpppppppp################################PPPPPPPPRNBQKBNR1"); // just example...
	
	p.sendMessageToGraphics(msgToGraphics);   // send the board string

	// get message from graphics
	string msgFromGraphics = p.getMessageFromGraphics();

	
	while (msgFromGraphics != "quit")
	{
		// should handle the string the sent from graphics
		// according the protocol. Ex: e2e4 (move e2 to e4)

		// The source and the destination coords	
		int srcX = msgFromGraphics[0] - 'a', srcY = msgFromGraphics[1] - '1';
		int dstX = msgFromGraphics[2] - 'a', dstY = msgFromGraphics[3] - '1';

		strcpy_s(msgToGraphics, (gameBoard->getBoard() + msgToGraphics[65]).c_str()); // msgToGraphics should contain the result of the operation

		/******* JUST FOR EREZ DEBUGGING ******/
		// MAKE LATER A FUNCTION THAT CHECK IF THE SRC INDEXES ARE EMPTY
		int r = gameBoard->_chessBoard[srcY][srcX]->isValidMove(msgFromGraphics, gameBoard, gameBoard->getPlayerTurn());

		if (r == 0 || r == 1 || r == 8)
		{
			gameBoard->move(msgFromGraphics);
			gameBoard->changeTurn();
		}
		msgToGraphics[0] = (char)(r + '0');
		msgToGraphics[1] = 0;
		/******* JUST FOR EREZ DEBUGGING ******/

		// return result to graphics		
		p.sendMessageToGraphics(msgToGraphics);   

		// get message from graphics
		msgFromGraphics = p.getMessageFromGraphics();
	}

	p.close();
}