//
//  AVL.h
//  ProblemaPractico1
//
//  Created by iCaty on 9/6/15.
//  Copyright (c) 2015 Catalina Peralta. All rights reserved.
//

#ifndef ProblemaPractico1_AVL_h
#define ProblemaPractico1_AVL_h

#include "ArbolBinarioBusqueda.h"

template<class T>
class AVL : public ArbolBinarioBusqueda<T>
{
    
public:
    AVL(){}
    ~AVL();
    
    void rotateL(NodoB<T> * node);
    void rotateR(NodoB<T> * node);
    void rotateLR(NodoB<T> * node);
    void rotateRL(NodoB<T> * node);
    bool isAVL(NodoB<T> * node);
    void checkRotations(NodoB<T> * parent, NodoB<T> * node);
    void AVLinsert(T value);
    void remove(T value);
    
    NodoB<T> * getMaxMin(NodoB<T> * node);
    NodoB<T> * getMaxMin();
    
};

template <class T>
AVL<T>::~AVL()
{
    
}

template <class T>
bool AVL<T>::isAVL(NodoB<T> * node)
{
    
    if (node)
    {
        if (abs(this->getBalanceFactor(node)) > 1 )
        {
            return false;
        }
        return isAVL(node->getDerecho()) && isAVL(node->getIzquierdo());
    }
    else
    {
        return true;
    }
    
}

template <class T>
void AVL<T>::rotateR(NodoB<T> * pivot)
{
    NodoB<T> * temp = pivot->getIzquierdo();
    
    if(pivot->getPadre() && pivot->getInfo() <= pivot->getPadre()->getInfo())
    {
        pivot->getPadre()->setIzquierdo(temp);
    }
    else if(pivot->getPadre())
    {
        pivot->getPadre()->setDerecho(temp);
    }
    else
    {
        this->setRaiz(temp);
    }
    
    temp->setPadre(pivot->getPadre());
    pivot->setPadre(temp);
    
    pivot->setIzquierdo(temp->getDerecho());
    
    temp->setDerecho(pivot);
    
    if(pivot->getIzquierdo())
        pivot->getIzquierdo()->setPadre(pivot);
    
}

template <class T>
void AVL<T>::rotateL(NodoB<T> * pivot)
{
    
    NodoB<T> * temp = pivot->getDerecho();
    
    if(pivot->getPadre() && pivot->getInfo() <= pivot->getPadre()->getInfo())
    {
        pivot->getPadre()->setIzquierdo(temp);
    }
    else if (pivot->getPadre())
    {
        pivot->getPadre()->setDerecho(temp);
    }
    else
    {
        this->setRaiz(temp);
    }
    
    temp->setPadre(pivot->getPadre());
    pivot->setPadre(temp);
    
    pivot->setDerecho(temp->getIzquierdo());
    
    temp->setIzquierdo(pivot);
    
    if(pivot->getDerecho())
        pivot->getDerecho()->setPadre(pivot);
    
}

template <class T>
void AVL<T>::rotateLR(NodoB<T> * pivot)
{
    NodoB<T> * temp = pivot->getDerecho();
    rotateL(pivot);
    rotateR(temp->getPadre());
}

template <class T>
void AVL<T>::rotateRL(NodoB<T> * pivot)
{
    
    NodoB<T> * temp = pivot->getIzquierdo();
    rotateR(pivot);
    rotateL(temp->getPadre());
}

template <class T>
void AVL<T>::checkRotations(NodoB<T> * parent, NodoB<T> * node)
{
    
    if(this->getBalanceFactor(parent->getPadre()) == -2 && this->getBalanceFactor(parent->getPadre()->getIzquierdo())== -1)
    {
        rotateR(parent->getPadre());
    }
    if(this->getBalanceFactor(parent->getPadre()) == -2 && this->getBalanceFactor(parent->getPadre()->getIzquierdo())== 1)
    {
        rotateLR(parent);
    }
    if(this->getBalanceFactor(parent->getPadre()) == 2 && this->getBalanceFactor(parent->getPadre()->getDerecho())== 1)
    {
        rotateL(parent->getPadre());
    }
    if( (this->getBalanceFactor(parent->getPadre()) == 2 && this->getBalanceFactor(parent->getPadre()->getDerecho())== -1))
    {
        rotateRL(parent);
    }
    
}


template <class T>
void AVL<T>::AVLinsert(T value)
{
    NodoB<T> * nodo = this->insertar(value);
    checkRotations(this->getRaiz(), nodo);
}

template <class T>
void AVL<T>::remove(T value)
{
    NodoB<T> * node = this->buscar(value);
    
    if(node)
    {
        NodoB<T> * parent = node->getPadre();
        NodoB<T> * nodo = getMaxMin(node);
        
        if(nodo){
            nodo->setDerecho(node->getDerecho());
            if(nodo->getDerecho())
                nodo->getDerecho()->setPadre(nodo);
            nodo->getPadre()->setDerecho(nodo->getIzquierdo());
            nodo->setPadre(node->getPadre());
            
            if(node->getIzquierdo() == nodo)
            {
                if(!nodo->getIzquierdo())
                    nodo->setIzquierdo(nullptr);
            }
            else
            {
                nodo->setIzquierdo(node->getIzquierdo());
            }
            
        }
        
        if(!node->getPadre())
        {
            this->setRaiz(nodo);
        }
        else if(node->getInfo() <= node->getPadre()->getInfo())
        {
            node->getPadre()->setIzquierdo(nodo);
        }
        else
        {
            node->getPadre()->setDerecho(nodo);
        }
        
        
        delete node;
        
        
        if(this->getBalanceFactor(parent) == -2 && this->getBalanceFactor(parent->getIzquierdo()) == -1)
        {
            rotateR(parent);
        }
        if(this->getBalanceFactor(parent) == -2 && this->getBalanceFactor(parent->getIzquierdo())== 1)
        {
            rotateLR(parent->getIzquierdo());
        }
        if(this->getBalanceFactor(parent) == 2 && this->getBalanceFactor(parent->getDerecho())== 1)
        {
            rotateL(parent);
        }
        if( (this->getBalanceFactor(parent) == 2 && this->getBalanceFactor(parent->getDerecho())== -1))
        {
            rotateRL(parent->getDerecho());
        }
        parent =  parent->getPadre();
        
        
        if(this->getBalanceFactor(nodo) == -2 && this->getBalanceFactor(nodo->getIzquierdo()) == -1)
        {
            rotateR(nodo);
        }
        if(this->getBalanceFactor(nodo) == -2 && this->getBalanceFactor(nodo->getIzquierdo())== 1)
        {
            rotateLR(nodo->getIzquierdo());
        }
        if(this->getBalanceFactor(nodo) == 2 && this->getBalanceFactor(nodo->getDerecho())== 1)
        {
            rotateL(nodo);
        }
        if((this->getBalanceFactor(nodo) == 2 && this->getBalanceFactor(nodo->getDerecho())== -1))
        {
            rotateRL(nodo->getDerecho());
        }
        
    }
    
}

template <class T>
NodoB<T> * AVL<T>::getMaxMin()
{
    return getMaxMin(this->root);
}


template <class T>
NodoB<T> * AVL<T>::getMaxMin(NodoB<T> * node)
{
    if(node)
    {
        NodoB<T> * workingNode = node->getIzquierdo();
        if(workingNode)
        {
            while (workingNode->getDerecho() != nullptr)
            {
                workingNode = workingNode->getDerecho();
            }
            return workingNode;
        }
        return nullptr;
        
    }
    else
    {
        return nullptr;
    }
    
}

#endif
