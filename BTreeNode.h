template <class T>
class BTreeNode 
{    
    protected:
    int key = 0;
    int fill= 0;
    int parent = 0;
    bool leaf = false;
    T *info;
    int *sons;
    bool isRoot = false;

    public:
    BTreeNode(int);
    BTreeNode(int,int,std::fstream &);
    virtual ~BTreeNode();
    bool checkFull(int);
    void printInfoNode();
    void print(int);

    template <class Y>
    friend class BTree; 
};

template <class T>
void BTreeNode<T>::printInfoNode()
{
    for(int i = 0; i < fill;i++)
    {
        std::cout << info[i] << " ";
    }
}

template <class T>
bool BTreeNode<T>::checkFull(int order)
{
    return fill==order*2-1;
}


template <class T>
BTreeNode<T>::BTreeNode(int order)
{
    info = new T[2*order-1];
    sons = new int[2*order+1];
}

template <class T>
void BTreeNode<T>::print(int order)
{
    std::cout << "Nodo: ";
    std::cout << key << std::endl;
    if(this->isRoot)
    {
        std::cout << "Root" << std::endl;
    }
    else
    {
        std::cout << "Parent: ";
        std::cout << parent << std::endl;
    }
    std::cout << "Info: ";
    printInfoNode();
    std::cout << std::endl;
    if(!leaf)
    {
        std::cout << "Sons: ";
        for(int i = 0; i < fill+1;i++)
        {
            std::cout << sons[i] << " ";
        }
        std::cout << std::endl;
    }
    else
    {
        std::cout << "Leaf" << std::endl;
    }
    
    std::cout << std::endl;
}

template <class T>
BTreeNode<T>::~BTreeNode()
{

}
