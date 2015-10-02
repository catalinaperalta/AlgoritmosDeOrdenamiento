#include "BTreeNode.h"
#include <fstream>

template <class T>
class BTree 
{
    private:
    int currentID;
    int order;
    std::fstream data;
    void setData();
    
    public:
    BTree(int);
    ~BTree();
    void insert(T);
    void print();
    void updateTotal(int);
    int getRoot();
    void setRoot(int);
    void insertdata(BTreeNode<T> &,T);
    void divideNode (BTreeNode<T> &,int,BTreeNode<T> &);
    void save(BTreeNode<T> &);
    BTreeNode<T> load(int);
    void loadNode(BTreeNode<T> *,int);
    int totalNodes();
    bool search(T);
    void eliminate (T);
    bool searchData(BTreeNode<T> &,T);
    void deleteData(BTreeNode<T> &,T);
    void join(BTreeNode<T> &, int);
    void borrowBefore(BTreeNode<T> &,int);
    void borrowNext(BTreeNode<T> &,int);
    void deleteNotLeaf(BTreeNode<T> &,int);
    void deleteLeaf(BTreeNode<T> &,int);
    int getPrevious(BTreeNode<T> &,int);
    int getNext(BTreeNode<T> &,int);
    void fill(BTreeNode<T> &,int);
    void printAsc();
    void printAsc(BTreeNode<T> &);
    void printDesc();
    void printDesc(BTreeNode<T> &);
    int findInfo(BTreeNode<T> &,T);
};

template <class T>
BTree<T>::BTree(int order)
{
    this->order = order;
    currentID = 0;
    setData();
    BTreeNode<T> node(order);
    node.key = currentID;
    node.leaf = true;
    node.isRoot = true;
    save(node);
    currentID++;
}

template <class T>
void BTree<T>::insert(T data)
{
    BTreeNode<T> root = load(getRoot());
    if(root.checkFull(order))
    {
        BTreeNode<T> nodeparent(order);
        nodeparent.key = currentID;
        setRoot(currentID);
        nodeparent.leaf = false;
        nodeparent.fill = 0;
        nodeparent.sons[0] = root.key;
        nodeparent.parent = nodeparent.key;
        nodeparent.isRoot = true;
        currentID++;
        divideNode(nodeparent, 0, root);
        insertdata(nodeparent, data);
    }
    else
    {
        insertdata(root, data);
    }
}

template <class T>
void BTree<T>::insertdata(BTreeNode<T> & node,T data)
{
    int i = node.fill-1;
    if(node.leaf)
    {
        while (i >= 0 && data < node.info[i])
        {
            node.info[i+1] = node.info[i];
            i--;
        }
        node.info[i+1] = data;
        node.fill++;
        save(node);
    }
    else
    {
        while (i >= 0 && data < node.info[i])
        {
            i--;
        }
        i ++;
        BTreeNode<T> nodeson = load(node.sons[i]);
        if(nodeson.checkFull(order))
        {
            divideNode(node, i, nodeson);
            if(data > node.info[i])
            {
                i++;
                nodeson = load(node.sons[i]);
            }
        }
        insertdata(nodeson, data);
    }
}

template <class T>
void BTree<T>::divideNode(BTreeNode<T> & nodeparent,int i,BTreeNode<T> & node)
{
    node.parent = nodeparent.key;
    BTreeNode<T> nodeBrother(order);
    nodeBrother.key = currentID;
    nodeBrother.parent = nodeparent.key;
    currentID++;
    nodeBrother.leaf = node.leaf;
    int div = order-1;
    nodeBrother.fill = div;
    
    for(int j = 0; j < div; j++)
    {
        nodeBrother.info[j] = node.info[j+order];
    }
    if (!node.leaf){
        for(int j = 0; j < div+1; j++)
        {
            nodeBrother.sons[j] = node.sons[j+order];
        }
    }
    node.fill = div;
    
    for (int j = nodeparent.fill+1; j >= i+1;j--)
    {
        nodeparent.sons[j+1] = nodeparent.sons[j];
    }
    
    nodeparent.sons[i+1] = nodeBrother.key;
    
    for (int j = nodeparent.fill; j >= i; j--)
    {
        nodeparent.info[j] = nodeparent.info[j-1];
    }
    
    nodeparent.info[i] = node.info[order-1];
    nodeparent.fill++;
    
    save(node);
    save(nodeparent);
    save(nodeBrother);
}

template <class T>
void BTree<T>::print()
{
    BTreeNode<T> node(order);
    for(int i = 0; i < currentID; i++)
    {
        node = load(i);
        if(i == getRoot())
        {
            node.print(order);
        }
        else
        {
            node.print(order);
        }
    }
}

template <class T>
void BTree<T>::setData()
{
    int root = 0;
    data.open("./data.dat", std::ios::out|std::ios::in| std::ios::binary);
    data.seekp(0);
    data.write(reinterpret_cast<char*>(&root), sizeof(int));
}

template <class T>
int BTree<T>::getRoot()
{
    int root;
    data.seekg(0);
    data.read(reinterpret_cast<char*>(&root), sizeof(int));
    return root;
}

template <class T>
void BTree<T>::setRoot(int rootID)
{
    data.seekp(0);
    data.write(reinterpret_cast<char*>(&rootID), sizeof(int));
}

template <class T>
int BTree<T>::totalNodes()
{
    int totalNodes;
    data.seekg(0);
    data.read(reinterpret_cast<char*>(&totalNodes), sizeof(int));
    return totalNodes;
}


template <class T>
void BTree<T>::updateTotal(int value)
{
    int total;
    data.seekg(0);
    data.read(reinterpret_cast<char*>(&total), sizeof(int));
    total += value;
    data.seekp(0);
    data.write(reinterpret_cast<char*>(&total), sizeof(int));
}


template <class T>
void BTree<T>::save(BTreeNode<T> & node)
{
    data.seekp(sizeof(int)+node.key*sizeof(BTreeNode<T>));
    data.write(reinterpret_cast<char*>(&node), sizeof(BTreeNode<T>));
}

template <class T>
BTreeNode<T>  BTree<T>::load(int keyDeload)
{
    BTreeNode<T> node(order);
    data.seekg(sizeof(int)+keyDeload*sizeof(BTreeNode<T>));
    data.read(reinterpret_cast<char*>(&node), sizeof(BTreeNode<T>));
    return node; 
}

template <class T>
bool BTree<T>::search(T data)
{
    BTreeNode<T> root = load(getRoot());
    bool found = searchData(root, data);
    return found;
}

template <class T>
bool BTree<T>::searchData(BTreeNode<T> & node, T data){
    int i = 0;
    while(i <= node.fill && data > node.info[i])
    {
        i++;
    }
    if (i <= node.fill && data == node.info[i])
    {
        return true;
    }
    else if (node.leaf)
    {
        return false;
    }
    else
    {
        for(int i=0; i<node.fill+1;i++)
        {
            node = load(node.sons[i]);
            return searchData(node, data);
        }
    }
}

template <class T>
BTree<T>::~BTree()
{
    data.close();
}

template <class T>
void BTree<T>::printAsc()
{
    BTreeNode<T> root = load(getRoot());
    printAsc(root);
    std::cout << std::endl;
}

template <class T>
void BTree<T>::printAsc(BTreeNode<T> & node)
{
    BTreeNode<T> son(order);
    int i;
    for(i = 0; i < node.fill; i++)
    {
        if(!node.leaf)
        {
            son = load(node.sons[i]);
            printAsc(son);
        }
        std::cout << " " << node.info[i];
    }
    if(node.leaf == false)
    {
        son = load(node.sons[i]);
        printAsc(son);
    }
}

template <class T>
void BTree<T>::printDesc()
{
    BTreeNode<T> root = load(getRoot());
    printDesc(root);
    std::cout << std::endl;
}

template <class T>
void BTree<T>::printDesc(BTreeNode<T> & node)
{
    BTreeNode<T> son(order);
    int i;
    for(i = node.fill; i > 0; i--)
    {
        if(!node.leaf)
        {
            son = load(node.sons[i]);
            printDesc(son);
        }
        std::cout << " " << node.info[i-1];
    }
    if(node.leaf == false)
    {
        son = load(node.sons[i]);
        printDesc(son);
    }
}

template <class T>
void BTree<T>::deleteData(BTreeNode<T> & node,T data)
{
    int i = findInfo(node, data);
    if(i < node.fill && node.info[i] == data)
    {
        if(node.leaf)
        {
            deleteLeaf(node,i);
            save(node);
        }
        else
        {
            deleteNotLeaf(node,i);
            save(node);
        }
    }
    else
    {
        if(node.leaf)
        {
            std::cout << "El dato " << data << " no existe en el arbol" << std::endl;
        }
        else
        {
            bool flag = ( (i==node.fill)? true : false );
            BTreeNode<T> son = load(node.sons[i]);
            T data2 = son.info[1];
            if(son.fill < order)
            {
                fill(node,i);
            }
            if(flag && i > node.fill)
            {
                son = load(node.sons[i-1]);
                deleteData(son, data);
            }
            else
            {
                son = load(node.sons[i]);
                data2 = son.info[2];
                deleteData(son,data);
            }
        }
    }
}

template <class T>
void BTree<T>::deleteLeaf(BTreeNode<T> & nodo,int i)
{
    for (int j = i+1; j < nodo.fill; j++)
    {
        nodo.info[j-1] = nodo.info[j];
    }
    nodo.fill--;
}

template <class T>
void BTree<T>::deleteNotLeaf(BTreeNode<T> & parent,int i)
{
    T data = parent.info[i];
    BTreeNode<T> son = load(parent.sons[i]);
    BTreeNode<T> sonBrother = load(parent.sons[i+1]);
    if(son.fill >= order)
    {
        T antes = getPrevious(parent,i);
        parent.info[i] = antes;
        deleteData(son, antes);
    }
    else if(sonBrother.fill >= order)
    {
        T siguiente = getNext(parent,i);
        parent.info[i] = siguiente;
        deleteData(sonBrother, siguiente);
    }
    else
    {
        join(parent,i);
        son = load(son.key);
        deleteData(son,data);
    }
}


template <class T>
int BTree<T>::getPrevious(BTreeNode<T> & parent,int i)
{
    BTreeNode<T> son = load(parent.sons[i]);
    while(!son.leaf)
    {
        son = load(son.sons[son.fill]);
    }
    return son.info[son.fill-1];
}


template <class T>
int BTree<T>::getNext(BTreeNode<T> & parent, int i)
{
    BTreeNode<T> son = load(parent.sons[i+1]);
    while(!son.leaf)
    {
        son = load(son.sons[0]);
    }
    return son.info[0];
}

template <class T>
void BTree<T>::fill(BTreeNode<T> & nodo,int i)
{
    BTreeNode<T> son = load(nodo.sons[i-1]);
    BTreeNode<T> sonBrother = load(nodo.sons[i+1]);
    if(i != 0 && son.fill >= order)
    {
        borrowBefore(nodo,i);
    }
    else if(i != nodo.fill && sonBrother.fill >= order)
    {
        borrowNext(nodo,i);
    }
    else
    {
        if(i != nodo.fill)
        {
            join(nodo,i);
        }
        else
        {
            join(nodo,i-1);
        }
    }
    
}

template <class T>
void BTree<T>::borrowBefore(BTreeNode<T> & parent,int i)
{
    BTreeNode<T> son = load(parent.sons[i]);
    BTreeNode<T> sonBrother = load(parent.sons[i-1]);
    
    for(int j = son.fill; j>= 0;j--)
    {
        son.info[j+1] = son.info[j];
    }
    if(!son.leaf)
    {
        for(int j = son.fill; j>=0; j--)
        {
            son.sons[j+1] = son.sons[j];
        }
    }
    son.info[0] = parent.info[i-1];

    if(!parent.leaf)
    {
        son.sons[0] = sonBrother.sons[sonBrother.fill];
    }
    
    parent.info[i-1] = sonBrother.info[sonBrother.fill-1];
    
    son.fill++;
    sonBrother.fill--;
    
    save(parent);
    save(son);
    save(sonBrother);
    
        
    
}

template <class T>
void BTree<T>::borrowNext(BTreeNode<T> & parent,int i){
    BTreeNode<T> son = load(parent.sons[i]);
    BTreeNode<T> sonBrother = load(parent.sons[i+1]);
    
    son.info[son.fill] = parent.info[i];
    
    if(!son.leaf)
        son.sons[son.fill+1] = sonBrother.sons[0];
    
    
    parent.info[i] = sonBrother.info[0];
    
    for(int j = 1 ; j < sonBrother.fill;j++)
    {
        sonBrother.info[j-1] = sonBrother.info[j];
    }
    
    if(!sonBrother.leaf)
    {
        for(int j = 1; j <= sonBrother.fill; j++)
        {
            sonBrother.sons[j-1] = sonBrother.sons[j];
        }
    }
    
    
    son.fill++;
    sonBrother.fill--;
    
    save(parent);
    save(son);
    save(sonBrother);
    
}

template <class T>
void BTree<T>::join(BTreeNode<T> & parent, int i)
{
    BTreeNode<T> son = load(parent.sons[i]);
    BTreeNode<T> sonBrother = load(parent.sons[i+1]);
    son.info[order-1] = parent.info[i];
    
    for (int j=0; j<sonBrother.fill; j++)
    {
        son.info[j+order] = sonBrother.info[j];
    }
    
    
    if (!son.leaf)
    {
        for(int j=0; j<=sonBrother.fill; j++)
        {
            son.sons[j+order] = sonBrother.sons[j];
        }
    }
    

    for (int j=i+1; j<parent.fill; j++)
    {
        parent.info[j-1] = parent.info[j];
    }

    
    for (int j=i+2; j<=parent.fill; j++)
    {
        parent.sons[j-1] = parent.sons[j];
    }
    
    son.fill += sonBrother.fill+1;
    parent.fill--;
    
    save(parent);
    save(son);
    save(sonBrother);  
}

template <class T>
void BTree<T>::eliminate(T data)
{
    BTreeNode<T> root = load(getRoot());
    deleteData(root, data);
    if(root.fill==0)
    {
        if(!root.leaf)
        {
            setRoot(root.sons[0]);
        }
    }
}

template <class T>
int BTree<T>::findInfo(BTreeNode<T> & node,T data)
{
    int i=0;
    while (i<node.fill && node.info[i] < data)
    {
        i++;
    }
    return i;
}
