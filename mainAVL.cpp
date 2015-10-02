#include <iostream>

#include "AVL.h"

using namespace std;

int main(int argc, const char * argv[])
{
    AVL<int> * arbolAVL = new AVL<int>();
    
    arbolAVL->AVLinsert(10);
    arbolAVL->AVLinsert(5);
    arbolAVL->AVLinsert(20);
    arbolAVL->AVLinsert(30);

    int op = 0;
     while (op != 9)
            {
                std::cout<<"------------AVL------------"<<std::endl;
                std::cout<<"Eliga una opción:\n 1. Insertar\n 2. Borrar\n 3. Buscar\n 4. Imprimir ordenado asc\n 5. Imprimir ordenado desc\n 6. Obtener altura de un nodo\n 7. Obtener profundidad de un nodo\n 8. Obtener nivel del un nodo\n 9. Salir\n";
                std::cin>>op;
                
                switch (op)
                {
                    case 1:
                    {
                        int num;
                        std::cout<<"Número a insertar: ";
                        std::cin>>num;
                        arbolAVL->AVLinsert(num);
                    }
                        break;
                    case 2:
                    {
                        int num;
                        std::cout<<"Número a borrar: ";
                        std::cin>>num;
                        arbolAVL->remove(num);
                    }
                        break;
                    case 3:
                    {
                        int num;
                        std::cout<<"Número a buscar: ";
                        std::cin>>num;
                        if (arbolAVL->buscar(num))
                        {
                            std::cout<<"Si existe el número "<<*arbolAVL->buscar(num)<<" en el arbol.\n";
                        }
                        else
                        {
                            std::cout<<"No se encontró ese número. \n";
                        }
                    }
                        break;
                    case 4:
                    {
                        arbolAVL->inOrden();
                    }
                        break;
                    case 5:
                    {
                        arbolAVL->revOrden();
                    }
                        break;
                    case 6:
                    {
                        int num;
                        std::cout<<"Número: ";
                        std::cin>>num;
                        NodoB<int> * nodo = arbolAVL->buscar(num);
                        std::cout<<"Altura: "<<arbolAVL->getHeight(nodo)<<std::endl;
                    }
                        break;
                    case 7:
                    {
                        int num;
                        std::cout<<"Número: ";
                        std::cin>>num;
                        NodoB<int> * nodo = arbolAVL->buscar(num);
                        std::cout<<"Profundidad: "<<arbolAVL->getProfundidad(nodo)<<std::endl;
                    }
                        break;
                    case 8:
                    {
                        int num;
                        std::cout<<"Número: ";
                        std::cin>>num;
                        NodoB<int> * nodo = arbolAVL->buscar(num);
                        std::cout<<"Nivel: "<<arbolAVL->getNivel(nodo)<<std::endl;
                    }
                        break;
                    case 0:
                        op = 0;
                        break;
                    default:
                        break;
                }
            }

    return 0;
}
