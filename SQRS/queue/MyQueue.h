#ifndef MYQUEUE_H
#define MYQUEUE_H
#include <iostream>
#include "../node/node.h"
#include "../linked_list_functions/linkedlistfunctionsTemplated.h"
using namespace std;
template <typename T>
class Queue
{
public:
    class Iterator
    {
    public:
        friend class Queue;            // give access to list to access _ptr
        Iterator() { _ptr = nullptr; } // default ctor
        Iterator(node<T> *p)           // Point Iterator to where  p is pointing to
        {
            _ptr = p;
        }

        T &operator*() { return _ptr->_item; } // dereference operator
        const T &operator*() const { return _ptr->_item; }

        // T *operator->() { return &(_ptr->_item); } // member access operator // & returns address and * the item
        // const T *operator->() const { return &(_ptr->_item); }

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
        node<T> *_ptr; // pointer being encapsulated
    };

    Queue();
    Queue(const Queue<T> &copyMe);
    ~Queue();
    Queue &operator=(const Queue<T> &RHS);

    bool empty();
    T front();
    T back();

    void push(T item);
    T pop();

    Iterator begin() const; // Iterator to the head node
    Iterator end() const;   // Iterator to NULL
    void print_pointers();
    int size() const { return _size; }
    template <typename TT>
    friend ostream &operator<<(ostream &outs, const Queue<TT> &printMe);

private:
    node<T> *_front;
    node<T> *_rear;
    int _size;
};

template <typename T>
Queue<T>::Queue()
{
    _front = nullptr;
    _rear = nullptr;
    _size = 0;
}

template <typename T>
Queue<T>::Queue(const Queue<T> &copyMe)
{
    // if (_front != nullptr)
    // {
    //     _clear_list(_front);
    // }
    _front = nullptr;
    _rear = nullptr;

    _rear = _copy_list(_front, copyMe._front);
    _size = copyMe._size;
}

template <typename T>
Queue<T>::~Queue()
{
    _clear_list(_front);
    _rear = nullptr;
}

template <typename T>
Queue<T> &Queue<T>::operator=(const Queue<T> &RHS)
{
    if (this == &RHS)
    {
        return *this;
    }
    _clear_list(_front);
    _rear = _copy_list(_front, RHS._front);
    _size = RHS._size;
    return *this;
}

template <typename T>
bool Queue<T>::empty()
{
    if (_front == nullptr)
    {
        return true;
    }
    return false;
}

template <typename T>
T Queue<T>::front()
{
    if (_front != nullptr)
    {
        return _front->_item;
    }
    else
    {
        return T();
    }
}

template <typename T>
T Queue<T>::back()
{
    return _rear->_item;
}

template <typename T>
void Queue<T>::push(T item)
{
    _rear = _insert_after(_front, _rear, item);
    _size++;
}

template <typename T>
T Queue<T>::pop()
{
    assert(!empty() && "cannot pop an empty queue");
    // if (_front == nullptr)
    // {

    //     _rear = nullptr;
    //     return T();
    // }
    if (_front->_next == nullptr) // && _front == _rear)
    {
        _rear = nullptr;
    }
    _size--;
    return _delete_node(_front, _front);
}

template <typename T>
typename Queue<T>::Iterator Queue<T>::begin() const
{
    return Iterator(_front);
}

template <typename T>
typename Queue<T>::Iterator Queue<T>::end() const
{
    return Iterator(nullptr);
}

template <typename T>
void Queue<T>::print_pointers()
{
}

template <typename TT>
ostream &operator<<(ostream &outs, const Queue<TT> &printMe)
{
    outs << "Queue:Head->";
    _print_list(printMe._front);
    return outs;
}
#endif