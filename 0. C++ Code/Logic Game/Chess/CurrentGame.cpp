#include "GameInfo.h"
#include "../GraphicManager.h"
#include "ChessBoard.hpp"
#include "CurrentGame.hpp"

#include <iostream>

using namespace std;

CurrentGame::CurrentGame()
{


}


void CurrentGame::init(GameMode mode, const string& intitialBoardFile, const string& movementsFile)
{
    // Dibuixem el tauler, eliminem les fitxes a resaltar i asignem el 1r torn a les blanques;
    m_mode = mode;
    chessBoard.LoadBoardFromFile(intitialBoardFile);
    casellesResaltar.clear();
    m_torn = CPC_White;
}


void CurrentGame::end()
{

}

bool CurrentGame::updateAndRender(int mousePosX, int mousePosY, bool mouseStatus) 
{
    int posX = 4;
    int posY = 6;
    //Iniciar tablero:

    //Display tablero
    GraphicManager::getInstance()->drawSprite(IMAGE_BOARD, 0, 0);



    //Display tablero inicial
    chessBoard.displayPices();

    //Mostrar casillas a resaltar
    for (int i = 0; i < casellesResaltar.size(); i++)
        GraphicManager::getInstance()->drawSprite(IMAGE_VALID_POS, CELL_INIT_X + CELL_W * casellesResaltar.at(i).getX(), CELL_INIT_Y + CELL_H * casellesResaltar.at(i).getY());

    // Esperar a que haga click en el tablero
    posX = 0;
    bool trobat = false;
    while (posX < NUM_COLS && !trobat)
    {
        int  posY = 0;
        while (posY < NUM_ROWS && !trobat)
        {

            //click en el tablero
            if (mouseStatus && (CELL_INIT_X + CELL_W * posX < mousePosX) && (mousePosX < CELL_INIT_X + CELL_W * (posX + 1)) && (CELL_INIT_Y + CELL_H * posY < mousePosY) && (mousePosY < CELL_INIT_Y + CELL_H * (posY + 1)))
            {
                //mirar si es en una casilla resaltada
                int k = 0;
                bool moure = false;
                while (k < casellesResaltar.size() && !moure)
                {
                    if ((casellesResaltar.at(k).getX() == posX ) && (casellesResaltar.at(k).getY() == posY))
                        moure = true;

                    k++;
                }

                //si era en una casilla resaltada se mueve la pieza y se cambia de turno
                if (moure)
                {
                    ChessPosition toPos(posX, posY);
                    ChessPosition fromPos = chessBoard.getCasellaSeleccionada();
                    chessBoard.MovePiece(fromPos, toPos, chessBoard);

                    Moviments aux(fromPos, toPos);
                    m_moviments.insertarCola(m_moviments.m_inicial, m_moviments.m_final, aux);

                    casellesResaltar.clear();
                    if (m_torn == CPC_White)
                        m_torn = CPC_Black;
                    else
                        m_torn = CPC_White;
                }
                //si no era un casilla resaltada se mira si ha dado click en una pieza que tiene turno
                else
                {
                    ChessPosition pos(posX, posY);
                    //si es en una pieza con turno se resaltan los posibles movimientos
                    if (chessBoard.m_board[posX][posY].getColor() == m_torn)
                    {
                        chessBoard.setCasellaSeleccionada(pos);
                        casellesResaltar = chessBoard.GetValidMoves(chessBoard.getCasellaSeleccionada(), chessBoard);
                    }

                }

                trobat = true;
            }
            posY++;
        }
        posX++;
    }

    if (chessBoard.getNBlanques() == 0 || chessBoard.getNNegres() == 0)
    {
        string guanyador = "";
        if (chessBoard.getNBlanques() == 0)
            guanyador = "NEGRES";
        else
            guanyador = "BLANQUES";
        int posResultatX = 40;
        int posResultatY = 150;
        std::string msg_resultat = "GUANYEN LES\n   " + guanyador;
        GraphicManager::getInstance()->drawFont(FONT_GREEN_30, posResultatX, posResultatY, 3, msg_resultat);
    }
    else
    {
        int posTornX = CELL_INIT_X;
        int posTornY = CELL_INIT_Y + (CELL_H * NUM_ROWS) + 60;
        std::string msg_torn = "Tenen el torn les peces " + chessBoard.colorToString(m_torn) + ".";
        GraphicManager::getInstance()->drawFont(FONT_RED_30, posTornX, posTornY, 0.8, msg_torn);

        int posMarcadorBX = 600;
        int posMarcadorBY = 20;
        std::string msg_marcadorB = "N.Blanques: \n" + to_string(chessBoard.getNBlanques());
        GraphicManager::getInstance()->drawFont(FONT_RED_30, posMarcadorBX, posMarcadorBY, 0.8, msg_marcadorB);

        int posMarcadorNX = 600;
        int posMarcadorNY = 400;
        std::string msg_marcadorN = "N.Negres: \n" + to_string(chessBoard.getNNegres());
        GraphicManager::getInstance()->drawFont(FONT_RED_30, posMarcadorNX, posMarcadorNY, 0.8, msg_marcadorN);
    }
    


    return false;

}

