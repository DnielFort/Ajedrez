#ifndef Chessboard_hpp
#define Chessboard_hpp

#include <stdio.h>
#include "Piece.hpp"
#include "GameInfo.h"
#include "ChessPosition.hpp"
#include <vector>
#include <string>

using namespace std;

class Chessboard {

public:
    Chessboard();
    
    void            LoadBoardFromFile(const string& path);
    VecOfPositions  GetValidMoves (ChessPosition pos) const;
    bool            MovePiece (const ChessPosition& posFrom, const ChessPosition& posTo);
    string          ToString () const;
    
    
private:
    Piece m_board[NUM_COLS][NUM_ROWS];
    int charToInt(char c);
    ChessPieceColor intToColor(int i);
    ChessPieceType charToType(char c);
    void matar(const ChessPosition& pos);
    string intToString(int i) const;
    string colorToString(ChessPieceColor c) const;
    string typeToString(ChessPieceType t) const;

    VecOfPositions Derecha(ChessPosition& pos, VecOfPositions& VecPositions, ChessPieceColor color, bool& obstaculo, ChessPosition& newPos) const;
    VecOfPositions Izquierda(ChessPosition& pos, VecOfPositions& VecPositions, ChessPieceColor color, bool& obstaculo, ChessPosition& newPos) const;
    VecOfPositions Arriba(ChessPosition& pos, VecOfPositions& VecPositions, ChessPieceColor color, bool& obstaculo, ChessPosition& newPos) const;
    VecOfPositions Abajo(ChessPosition& pos, VecOfPositions& VecPositions, ChessPieceColor color, bool& obstaculo, ChessPosition& newPos) const;
    VecOfPositions DiagonalSuperiorDerecha(ChessPosition& pos, VecOfPositions& VecPositions,ChessPieceColor color, bool& obstaculo, ChessPosition& newPos) const;
    VecOfPositions DiagonalSuperiorIzquierda(ChessPosition& pos, VecOfPositions& VecPositions, ChessPieceColor color, bool& obstaculo, ChessPosition& newPos) const;
    VecOfPositions DiagonalInferiorDerecha(ChessPosition& pos, VecOfPositions& VecPositions, ChessPieceColor color, bool& obstaculo, ChessPosition& newPos) const;
    VecOfPositions DiagonalInferiorIzquierda(ChessPosition& pos, VecOfPositions& VecPositions, ChessPieceColor color, bool& obstaculo, ChessPosition& newPos) const;
};


#endif /* Chessboard_hpp */
