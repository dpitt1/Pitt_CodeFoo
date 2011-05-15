/*
 * File: KnightPuzzle.cpp
 * ----------------------
 * By David Pitt ~ 05/2011
 *
 * Documentation: This command-line c++ program find the range of squares a knight
 *	can reach on a chess board in a given number of moves. The program adds moves,
 *	extending the range of the knight in a breadth-first manner, until all squares
 *	on the chess board have been found.
 *
 */

#include <iostream>
#include <string>
#include <queue.h>

using namespace std;


/* constants */
static const int BOARD_DIM = 8;

/* Stores the knight's poisiton on the chess board
 *	and	the number of moves it took to get there. */
struct coordT {
	int row, col, numMoves;
};



/* Checks if a knight move is 1) in bounds and 2) not redundant. If 
 *	both these conditions are true, the move is put in the queue
 *	and numMoves is incremented */
void AddIfLegal(int row, int col, int numMoves, int** board, queue<coordT>& q) {
	
	coordT start = q.front();
	
	if(row >= 0 && row < BOARD_DIM &&
	   col >= 0 && col < BOARD_DIM &&
	   board[row][col] < 0) {
		
		coordT move;
		move.row = row;
		move.col = col;
		move.numMoves = ++numMoves;
		
		q.push(move);
		
		board[row][col] = numMoves;

	}	
	
}

/* This function attempts to enqueue the eight possible moves a
 *	knight can make from any given position. Of course, not all
 *	the moves will be in bounds, and some will be redundant. */
void EnqueueEightMoves(int** board, queue<coordT>& q, int& count) {
	
	coordT start = q.front();
	
	int row = start.row;
	int col = start.col;
	int numMoves = start.numMoves;
	
	AddIfLegal(row - 2, col - 1, numMoves, board, q);
	
	AddIfLegal(row - 2, col + 1, numMoves, board, q);
	
	AddIfLegal(row - 1, col - 2, numMoves, board, q);
	
	AddIfLegal(row - 1, col + 2, numMoves, board, q);
	
	AddIfLegal(row + 1, col - 2, numMoves, board, q);
	
	AddIfLegal(row + 1, col + 2, numMoves, board, q);
	
	AddIfLegal(row + 2, col - 1, numMoves, board, q);
	
	AddIfLegal(row + 2, col + 1, numMoves, board, q);
	
	
}

/* The chess board is a 2D array of integers (8 x 8), where each square 
 *	stores the number of moves it takes for the knight to reach it. */
int **InitializeBoard() {
	
	int **result = new int*[BOARD_DIM];
	
	
	for (size_t i = 0; i < BOARD_DIM; ++i) {
		int *cols = new int[BOARD_DIM];
		result[i] = cols;
	}
	
	for (size_t i = 0; i < BOARD_DIM * BOARD_DIM; ++i) {
		/* initial value -1 means the path to that square has
		 *	not yet been found by a knight move  */
		result[i / BOARD_DIM][i % BOARD_DIM] = -1;
	}
	
	return result;
	
}

/* We don't want to orphan memory! */
void deleteBoard(int **board) {
	
	for (size_t i = 0; i < BOARD_DIM; ++i) {
		delete board[i];
	}
	
	delete board;
		
}

/* We are trying to find the minimum number of moves with which
 *	to cover the board, so breadth-first search is ideal. We store
 *	locations visited in a queue, enqueuing new legal moves and dequeuing
 *	moves we already considered. Once the queue is empty, the search is over. */
void BreadthFirstSearch(coordT start) {
	
	int locationsCovered = 1;
	
	int maxMoves = -1; // -1 so that 0 moves can be recognized as the "first" move //
	
	int **visited = InitializeBoard();
	
	visited[start.row][start.col] = start.numMoves;
	
	queue<coordT> q;
	q.push(start);
	
	while (!q.empty()) {
		
		start = q.front();

		if (start.numMoves > maxMoves) {

			maxMoves = start.numMoves;
			
			cout << endl << "Num moves: " << maxMoves << ". Locations covered: " << locationsCovered << endl;
			
			cout << "Board looks like this:" << endl;
			for (int i = 0; i < BOARD_DIM; i++) {
				for (int j = 0; j < BOARD_DIM; j++) {
					
					if (visited[j][i] >= 0) {
						cout << " " << visited[j][i] << " ";
					}
					else {
						cout << " _ ";
					}
				}
				cout << endl;
			}
			cout << endl;
			
		}
		
		EnqueueEightMoves(visited, q, locationsCovered);
				
		q.pop();

	}
	
	deleteBoard(visited);
	
}

int main () {
	
    cout << "This program find the range of a knight on the chess board after n moves." << endl;
	cout << "How many moves does it take for the knight to cover the whole board?" << endl << endl;
		
	coordT start;
	start.row = 1;
	start.col = 0; //describes the standard start position of a knight on a chess board
	start.numMoves = 0;

	cout << "The knight starts in the standard position on the board: top row, second column." << endl;
//	cout << "...Unless you want to "
//	while (true) {
//		cout << "specify your own start loation (Y/N): ";
		

	BreadthFirstSearch(start);
	
    return 0;
}
