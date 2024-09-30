#ifndef MYSTACK_H
#define MYSTACK_H
#include <iostream>
#include "../node/node.h"
#include "../linked_list_functions/linkedlistfunctionsTemplated.h"
using namespace std;
template <typename ITEM_TYPE>
class Stack
{
public:
    class Iterator
    {
    public:
        friend class Stack;            // give access to list to access _ptr
        Iterator() { _ptr = nullptr; } // default ctor
        Iterator(node<ITEM_TYPE> *p)   // Point Iterator to where  p is pointing to
        {
            _ptr = p;
        }

        ITEM_TYPE operator*() { return _ptr->_item; } // dereference operator

        const ITEM_TYPE &operator*() const { return _ptr->_item; }

        // ITEM_TYPE *operator->() { return &(_ptr->_item); }

        // const ITEM_TYPE *operator->() const { return &(_ptr->_item); }

        // & returns address and * the item
        operator bool() // casting operator: true if _ptr not NULL
        {               //       this turned out to be a pain!
            if (_ptr != nullptr)
            {
                return true;
            }
            return false;
        }

        bool is_null() // true if _ptr is NULL
        {
            if (_ptr == nullptr)
            {
                return true;
            }
            return false;
        }

        friend bool operator!=(const Iterator &left, const Iterator &right) // true if left != right
        {
            return left._ptr != right._ptr;
        }

        friend bool operator==(const Iterator &left, const Iterator &right) // true if left == right
        {
            return left._ptr == right._ptr;
        }

        Iterator &operator++() // member operator:++it // or ++it = new_value
        {
            _ptr = _ptr->_next;
            return *this;
        }

        friend Iterator operator++(Iterator &it, int unused) // friend operator: it++
        {
            assert(it._ptr != NULL);
            Iterator hold;
            hold = it;
            it._ptr = it._ptr->_next;
            return hold;
        }

    private:
        node<ITEM_TYPE> *_ptr; // pointer being encapsulated
    };

    Stack();
    Stack(const Stack<ITEM_TYPE> &copyMe);
    ~Stack();
    Stack<ITEM_TYPE> &operator=(const Stack<ITEM_TYPE> &RHS);
    ITEM_TYPE top();
    bool empty();
    void push(ITEM_TYPE item);
    ITEM_TYPE pop();
    template <typename T>
    friend ostream &operator<<(ostream &outs, const Stack<T> &printMe);
    Iterator begin() const; // Iterator to the head node
    Iterator end() const;   // Iterator to NULL
    int size() const { return _size; }

private:
    node<ITEM_TYPE> *_top;
    int _size;
};

template <typename ITEM_TYPE>
Stack<ITEM_TYPE>::Stack()
{
    _top = nullptr;
    _size = 0;
}

template <typename ITEM_TYPE>
Stack<ITEM_TYPE>::Stack(const Stack<ITEM_TYPE> &copyMe)
{
    // if (_top != nullptr)
    // {
    //     _clear_list(_top);
    // }
    _top = nullptr;
    _top = _copy_list(copyMe._top);
    _size = copyMe._size;
}

template <typename ITEM_TYPE>
Stack<ITEM_TYPE>::~Stack()
{
    _clear_list(_top);
    //_top = nullptr;
}

template <typename ITEM_TYPE>
Stack<ITEM_TYPE> &Stack<ITEM_TYPE>::operator=(const Stack<ITEM_TYPE> &RHS)
{
    if (this == &RHS)
    {
        return *this;
    }

    _clear_list(_top);
    _top = _copy_list(_top, RHS._top);
    _size = RHS._size;
    return *this;
}

template <typename ITEM_TYPE>
ITEM_TYPE Stack<ITEM_TYPE>::top()
{
    if (_top != nullptr)
    {
        return _top->_item;
    }
    else
    {
        return ITEM_TYPE();
    }
}

template <typename ITEM_TYPE>
bool Stack<ITEM_TYPE>::empty()
{
    if (_top == nullptr)
    {
        return true;
    }
    return false;
}

template <typename ITEM_TYPE>
void Stack<ITEM_TYPE>::push(ITEM_TYPE item)
{
    _top = _insert_head(_top, item);
    _size++;
}

template <typename ITEM_TYPE>
ITEM_TYPE Stack<ITEM_TYPE>::pop()
{
    if (_top == nullptr)
    {
        return ITEM_TYPE();
    }
    _size--;
    return _delete_node(_top, _top);
}

template <typename T>
ostream &operator<<(ostream &outs, const Stack<T> &printMe)
{
    outs << "Stack:Head-> ";
    _print_list(printMe._top);
    return outs;
}

template <typename ITEM_TYPE>
typename Stack<ITEM_TYPE>::Iterator Stack<ITEM_TYPE>::begin() const
{
    return Iterator(_top);
}

template <typename ITEM_TYPE>
typename Stack<ITEM_TYPE>::Iterator Stack<ITEM_TYPE>::end() const
{
    return Iterator(nullptr);
}
#endif