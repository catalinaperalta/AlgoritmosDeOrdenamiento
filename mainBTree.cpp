#include <iostream>
#include "BTree.h"
#include <ctime>

int main() 
{
	BTree<int> * arbol = new BTree<int>(2);

	srand((int) time(NULL));

    for(int i = 0; i < 10; i++)
    {
        arbol->insert(rand()%1000);
    }

    int op = 0;
    while (op != 6)
            {
                std::cout<<"------------B-Tree------------"<<std::endl;
                std::cout<<"Eliga una opción:\n 1. Insertar\n 2. Borrar\n 3. Buscar\n 4. Imprimir ordenado asc\n 5. Imprimir ordenado desc\n 6. Salir\n";
                std::cin>>op;
                
                switch (op)
                {
                    case 1:
                    {
                        int num;
                        std::cout<<"Número a insertar: ";
                        std::cin>>num;
                        arbol->insert(num);
                    }
                        break;
                    case 2:
                    {
                        int num;
                        std::cout<<"Número a borrar: ";
                        std::cin>>num;
                        arbol->eliminate(num);
                    }
                        break;
                    case 3:
                    {
                        int num;
                        std::cout<<"Número a buscar: ";
                        std::cin>>num;
                        if (arbol->search(num))
                        {
                            std::cout<<"Si existe el número "<< num <<" en el arbol.\n";
                        }
                        else
                        {
                            std::cout<<"No se encontró ese número. \n";
                        }
                    }
                        break;
                    case 4:
                    {
                        std::cout << std::endl;
                        arbol->printDesc();
                    }
                        break;
                    case 5:
                    {
                        std::cout << std::endl;
                        arbol->printAsc();
                    }
                        break;
                    case 0:
                        op = 0;
                        break;
                    default:
                        break;
                }
            }
}
