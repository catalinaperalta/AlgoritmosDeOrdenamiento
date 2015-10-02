template <class T>
class TwoThreeNode
{
    protected:
    bool hasSmall = false;
    bool hasHigh = false;
    bool full = false;
    TwoThreeNode<T>* parent = nullptr;
    TwoThreeNode<T>* leftChild = nullptr;
    TwoThreeNode<T>* middleChild = nullptr;
    TwoThreeNode<T>* rightChild = nullptr;
    TwoThreeNode<T>* tempChild = nullptr;
    
    public:
    T* lower = nullptr;
    T* higher = nullptr;
    T* tempMiddle = nullptr;
    TwoThreeNode(T);
    TwoThreeNode();
    virtual ~TwoThreeNode();
    void deleteTempMiddle();
    void setTempMiddle(T);
    bool hasTempMiddle();
    void setLower(T);
    void setHigher(T);
    T getLower();
    T getHigher();
    T getMedium();
    bool isFull();
    bool has3Keys();
    void setValue(T);
    void setMiddleValue(T);
    void swapHigherToLower();
    void deleteHigher();
    void deleteLower();
    bool hasLower();
    bool hasHigher();
    void deleteAllKeys();
    bool hasNoKeys();

    TwoThreeNode<T> * getLeft() const { return leftChild; }
    void setLeft(TwoThreeNode<T> * value) { leftChild = value; }
    
    TwoThreeNode<T> * getRight() const { return rightChild; }
    void setRight(TwoThreeNode<T> * value) { rightChild = value; }
    
    TwoThreeNode<T> * getMiddle() const { return middleChild; }
    void setMiddle(TwoThreeNode<T> * value) { middleChild = value; }
    
    TwoThreeNode<T> * getParent() const { return parent; }
    void setParent(TwoThreeNode<T> * value) { parent = value; }

    TwoThreeNode<T> * getTempChild() const { return tempChild; }
    void setTempChild(TwoThreeNode<T> * value) { tempChild = value;}

    T getTempMiddle() const { return *tempMiddle;}
};

template <class T>
TwoThreeNode<T>::TwoThreeNode():leftChild(nullptr),middleChild(nullptr),rightChild(nullptr),parent(nullptr),lower(nullptr),higher(nullptr),tempMiddle(nullptr),tempChild(nullptr)
{

}

template <class T>
TwoThreeNode<T>::TwoThreeNode(T low)
{
    lower = new T(low);
    hasSmall = true;
}

template <class T>
TwoThreeNode<T>::~TwoThreeNode()
{
    leftChild = middleChild = rightChild = parent = tempChild = nullptr;
    lower = higher = nullptr;
}
  
template <class T>  
void TwoThreeNode<T>::deleteTempMiddle()
{
    if(tempMiddle)
    {
        tempMiddle = nullptr;
    }
}

template <class T>    
void TwoThreeNode<T>::setTempMiddle(T value)
{
    if(tempMiddle == nullptr)
    {
        tempMiddle = new T(value);
    }
    else
    {
        *tempMiddle = value;
    }
}
  
template <class T>   
bool TwoThreeNode<T>::hasTempMiddle()
{
    if(tempMiddle)
    {
        return true;
    }
    else
    {
        return false;
    }
}
    
template <class T>
void TwoThreeNode<T>::setLower(T value)
{
    if(lower!=nullptr)
    {
        *lower = value;
    }
    else
    {
        lower = new T(value);
    }
}

template <class T>
void TwoThreeNode<T>::setHigher(T value)
{
    if(higher!=nullptr)
    {   
        *higher = value;
    }
    else
    {
        higher = new T(value);
    }
}
    
template <class T>
T TwoThreeNode<T>::getLower()
{
    return *lower;
}
    
template <class T>
T TwoThreeNode<T>::getHigher()
{
    return *higher;
}

template <class T>
T TwoThreeNode<T>::getMedium()
{
    return *tempMiddle;
}
    
template <class T>
bool TwoThreeNode<T>::isFull()
{
    if(higher && lower)
    {
        return true;
    }
    return false;
}

template <class T>
bool TwoThreeNode<T>::has3Keys()
{
    return higher && lower && tempMiddle;
}
    
template <class T>
void TwoThreeNode<T>::setValue(T value)
{
    if(!lower)
    {
        lower = new T(value);
    }
    else
    {
        if(value >= *lower)
        {
            if(!higher)
            {
                higher = new T(value);
            }
        }
        else if(value < *lower)
        {
            higher = new T(*lower);
            *lower = value;
        }
    }
}
    
template <class T>
void TwoThreeNode<T>::setMiddleValue(T value)
{
    if(higher && lower)
    {
        if(!tempMiddle)
        {
            tempMiddle = new T(value);
            if(value < *lower)
            {
                *tempMiddle = *lower;
                *lower = value;
            }
            else if(value >= *lower && value <= *higher)
            {
                *tempMiddle = value;
            }
            else
            {
                *tempMiddle = *higher;
                *higher = value;
            }
        }
        else
        {
            if(value < *lower)
            {
                *tempMiddle = *lower;
                *lower = value;
            }
            else if(value >= *lower && value <= *higher)
            {
                *tempMiddle = value;
            }
            else
            {
                *tempMiddle = *higher;
                *higher = value;
            }
        }
    }
}
    
template <class T>
void TwoThreeNode<T>::swapHigherToLower()
{
    if (!lower)
    {
        lower = new T (*higher);
    }
    else
    {
        *lower = *higher;
    }
    higher = nullptr;
}
    
template <class T>
void TwoThreeNode<T>::deleteHigher()
{
    if (higher)
    {
        higher = nullptr;
    }
}

template <class T>
void TwoThreeNode<T>::deleteLower()
{
    if (lower)
    {
        lower = nullptr;
    }
}
    
template <class T>
bool TwoThreeNode<T>::hasLower()
{
    if(lower==nullptr)
    {
        return false;
    }
    else
    {
        return true;
    }
}

template <class T>
bool TwoThreeNode<T>::hasHigher()
{
    if(higher==nullptr)
    {
        return false;
    }
    else
    {
        return true;
    }
}

template <class T>
void TwoThreeNode<T>::deleteAllKeys()
{
    if(lower)
    {
        lower = nullptr;
    }
    
    if(higher)
    {
        higher = nullptr;
    }
}

template <class T>
bool TwoThreeNode<T>::hasNoKeys()
{
    return !lower && !higher;
}
