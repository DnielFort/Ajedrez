#ifndef CurrentGame_hpp
#define CurrentGame_hpp
#include "QueueMovements.h"
#include <stdio.h>
#include <string>
#include "GameInfo.h"
#include "Chessboard.hpp"


using namespace std;



class CurrentGame {

public:
    CurrentGame();
    
    void            init(GameMode mode, const string& intitialBoardFile, const string& movementsFile);
	bool			updateAndRender(int mousePosX, int mousePosY, bool mouseStatus);
    void            end();  

    
    
    
private:
    Chessboard chessBoard;
    VecOfPositions casellesResaltar;
    ChessPieceColor m_torn;
    GameMode m_mode;
    QueueMovements m_moviments;
};

#endif /* CurrentGame_hpp */
