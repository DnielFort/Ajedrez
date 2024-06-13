#include "Piece.hpp"
#include <string>
#include <iostream>
using namespace std;
#include "CurrentGame.hpp"
#include <fstream>

#include "GameInfo.h"
#include "../GraphicManager.h"
/// <summary>
/// Devuelve char corresponiente al tipo de la pieza
/// </summary>
/// <returns></returns>
char Piece::typeToChar()
{
	ChessPieceType t = m_type;
	switch (t)
	{
	case CPT_King:
		return 'R';
		break;
	case CPT_Queen:
		return 'D';
		break;
	case CPT_Rook:
		return'T';
		break;
	case CPT_Bishop:
		return 'A';
		break;
	case CPT_Knight:
		return 'C';
		break;
	case CPT_Pawn:
		return 'P';
		break;
	case CPT_EMPTY:
		return 'E';
		break;
	default:
		return ' ';
	}

}

void Piece::render(int posX, int posY)
{

	if (m_color == CPC_Black)
	{
		switch (m_type)
		{
		case CPT_King:
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_KING_BLACK, posX, posY);
			break;
		case CPT_Queen:
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_QUEEN_BLACK, posX, posY);
			break;
		case CPT_Bishop:
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_BISHOP_BLACK, posX, posY);
			break;
		case CPT_Knight:
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_KNIGHT_BLACK, posX, posY);
			break;
		case CPT_Rook:
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_ROOK_BLACK, posX, posY);
			break;
		case CPT_Pawn:
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_PAWN_BLACK, posX, posY);
			break;
		}
	}
	else if (m_color == CPC_White)
	{
		switch (m_type)
		{
		case CPT_King:
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_KING_WHITE, posX, posY);
			break;
		case CPT_Queen:
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_QUEEN_WHITE, posX, posY);
			break;
		case CPT_Bishop:
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_BISHOP_WHITE, posX, posY);
			break;
		case CPT_Knight:
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_KNIGHT_WHITE, posX, posY);
			break;
		case CPT_Rook:
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_ROOK_WHITE, posX, posY);
			break;
		case CPT_Pawn:
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_PAWN_WHITE, posX, posY);
			break;
		}
	}
}