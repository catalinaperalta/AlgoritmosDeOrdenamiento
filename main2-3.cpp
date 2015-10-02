#include "TwoThreeTree.h"
#include <chrono>

int main ()
{
    TwoThreeTree<int> * dosTres = new TwoThreeTree<int>();

    int numeros[100000];
    int busqueda[10];

    srand((int) time(NULL));

    for(int i=0;i<10;i++)
    {
        numeros[i] = i;
    }

    for(int i=0;i<10;i++)
    {
        busqueda[i] = numeros[i];
    }

    for(int i=0; i<10; i++)
    {
        dosTres->insert23(numeros[i]);
    }

    int op = 0;
    while (op != 6)
            {
                std::cout<<"------------2-3------------"<<std::endl;
                std::cout<<"Eliga una opción:\n 1. Insertar\n 2. Borrar\n 3. Buscar\n 4. Imprimir ordenado asc\n 5. Imprimir ordenado desc\n 6. Salir\n";
                std::cin>>op;
                
                switch (op)
                {
                    case 1:
                    {
                        int num;
                        std::cout<<"Número a insertar: ";
                        std::cin>>num;
                        dosTres->insert23(num);
                    }
                        break;
                    case 2:
                    {
                        int num;
                        std::cout<<"Número a borrar: ";
                        std::cin>>num;
                        dosTres->deleteNode(num);
                    }
                        break;
                    case 3:
                    {
                        int num;
                        std::cout<<"Número a buscar: ";
                        std::cin>>num;
                        if (dosTres->searchNode(num,dosTres->getRoot()))
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
                        dosTres->printDesc(dosTres->getRoot());
                    }
                        break;
                    case 5:
                    {
                        std::cout << std::endl;
                        dosTres->printAsc();
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
