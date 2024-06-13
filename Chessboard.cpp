#include "Chessboard.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>


using namespace std;

/// <summary>
/// Devuelve la posición las letras (a-h) en el alfabeto
/// Si se pasa cualquier otra letra devuelve 0
/// </summary>
/// <param name="c"></param>
/// <returns></returns>
///

Chessboard::Chessboard() {

}


int Chessboard::charToInt(char c) {
    int numReturn;

    switch (c) {
    case 'a':
        numReturn = 1;
        break;
    case 'b':
        numReturn = 2;
        break;
    case 'c':
        numReturn = 3;
        break;
    case 'd':
        numReturn = 4;
        break;
    case 'e':
        numReturn = 5;
        break;
    case 'f':
        numReturn = 6;
        break;
    case 'g':
        numReturn = 7;
        break;
    case 'h':
        numReturn = 8;
        break;

    default:
        numReturn = 0;
    }
    return numReturn;
}

/// <summary>
/// Pasa int a ChessPieceColor. 0: blanques / 1: negres / 2: sin color
/// </summary>
/// <param name="i">int que se desea pasar a color</param>
/// <returns>ChessPieceColor</returns>
ChessPieceColor Chessboard::intToColor(int i) {
    ChessPieceColor colorToReturn;
    switch (i) {
    case 0:
        colorToReturn = CPC_White;
        break;
    case 1:
        colorToReturn = CPC_Black;
        break;
    case 2:
        colorToReturn = CPC_NONE;
        break;
    }
    return colorToReturn;
}

/// <summary>
/// Transforma char a ChessPieceType. Chars aceptados: {R,D,T,A,C,P}
/// </summary>
/// <param name="c">R: Rei / D: Dama /T : Torre / A : Alfil / C : Cavall / P : Peó </param>
/// <returns>ChessPieceType</returns>
ChessPieceType Chessboard::charToType(char c) {
    ChessPieceType typeToReturn;

    switch (c) {
    case 'R':
        typeToReturn = CPT_King;
        break;
    case 'D':
        typeToReturn = CPT_Queen;
        break;
    case 'T':
        typeToReturn = CPT_Rook;
        break;
    case 'A':
        typeToReturn = CPT_Bishop;
        break;
    case 'C':
        typeToReturn = CPT_Knight;
        break;
    case 'P':
        typeToReturn = CPT_Pawn;
        break;
    case 'E':
        typeToReturn = CPT_EMPTY;
        break;
    }
    return typeToReturn;
}


/// <summary>
/// Inicializa partida a través de txt.
/// </summary>
/// <param name="path">Nombre del archivo txt</param>
void Chessboard::LoadBoardFromFile(const string& path) {
    ifstream fitxer;
    fitxer.open(path);
    if (fitxer.is_open()) {
        char point;
        int intcolumna;
        //COLOR -> blanca = 0 / negra = 1
        int color;
        //FILA -> Mas baja = 1, mas alta=8
        int fila;
        //TIPO DE PIEZA -> R: rei / D: Dama / T: Torre / A: Alfil / C: Cavall / P: Peó
        char tipus;
        //COLUMNA -> max derecha = a / max izquierda = h
        char columna;

        fitxer >> color >> point >> tipus >> columna >> fila;
        while (!fitxer.eof()) {
            intcolumna = charToInt(columna);
            m_board[intcolumna][fila].setColor(intToColor(color));
            m_board[intcolumna][fila].setType(charToType(tipus));
            fitxer >> color >> point >> tipus >> columna >> fila;
        }
        fitxer.close();
    }
}


/// <summary>
/// Elimina una pieza del tablero
/// </summary>
/// <param name="pos">La elimina pasando su m_type a CPT_EMPTY y su m_color a CPC_NONE</param>
void Chessboard::matar(const ChessPosition& pos) {
    m_board[pos.getX()][pos.getY()].setColor(CPC_NONE);
    m_board[pos.getX()][pos.getY()].setType(CPT_EMPTY);
}


/// <summary>
/// Mueve pieza de una posición a otra.
/// </summary>
/// <param name="posFrom"></param>
/// <param name="posTo"></param>
/// <returns></returns>
bool Chessboard::MovePiece(const ChessPosition& posFrom, const ChessPosition& posTo) {
    VecOfPositions validMoves = GetValidMoves(posFrom);

    //Buscar si posTo es un movimiento válido.
    if (find(validMoves.begin(), validMoves.end(), posTo) != validMoves.end()) {
        //Es movimiento válido

        //Buscar si hay alguna pieza en esa posición
        if (m_board[posTo.getX()][posTo.getY()].getType() != CPC_NONE) {
            //Si hay pieza la mata
            matar(posTo);
        }
        //Se mueve a la posición
        m_board[posTo.getX()][posTo.getY()].setType(m_board[posFrom.getX()][posFrom.getY()].getType());
        m_board[posTo.getX()][posTo.getY()].setColor(m_board[posFrom.getX()][posFrom.getY()].getColor());
        //Libera la posición posFrom
        matar(posFrom);
        return true;
    }
    else {
        //No es un movimiento válido, no hace nada.
        return false;
    }
}

/// <summary>
/// A partir de un int devuelve la letra de la posición i del abecedario
/// </summary>
/// <param name="i"></param>
/// <returns></returns>
string Chessboard::intToString(int i) const {
    return string(1, static_cast<char>('A' - 1 + i));
}


/// <summary>
/// Deuvele un string indicando el color
/// </summary>
/// <param name="c">si ChessPieceColor =CPC_Black -> "b" /si ChessPieceColor = CPC_White ->"w" </param>
/// <returns></returns>
string Chessboard::colorToString(ChessPieceColor c) const {
    if (c == CPC_Black) {
        return "b";
    }
    if (c == CPC_White) {
        return "w";
    }
    else
        return "Error, colorToString no ha recibido un valor valido";
}

string Chessboard::typeToString(ChessPieceType t) const {
    if (t == CPT_King)
        return "R";
    else if (t == CPT_Queen)
        return "D";
    else if (t == CPT_Rook)
        return "T";
    else if (t == CPT_Bishop)
        return "A";
    else if (t == CPT_Knight)
        return "A";
    else if (t == CPT_Pawn)
        return "P";
    else
        return "Error, typeToString no ha recibido un valor valido";
}


string Chessboard::ToString() const {
    string arrayS[8][8];
    //añade los números de las filas
    int c = 8;
    for (int i = 0; i < 8; i++) {
        arrayS[i][0] = to_string(c) + " ";
        c--;
    }
    //añade las letras de las columnas
    arrayS[8][0] = "  ";
    for (int i = 1; i < 9; i++) {
        arrayS[8][i] = " " + intToString(i) + " ";
    }

    //añade las piezas en el tablero
    for (int i = 1; i < 9; i++) {
        int contadorBoardI = i - 1;
        for (int j = 0; j < 8; j++) {
            //comprueba si la posición está vacía
            if (m_board[contadorBoardI][j].getColor() == CPC_NONE) {
                //Si vacía
                arrayS[i][j] = "__ ";
            }
            else {
                //no vacía
                arrayS[i][j] = colorToString(m_board[contadorBoardI][j].getColor()) +
                    typeToString(m_board[contadorBoardI][j].getType()) + " ";
            }
        }
    }

    //El tablero array a un solo string;
    string stringReturn = "";
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            stringReturn += arrayS[i][j];
            if (i == 8) {
                stringReturn += "\n";
            }
        }
    }
    return stringReturn;
}

VecOfPositions Chessboard::GetValidMoves(ChessPosition pos) const {
    //DESCRIPCIÓN:
    //Calcula las posiciones a las que se puede mover una pieza en base a la posición inicial

    //PARAMETROS:
    //La posición inicial de la pieza

    //RETURN:
    //Retorna el conjunto de las posiciones a las cuales se puede mover la pieza

    std::vector<ChessPosition> VecPositions;
    ChessPosition newPos = pos;
    bool obstaculo = true;
    ChessPieceColor color = m_board[pos.getX()][pos.getY()].getColor();


    ChessPieceType t = m_board[pos.getX()][pos.getY()].getType();

    switch (t) {
        //posición Rey
    case CPT_King:

        for (int i = 0; i < 1; i++) {

            Chessboard::Derecha(pos, VecPositions, color, obstaculo, newPos);

            Chessboard::Izquierda(pos, VecPositions, color, obstaculo, newPos);

            Chessboard::Abajo(pos, VecPositions, color, obstaculo, newPos);

            Chessboard::Arriba(pos, VecPositions, color, obstaculo, newPos);

            Chessboard::DiagonalSuperiorIzquierda(pos, VecPositions, color, obstaculo, newPos);

            Chessboard::DiagonalSuperiorDerecha(pos, VecPositions, color, obstaculo, newPos);

            Chessboard::DiagonalInferiorIzquierda(pos, VecPositions, color, obstaculo, newPos);

            Chessboard::DiagonalInferiorDerecha(pos, VecPositions, color, obstaculo, newPos);
        }

        break;

        //posición Dama

    case CPT_Queen:

        if (pos.getX() <= NUM_ROWS) {
            //Derecha

            Chessboard::Derecha(pos, VecPositions, color, obstaculo, newPos);

            //Izquierda

            Chessboard::Izquierda(pos, VecPositions, color, obstaculo, newPos);
            //return(ChessPosition('a4'))
        }

        if (pos.getY() <= NUM_COLS) {

            //Abajo

            Chessboard::Abajo(pos, VecPositions, color, obstaculo, newPos);

            //Arriba

            Chessboard::Arriba(pos, VecPositions, color, obstaculo, newPos);
        }

        Chessboard::DiagonalSuperiorIzquierda(pos, VecPositions, color, obstaculo, newPos);

        Chessboard::DiagonalSuperiorDerecha(pos, VecPositions, color, obstaculo, newPos);

        Chessboard::DiagonalInferiorIzquierda(pos, VecPositions, color, obstaculo, newPos);

        Chessboard::DiagonalInferiorDerecha(pos, VecPositions, color, obstaculo, newPos);

        break;

        //posición Torre

    case CPT_Rook:

        //Horizontal

        //Comprobar que no salga fuera del tablero (En caso que se pase una posición no valida)

        if (pos.getX() <= NUM_ROWS) {

            //Derecha

            Chessboard::Derecha(pos, VecPositions, color, obstaculo, newPos);

            //Izquierda

            Chessboard::Izquierda(pos, VecPositions, color, obstaculo, newPos);
            //return(ChessPosition('a4'))
        }

        if (pos.getY() <= NUM_COLS) {

            //Abajo

            Chessboard::Abajo(pos, VecPositions, color, obstaculo, newPos);

            //Arriba

            Chessboard::Arriba(pos, VecPositions, color, obstaculo, newPos);
        }

        break;

        //posición Alfil

    case CPT_Bishop:

        Chessboard::DiagonalSuperiorIzquierda(pos, VecPositions, color, obstaculo, newPos);

        Chessboard::DiagonalSuperiorDerecha(pos, VecPositions, color, obstaculo, newPos);

        Chessboard::DiagonalInferiorIzquierda(pos, VecPositions, color, obstaculo, newPos);

        Chessboard::DiagonalInferiorDerecha(pos, VecPositions, color, obstaculo, newPos);

        break;

        //posición Caballo

    case CPT_Knight:

        break;

        //posición Peón

    case CPT_Pawn:

        if (pos.getX() <= NUM_ROWS) {

            //Recorrido para saltar dos casillas (peones negros)

            int segunda_columna[NUM_COLS - 6][1];
            int sexta_columna[NUM_COLS - 2][1];

            if (reinterpret_cast<int>(segunda_columna) == pos.getX()) {
                for (int i = 0; i < 2; i++) {
                    Chessboard::Abajo(pos, VecPositions, color, obstaculo, newPos);
                }

            }
            //Recorrido para saltar dos casillas (peones blancos)

            if (reinterpret_cast<int>(sexta_columna) == pos.getX()) {
                for (int i = 0; i < 2; i++) {
                    Chessboard::Abajo(pos, VecPositions, color, obstaculo, newPos);
                }

            }
        }
        break;



        //posición Vacía
    case CPT_EMPTY:

        break;

    }

    return VecPositions;
}

VecOfPositions
Chessboard::Derecha(ChessPosition& pos, VecOfPositions& VecPositions, ChessPieceColor color, bool& obstaculo,
    ChessPosition& newPos) const {

    int i = pos.getX();

    if ((pos.getX() <= NUM_ROWS) && (pos.getY() <= NUM_COLS)) {
        while (i <= NUM_ROWS && !obstaculo) {
            //Diferente color, la pieza puede matar a la otra

            if (m_board[pos.getX()][pos.getY()].getColor() != color) {
                newPos.setX(i);
                VecPositions.push_back(newPos);
                obstaculo = false;
            }

            //Color igual, acabar el recorrido

            if (m_board[pos.getX()][pos.getY()].getColor() == color) {
                newPos.setX(i);
                VecPositions.push_back(newPos);
                obstaculo = false;
            }
            else {
                newPos.setX(i);
                VecPositions.push_back(newPos);
                i++;
            }
        }

    }
    else {
        newPos.setX(i);
        VecPositions.push_back(newPos);
        i++;
    }
    return VecPositions;

    //No emprar pos, utilitzar una pos nova per poder guardar les posicions de la peça (posPeça p.ex)
    //posicio i j valida -- push_back i seguir el recorregut, sino aturar el recorregut
    //si es del mateix color acabar recorregt
}

VecOfPositions
Chessboard::Izquierda(ChessPosition& pos, VecOfPositions& VecPositions, ChessPieceColor color, bool& obstaculo,
    ChessPosition& newPos) const {

    int i = pos.getX();

    if ((pos.getX() <= NUM_ROWS) && (pos.getY() <= NUM_COLS)) {
        while (i >= NUM_ROWS && !obstaculo) {
            //Diferente color, la pieza puede matar a la otra

            if (m_board[pos.getX()][pos.getY()].getColor() != color) {
                newPos.setX(i);
                VecPositions.push_back(newPos);
                obstaculo = false;
            }

            //Color igual, acabar el recorrido

            if (m_board[pos.getX()][pos.getY()].getColor() == color) {
                newPos.setX(i);
                VecPositions.push_back(newPos);
                obstaculo = false;
            }
            else {
                newPos.setX(i);
                VecPositions.push_back(newPos);
                i--;
            }
        }

    }
    else {
        newPos.setX(i);
        VecPositions.push_back(newPos);
        i--;
    }
    return VecPositions;

}

VecOfPositions
Chessboard::Arriba(ChessPosition& pos, VecOfPositions& VecPositions, ChessPieceColor color, bool& obstaculo,
    ChessPosition& newPos) const {

    int j = pos.getY();

    if ((pos.getX() <= NUM_ROWS) && (pos.getY() <= NUM_COLS)) {
        while (j >= NUM_COLS && !obstaculo) {
            //Diferente color, la pieza puede matar a la otra

            if (m_board[pos.getX()][pos.getY()].getColor() != color) {
                newPos.setY(j);
                VecPositions.push_back(newPos);
                obstaculo = false;
            }

            //Color igual, acabar el recorrido

            if (m_board[pos.getX()][pos.getY()].getColor() == color) {
                newPos.setY(j);
                VecPositions.push_back(newPos);
                obstaculo = false;
            }
            else {
                newPos.setY(j);
                VecPositions.push_back(newPos);
                j--;
            }
        }

    }
    else {
        newPos.setY(j);
        VecPositions.push_back(newPos);
        j--;
    }
    return VecPositions;

}

VecOfPositions
Chessboard::Abajo(ChessPosition& pos, VecOfPositions& VecPositions, ChessPieceColor color, bool& obstaculo,
    ChessPosition& newPos) const {

    int j = pos.getY();

    if ((pos.getX() <= NUM_ROWS) && (pos.getY() <= NUM_COLS)) {
        while (j <= NUM_COLS && !obstaculo) {
            //Diferente color, la pieza puede matar a la otra

            if (m_board[pos.getX()][pos.getY()].getColor() != color) {
                newPos.setY(j);
                VecPositions.push_back(newPos);
                obstaculo = false;
            }

            //Color igual, acabar el recorrido

            if (m_board[pos.getX()][pos.getY()].getColor() == color) {
                newPos.setY(j);
                VecPositions.push_back(newPos);
                obstaculo = false;
            }
            else {
                newPos.setY(j);
                VecPositions.push_back(newPos);
                j++;
            }
        }
    }
    else {
        newPos.setY(j);
        VecPositions.push_back(newPos);
        j++;
    }
    return VecPositions;

}

VecOfPositions
Chessboard::DiagonalInferiorDerecha(ChessPosition& pos, VecOfPositions& VecPositions, ChessPieceColor color,
    bool& obstaculo, ChessPosition& newPos) const {

    int i = pos.getX();
    int j = pos.getY();

    if ((pos.getX() <= NUM_ROWS) && (pos.getY() <= NUM_COLS)) {
        while (i <= NUM_COLS && j <= NUM_ROWS && !obstaculo) {
            //Diferente color, la pieza puede matar a la otra

            if (m_board[pos.getX()][pos.getY()].getColor() != color) {
                newPos.setX(i);
                newPos.setY(j);
                VecPositions.push_back(newPos);
                obstaculo = false;
            }

            //Color igual, acabar el recorrido

            if (m_board[pos.getX()][pos.getY()].getColor() == color) {
                newPos.setX(i);
                newPos.setY(j);
                VecPositions.push_back(newPos);
                obstaculo = false;
            }
            else {
                newPos.setX(i);
                newPos.setY(j);
                VecPositions.push_back(newPos);
                i++;
                j++;
            }
        }
    }
    else {
        newPos.setX(i);
        newPos.setY(j);
        VecPositions.push_back(newPos);
        i++;
        j++;
        return VecPositions;
    }
}

VecOfPositions
Chessboard::DiagonalInferiorIzquierda(ChessPosition& pos, VecOfPositions& VecPositions, ChessPieceColor color,
    bool& obstaculo, ChessPosition& newPos) const {

    int i = pos.getX();
    int j = pos.getY();

    if ((pos.getX() <= NUM_ROWS) && (pos.getY() <= NUM_COLS)) {
        while (i >= NUM_COLS && j <= NUM_ROWS && !obstaculo) {
            //Diferente color, la pieza puede matar a la otra

            if (m_board[pos.getX()][pos.getY()].getColor() != color) {
                newPos.setX(i);
                newPos.setY(j);
                VecPositions.push_back(newPos);
                obstaculo = false;
            }

            //Color igual, acabar el recorrido

            if (m_board[pos.getX()][pos.getY()].getColor() == color) {
                newPos.setX(i);
                newPos.setY(j);
                VecPositions.push_back(newPos);
                obstaculo = false;
            }
            else {
                newPos.setX(i);
                newPos.setY(j);
                VecPositions.push_back(newPos);
                i--;
                j++;
            }
        }
    }
    else {
        newPos.setX(i);
        newPos.setY(j);
        VecPositions.push_back(newPos);
        i--;
        j++;
        return VecPositions;
    }
}

VecOfPositions
Chessboard::DiagonalSuperiorDerecha(ChessPosition& pos, VecOfPositions& VecPositions, ChessPieceColor color,
    bool& obstaculo, ChessPosition& newPos) const {

    int i = pos.getX();
    int j = pos.getY();

    if ((pos.getX() <= NUM_ROWS) && (pos.getY() <= NUM_COLS)) {
        while (i <= NUM_COLS && j >= NUM_ROWS && !obstaculo) {
            //Diferente color, la pieza puede matar a la otra

            if (m_board[pos.getX()][pos.getY()].getColor() != color) {
                newPos.setX(i);
                newPos.setY(j);
                VecPositions.push_back(newPos);
                obstaculo = false;
            }

            //Color igual, acabar el recorrido

            if (m_board[pos.getX()][pos.getY()].getColor() == color) {
                newPos.setX(i);
                newPos.setY(j);
                VecPositions.push_back(newPos);
                obstaculo = false;
            }
            else {
                newPos.setX(i);
                newPos.setY(j);
                VecPositions.push_back(newPos);
                i++;
                j--;
            }
        }
    }
    else {
        newPos.setX(i);
        newPos.setY(j);
        VecPositions.push_back(newPos);
        i++;
        j--;
        return VecPositions;
    }
}

VecOfPositions
Chessboard::DiagonalSuperiorIzquierda(ChessPosition& pos, VecOfPositions& VecPositions, ChessPieceColor color,
    bool& obstaculo, ChessPosition& newPos) const {


    int i = pos.getX();
    int j = pos.getY();

    if ((pos.getX() <= NUM_ROWS) && (pos.getY() <= NUM_COLS)) {
        while (i >= NUM_COLS && j >= NUM_ROWS && !obstaculo) {
            //Diferente color, la pieza puede matar a la otra

            if (m_board[pos.getX()][pos.getY()].getColor() != color) {
                newPos.setX(i);
                newPos.setY(j);
                VecPositions.push_back(newPos);
                obstaculo = false;
            }

            //Color igual, acabar el recorrido

            if (m_board[pos.getX()][pos.getY()].getColor() == color) {
                newPos.setX(i);
                newPos.setY(j);
                VecPositions.push_back(newPos);
                obstaculo = false;
            }
            else {
                newPos.setX(i);
                newPos.setY(j);
                VecPositions.push_back(newPos);
                i--;
                j--;
            }
        }
    }
    else {
        newPos.setX(i);
        newPos.setY(j);
        VecPositions.push_back(newPos);
        i--;
        j--;
        return VecPositions;
    }
}


