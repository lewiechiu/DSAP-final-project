
#include "BinaryNode.cpp"
#include "LinkList.cpp"
#include <stdio.h>
/*
 Binary Tree
 left subNode is smaller
 right subNode is bigger or qual to the parent
 use inorderTraverse to take out/ print all the missions
 
 RELATION BETWEEN PUBLIC FUNCTION AND PROTECTED FUNCTION
 PUBLIC                                  PROTECTED
 ----------------------------------------------------------------------
 Tree2SortedList()      <->              inorderTakeOut()
 getNumberOfNodes()     <->              getNumberOfNodesHelper()
 add()                  <->              insertInorder()
 remove()               <->              RemoveValue() -> RemoveNode()
 clear()                <->              destoryTree()
 contains()             <->              findNode()
 inorderTraverse()      <->              inorder()
 
 *CAUSION*
 In Mission class, we need to implement < > ==
 Need to implemnet visit function outside to parse into inorderTraverse() function
 */
template<class ItemType>
class BinaryNodeTree
{
public:
    /*CONSTRUCTOR & DESTRUCTOR*/
    BinaryNodeTree();
    BinaryNodeTree(const ItemType& rootItem);
    BinaryNodeTree(const ItemType& rootItem, const BinaryNodeTree<ItemType>* leftTreePtr, const BinaryNodeTree<ItemType>* rightTreePtr);
    BinaryNodeTree(const BinaryNodeTree<ItemType>& tree);
    ~BinaryNodeTree();
    /*PUBLIC FUNCTION*/
    int getNumberOfNodes() ;
    bool add(const ItemType& newData) ;
    bool remove(const ItemType& data) ;
    void clear() ;
    bool contains(const ItemType& anEntry) ;
    void inorderTraverse(void visit(ItemType&)) const;
    LinkList<ItemType>* Tree2SortedList()const;
    //Sorted list: descending order
protected:
    BinaryNode<ItemType>* rootPtr;
    /*PIVATED*/
    int getNumberOfNodesHelper(BinaryNode<ItemType>* subTreePtr) const;
    BinaryNode<ItemType>* copyTree(const BinaryNode<ItemType>* treePtr) const;
    void destroyTree(BinaryNode<ItemType>* subTreePtr);
    void inorder(void visit(ItemType&), BinaryNode<ItemType>* treePtr) const;
    void inorderTakeOut(BinaryNode<ItemType>* treePtr, LinkList<ItemType>* List) const;
    BinaryNode<ItemType>* insertInorder(BinaryNode<ItemType>* subTreePtr,BinaryNode<ItemType>* newNodePtr);
    BinaryNode<ItemType>* RemoveNode(BinaryNode<ItemType>* nodePtr);
    BinaryNode<ItemType>* RemoveValue(BinaryNode<ItemType>* subTreePtr,ItemType target, bool&success);
    BinaryNode<ItemType>* findNode (BinaryNode<ItemType>* subTreePtr, ItemType target);
};

/*CONSTRUCTOR & DESTRUCTOR*/
template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree()
: rootPtr(nullptr)
{
}

template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const ItemType& rootItem)
{
    rootPtr = new BinaryNode<ItemType>(rootItem, nullptr, nullptr);
    
}

template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const ItemType& rootItem,const BinaryNodeTree<ItemType>* leftTreePtr, const BinaryNodeTree<ItemType>* rightTreePtr)
{
    rootPtr = new BinaryNode<ItemType>(rootItem, copyTree(leftTreePtr->rootPtr), copyTree(rightTreePtr->rootPtr) );
}

template<class ItemType>
BinaryNode<ItemType>* BinaryNodeTree<ItemType>::copyTree(const BinaryNode<ItemType>* treePtr) const
{
    BinaryNode<ItemType>* newTreePtr = nullptr;
    // Copy tree nodes during a preorder traversal
    if (treePtr != nullptr)
    { // Copy node
        newTreePtr = new BinaryNode<ItemType>(treePtr->getItem(), nullptr, nullptr);
        newTreePtr->setLeftChildPtr(copyTree(treePtr->getLeftChildPtr()));
        newTreePtr->setRightChildPtr(copyTree(treePtr->getRightChildPtr()));
    } // end if
    return newTreePtr;
}  // end copyTree

template<class ItemType>
BinaryNodeTree<ItemType>::~BinaryNodeTree()
{
    clear();
    
} // end destructor

/*PUBLIC FUNCTION*/
template<class ItemType>
int BinaryNodeTree<ItemType>::getNumberOfNodes()
{
    int number = this->getNumberOfNodes(this->rootPtr);
    return number;
}

template<class ItemType>
void BinaryNodeTree<ItemType>::inorderTraverse(void visit(ItemType&)) const
{
    inorder(visit,rootPtr);
}


template<class ItemType>
LinkList<ItemType>*  BinaryNodeTree<ItemType>::Tree2SortedList()const
{
    LinkList<ItemType>* List;
    inorderTakeOut(rootPtr, List);
    return List;
}

template<class ItemType>
void BinaryNodeTree<ItemType>::inorderTakeOut(BinaryNode<ItemType>* treePtr, LinkList<ItemType>* List) const
{
    if (treePtr != nullptr)
    {
        inorderTakeOut(treePtr->getLeftChildPtr(), List);
        ItemType theItem = treePtr->getItem();
        DoubleNode<ItemType>* newNode = new DoubleNode<ItemType>(theItem);
        List->insertAtFront(newNode);
        // treePtr->setItem(theItem);
        inorderTakeOut(treePtr->getRightChildPtr(), List);
    }
}

template<class ItemType>
bool BinaryNodeTree<ItemType>::add(const ItemType& newData)
{
    BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newData);
    rootPtr = insertInorder(rootPtr, newNodePtr);
    return true;
}

template<class ItemType>
bool BinaryNodeTree<ItemType>::remove(const ItemType& newData)
{
    BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newData);
    bool success = false;
    rootPtr = RemoveValue(rootPtr, newData, success);
    return success;
}

template<class ItemType>
void BinaryNodeTree<ItemType>::clear()
{
    destroyTree(this->rootPtr);
}

template<class ItemType>
bool BinaryNodeTree<ItemType>::contains(const ItemType& anEntry)
{
    if (findNode(rootPtr, anEntry)==nullptr)
         return false;
    else
        return true;
}

/*PIVATED*/
template<class ItemType>
BinaryNode<ItemType>* BinaryNodeTree<ItemType>::insertInorder(BinaryNode<ItemType>* subTreePtr,BinaryNode<ItemType>* newNodePtr)
{
    if (subTreePtr==nullptr)
        return newNodePtr;
    else if ( subTreePtr->getItem() > newNodePtr->getItem())
    {
        BinaryNode<ItemType>* tempPtr;
        tempPtr = insertInorder(subTreePtr->getLeftChildPtr(), newNodePtr);
        subTreePtr->setLeftChildPtr(tempPtr);
    }
    else
    {
        BinaryNode<ItemType>* tempPtr;
        tempPtr = insertInorder(subTreePtr->getRightChildPtr(), newNodePtr);
        subTreePtr->setRightChildPtr(tempPtr);
    }
    
    return subTreePtr;
}



template<class ItemType>
BinaryNode<ItemType>* BinaryNodeTree<ItemType>::RemoveNode(BinaryNode<ItemType>* nodePtr)
{
    if (nodePtr->isLeaf())
    {
        delete nodePtr;
        nodePtr = nullptr;
        return nodePtr;
    }
    else if (nodePtr->getLeftChildPtr()!=nullptr || nodePtr->getRightChildPtr()!=nullptr)   //has one child
    {
        BinaryNode<ItemType>* nodeToConnectPtr;
        if (nodePtr->getRightChildPtr()!=nullptr)
            nodeToConnectPtr = nodePtr->getLeftChildPtr();
        else
            nodeToConnectPtr = nodePtr->getRightChildPtr();
        delete nodePtr;
        nodePtr = nullptr;
        return nodeToConnectPtr;
    }
    else    //has more than one child
    {
        BinaryNode<ItemType>* tempPtr;
        ItemType Answer;
        //be thrown into the removeLeftmostNode function, the value will change over the iteration
        tempPtr = removeLeftmostNode(nodePtr->getRightChildPtr(), Answer);
        nodePtr->setRightChildPtr(tempPtr);
        nodePtr->setItem(nodePtr->getItem());
        return nodePtr;
    }
}


template<class ItemType>
BinaryNode<ItemType>* findNode (BinaryNode<ItemType>* subTreePtr, ItemType target)
{
    if(subTreePtr == nullptr)
        return nullptr;
    else if (subTreePtr->getItem()== target)
        return subTreePtr;
    else if (subTreePtr->getItem() >target) //smaller is on the left
        return findNode(subTreePtr->getLeftChildPtr(), target);
    else    //bigger is on the right
        return findNode(subTreePtr->getRightChildPtr(), target);
}

template<class ItemType>
int BinaryNodeTree<ItemType>::getNumberOfNodesHelper(BinaryNode<ItemType>* subTreePtr) const
{
    if(subTreePtr==nullptr)
        return 0;
    else
    {
        int leftNodes = getNumberOfNodes(subTreePtr->getLeftChildPtr());
        int rightNodes = getNumberOfNodes(subTreePtr->getRightChildPtr());
        return 1+rightNodes+leftNodes;
    }
}


template<class ItemType>
void BinaryNodeTree<ItemType>::destroyTree(BinaryNode<ItemType>* subTreePtr)
{
    if (subTreePtr != nullptr)
    {
        destroyTree (subTreePtr->getLeftChildPtr());
        destroyTree (subTreePtr->getRightChildPtr());
        delete subTreePtr;
    } //endif
} // end destroyTree

template<class ItemType>
void BinaryNodeTree<ItemType>::inorder(void visit(ItemType&), BinaryNode<ItemType>* treePtr) const
{
    if (treePtr != nullptr)
    {
        inorder(visit, treePtr->getLeftChildPtr());
        ItemType theItem = treePtr->getItem();
        visit(theItem);
        // treePtr->setItem(theItem);
        inorder(visit, treePtr->getRightChildPtr());
    }
}


template<class ItemType>
BinaryNode<ItemType>* BinaryNodeTree<ItemType>::RemoveValue(BinaryNode<ItemType>* subTreePtr, ItemType target, bool&success)
{
    if(subTreePtr == nullptr)
    {
        success = false;
        return nullptr;
    }
    else if (subTreePtr->getItem() == target)
    {
        subTreePtr = removeNode(subTreePtr);
        success = true;
        return subTreePtr;
    }
    else if (subTreePtr->getItem() > target)
    {
        BinaryNode<ItemType>* tempPtr;
        tempPtr = removeValue(subTreePtr->getLeftChildPtr(), target, success);
        subTreePtr->setLeftChildPtr(tempPtr);
        return subTreePtr;
    }
    else
    {
        BinaryNode<ItemType>* tempPtr;
        tempPtr = removeValue(subTreePtr->getRightChildPtr(), target, success);
        subTreePtr->setRightChildPtr(tempPtr);
        return subTreePtr;
    }
}

template<class ItemType>
BinaryNode<ItemType>*  removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType& theLowerNode)
{
    if (nodePtr->getLeftChildPtr() == nullptr)
    {
        theLowerNode = nodePtr->getItem();
        return removeNode(nodePtr);
    }
    else
    {
        BinaryNode<ItemType>* tempPtr;
        tempPtr = removeLeftmostNode(nodePtr->getLeftChildPtr(),theLowerNode);
        nodePtr->setLeftChildPtr(tempPtr);
        return nodePtr;
    }
}
