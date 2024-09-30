#ifndef LIST_H
#define LIST_H

#include "../node/node.h"
#include <iostream>
#include <assert.h>
using namespace std;

// Linked List General Functions:
template <typename T>
void _print_list(node<T> *head);

// recursive fun! :)
template <typename T>
void _print_list_backwards(node<T> *head);

// return ptr to key or NULL
template <typename T>
node<T> *_search_list(node<T> *head, T key);

template <typename T>
node<T> *_insert_head(node<T> *&head, T insert_this);

// insert after ptr: insert head if marker null
template <typename T>
node<T> *_insert_after(node<T> *&head, node<T> *after_this, T insert_this);

// insert before ptr: insert head if marker null
template <typename T>
node<T> *_insert_before(node<T> *&head, node<T> *before_this, T insert_this);

// ptr to previous node
template <typename T>
node<T> *_previous_node(node<T> *prev_to_this);

// delete, return item
template <typename T>
T _delete_node(node<T> *&head, node<T> *delete_this);

// duplicate the list...
template <typename T>
node<T> *_copy_list(node<T> *head);

// duplicate the list, return pointer to last node in dest...
//      use this function in your queue big three
template <typename T>
node<T> *_copy_list(node<T> *&dest, node<T> *src);

// delete all the nodes
template <typename T>
void _clear_list(node<T> *&head);

//_item at this position
template <typename T>
T &_at(node<T> *head, int pos);

template <typename T>
node<T> *_last_node(node<T> *head);

////////////////////////////////////////////////////////

// Linked List General Functions:
template <typename T>
void _print_list(node<T> *head)
{
    node<T> *walker = head;
    while (walker != nullptr)
    {
        cout << *walker << "    ";
        walker = walker->_next;
    }
    cout << "|||" << endl;
}

// recursive fun! :)
template <typename T>
void _print_list_backwards(node<T> *head)
{
    node<T> *walker = head;
    if (walker->_next == nullptr)
    {
        walker = walker->_prev;
        cout << *walker;
    }
}

// return ptr to key or NULL
template <typename T>
node<T> *_search_list(node<T> *head, T key)
{
    node<T> *walker = head;
    if (head == nullptr)
    {
        return nullptr;
    }

    while (walker != nullptr)
    {
        if (walker->_item == key)
        {
            return walker;
        }
        walker = walker->_next;
    }

    return nullptr; // this is for when there is no search in the list
}

template <typename T>
node<T> *_insert_head(node<T> *&head, T insert_this)
{
    // node<T> *n = new node<T>(insert_this, head);

    // if (head != nullptr)
    // {
    //     head->_prev = n;
    // }
    // n->_next = head;
    // head = n;
    // n->_prev = NULL;
    // return head;
    node<T> *temp = new node<T>(insert_this, head);
    {
        if (head == nullptr) // empty list
        {
            head = temp;
            return head;
        }

        head->_prev = temp; // 4. point first node to new node
        head = temp;
        return head;
    }
}

// insert after ptr: insert head if marker null
template <typename T>
node<T> *_insert_after(node<T> *&head, node<T> *after_this, T insert_this)
{
    node<T> *n = new node<T>(insert_this);
    if (after_this == nullptr)
    {
        return _insert_head(head, insert_this);
    }
    else
    {
        node<T> *temp = after_this->_next;
        n->_prev = after_this;
        n->_next = temp;
        after_this->_next = n;
        if (temp != nullptr)
        {
            temp->_prev = n;
        }
        return n;
    }
}

// insert before ptr: insert head if marker null
template <typename T>
node<T> *_insert_before(node<T> *&head, node<T> *before_this, T insert_this)
{
    node<T> *n = new node<T>(insert_this);
    node<T> *walker1;
    if (before_this->_prev == nullptr)
    {
        return _insert_head(head, insert_this);
    }
    walker1 = before_this->_prev;
    n->_prev = walker1;
    n->_next = before_this;
    walker1->_next = n;
    before_this->_prev = n;

    return n;
}

// ptr to previous node
template <typename T>
node<T> *_previous_node(node<T> *prev_to_this)
{
    node<T> *temp = prev_to_this->_prev;
    return temp;
}

// delete, return item
template <typename T>
T _delete_node(node<T> *&head, node<T> *delete_this)
{
    // cout << "calling delete" << endl;
    T itemReturn;
    if (head == nullptr) // when list is empty
    {
        // cout << "empty" << endl;
        return T();
    }

    else if (delete_this == head) // deleting the head
    {
        node<T> *walker = head;

        if (walker->_next != nullptr) // when the list is not empty prev points to null
        {
            // cout << "head case" << endl;
            walker = walker->_next;
            // cout << "here0" << endl;
            head = walker;
            // cout << "here1" << endl;
            itemReturn = delete_this->_item;
            // cout << "here2" << endl;
            delete delete_this;
            // cout << "here3" << endl;
            head->_prev = nullptr;
            // cout << "here4" << endl;
            return itemReturn;
        }

        if (walker->_next == nullptr) // one node
        {
            // cout << "one node case" << endl;
            head = nullptr;
            itemReturn = delete_this->_item;
            delete delete_this;
            return itemReturn;
        }
    }

    else if (delete_this->_next == nullptr) // the last node
    {
        // cout << "last node case" << endl;
        node<T> *walker1 = delete_this->_prev;
        walker1->_next = nullptr;
        itemReturn = delete_this->_item;
        delete delete_this;
        return itemReturn;
    }

    else // deleting the node in the linked list
    {
        // cout << "middle node case" << endl;
        node<T> *walker1 = delete_this->_prev;
        node<T> *walker2 = delete_this->_next;

        walker1->_next = walker2;
        walker2->_prev = walker1;

        itemReturn = delete_this->_item;
        delete delete_this;
        return itemReturn;
    }
}

// duplicate the list...
template <typename T>
node<T> *_copy_list(node<T> *head)
{
    node<T> *n = nullptr;
    if (head == nullptr)
    {
        return nullptr;
    }

    // n = new node<T>(head->_item);
    _insert_head(n, head->_item);

    node<T> *walker = head->_next;
    node<T> *temp = n;
    while (walker != nullptr)
    {
        temp = _insert_after(n, temp, walker->_item);
        walker = walker->_next;
    }
    return n;
}
// duplicate the list, return pointer to last node in dest...
//      use this function in your queue big three
template <typename T>
node<T> *_copy_list(node<T> *&dest, node<T> *src)
{
    dest = _copy_list(src);
    return _last_node(dest);
}

// delete all the nodes
template <typename T>
void _clear_list(node<T> *&head)
{
    // cout << "calling clear" << endl;
    // node<T> *walker1 = head;
    // node<T> *walker2 = head;
    // while (walker1 != nullptr && walker1->_next != nullptr)
    // {
    //     // cout << "in the clear loop" << endl;
    //     walker2 = walker2->_next;
    //     _delete_node(head, walker1);
    //     // cout << "after calling delete in clear" << endl;
    //     walker1 = walker2;
    //     //_print_list(head);
    // }
    // delete walker1;
    // walker2 = nullptr;
    // head = nullptr; // no more first node so point to null for empty

    node<T> *walker1 = head;
    node<T> *walker2 = head;
    if (head != nullptr)
    {
        while (walker1 != nullptr)
        {
            walker1 = walker1->_next;
            delete walker2;
            walker2 = walker1;
        }
        head = nullptr;
    }
}

template <typename T>
node<T> *_last_node(node<T> *head)
{
    // assert(head && "last node of an empty list!");
    if (head == nullptr)
    {
        return nullptr;
    }
    node<T> *walker = head;
    while (walker->_next != nullptr)
    {
        walker = walker->_next;
    }
    return walker;
}

//_item at this position
template <typename T>
T &_at(node<T> *head, int pos)
{
    assert(pos >= 0);
    node<T> *walker = head;
    int i = 0;
    while (walker != nullptr && i < pos)
    {
        walker = walker->_next;
        i++;
    }
    T *itemReturn = &(walker->_item);
    return *itemReturn;
}

#endif