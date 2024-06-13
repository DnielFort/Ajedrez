#ifndef Chessboard_hpp;
#define Chessboard_hpp

#include <stdio.h>
#include "Piece.hpp"
#include "GameInfo.h"

#include "ChessPosition.hpp"

typedef vector<ChessPosition> VecOfPositions;

class Chessboard {

public:
    Chessboard() {};
    
    void            LoadBoardFromFile(const string& path);  //check
    VecOfPositions  GetValidMoves (ChessPosition pos, Chessboard cb) const; //check
    bool            MovePiece (const ChessPosition& posFrom, const ChessPosition& posTo, Chessboard cb);
    string          ToString () const;  //check
    bool posProhibida(int x, int y, ChessPieceColor c, Chessboard cb)const; //check

    void vertical(int x, int y, VecOfPositions &vector, ChessPieceColor c, Chessboard cb); //check
    void horizontal(int x, int y, VecOfPositions& vector, ChessPieceColor c, Chessboard cb);//check
    void diagonal(int x, int y, VecOfPositions& vector, ChessPieceColor c, Chessboard cb);//check
    Piece m_board[NUM_COLS][NUM_ROWS];

    string colorToString(ChessPieceColor c) { if (c == CPC_Black) return "negres"; else return "blanques"; }


    ChessPosition getCasellaSeleccionada() { return m_casellaSeleccionada; }
    void setCasellaSeleccionada(ChessPosition casella) { m_casellaSeleccionada = casella; }

    void displayPices();

    int getNBlanques() { return n_blanques; }
    int getNNegres() { return n_negres; }
    
private:
    


    int charToInt(char c);
    ChessPieceColor intToColor(int i);
    ChessPieceType charToType(char c);
    void matar(const ChessPosition& pos);
    string intToString(int i) const;
    string colorToString(ChessPieceColor c) const;
    string typeToString(ChessPieceType t) const;

    ChessPosition m_casellaSeleccionada = ChessPosition(0,0);

    int n_blanques=NULL;
    int n_negres=NULL;
    bool reiMort = false;

};


#endif /* Chessboard_hpp */
