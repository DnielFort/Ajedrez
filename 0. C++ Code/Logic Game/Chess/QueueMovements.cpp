#include "QueueMovements.h"


Moviments::Moviments(int inicial_x, int inicial_y, int final_x, int final_y)
{
    ChessPosition AuxInicial(inicial_x, inicial_y);
    ChessPosition AuxFinal(final_x, final_y);
    m_inicialM = AuxInicial;
    m_finalM = AuxFinal;
}

void QueueMovements::insertarCola(Moviments*& frente, Moviments* &fin, Moviments& nou)
{
    Moviments* nuevo_movimiento = new Moviments();
    nuevo_movimiento->setInicial(nou.getInicial());
    nuevo_movimiento->setFinal(nou.getFinal());

    if (n_elements == 0)
    {
        frente = nuevo_movimiento;
    }
    else
    {
        fin->setSeg(nuevo_movimiento);
    }
    fin = nuevo_movimiento;
    n_elements++;
}

void QueueMovements::suprimirCola(Moviments* frente, Moviments* fin, Moviments& valor)
{
    valor.setInicial(frente->getInicial());
    valor.setFinal(frente->getFinal());

    Moviments* aux = frente;

    if (frente == fin)
    {
        frente = nullptr;
        fin = nullptr;
    }
    else
    {
        frente->setSeg(frente->getSeg());
    }
    delete aux;
    n_elements--;
}