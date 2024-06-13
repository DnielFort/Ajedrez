#include "ChessPosition.hpp"
#include "GameInfo.h"

using namespace std;

//DESCRIPCIÓN
//Métodos de la classe, constructor, getters, setters

//Constructor, recibe por paràmetro un string

ChessPosition::ChessPosition(const string& s) {}


//sobrecàrrega operador "="
//Compara si dos posiciones son iguales o no

bool ChessPosition::operator==(const ChessPosition& pos) const
{
    return ((m_posX == pos.m_posX) && (m_posY == pos.m_posY));
}
