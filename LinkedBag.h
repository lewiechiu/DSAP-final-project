#ifndef BAG_H_INCLUDED
#define BAG_H_INCLUDED
using namespace std;

template <class Type>
class Node
{
public:
    /*VARIABLES*/
    Type item;
    //value of the Node. depend on the type we input
    Node<Type>* next;
    //save the memory location of next Node

    /*CONSTRUCTOR & DESSTRUCTOR*/
    Node();
    Node(const Type& anItem);   //copy constructor
    Node(const Type& anItem, const Node<Type>* nextNodeprt);    //copy constructor
    //@param: value of <Type> item
    //@param: pointer pointing to the next <Type> Node
    Node<Type>& operator=(const Node<Type> other);  //assignment operation overload

    /*FUNCTION*/
    void setItem(const Type& anItem);
    //set the value of the Node
    //@param:  <Type> item
    void setNext(Node<Type>* nextNodeprt);
    //let the next pointer point to the memory location of next Node
    //@param:  pointer pointing to the next <Type> item
    Type getItem() const ;
    //get the value of that Node
    Node<Type>* getNext() const ;
    //get the memory location of next Node
    bool operator==(const Node<Type> other) const;
    //equal comparison operation overload, comparing the value of Node and the memory location of next Node
    //@param: <Type> Node object
};


/*----------------------------------------------------Myexception.hpp--------------------------------------------------------*/

template<typename Type>
class LinkedBag
{
protected:
/*----Protected Data-----*/
    Node<Type>* headptr;
    //indicate the head of the LinkedBag
    int item_count;
    //the total amount of Nodes inside the LinkedBag

/*----Protected Function-----*/
    Node<Type>* getPointer(const Type& goalItem) const ;
    //get the memory location of the Node which has the same <Type> item as the given one
    //@param: <Type> item
public:
/*-----Constructor-----*/
    LinkedBag();
    LinkedBag(const LinkedBag<Type>& abag); //copy constructor
    ~LinkedBag();

/*-----public function-----*/
    void add(const Type &addItem );
    //add a Node into the LinkedBag with its <Type >item value
    //@param: <Type> item
    void remove(const Type& removeItem) ;
    //remove certain Node which has same <Type> item as the given one from the LinkedBag
    //@param: <Type> Item
    int getSize() const;
    //get the size of the LinkedBag
    bool isEmpty() const;
    //check if the LinkedBag is empty
    bool contains(const Type& goalItem);
    //check if the LinkedBag contains the Node which has same <Type> item as the given one
    //@para: <Type> item
    void clearAll();
    //delete all the pointer between Nodes

    Type operator[](int index)const;
    //if index out of range, it will throw Myexception

    LinkedBag<Type>& operator=(const LinkedBag<Type>& abag);
    //assignment operator. do a deep copy

    int get_itemCount();
};


#endif // BAG_H_INCLUDED
