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
    void setType(ChessPieceType t) {m_type = t;}
    ChessPieceType getType() const {return m_type;}


private:
    //Por defecto las casillas están sin pieza. Esta se añade al incializar el tablero.
    ChessPieceType  m_type = CPT_EMPTY;

    //Por defecto las casillas están sin color. Este se añade al inicializar el tablero.
    ChessPieceColor m_color = CPC_NONE;
};


#endif /* Piece_hpp */
