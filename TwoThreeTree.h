#include "TwoThreeNode.h"
#include <iostream>
#include <vector>

template <class T>
class TwoThreeTree 
{
    
    protected:
    TwoThreeNode<T> * root = nullptr;
    std::vector<T> leafLevels;
    
    public:
    TwoThreeTree() {}
    ~TwoThreeTree() {clear();}
    bool empty() {return root == nullptr;}
    void clear() {clear(root);}
    void clear(TwoThreeNode<T> *);
    TwoThreeNode<T> * getRoot() const {return root;}
    void setRoot(const T);
    void setRoot(TwoThreeNode<T> *);
    bool isRoot(TwoThreeNode<T> *);
    bool insert(TwoThreeNode<T> *, const T);
    bool insert(TwoThreeNode<T> *, TwoThreeNode<T> *);
    void insert(const T);
    void insert(TwoThreeNode<T> *);
    void insert23(T node);
    void insert23(TwoThreeNode<T> *);
    void insert23(TwoThreeNode<T> *, TwoThreeNode<T> *);
    void inverseInOrder() const;
    void inverseInOrder(TwoThreeNode<T> *) const;
    void toInOrderArray(T *, int);
    void toInOrderArray(TwoThreeNode<T> *, T *, int, int &);
    void isLeaf() ;
    bool isLeaf(TwoThreeNode<T> *) ;
    void ancestors(TwoThreeNode<T> *) const;
    int getHeight() const;
    int getHeight(TwoThreeNode<T> *) const ;
    int getDepth() const;
    int getDepth(TwoThreeNode<T> *) const;
    int getLevel() const;
    int getLevel(TwoThreeNode<T> *) const;
    int getBalanceFactor() const;
    int getBalanceFactor(TwoThreeNode<T> *) const ;
    void forceRoot(TwoThreeNode<T>*);
    TwoThreeNode<T>* searchNode(const T, TwoThreeNode<T> *);
    void insert23(TwoThreeNode<T> *, T);
    void redistributeChildren(TwoThreeNode<T>*, TwoThreeNode<T>*, TwoThreeNode<T>*);
    void split(TwoThreeNode<T>*);
    bool isTwoNode(TwoThreeNode<T>*);
    bool isThreeNode(TwoThreeNode<T>*);
    bool hasFreeChildren(TwoThreeNode<T>*);
    bool isTT(TwoThreeNode<T>*);
    void getLeafLevels(TwoThreeNode<T>*);
    bool getNodeKeys(TwoThreeNode<T>*);
    bool getNodeChildren(TwoThreeNode<T>*);
    bool findNode(TwoThreeNode<T>*, T);
    TwoThreeNode<T>* findNodeToDelete(TwoThreeNode<T>*, T);
    bool deleteNode(TwoThreeNode<T>*);
    bool deleteNode(T);
    void fixTree(TwoThreeNode<T>*);
    TwoThreeNode<T>* getInorderSuccesor(TwoThreeNode<T>*);
    bool isTT () {return isTT(root);}
    void sort(T a[], int);
    void printAsc() const;
    void printAsc(TwoThreeNode<T> * node) const;
    void printDesc() const;
    void printDesc(TwoThreeNode<T> * node) const;
};


template <class T>
void TwoThreeTree<T>::insert(const T node)
{
    this->insertOrder(node);
}

template <class T>
void TwoThreeTree<T>::insert(TwoThreeNode<T> * node)
{
    this->insertOrder(node);
}

template <class T>
void TwoThreeTree<T>::clear(TwoThreeNode<T> * node)
{
    if (node) 
    {
        clear(node->getLeft());
        clear(node->getRight());
        delete node;
    }
}

template <class T>
void TwoThreeTree<T>::setRoot(const T element)
{
    TwoThreeNode<T> * node = new TwoThreeNode<T>(element);
    setRoot(node);
}

template <class T>
void TwoThreeTree<T>::setRoot(TwoThreeNode<T> * node)
{
    if (!empty()) 
    {
        node->setLeft(root);
        root->setParent(node);
        root = node;
    }
    else 
    {
        root = node;
    }
}

template <class T>
bool TwoThreeTree<T>::isRoot(TwoThreeNode<T> * node)
{
    return node == this->root;
}

template <class T>
void TwoThreeTree<T>::insert23(T node)
{
    insert23(this->root, node);
}

template <class T>
void TwoThreeTree<T>::insert23(TwoThreeNode<T> * node)
{
    insert23(this->root, node);
}

template <class T>
void TwoThreeTree<T>::forceRoot(TwoThreeNode<T>* node)
{
    root = node;
}

template <class T>
void TwoThreeTree<T>::redistributeChildren(TwoThreeNode<T>* container, TwoThreeNode<T>* n1, TwoThreeNode<T>* n2)
{
    n1->setLeft(container->getLeft());
    n1->setRight(container->getMiddle());
    n2->setLeft(container->getTempChild());
    n2->setRight(container->getRight());
    n1->getLeft()->setParent(n1);
    n1->getRight()->setParent(n1);
    n2->getLeft()->setParent(n2);
    n2->getRight()->setParent(n2);
}

template <class T>
void TwoThreeTree<T>::split(TwoThreeNode<T>* container)
{
    if(isRoot(container))
    {
        TwoThreeNode<T>* newRoot = new TwoThreeNode<T>(container->getTempMiddle());
        forceRoot(newRoot);
        TwoThreeNode<T>* n1 = new TwoThreeNode<T>(container->getLower());
        TwoThreeNode<T>* n2 = new TwoThreeNode<T>(container->getHigher());
        if(container->getTempChild()!=nullptr)
        {
            redistributeChildren(container, n1, n2);
        }
        newRoot->setLeft(n1);
        newRoot->setRight(n2);
        newRoot->getLeft()->setParent(newRoot);
        newRoot->getRight()->setParent(newRoot);
        delete container;
    }
    else if(container->getParent() != nullptr)
    {
        TwoThreeNode<T>* parent = container->getParent();
        if(parent->isFull())
        {
            parent->setMiddleValue(container->getTempMiddle());
            if(parent->getRight() == container)
            {
                TwoThreeNode<T>* n1 = new TwoThreeNode<T>(container->getLower());
                TwoThreeNode<T>* n2 = new TwoThreeNode<T>(container->getHigher());
                if(container->getTempChild()!=nullptr)
                {
                    redistributeChildren(container, n1, n2);
                }
                parent->setRight(n2);
                parent->setTempChild(n1);
                parent->getRight()->setParent(parent);
                parent->getTempChild()->setParent(parent);
                delete container;
            }
            else if(parent->getLeft() == container)
            {
                TwoThreeNode<T>* n1 = new TwoThreeNode<T>(container->getLower());
                TwoThreeNode<T>* n2 = new TwoThreeNode<T>(container->getHigher());
                if(container->getTempChild()!=nullptr)
                {
                    redistributeChildren(container, n1, n2);
                }
                parent->setLeft(n1);
                parent->setTempChild(parent->getMiddle());
                parent->setMiddle(n2);
                parent->getLeft()->setParent(parent);
                parent->getMiddle()->setParent(parent);
                parent->getTempChild()->setParent(parent);
                delete container;
                
            }
            else
            {
                TwoThreeNode<T>* n1 = new TwoThreeNode<T>(container->getLower());
                TwoThreeNode<T>* n2 = new TwoThreeNode<T>(container->getHigher());
                if(container->getTempChild()!=nullptr)
                {
                    redistributeChildren(container, n1, n2);
                }
                parent->setMiddle(n1);
                parent->setTempChild(n2);
                parent->getMiddle()->setParent(parent);
                parent->getTempChild()->setParent(parent);
                delete container;
            }
            split(parent);
        }
        else
        {
            parent->setValue(container->getTempMiddle());
            if(parent->getRight() == container)
            {
                TwoThreeNode<T>* n1 = new TwoThreeNode<T>(container->getLower());
                TwoThreeNode<T>* n2 = new TwoThreeNode<T>(container->getHigher());
                if(container->getTempChild()!=nullptr)
                {
                    redistributeChildren(container, n1, n2);
                }
                parent->setRight(n2);
                parent->setMiddle(n1);
                parent->getRight()->setParent(parent);
                parent->getMiddle()->setParent(parent);
                delete container;
            }
            else if(parent->getLeft() == container)
            {
                TwoThreeNode<T>* n1 = new TwoThreeNode<T>(container->getLower());
                TwoThreeNode<T>* n2 = new TwoThreeNode<T>(container->getHigher());
                if(container->getTempChild()!=nullptr)
                {
                    redistributeChildren(container, n1, n2);
                }
                parent->setLeft(n1);
                parent->setMiddle(n2);
                parent->getLeft()->setParent(parent);
                parent->getMiddle()->setParent(parent);
                delete container;
            }
            if(parent->has3Keys())
                split(parent);
        }
    }
}

template <class T>
bool TwoThreeTree<T>:: isTwoNode(TwoThreeNode<T>* node)
{
    if((node->hasLower() && !node->hasHigher()) || (!node->hasLower() && node->hasHigher()))
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <class T>
bool TwoThreeTree<T>:: isThreeNode(TwoThreeNode<T>* node)
{
    if(node->hasLower() && node->hasHigher())
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <class T>
bool TwoThreeTree<T>::hasFreeChildren(TwoThreeNode<T>* node)
{
    if(node->getLeft() == nullptr || node->getMiddle() == nullptr || node->getRight() == nullptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <class T>
void TwoThreeTree<T>::insert23(TwoThreeNode<T> * parent, T node)
{
    TwoThreeNode<T>* container = new TwoThreeNode<T>();
    if(root == nullptr)
    {
        forceRoot(new TwoThreeNode<T>(node));
        return;
    }
    container = searchNode(node, root);
    if(isTwoNode(container))
    {
        container->setValue(node);
        container->deleteTempMiddle();
    }
    else if(isThreeNode(container))
    {
        container->setMiddleValue(node);
        split(container);
    }
}

template <class T>
TwoThreeNode<T>* TwoThreeTree<T>::searchNode(const T value, TwoThreeNode<T> * node)
{
    if(node == nullptr)
    {
        return nullptr;
    }
    if(isLeaf(node))
    {
        return node;
    }
    else if(isTwoNode(node))
    {
        if(value <= node->getLower())
        {
            return searchNode(value, node->getLeft());
        }
        else
        {
            return searchNode(value, node->getRight());
        }
    }
    else if(isThreeNode(node))
    {
        if(value <= node->getLower())
        {
            return searchNode(value, node->getLeft());
        }
        else if(value > node->getHigher())
        {
            return searchNode(value, node->getRight());
        }
        else
        {
            return searchNode(value, node->getMiddle());
        }
    }
    return node;
}


template <class T>
void TwoThreeTree<T>::fixTree(TwoThreeNode<T>* node)
{
    if(isRoot(node))
    {
        forceRoot(node->getMiddle());
        delete node;
    }
    else
    {
        bool threeKeys = false;
        TwoThreeNode<T>* parent = node->getParent();
        if(isTwoNode(parent))
        {
            TwoThreeNode<T>* sibling = new TwoThreeNode<T>();
            if(parent->getRight() == node)
            {
                sibling = parent->getLeft();
            }
            else
            {
                sibling = parent->getRight();
            }
            if(parent->getRight() == node)
            {
                if(isThreeNode(parent->getLeft()))
                {
                    threeKeys = true;
                    T siblingLower = sibling->getLower();
                    T siblingHigher = sibling->getHigher();
                    T parentVal = parent->getLower();
                    T keys[3] = {siblingLower,siblingHigher,parentVal};
                    sort(keys,3);
                    T low = keys[0];
                    T mid = keys[1];
                    T high = keys[2];
                    node->setValue(high);
                    parent->deleteAllKeys();
                    parent->setValue(mid);
                    sibling->deleteAllKeys();
                    sibling->setValue(low);
                    

                    if(!isLeaf(node))
                    {
                        node->setRight(node->getMiddle());
                        node->setMiddle(nullptr);
                        node->setLeft(sibling->getRight());
                        node->getLeft()->setParent(node);
                        sibling->setRight(sibling->getMiddle());
                        sibling->setMiddle(nullptr);
                    }
                }
            }
            else
            {
                if(isThreeNode(parent->getRight()))
                {
                    threeKeys = true;
                    T siblingLower = sibling->getLower();
                    T siblingHigher = sibling->getHigher();
                    T parentVal = parent->getLower();
                    T keys[3] = {siblingLower,siblingHigher,parentVal};
                    sort(keys,3);
                    T low = keys[0];
                    T mid = keys[1];
                    T high = keys[2];
                    node->setValue(low);
                    parent->deleteAllKeys();
                    parent->setValue(mid);
                    sibling->deleteAllKeys();
                    sibling->setValue(high);
                    
                    if(!isLeaf(node))
                    {
                        node->setLeft(node->getMiddle());
                        node->setMiddle(nullptr);
                        node->setRight(sibling->getLeft());
                        node->getRight()->setParent(node);
                        sibling->setLeft(sibling->getMiddle());
                        sibling->setMiddle(nullptr);
                    }
                }
            }
        }
        else if(isThreeNode(parent))
        {
            TwoThreeNode<T>* sibling = new TwoThreeNode<T>();
            if(parent->getRight() == node)
            {
                if(isThreeNode(parent->getMiddle()))
                {
                    threeKeys = true;
                    sibling = parent->getMiddle();
                    node->setValue(parent->getHigher());
                    parent->setHigher(sibling->getHigher());
                    sibling->deleteHigher();
                    if(!isLeaf(node))
                    {
                        node->setRight(node->getMiddle());
                        node->setLeft(sibling->getRight());
                        node->getLeft()->setParent(node);
                        sibling->setRight(sibling->getMiddle());
                        sibling->setMiddle(nullptr);
                    }
                }
            }
            else if(parent->getMiddle() == node)
            {
                if(isThreeNode(parent->getLeft()))
                {
                    threeKeys = true;
                    sibling = parent->getLeft();
                    node->setValue(parent->getLower());
                    parent->setLower(sibling->getHigher());
                    sibling->deleteHigher();
                    if(!isLeaf(node))
                    {
                        node->setRight(node->getMiddle());
                        node->setLeft(sibling->getRight());
                        node->getLeft()->setParent(node);
                        sibling->setRight(sibling->getMiddle());
                        sibling->setMiddle(nullptr);
                    }
                }
            }
            else
            {
                if(isThreeNode(parent->getMiddle()))
                {
                    threeKeys = true;
                    sibling = parent->getMiddle();
                    node->setValue(parent->getLower());
                    parent->setLower(sibling->getLower());
                    sibling->swapHigherToLower();
                    if(!isLeaf(node))
                    {
                        node->setLeft(node->getMiddle());
                        node->setRight(sibling->getLeft());
                        node->getRight()->setParent(node);
                        sibling->setLeft(sibling->getMiddle());
                        sibling->setMiddle(nullptr);
                    }
                }
            }
        }
        if(!threeKeys)
        {
            TwoThreeNode<T>* sibling = new TwoThreeNode<T>();
            if(isTwoNode(parent))
            {
                if(parent->getRight() == node)
                {
                    sibling = parent->getLeft();
                    sibling->setValue(parent->getLower());
                    if(!isLeaf(node))
                    {
                        sibling->setMiddle(sibling->getRight());
                        sibling->setRight(node->getMiddle());
                    }
                    parent->setMiddle(sibling);
                    parent->getMiddle()->setParent(parent);
                    parent->setLeft(nullptr);
                    parent->setRight(nullptr);
                    parent->deleteAllKeys();
                    delete node;
                }
                else
                {
                    sibling = parent->getRight();
                    sibling->setValue(parent->getLower());
                    if(!isLeaf(node))
                    {
                        sibling->setMiddle(sibling->getLeft());
                        sibling->setLeft(node->getMiddle());
                        sibling->getLeft()->setParent(sibling);
                    }
                    parent->setMiddle(sibling);
                    parent->getMiddle()->setParent(parent);
                    parent->setLeft(nullptr);
                    parent->setRight(nullptr);
                    parent->deleteAllKeys();
                    delete node;
                }
            }
            else if(isThreeNode(parent))
            {
                if(parent->getRight() == node)
                {
                    sibling = parent->getMiddle();
                    sibling->setValue(parent->getHigher());
                    if(!isLeaf(node))
                    {
                        sibling->setMiddle(sibling->getRight());
                        sibling->setRight(node->getMiddle());
                        sibling->getRight()->setParent(sibling);
                    }
                    parent->setRight(sibling);
                    parent->getRight()->setParent(parent);
                    parent->setMiddle(nullptr);
                    parent->deleteHigher();
                    delete node;
                }
                else if(parent->getMiddle() == node)
                {
                    sibling = parent->getLeft();
                    sibling->setValue(parent->getLower());
                    if(!isLeaf(node))
                    {
                        sibling->setMiddle(sibling->getRight());
                        sibling->setRight(node->getMiddle());
                        sibling->getRight()->setParent(sibling);
                    }
                    parent->setLeft(sibling);
                    parent->getLeft()->setParent(parent);
                    parent->setMiddle(nullptr);
                    parent->deleteLower();
                    parent->swapHigherToLower();
                    delete node;
                }
                else
                {
                    sibling = parent->getMiddle();
                    sibling->setValue(parent->getLower());
                    if(!isLeaf(node))
                    {
                        sibling->setMiddle(sibling->getLeft());
                        sibling->setLeft(node->getMiddle());
                        sibling->getLeft()->setParent(sibling);
                    }
                    parent->setLeft(sibling);
                    parent->getLeft()->setParent(parent);
                    parent->setMiddle(nullptr);
                    parent->deleteLower();
                    parent->swapHigherToLower();
                    delete node;
                }
            }
            if(parent->hasNoKeys())
            {
                sibling->setParent(parent);
                fixTree(parent);
            }
        }
    }
}

template <class T>
bool TwoThreeTree<T>::deleteNode(T value)
{
    TwoThreeNode<T>* node = new TwoThreeNode<T>();
    node = findNodeToDelete(root, value);
    if(node)
    {
        TwoThreeNode<T>* leafNode = new TwoThreeNode<T>();
        if(!isLeaf(node))
        {
            leafNode = getInorderSuccesor(node);
            T swapVal = leafNode->getLower();
            node->setLower(swapVal);
        }
        leafNode->deleteLower();
        if(leafNode->hasNoKeys())
        {
            fixTree(leafNode);
        }
        return true;
    }
    else
    {
        return false;
    }
}

template <class T>
TwoThreeNode<T>* TwoThreeTree<T>::getInorderSuccesor(TwoThreeNode<T>* node)
{
    if (node)
    {
        TwoThreeNode<T> * workingNode = node->getLeft();
        if(workingNode)
        {
            while (workingNode->getRight() != nullptr)
            {
                workingNode = workingNode->getRight();
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

template <class T>
TwoThreeNode<T>* TwoThreeTree<T>::findNodeToDelete(TwoThreeNode<T>* node, T value)
{
    if(node == nullptr)
    {
        return nullptr;
    }
    if(isLeaf(node))
    {
        if(isTwoNode(node))
        {
            if(node->getLower() == value)
            {
                return node;
            }
        }
        else if(isThreeNode(node))
        {
            if(node->getLower() == value || node->getHigher() == value)
            {
                return node;
            }
        }
        return nullptr;
    }
    else if(isTwoNode(node))
    {
        if(value == node->getLower())
        {
            return node;
        }
        
        if(value < node->getLower())
        {
            return findNodeToDelete(node->getLeft(), value);
        }
        else
        {
            return findNodeToDelete( node->getRight(), value);
        }
    }
    else if(isThreeNode(node))
    {
        if(node->getLower() == value || node->getHigher() == value)
        {
            return node;
        }
        if(value < node->getLower())
        {
            return findNodeToDelete(node->getLeft(), value);
        }
        else if(value > node->getHigher())
        {
            return findNodeToDelete(node->getRight(), value);
        }
        else
        {
            return findNodeToDelete(node->getMiddle(), value);
        }
    }
    return nullptr;
}

template <class T>
bool TwoThreeTree<T>::findNode(TwoThreeNode<T>* node, T value)
{
    if(node == nullptr)
    {
        return false;
    }
    if(isLeaf(node))
    {
        if(isTwoNode(node))
        {
            if(node->getLower() == value)
            {
                return true;
            }
        }
        else if(isThreeNode(node))
        {
            if(node->getLower() == value || node->getHigher() == value)
            {
                return true;
            }
        }
        return false;
    }
    else if(isTwoNode(node))
    {
        if(value == node->getLower())
        {
            return true;
        }
        
        if(value < node->getLower())
        {
            return findNode(node->getLeft(), value);
        }
        else
        {
            return findNode( node->getRight(), value);
        }
    }
    else if(isThreeNode(node))
    {
        if(node->getLower() == value || node->getHigher() == value)
        {
            return true;
        }
        if(value < node->getLower())
        {
            return findNode(node->getLeft(), value);
        }
        else if(value > node->getHigher())
        {
            return findNode(node->getRight(), value);
        }
        else
        {
            return findNode(node->getMiddle(), value);
        }
    }
    return false;
}

template <class T>
bool TwoThreeTree<T>::isTT(TwoThreeNode<T>* node)
{
    leafLevels.clear();
    getLeafLevels(root);
    T cmp = leafLevels[0];
    bool leafs = true;
    for(int i=1; i<leafLevels.size(); i++)
    {
        if(leafLevels[i] != cmp)
        {
            leafs = false;
        }
    }
    return leafs;
}

template <class T>
void TwoThreeTree<T>::getLeafLevels(TwoThreeNode<T>* node)
{
    if(node == nullptr) return;
    if(isLeaf(node))
    {
        leafLevels.push_back(getLevel(node));
    }
    else if(isTwoNode(node))
    {
        getLeafLevels(node->getLeft());
        getLeafLevels(node->getRight());
    }
    else if(isThreeNode(node))
    {
        getLeafLevels(node->getLeft());
        getLeafLevels(node->getMiddle());
        getLeafLevels(node->getRight());
    }
}

template <class T>
bool TwoThreeTree<T>::insert(TwoThreeNode<T> * parent, const T value)
{
    TwoThreeNode<T> * node = new TwoThreeNode<T>(value);
    bool inserted = insert(parent, node);
    
    if (!inserted) 
    {
        delete node;
    }

    return inserted;
}

template <class T>
bool TwoThreeTree<T>::insert(TwoThreeNode<T> * parent, TwoThreeNode<T> * value)
{
    bool inserted = false;
    
    if (empty() || !parent) 
    {
        setRoot(value);
        inserted = true;
    }
    else 
    {
        if (!parent->getLeft()) 
        {
            parent->setLeft(value);
            value->setParent(parent);
            inserted = true;
        }
        else if (!parent->getRight()) 
        {
            parent->setRight(value);
            value->setParent(parent);
            inserted = true;
        }
    }
    
    return inserted;
}

template <class T>
void TwoThreeTree<T>::toInOrderArray(T * array, int arraySize)
{
    int i = 0;
    toInOrderArray(root, array, arraySize, i);
}

template <class T>
void TwoThreeTree<T>::toInOrderArray(TwoThreeNode<T> * node, T * array,int arraySize, int & i)
{
    if (node)
    {
        toInOrderArray(node->getLeft(), array, arraySize, i);
        array[i] = node->getInfo();
        i++;
        toInOrderArray(node->getRight(), array, arraySize, i);
    }
}

template <class T>
void TwoThreeTree<T>::isLeaf()
{
    isLeaf(root);
}

template <class T>
bool TwoThreeTree<T>::isLeaf(TwoThreeNode<T> * node)
{
    if(node->getLeft() == nullptr && node->getMiddle() == nullptr && node->getRight() == nullptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <class T>
void TwoThreeTree<T>::ancestors(TwoThreeNode<T> * node) const
{
    if (node)
    {
        std::cout << *node << " -> ";
        ancestors(node->getParent());
    }
}

template <class T>
int TwoThreeTree<T>::getHeight() const
{
    return getHeight(root);
}

template <class T>
int TwoThreeTree<T>::getHeight(TwoThreeNode<T> * node) const
{
    if (!node)
    {
        return -1;
    }

    return 1 + std::max(getHeight(node->getLeft()), getHeight(node->getRight()));
}

template <class T>
int TwoThreeTree<T>::getDepth() const
{
    return getDepth(root);
}

template <class T>
int TwoThreeTree<T>::getDepth(TwoThreeNode<T> * node) const
{
    if (node == nullptr)
    {
        return 0;
    }
    else
    {
        return getDepth(node->getParent())+1;
    }
}

template <class T>
int TwoThreeTree<T>::getLevel() const
{
    return getLevel(root);
}

template <class T>
int TwoThreeTree<T>::getLevel(TwoThreeNode<T> * node) const
{
    int level = 0;
    while (node != nullptr && node->getParent() != nullptr) 
    {
        level++;
        node = node->getParent();
    }
    return level;
}

template <class T>
int TwoThreeTree<T>::getBalanceFactor() const
{
    return getBalanceFactor(root);
}

template <class T>
int TwoThreeTree<T>::getBalanceFactor(TwoThreeNode<T> * node) const
{
    return getHeight(node->getRight()) - getHeight(node->getLeft());
}

template <class T>
void TwoThreeTree<T>::sort(T a[], int N)
{
        int i, j, flag = 1;
        int temp;
        int numLength = N;
        for(i = 1; (i <= numLength) && flag; i++)
        {
            flag = 0;
            for (j=0; j < (numLength -1); j++)
            {
                if (a[j+1] < a[j])
                {
                    temp = a[j];
                    a[j] = a[j+1];
                    a[j+1] = temp;
                    flag = 1;
                }
            }
        }
        return;
}

template <class T>
void TwoThreeTree<T>::printAsc() const
{
    printAsc(root);
}

template <class T>
void TwoThreeTree<T>::printAsc(TwoThreeNode<T> * node) const
{
    if (node)
    {
        printAsc(node->getRight());
        if (node->hasHigher())
        {
            std::cout << node->getHigher() << std::endl;
        }
        if (node->hasTempMiddle())
        {
            std::cout << node->getMedium() << std::endl;
        }
        if (node->hasLower())
        {
            std::cout << node->getLower() << std::endl;   
        }
        printAsc(node->getMiddle());
        printAsc(node->getLeft());
    }
}

template <class T>
void TwoThreeTree<T>::printDesc() const
{
    printDesc(root);
}

template <class T>
void TwoThreeTree<T>::printDesc(TwoThreeNode<T> * node) const
{
    if (node) 
    {
        printDesc(node->getLeft());
        if (node->hasLower())
        {
            std::cout << node->getLower() << std::endl;
        }
        if (node->hasTempMiddle())
        {
            std::cout << node->getMedium() << std::endl;
        }
        if (node->hasHigher())
        {
            std::cout << node->getHigher() << std::endl;   
        }
        printDesc(node->getMiddle());
        printDesc(node->getRight());
    }
}
