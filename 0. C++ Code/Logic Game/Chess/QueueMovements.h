#pragma once
#include "ChessPosition.hpp"
#define MAX_MOV 100

using namespace std;

class Moviments {
public:
    Moviments() {}
    Moviments(ChessPosition inici, ChessPosition final) { m_inicialM = inici; m_finalM = final; }
    Moviments(int inicial_x, int inicial_y, int final_x, int final_y);
    void setInicial(ChessPosition i) { m_inicialM = i; }
    ChessPosition getInicial() { return m_inicialM; }
    void setFinal(ChessPosition f) { m_finalM = f; }
    ChessPosition getFinal() { return m_finalM; }
    void setSeg(Moviments* ptr) { siguiente = ptr; }
    Moviments* getSeg() { return siguiente; }

private:
    ChessPosition m_inicialM;
    ChessPosition m_finalM;
    Moviments* siguiente = nullptr;

};


class QueueMovements {
public:
    void insertarCola(Moviments*& frente, Moviments*& fin, Moviments& nou);
    void suprimirCola(Moviments* frente, Moviments* fin, Moviments& nou);


    void setFinal(Moviments* pFinal) { m_final = pFinal; }
    Moviments* getFinal() { return m_final; }
    void setInici(Moviments* pInicial) { m_inicial = m_inicial; }
    Moviments* getInici() { return m_inicial; }
    int getNElements() { return n_elements; }
    int setNElements(int n) { n_elements = n; }

    Moviments* m_inicial = nullptr;
    Moviments* m_final = nullptr;
private:

    int n_elements = 0;
};