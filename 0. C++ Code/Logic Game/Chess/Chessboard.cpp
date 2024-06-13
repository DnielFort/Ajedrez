#include "Chessboard.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

/// <summary>
/// Devuelve la posición las letras (a-h) en el alfabeto
/// Si se pasa cualquier otra letra devuelve 0
/// </summary>
/// <param name="c"></param>
/// <returns></returns>
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
void Chessboard::LoadBoardFromFile(const string &path) {
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
            if (color == 0)
            {
                n_blanques++;
            }
            else if (color == 1)
            {
                n_negres++;
            }
            cout << endl;
            cout << "guardando color:" << color << ",    Guardando tipo: " << tipus << ",    Guardando en la columna: " << columna << ",   Guardando en la fila: " << fila << endl;
            intcolumna = charToInt(columna);
            m_board[intcolumna - 1][fila - 1].setColor(intToColor(color));
            m_board[intcolumna - 1][fila - 1].setType(charToType(tipus));
            fitxer >> color >> point >> tipus >> columna >> fila;
        }
        cout << endl;
        cout << "guardando color:" << color << " Guardando tipo: " << tipus << "  Guardando en la columna: " << charToInt(columna)-1 << " Guardando en la fila: " << fila << endl;
        intcolumna = charToInt(columna);
        if (color == 0)
        {
            n_blanques++;
        }
        else if (color == 1)
        {
            n_negres++;
        }
        m_board[intcolumna - 1][fila - 1].setColor(intToColor(color));
        m_board[intcolumna - 1][fila - 1].setType(charToType(tipus));
        fitxer.close();
    }
}


/// <summary>
/// Elimina una pieza del tablero
/// </summary>
/// <param name="pos">La elimina pasando su m_type a CPT_EMPTY y su m_color a CPC_NONE</param>
void Chessboard::matar(const ChessPosition &pos) 
{
    m_board[pos.getX()][pos.getY()].setColor(CPC_NONE);
    m_board[pos.getX()][pos.getY()].setType(CPT_EMPTY);
}


/// <summary>
/// Mueve pieza de una posición a otra.
/// </summary>
/// <param name="posFrom"></param>
/// <param name="posTo"></param>
/// <returns></returns>
bool Chessboard::MovePiece(const ChessPosition &posFrom, const ChessPosition &posTo, Chessboard cb) {
    VecOfPositions validMoves = GetValidMoves(posFrom, cb);

    //Buscar si posTo es un movimiento válido.
    if (find(validMoves.begin(), validMoves.end(), posTo) != validMoves.end()) {
        //Es movimiento válido
        m_board[posFrom.getX()][posFrom.getY()].setMoved(true);

        //Regula el marcador
        if (m_board[posFrom.getX()][posFrom.getY()].getColor() == m_board[posTo.getX()][posTo.getY()].colorContrari())
        {
            //mira que no hayan matado al rei
            if (m_board[posTo.getX()][posTo.getY()].getType() == CPT_King)
            {
                reiMort = true;
                if (m_board[posTo.getX()][posTo.getY()].getColor() == CPC_White)
                {
                    n_blanques = 0;
                    
                }
                else
                    n_negres= 0;
            }

            else if (m_board[posTo.getX()][posTo.getY()].getColor() == CPC_White)
            {
                n_blanques--;
            }
            else if (m_board[posTo.getX()][posTo.getY()].getColor() == CPC_Black)
                n_negres--;
        }
        //Buscar si hay alguna pieza en esa posición
        if (m_board[posTo.getX()][posTo.getY()].getType() != CPC_NONE) {
            //Si hay pieza la mata
            matar(posTo);
        }
        //Se mueve a la posición
        m_board[posTo.getX()][posTo.getY()].setType(m_board[posFrom.getX()][posFrom.getY()].getType());
        m_board[posTo.getX()][posTo.getY()].setColor(m_board[posFrom.getX()][posFrom.getY()].getColor());
        m_board[posTo.getX()][posTo.getY()].setMoved(m_board[posFrom.getX()][posFrom.getY()].getMoved());
        //Libera la posición posFrom
        
        matar(posFrom);
        return true;
    } else {
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
    } else
        return "\nError, colorToString no ha recibido un valor valido";
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
        return "K";
    else if (t == CPT_Pawn)
        return "P";
    else
        return "\nError, typeToString no ha recibido un valor valido";
}


/// <summary>
/// Comprueba que la posición no se salga del tablero y que en la posición no se encuentre
/// una pieza del mismo color
/// </summary>
/// <param name="p">posicion que se mira</param>
/// <returns>return true si no se puede mover a esa posicion</returns>
bool Chessboard::posProhibida(int x, int y, ChessPieceColor c, Chessboard cb)const
{
    bool prohibido = false;

    ChessPieceColor posColor = cb.m_board[x][y].getColor();

    //Mirar que no se salga del tablero
    if (y < 0 || x > 7 || x < 0 || y > 7)
    {
        prohibido = true;
    }
    else if (posColor == c)
    {
        prohibido = true;

    }
    return prohibido;
}


string Chessboard::ToString() const {
    string arrayS[9][9];
    //añade los números de las filas
    int c =1;
    for (int i = 0; i < 9; i++)
    {
        arrayS[i][0] = to_string(c) + " ";
        c++;
    }
    //añade las letras de las columnas
    arrayS[8][0] = "  ";
    for (int i = 1; i < 9; i++)
    {
        arrayS[8][i] = " " + intToString(i) + " ";
    }

    //añade las piezas en el tablero
    for (int i = 0; i < 8; i++)
    {
        for (int j = 1; j < 9; j++)
        {
            //comprueba si la posición está vacía
            if (m_board[i][j-1].getColor() == CPC_NONE)
            {
                //Si vacía
                arrayS[i][j] = "__ ";
            }
            else
            {
                //no vacía
                arrayS[i][j] = colorToString(m_board[i][j - 1].getColor()) + typeToString(m_board[i][j - 1].getType()) + " ";
            }
        }
    }

    //El tablero array a un solo string;
    string stringReturn = "";
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            stringReturn += arrayS[i][j];
            if (j == 8)
            {
                stringReturn += "\n";
            }
        }
    }
    return stringReturn;



}



VecOfPositions Chessboard::GetValidMoves(ChessPosition pos, Chessboard cb) const
{
//DESCRIPCIÓN:
//Calcula las posiciones a las que se puede mover una pieza en base a la posición inicial

//PARAMETROS:
//La posición inicial de la pieza

//RETURN:
//Retorna el conjunto de las posiciones a las cuales se puede mover la pieza

    VecOfPositions vector;

    //miramos que pieza hay en esa posicion
    Piece actual = m_board[pos.getX()][pos.getY()];
    ChessPieceColor c = actual.getColor();
    int posX = pos.getX();
    int posY = pos.getY();

    Chessboard aux;

    switch (actual.typeToChar()) {
        //Rey
        case 'R': //check
        {
            cout << "La posicin introducida en GetValidMoves contena un rey " << endl;
            //esquina superior derecha
            if (!posProhibida(posX + 1, posY + 1, actual.getColor(), cb))
            {
                vector.push_back(ChessPosition(posX + 1, posY + 1));
            }
            //derecha
            if (!posProhibida(posX + 1, posY, actual.getColor(), cb))
            {
                vector.push_back(ChessPosition(posX + 1, posY));
            }
            //esquina inferior derecha
            if (!posProhibida(posX + 1, posY - 1, actual.getColor(), cb))
            {
                vector.push_back(ChessPosition(posX + 1, posY - 1));
            }
            //abajo
            if (!posProhibida(posX, posY - 1, actual.getColor(), cb))
            {
                vector.push_back(ChessPosition(posX, posY - 1));
            }
            //esquina inferior izquierda
             if (!posProhibida(posX - 1, posY - 1, actual.getColor(), cb))
            {
                vector.push_back(ChessPosition(posX - 1, posY - 1));
            }
            //izquierda
             if (!posProhibida(posX - 1, posY, actual.getColor(), cb))
            {
                vector.push_back(ChessPosition(posX - 1, posY));
            }
            //esquina superior izquierda
             if (!posProhibida(posX - 1, posY + 1, actual.getColor(), cb))
            {
                vector.push_back(ChessPosition(posX - 1, posY + 1));
            }
            //arriba
             if (!posProhibida(posX, posY + 1, actual.getColor(), cb))
            {
                vector.push_back(ChessPosition(posX, posY + 1));
            }
        }
            break;

        //dama
        case 'D': //check
        
            cout << "La posición introducida en GetValidMoves contenía una dama" << endl;
            aux.vertical(posX, posY, vector, c,  cb);
            aux.horizontal(posX, posY, vector, c, cb);
            aux.diagonal(posX, posY, vector, c, cb);
            break;

            //posición Torre

        case 'T': //check
            cout << "La posición introducida en GetValidMoves contenía una torre" << endl;
            aux.vertical(posX, posY, vector, c, cb);
            aux.horizontal(posX, posY, vector, c, cb);

            break;
            //posición Alfil
        case 'A': //check
            cout << "La posición introducida en GetValidMoves contenía un alfil " << endl;
            aux.diagonal(posX, posY, vector, c, cb);

            break;

            //posición Caballo
        case 'C': //check
            cout << "La posición introducida en GetValidMoves contenía un cavallo " << endl;
        {
            //esquina superior derecha 1
            if (!posProhibida(posX + 1, posY + 2, actual.getColor(), cb))
            {
                vector.push_back(ChessPosition(posX + 1, posY + 2));
            }
            //esquina superior derecha 2
             if (!posProhibida(posX + 2, posY + 1, actual.getColor(), cb))
            {
                vector.push_back(ChessPosition(posX + 2, posY + 1));
            }
            //esquina inferior derecha 1
             if (!posProhibida(posX + 2, posY - 1, actual.getColor(), cb))
            {
                vector.push_back(ChessPosition(posX + 2, posY - 1));
            }
            //esquina inferior derecha 2
             if (!posProhibida(posX + 1, posY - 2, actual.getColor(), cb))
            {
                vector.push_back(ChessPosition(posX + 1, posY - 2));
            }
            //esquina inferior izquierda 1
             if (!posProhibida(posX - 2, posY - 1, actual.getColor(), cb))
            {
                vector.push_back(ChessPosition(posX - 2, posY - 1));
            }
            //esquina inferior izquierda 2
             if (!posProhibida(posX - 1, posY - 2, actual.getColor(), cb))
            {
                vector.push_back(ChessPosition(posX - 1, posY - 2));
            }
            //esquina superior izquierda1
             if (!posProhibida(posX - 2, posY + 1, actual.getColor(), cb))
            {
                vector.push_back(ChessPosition(posX - 2, posY + 1));
            }
            //esquina superior izquierda2
             if (!posProhibida(posX-1, posY + 2, actual.getColor(), cb))
            {
                vector.push_back(ChessPosition(posX - 1, posY + 2));
            }
    }
            break;

            //posición Peón
        case 'P':
            //blancas suman, negras restan
            cout << "La posición introducida en GetValidMoves contenía un peon" << endl;
                if (c == CPC_White)
            {
                if ((!posProhibida(posX, posY + 1, actual.getColor(), cb))&& cb.m_board[posX][posY + 1].colorContrari()!=c)
                {
                    vector.push_back(ChessPosition(posX , posY + 1));
                }
                if ((!posProhibida(posX, posY + 2, actual.getColor(), cb)) && !actual.getMoved() && cb.m_board[posX][posY + 2].colorContrari() != c)
                {
                    vector.push_back(ChessPosition(posX, posY + 2));
                }
                if ((!posProhibida(posX + 1, posY + 1, actual.getColor(), cb) && cb.m_board[posX + 1][posY + 1].colorContrari() == c))
                {
                    vector.push_back(ChessPosition(posX + 1, posY + 1));
                }
                if ((!posProhibida(posX - 1, posY + 1, actual.getColor(), cb) && cb.m_board[posX - 1][posY + 1].colorContrari() == c))
                {
                    vector.push_back(ChessPosition(posX - 1, posY + 1));
                }

            }
                else if (c == CPC_Black)
                {
                    if (!posProhibida(posX , posY - 1, actual.getColor(), cb) && cb.m_board[posX][posY - 1].colorContrari() != c)
                    {
                        vector.push_back(ChessPosition(posX , posY - 1));
                    }
                    if (!posProhibida(posX, posY - 2, actual.getColor(), cb) && !actual.getMoved() && cb.m_board[posX][posY - 2].colorContrari() != c)
                    {
                        vector.push_back(ChessPosition(posX, posY - 2));
                    }
                    if ((!posProhibida(posX + 1, posY - 1, actual.getColor(), cb) && cb.m_board[posX + 1][posY - 1].colorContrari() == c))
                    {
                        vector.push_back(ChessPosition(posX + 1, posY - 1));
                    }
                    if ((!posProhibida(posX - 1, posY - 1, actual.getColor(), cb) && cb.m_board[posX - 1][posY - 1].colorContrari() == c))
                    {
                        vector.push_back(ChessPosition(posX - 1, posY - 1));
                    }
                }

            break;
        default:
            cout << "La posición introducida en GetValidMoves no contenía ninguna pieza" << endl;
            break;
    }


    //cout de las posiciones para ver que todo funciona
    cout << "\n";
    cout << "La pieza es: " << actual.getType();
    cout << "Las posiciones a las que se puede mover son:" << endl;

    for (auto i = vector.begin(); i != vector.end(); i++)
        cout << "x: " << (*i).getX() << ' ' <<"Y: " << (*i).getY()<< "           ,";
    cout << "\n";
    cout << "\n";
    cout << "\n";
    cout << "\n";

    return vector;
}


void Chessboard::horizontal(int x, int y, VecOfPositions& vector, ChessPieceColor c, Chessboard cb)
{
    //horizontal derecha
    int auxX = x;
    int auxY = y+1;
    bool matar = false;
    while (!posProhibida(auxX, auxY, c, cb) && !matar)
    {
        vector.push_back(ChessPosition(auxX, auxY));

        if (cb.m_board[auxX][auxY].colorContrari() == c)
        {
            matar = true;
        }
        auxY++;
        
    }

    //horizontal inzq
    matar = false;
    auxY = y - 1;
    while (!posProhibida(auxX, auxY, c, cb) && !matar)
    {
        vector.push_back(ChessPosition(auxX, auxY));
        if (cb.m_board[auxX][auxY].colorContrari() == c)
        {
            matar = true;
        }
        auxY--;
        
    }
}

void Chessboard::vertical(int x, int y, VecOfPositions& vector, ChessPieceColor c, Chessboard cb)
{
    //vertical sup
    int auxX = x+1;
    int auxY = y;
    bool matar = false;
    while (!posProhibida(auxX, auxY, c, cb) && !matar)
    {
        vector.push_back(ChessPosition(auxX, auxY));
        if (cb.m_board[auxX][auxY].colorContrari() == c)
        {
            matar = true;
        }
        auxX++;
        
    }

    //vertical inf
    auxX = x-1;
    auxY = y;
    matar = false;
    while (!posProhibida(auxX, auxY, c, cb) && !matar)
    {
        vector.push_back(ChessPosition(auxX, auxY));
        if (cb.m_board[auxX][auxY].colorContrari() == c)
        {
            matar = true;
        }
        auxX--;
        
    }
}

void Chessboard::diagonal(int x, int y, VecOfPositions& vector, ChessPieceColor c, Chessboard cb)
{
    //diagonal superior derecha
    int auxX = x + 1;
    int auxY = y + 1;
    bool matar = false;

    while (!posProhibida(auxX, auxY, c, cb) && !matar )
    {
        vector.push_back(ChessPosition(auxX, auxY));
        if (cb.m_board[auxX][auxY].colorContrari() == c)
        {
            matar = true;
        }
        auxX++;
        auxY++;

       

    }

    //diagonal inferior derecha
    auxX = x + 1;
    auxY = y - 1;
    matar = false;
    while (!posProhibida(auxX, auxY, c, cb) && !matar)
    {
        vector.push_back(ChessPosition(auxX, auxY));
        if (cb.m_board[auxX][auxY].colorContrari() == c)
        {
            matar = true;
        }
        auxX++;
        auxY--;
        
    }

    //diagonal inferior izquierda
     auxX = x - 1;
     auxY = y - 1;
     matar = false;
    while (!posProhibida(auxX, auxY, c, cb) && !matar)
    {
        vector.push_back(ChessPosition(auxX, auxY));
        if (cb.m_board[auxX][auxY].colorContrari() == c)
        {
            matar = true;
        }
        auxX--;
        auxY--;
       
    }
    //diagonal superior izquierda
    auxX = x - 1;
    auxY = y + 1;
    matar = false;
    while (!posProhibida(auxX, auxY, c, cb) && !matar)
    {
        vector.push_back(ChessPosition(auxX, auxY));
        if (cb.m_board[auxX][auxY].colorContrari() == c)
        {
            matar = true;
        }
        auxX--;
        auxY++;
       
    }

}

void Chessboard::displayPices()
{
    for (int posX = 0; posX < NUM_COLS; posX++)
    {
        for (int posY = 0; posY < NUM_COLS; posY++)
        {
            m_board[posX][posY].render(CELL_INIT_X + (posX * CELL_W), CELL_INIT_X + (posY * CELL_H));
        }
    }
}
