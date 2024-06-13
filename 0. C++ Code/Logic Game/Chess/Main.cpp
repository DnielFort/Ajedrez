#include <iostream>
#include <algorithm>
#include <sstream>
#include "chessboard.hpp"
#include <fstream>

using namespace std;



int main()
{
	Chessboard c;

	//abriendo tablero inicial
	c.LoadBoardFromFile("C:/Users/PcCom/Desktop/nuevoAjedrez/taulerInicial.txt");

	//print tablero inicial
	cout << c.ToString();

	ChessPosition p(0, 1);
	c.GetValidMoves(p, c);

	ChessPosition a(0, 1);
	ChessPosition b(0, 0);
	c.MovePiece(a,b,c);


	cout << c.ToString();


	return 0;





}


