//
//  ArbolBinarioBusqueda.h
//  ProblemaPractico1
//
//  Created by iCaty on 9/6/15.
//  Copyright (c) 2015 Catalina Peralta. All rights reserved.
//

#ifndef ProblemaPractico1_ArbolBinarioBusqueda_h
#define ProblemaPractico1_ArbolBinarioBusqueda_h

#include <iostream>

#include "ArbolBinario.h"

template<class T>
class ArbolBinarioBusqueda : public ArbolBinario<T>
{
public:
    ArbolBinarioBusqueda();
    virtual NodoB<T>* insertar(T valor);
    NodoB<T> * removeNodo(NodoB<T> * nodo, T valor);
    
    NodoB<T> * minNodo(NodoB<T> * nodo)
    {
        NodoB<T> * actual = nodo;
        
        while (actual->getIzquierdo() != nullptr)
            actual = actual->getIzquierdo();
        
        return actual;
    }
    
    void print();
};

template<class T>
ArbolBinarioBusqueda<T>::ArbolBinarioBusqueda() : ArbolBinario<T>()
{
    
}

template<class T>
NodoB<T>* ArbolBinarioBusqueda<T>::insertar(T valor)
{
    NodoB<T> * nodo = new NodoB<T>(valor);
    NodoB<T> * padre;
    
    nodo->setDerecho(nullptr);
    nodo->setIzquierdo(nullptr);
    
    padre = nodo->getPadre();
    
    if(this->empty())
    {
        //NodoB<T> * raiz = this->getRaiz();
        this->setRaiz(nodo);
    }
    else
    {
        NodoB<T> * actual = new NodoB<T>();
        
        actual = this->getRaiz();
        
        while (actual)
        {
            padre = actual;
            
            if(nodo->getInfo() >= actual->getInfo())
            {
                actual = actual->getDerecho();
            }
            else
            {
                actual = actual->getIzquierdo();
            }
        }
        
        if(nodo->getInfo() >= padre->getInfo())
        {
            padre->setDerecho(nodo);
            nodo->setPadre(padre);
        }
        else
        {
            padre->setIzquierdo(nodo);
            nodo->setPadre(padre);
        }
    }
    return nodo;
    
    
}

template<class T>
void ArbolBinarioBusqueda<T>::print()
{
    std::cout<<*this;
}

#endif
