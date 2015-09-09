//
//  Rojinegro.h
//  ProblemaPractico1
//
//  Created by iCaty on 9/8/15.
//  Copyright (c) 2015 Catalina Peralta. All rights reserved.
//

#ifndef ProblemaPractico1_Rojinegro_h
#define ProblemaPractico1_Rojinegro_h

#include "ArbolBinarioBusqueda.h"
#include <assert.h>
#include <iomanip>

template<class T>
class Rojinegro : public ArbolBinarioBusqueda<T>
{
public:
    Rojinegro();
    
    NodoB<T> * grandparent(NodoB<T> * nodo);
    NodoB<T> * uncle(NodoB<T> * nodo);
    NodoB<T> * sibling(NodoB<T> * nodo);
    
    void verifyProperties(Rojinegro * arbol);
    void verifyProperty1(NodoB<T> * nodo);
    void verifyProperty2(NodoB<T> * nodo);
    void verifyProperty3(NodoB<T> * nodo);
    void verifyProperty4(NodoB<T> * nodo, int countBlack, int & blackPath);
    
    std::string color(NodoB<T> * nodo);
    
    void rotateLeft(Rojinegro * arbol, NodoB<T> * nodo);
    void rotateRight(Rojinegro * arbol, NodoB<T> * nodo);
    
    void RBinsert(T valor);
    void insertCase1(Rojinegro * arbol, NodoB<T> * nodo);
    void insertCase2(Rojinegro * arbol, NodoB<T> * nodo);
    void insertCase3(Rojinegro * arbol, NodoB<T> * nodo);
    void insertCase4(Rojinegro * arbol, NodoB<T> * nodo);
    void insertCase5(Rojinegro * arbol, NodoB<T> * nodo);
    
    void RBdelete(T valor);
    void deleteCase1(Rojinegro * arbol, NodoB<T> * nodo);
    void deleteCase2(Rojinegro * arbol, NodoB<T> * nodo);
    void deleteCase3(Rojinegro * arbol, NodoB<T> * nodo);
    void deleteCase4(Rojinegro * arbol, NodoB<T> * nodo);
    void deleteCase5(Rojinegro * arbol, NodoB<T> * nodo);
    
    void prettyPrint(NodoB<T>* p, int indent);
};

template<class T>
Rojinegro<T>::Rojinegro() : ArbolBinarioBusqueda<T>() {}

template<class T>
NodoB<T> * Rojinegro<T>::grandparent(NodoB<T> * nodo)
{
    if(nodo != nullptr && nodo->getPadre() != nullptr)
        return nodo->getPadre()->getPadre();
    else
        return nullptr;
}

template<class T>
NodoB<T> * Rojinegro<T>::uncle(NodoB<T> * nodo)
{
    NodoB<T> * abuelo = grandparent(nodo);
    
    if(abuelo == nullptr)
        return nullptr;
    else if(nodo->getPadre() == abuelo->getIzquierdo())
        return abuelo->getDerecho();
    else
        return abuelo->getIzquierdo();
}

template<class T>
NodoB<T> * Rojinegro<T>::sibling(NodoB<T> * nodo)
{
    if(nodo != nullptr && nodo->getPadre() != nullptr)
    {
        if(nodo == nodo->getPadre()->getIzquierdo())
            return nodo->getPadre()->getDerecho();
        else
            return nodo->getPadre()->getIzquierdo();
    }
}

template<class T>
void Rojinegro<T>::verifyProperties(Rojinegro * arbol)
{
    verifyProperty1(arbol->getRaiz());
    verifyProperty2(arbol->getRaiz());
    verifyProperty3(arbol->getRaiz());
//    verifyProperty4(arbol->getRaiz());
}

template<class T>
void Rojinegro<T>::verifyProperty1(NodoB<T> * nodo)
{
    if(nodo == nullptr)
        return;
    
    assert(nodo->getColor() == "negro" || nodo->getColor() == "rojo");
    
    verifyProperty1(nodo->getIzquierdo());
    verifyProperty1(nodo->getDerecho());
}

template<class T>
void Rojinegro<T>::verifyProperty2(NodoB<T> * nodo)
{
    assert(color(nodo) == "negro");
}

template<class T>
void Rojinegro<T>::verifyProperty3(NodoB<T> * nodo)
{
    if (nodo == nullptr)
        return;
    
    if (color(nodo) == "rojo")
    {
        assert(color(nodo->getIzquierdo()) == "negro");
        assert(color(nodo->getDerecho()) == "negro");
        assert(color(nodo->getPadre()) == "negro");
    }
    
    verifyProperty3(nodo->getIzquierdo());
    verifyProperty3(nodo->getDerecho());
}

/************************************NOT WORKING ******************************************/
template<class T>
void Rojinegro<T>::verifyProperty4(NodoB<T> * nodo, int countBlack, int & blackPath)
{
//    int blackPath = -1;
//    
//    if (color(nodo) == "negro")
//    {
//        countBlack++;
//    }
//    
//    if (nodo == nullptr)
//    {
//        return;
//    }
//    
//    verifyProperty4(nodo->getIzquierdo(),  countBlack, *blackPath);
//    verifyProperty4(nodo->getDerecho(), countBlack, *blackPath);
}

template<class T>
std::string Rojinegro<T>::color(NodoB<T> * nodo)
{
    if(nodo == nullptr)
        return "negro";
    else
        return nodo->getColor();
}

template<class T>
void Rojinegro<T>::rotateLeft(Rojinegro * arbol, NodoB<T> * nodo)
{
    NodoB<T> * temp = nodo->getDerecho();
    
    if(nodo->getPadre() == nullptr)
        arbol->setRaiz(temp);
    else if(nodo->getPadre()->getIzquierdo() == nodo)
        nodo->getPadre()->setIzquierdo(temp);
    else
        nodo->getPadre()->setDerecho(temp);

    if(temp != nullptr)
        temp->setPadre(nodo->getPadre());
    
    nodo->setDerecho(temp->getIzquierdo());
    
    if (temp->getIzquierdo() != nullptr)
    {
        temp->getIzquierdo()->setPadre(nodo);
    }
    temp->setIzquierdo(nodo);
    nodo->setPadre(temp);
}

template<class T>
void Rojinegro<T>::rotateRight(Rojinegro * arbol, NodoB<T> * nodo)
{
    NodoB<T> * temp = nodo->getIzquierdo();
    
    if(nodo->getPadre() == nullptr)
        arbol->setRaiz(temp);
    else if(nodo->getPadre()->getIzquierdo() == nodo)
        nodo->getPadre()->setIzquierdo(temp);
    else
        nodo->getPadre()->setDerecho(temp);
    
    if(temp != nullptr)
        temp->setPadre(nodo->getPadre());
    
    nodo->setIzquierdo(temp->getDerecho());
    if (temp->getDerecho() != nullptr)
    {
        nodo->getDerecho()->setPadre(nodo);
    }
    temp->setDerecho(nodo);
    nodo->setPadre(temp);
}

template<class T>
void Rojinegro<T>::RBinsert(T valor)
{
    NodoB<T> * nodo = this->insertar(valor);
    nodo->setColor("rojo");
    insertCase1(this, nodo);
    verifyProperties(this);
    
}

template<class T>
void Rojinegro<T>::insertCase1(Rojinegro * arbol, NodoB<T> * nodo)
{
    if(nodo->getPadre() == nullptr)
        nodo->setColor("negro");
    else
        insertCase2(this, nodo);
}

template<class T>
void Rojinegro<T>::insertCase2(Rojinegro * arbol, NodoB<T> * nodo)
{
    if(nodo->getPadre()->getColor() == "negro")
        return;
    else
        insertCase3(this, nodo);
}

template<class T>
void Rojinegro<T>::insertCase3(Rojinegro * arbol, NodoB<T> * nodo)
{
    if(color(uncle(nodo)) == "rojo")
    {
        nodo->getPadre()->setColor("negro");
        uncle(nodo)->setColor("negro");
        grandparent(nodo)->setColor("rojo");
        insertCase1(arbol, grandparent(nodo));
    }
    else
    {
        insertCase4(arbol, nodo);
    }
}

template<class T>
void Rojinegro<T>::insertCase4(Rojinegro * arbol, NodoB<T> * nodo)
{
    if(nodo == nodo->getPadre()->getDerecho() && nodo->getPadre() == grandparent(nodo)->getIzquierdo())
    {
        rotateLeft(arbol, nodo->getPadre());
        nodo = nodo->getIzquierdo();
    }
    else if(nodo == nodo->getPadre()->getIzquierdo() && nodo->getPadre() == grandparent(nodo)->getDerecho())
    {
        rotateRight(arbol, nodo->getPadre());
        nodo = nodo->getDerecho();
    }
    insertCase5(arbol, nodo);
}

template<class T>
void Rojinegro<T>::insertCase5(Rojinegro * arbol, NodoB<T> * nodo)
{
    nodo->getPadre()->setColor("negro");
    grandparent(nodo)->setColor("rojo");
    if (nodo == nodo->getPadre()->getIzquierdo() && nodo->getPadre() == grandparent(nodo)->getIzquierdo())
    {
        rotateRight(arbol, grandparent(nodo));
    }
    else
    {
        assert(nodo == nodo->getPadre()->getDerecho() && nodo->getPadre() == grandparent(nodo)->getDerecho());
        rotateLeft(arbol, grandparent(nodo));
    }
}

template <class T>
void Rojinegro<T>::prettyPrint(NodoB<T>* p, int indent)
{
    if (p != nullptr) {
        if (p->getDerecho()) {
            prettyPrint(p->getDerecho(), indent + 4);
        }
        if (indent) {
            std::cout << std::setw(indent) << ' ';
        }
        if (p->getDerecho()) std::cout << " /\n" << std::setw(indent) << ' ';
        std::cout << p->getInfo() << "|" << p->getColor() << "\n ";
        if (p->getIzquierdo()) {
            std::cout << std::setw(indent) << ' ' << " \\\n";
            prettyPrint(p->getIzquierdo(), indent + 4);
        }
    }
}

#endif
