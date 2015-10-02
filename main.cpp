#include <iostream>
#include <iterator>
#include <cstring>
#include <chrono>
#include "TwoThreeTree.h"
#include "Rojinegro.h"
#include "BTree.h"
#include "AVL.h"

int main()
{
	TwoThreeTree<int> * dosTres = new TwoThreeTree<int>();
    Rojinegro<int> * rojiNegro = new Rojinegro<int>();
    BTree<int> * bTree = new BTree<int>(3);
    AVL<int> * arbolAVL = new AVL<int>();

	srand((int) time(NULL));

    int numeros[100000];
    int busqueda[10];

    for(int i=0;i<100000;i++)
    {
        numeros[i] = rand()%100000;
    }

    for(int i=0;i<10;i++)
    {
        busqueda[i] = numeros[i];
    }

    for(int i=0; i<100000; i++)
    {
        dosTres->insert23(numeros[i]);
    }

    for(int i = 0; i < 10; i++)
    {
        bool found = false;
        auto begin = std::chrono::high_resolution_clock::now();
        found = dosTres->searchNode(busqueda[i],dosTres->getRoot());
        auto end = std::chrono::high_resolution_clock::now();

        if (found)
        {
            std::cout << "El valor: " << busqueda[i] << " se encuentra en el árbol" << std::endl;
            auto tiempo = std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin);
            std::cout << "Le tomo: " << tiempo.count() << " nano segundos encontrarlo en el arbol 2-3" << std::endl;
        }
    }

    std::cout << std::endl;

    for(int i=0; i<100000;i++)
    {
        rojiNegro->RBinsert(numeros[i]);
    }

    for(int i = 0; i<10; i++)
    {
        bool found = false;
        auto begin = std::chrono::high_resolution_clock::now();
        found = rojiNegro->buscar(busqueda[i]);
        auto end = std::chrono::high_resolution_clock::now();

        if (found)
        {
            std::cout << "El valor: " << busqueda[i] << " se encuentra en el árbol" << std::endl;
            auto tiempo = std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin);
            std::cout << "Le tomo: " << tiempo.count() << " nano segundos encontrarlo en el arbol rojinegro" << std::endl;
        }
    }

    std::cout << std::endl;

    for(int i=0; i<100000; i++)
    {
        bTree->insert(numeros[i]);
    }

    for(int i = 0; i<10; i++)
    {
        bool found = false;
        auto begin = std::chrono::high_resolution_clock::now();
        found = bTree->search(busqueda[i]);
        auto end = std::chrono::high_resolution_clock::now();

        if (found)
        {
            std::cout << "El valor: " << busqueda[i] << " se encuentra en el árbol" << std::endl;
            auto tiempo = std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin);
            std::cout << "Le tomo: " << tiempo.count() << " nano segundos encontrarlo en el B Tree" << std::endl;
        }
    }

    std::cout << std::endl;

    for(int i=0; i<100000; i++)
    {
        arbolAVL->AVLinsert(numeros[i]);
    }

    for(int i = 0; i<10; i++)
    {
        bool found = false;
        auto begin = std::chrono::high_resolution_clock::now();
        found = arbolAVL->buscar(busqueda[i]);
        auto end = std::chrono::high_resolution_clock::now();

        if (found)
        {
            std::cout << "El valor: " << busqueda[i] << " se encuentra en el árbol" << std::endl;
            auto tiempo = std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin);
            std::cout << "Le tomo: " << tiempo.count() << " nano segundos encontrarlo en el arbo AVL" << std::endl;
        }
    }

    return 0;
}
