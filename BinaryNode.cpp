
template<class Type>
class BinaryNode
{
public:
    BinaryNode();
    void setItem(const Type& anItem);
    Type getItem() const;
    bool isLeaf() const;
    BinaryNode<Type>* getLeftChildPtr() const;
    BinaryNode<Type>* getRightChildPtr() const;
    void setLeftChildPtr(BinaryNode<Type>* leftPtr);
    void setRightChildPtr(BinaryNode<Type>* rightPtr);
protected:
    Type item;
    BinaryNode<Type>* leftChildPtr; // pointer to left child
    BinaryNode<Type>* rightChildPtr;// pointer to right child
};

template<class Type>
BinaryNode<Type>::BinaryNode()
:leftChildPtr(nullptr), rightChildPtr(nullptr)
{}

template<class Type>
void BinaryNode<Type>::setItem(const Type& anItem)
{
    this->item = anItem;
}

template<class Type>
bool BinaryNode<Type>::isLeaf() const
{
    return(this->leftChildPtr==nullptr&&this->rightChildPtr==nullptr);
}


template<class Type>
BinaryNode<Type>* BinaryNode<Type>::getLeftChildPtr() const
{
    return (this->leftChildPtr);
}

template<class Type>
BinaryNode<Type>* BinaryNode<Type>::getRightChildPtr() const
{
    return (this->leftChildPtr);
}

template<class Type>
void BinaryNode<Type>::setLeftChildPtr(BinaryNode<Type>* leftPtr)
{
    this->leftChildPtr = leftPtr;
}

template<class Type>
void BinaryNode<Type>::setRightChildPtr(BinaryNode<Type>* rightPtr)
{
    this->rightChildPtr = rightPtr;
}



