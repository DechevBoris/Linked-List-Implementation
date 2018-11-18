#pragma once
#include <iostream>

using namespace std;

template <typename T>
struct Node
{
    T data;
    Node<T>* next;
    Node(const T& _data, Node<T>* _next);
};

template <typename T>
class LList
{
private:
    Node<T>* first;
    Node<T>* last;
    size_t size;

    void copy(const LList<T>& other);
    void erase();
public:
    LList();
    LList(const LList<T>& other);
    LList& operator=(const LList<T>& other);
    ~LList();

    size_t getSize()const;
    bool empty()const;
    T front()const;
    T back()const;
    Node<T>* getFirst()const;
    Node<T>* getLast()const;
    T operator[](size_t index);

    void push_back(const T& element);
    void push_front(const T& element);
    void pop_back();
    void pop_front();
    void insert(size_t index, const T& element);
    void remove(size_t index);

    void reverse1();

    void print()const;

    //Exercises:


    //Exercise 1: Sum and Product of all the nodes which are less than K
    //in the linked list
    void sumAndProductBelow(int key)const;

    //Exercise 2: Find the second last node of a linked list in single traversal
    T secondLast()const;

    //Exercise 3: Reverse the list
    void reverse2();
};

template <typename T>
Node<T>::Node(const T& _data, Node<T>* _next): data(_data), next(_next){}

template <typename T>
void LList<T>::copy(const LList<T>& other)
{
    if(other.first == nullptr)
    {
        first = nullptr;
        last = nullptr;
        size = 0;
        return;
    }

    first = new Node<T>(other.first->data, nullptr);
    Node<T>* pointerToThis = first;
    Node<T>* pointerToOther = other.first->next;

    while(pointerToOther)
    {
        pointerToThis->next = new Node<T>(pointerToOther.data, pointerToOther->next);
        pointerToThis = pointerToThis->next;
        pointerToOther = pointerToOther->next;
    }
    last = pointerToThis;
    size = other.size;
}

template <typename T>
void LList<T>::erase()
{
    Node<T>* tmp;
    while(first)
    {
        tmp = first->next;
        delete[] first;
        first = tmp;
    }
    last = nullptr;
    size = 0;
}

template <typename T>
LList<T>::LList()
{
    first = nullptr;
    last = nullptr;
    size = 0;
}

template <typename T>
LList<T>::LList(const LList<T>& other)
{
    copy(other);
}

template <typename T>
LList<T>& LList<T>::operator=(const LList<T>& other)
{
    if(this != &other)
    {
        erase();
        copy(other);
    }
    return *this;
}

template <typename T>
LList<T>::~LList()
{
    erase();
}

template <typename T>
size_t LList<T>::getSize()const
{
    return size;
}

template <typename T>
bool LList<T>::empty()const
{
    return size == 0;
}

template <typename T>
T LList<T>::front()const
{
    if(empty())
    {
        throw "Empty list";
    }
    return first->data;
}

template <typename T>
T LList<T>::back()const
{
    if(empty())
    {
        throw "Empty list";
    }
    return last->data;
}

template <typename T>
Node<T>* LList<T>::getFirst()const
{
    if(empty())
    {
        throw "Empty list";
    }
    return first;
}


template <typename T>
Node<T>* LList<T>::getLast()const
{
    if(empty())
    {
        throw "Empty list";
    }
    return last;
}

template <typename T>
T LList<T>::operator[](size_t index)
{
    if(index >= size)
    {
        throw "IndexOutOfBound";
    }
    Node<T>* crr = first;
    size_t it = 0;
    while(it++ != index)
    {
        crr = crr->next;
    }
    return crr->data;
}

template <typename T>
void LList<T>::push_back(const T& element)
{
    Node<T>* newnode = new Node<T>(element, nullptr);
    if(size == 0)
    {
        first = last = newnode;
    }
    else
    {
        last->next = newnode;
        last = newnode;
    }
    size++;
}

template <typename T>
void LList<T>::push_front(const T& element)
{
    Node<T>* newnode = new Node<T>(element, first);
    if(size == 0)
    {
        first = last = newnode;
    }
    else
    {
        first = newnode;
    }
    size++;
}

template <typename T>
void LList<T>::pop_back()
{
    if(size == 0)
    {
        throw "Empty list";
    }
    Node<T>* crr = first;
    Node<T>* prev;
    while(crr->next)
    {
        prev = crr;
        crr = crr->next;
    }
    last = prev;
    prev->next = nullptr;
    delete crr;
    size--;
    if(size == 0)
    {
        first = nullptr;
        last = nullptr;
    }
}

template <typename T>
void LList<T>::pop_front()
{
    Node<T>* save = first->next;
    delete first;
    first = save;
    size--;
}

template <typename T>
void LList<T>::insert(size_t index, const T& element)
{
    if(index > size)
    {
        throw "IndexOutOfBound";
    }
    if(size == 0 )
    {
        push_back(element);
        return;
    }
    if(index == 0)
    {
        push_front(element);
        return;
    }


    Node<T>* crr = first;
    size_t it = 0;
    Node<T>* prev;
    while(it++ < index)
    {
        prev = crr;
        crr = crr->next;
    }
    Node<T>* newnode = new Node<T>(element, crr);
    prev->next = newnode;
    size++;
}

template <typename T>
void LList<T>::remove(size_t index)
{
    if(index >= size)
    {
        throw "IndexOutOfBound";
    }
    if(index == 0)
    {
        pop_front();
        return;
    }
    Node<T>* crr = first;
    Node<T>* prev;
    size_t it = 0;
    while(it++ < index)
    {
        prev = crr;
        crr = crr->next;
    }
    prev->next =crr->next;
    delete crr;
    size--;
}

template <typename T>
void LList<T>::reverse1()
{
    Node<T>* crr = first;
    Node<T>* nxt = nullptr;
    Node<T>* prev = nullptr;

    last = first;
    while(crr)
    {
        nxt = crr->next;
        crr->next = prev;
        prev = crr;
        crr = nxt;
    }
    first = prev;
}

template <typename T>
void LList<T>::print()const
{
    if(!empty())
    {
        Node<T>* crr = first;
        while(crr)
        {
            if(crr == last)
            {
                cout << crr->data << endl;
            }
            else
            {
                cout << crr->data << ", ";
            }
            crr = crr->next;
        }
    }
}

//Exercises:


    //Exercise 1: Sum and Product of all the nodes which are less than K
    //in the linked list
template <typename T>
void LList<T>::sumAndProductBelow(int key)const
{
    Node<int>* crr = first;
    int sum = 0, product = 1;
    while(crr)
    {
        if(crr->data < key)
        {
            sum += crr->data;
            product *= crr->data;
        }
        crr = crr->next;
    }
    cout << "Sum: " << sum << "\nProduct: " << product << endl;
}


//Exercise 2: Find the second last node of a linked list in single traversal
template <typename T>
T LList<T>::secondLast()const
{
    if(size < 2)
    {
        throw "Size less than 2";
    }
    Node<T>* crr = first;
    while(crr->next->next)
    {
        crr = crr->next;
    }
    return crr->data;
}


//Exercise 3: Reverse the list
template <typename T>
void LList<T>::reverse2()
{
    Node<T>* crr = first->next;
    Node<T>* tmp = first;
    last = first;
    while(crr)
    {
        push_front(crr->data);
        Node<T>* save = crr->next;
        delete crr;
        crr = save;
        tmp->next = crr;
    }
}
