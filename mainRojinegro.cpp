#include <iostream>
#include "Rojinegro.h"

using namespace std;

int main(int argc, const char * argv[])
{
    Rojinegro<int> * rojiNegro = new Rojinegro<int>();

    rojiNegro->RBinsert(100);
    rojiNegro->RBinsert(49);
    rojiNegro->RBinsert(23);
    rojiNegro->RBinsert(1);
    rojiNegro->RBinsert(2);
    rojiNegro->RBinsert(34);
    
    rojiNegro->RBinsert(2);
    rojiNegro->RBinsert(23);
    rojiNegro->RBinsert(55);
    rojiNegro->RBinsert(36);
    rojiNegro->RBinsert(17);
    rojiNegro->RBinsert(28);
    rojiNegro->RBinsert(35);
    rojiNegro->RBinsert(0);
    rojiNegro->RBinsert(79);
    rojiNegro->RBinsert(55);
    rojiNegro->RBinsert(42);
    rojiNegro->RBinsert(23);
    rojiNegro->RBinsert(12);
    rojiNegro->RBinsert(34);
    rojiNegro->RBinsert(11);
    rojiNegro->RBinsert(4);
    rojiNegro->RBinsert(7);
    rojiNegro->RBinsert(1);

    int op = 0;
    while (op != 9)
            {
                std::cout<<"------------ROJINEGRO------------"<<std::endl;
                std::cout<<"Eliga una opción:\n 1. Insertar\n 2. Borrar\n 3. Buscar\n 4. Imprimir ordenado asc\n 5. Imprimir ordenado desc\n 6. Obtener altura de un nodo\n 7. Obtener profundidad de un nodo\n 8. Obtener nivel del un nodo\n 9. Salir\n";
                std::cin>>op;
                
                switch (op)
                {
                    case 1:
                    {
                        int num;
                        std::cout<<"Número a insertar: ";
                        std::cin>>num;
                        rojiNegro->RBinsert(num);
                    }
                        break;
                    case 2:
                    {
                        int num;
                        std::cout<<"Número a borrar: ";
                        std::cin>>num;
                        rojiNegro->RBdelete(num);
                    }
                        break;
                    case 3:
                    {
                        int num;
                        std::cout<<"Número a buscar: ";
                        std::cin>>num;
                        if (rojiNegro->buscar(num))
                        {
                            std::cout<<"Si existe el número "<<*rojiNegro->buscar(num)<<" en el arbol.\n";
                        }
                        else
                        {
                            std::cout<<"No se encontró ese número. \n";
                        }
                    }
                        break;
                    case 4:
                    {
                        rojiNegro->inOrden();
                    }
                        break;
                    case 5:
                    {
                        rojiNegro->revOrden();
                    }
                        break;
                    case 6:
                    {
                        int num;
                        std::cout<<"Número: ";
                        std::cin>>num;
                        NodoB<int> * nodo = rojiNegro->buscar(num);
                        std::cout<<"Altura: "<<rojiNegro->getHeight(nodo)<<std::endl;
                    }
                        break;
                    case 7:
                    {
                        int num;
                        std::cout<<"Número: ";
                        std::cin>>num;
                        NodoB<int> * nodo = rojiNegro->buscar(num);
                        std::cout<<"Profundidad: "<<rojiNegro->getProfundidad(nodo)<<std::endl;
                    }
                        break;
                    case 8:
                    {
                        int num;
                        std::cout<<"Número: ";
                        std::cin>>num;
                        NodoB<int> * nodo = rojiNegro->buscar(num);
                        std::cout<<"Nivel: "<<rojiNegro->getNivel(nodo)<<std::endl;
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
