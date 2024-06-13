#ifndef ChessPosition_hpp
#define ChessPosition_hpp

#include <stdio.h>
#include <string>
using namespace std;




class ChessPosition {

public:

    ChessPosition(){}
    ChessPosition(const string& s);

    ChessPosition(int x, int y) { m_posX = x; m_posY = y;}

    int getX() const {return m_posX;}
    int getY() const{return m_posY;}
    void setX(int x) {m_posX = x;}
    void setY(int y) {m_posY = y;}





    bool operator==(const ChessPosition& pos) const;



private:
    int m_posX{}; //Column
    int m_posY{}; //Row


};


#endif /* ChessPosition_hpp */
