#ifndef Piece_hpp
#define Piece_hpp

#include <stdio.h>
#include <vector>
#include "GameInfo.h"
using namespace std;

typedef enum {
    CPT_King,
    CPT_Queen,
    CPT_Rook,
    CPT_Bishop,
    CPT_Knight,
    CPT_Pawn,
    CPT_EMPTY
} ChessPieceType;

typedef enum {
    CPC_Black,
    CPC_White,
    CPC_NONE
} ChessPieceColor;



class Piece {
public:
    void setColor(ChessPieceColor c) {m_color = c;}
    ChessPieceColor getColor() const {return m_color;}

    ChessPieceColor colorContrari() 
    {
        if (m_color == CPC_Black) return CPC_White;
        else if (m_color == CPC_White) return CPC_Black;
    }


    void setType(ChessPieceType t) {m_type = t;}

    bool getMoved() { return moved; }
    void setMoved(bool m) {moved=m; }

    ChessPieceType getType() const { return m_type; };
    void render(int posX, int posY);


    char typeToChar();


private:
    //Por defecto las casillas están sin pieza. Esta se añade al incializar el tablero.
    ChessPieceType  m_type = CPT_EMPTY;

    //Por defecto las casillas están sin color. Este se añade al inicializar el tablero.
    ChessPieceColor m_color = CPC_NONE;

    bool moved=false;
};


#endif /* Piece_hpp */
