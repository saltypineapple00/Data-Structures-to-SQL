#ifndef BPLUSTREE_H
#define BPLUSTREE_H
#include <cassert>
#include <iostream>
#include <iomanip>
#include "../../includes/bplustree/btree_array_funcs.h"
using namespace std;

template <class T>
class BPlusTree
{
public:
    class Iterator
    {
    public:
        friend class BPlusTree;
        Iterator(BPlusTree<T> *_it = NULL, int _key_ptr = 0) : it(_it), key_ptr(_key_ptr) {}

        T operator*()
        {
            return it->data[key_ptr];
        }

        Iterator operator++(int un_used) // it++
        {
            // cout << "here \t";
            assert(it);
            // cout << "it++!!" << endl;
            Iterator temp = *this;
            //++it;
            this->operator++();
            // if (key_ptr == it->data_count - 1)
            // {
            //     it = it->next;
            //     key_ptr = 0;
            // }
            // else
            // {
            //     key_ptr++;
            // }
            return temp;
            // return temp;
        }

        Iterator operator++() //++it
        {
            // cout << "calling the ++it op" << endl;
            assert(it);
            // assert(key_ptr < it->data_count);
            // key_ptr++;
            if (key_ptr < it->data_count - 1)
                key_ptr++;
            else
            {
                key_ptr = 0;
                it = it->next;
            }
            return *this;
        }

        friend bool operator==(const Iterator &lhs, const Iterator &rhs)
        {
            return (lhs.it == rhs.it) && (lhs.key_ptr == rhs.key_ptr);
        }

        friend bool operator!=(const Iterator &lhs, const Iterator &rhs)
        {
            return !(lhs == rhs);
        }

        void print_Iterator()
        {
            if (it)
            {
                cout << "iterator: ";
                print_array(it->data, it->data_count, key_ptr);
            }
            else
            {
                cout << "iterator: NULL, key_ptr: " << key_ptr << endl;
            }
        }

        bool is_null() { return !it; }
        void info()
        {
            cout << endl
                 << "Iterator info:" << endl;
            cout << "key_ptr: " << key_ptr << endl;
            cout << "it: " << *it << endl;
        }

    private:
        BPlusTree<T> *it;
        int key_ptr;
    };

    BPlusTree(bool dups = false);
    BPlusTree(T *a, int size, bool dups = false);

    // big three:
    BPlusTree(const BPlusTree<T> &other);
    ~BPlusTree();
    BPlusTree<T> &operator=(const BPlusTree<T> &RHS);

    void copy_tree(const BPlusTree<T> &other); // copy other into this object
    void copy_tree(const BPlusTree<T> &other, BPlusTree<T> *&last_node);

    void insert(const T &entry); // insert entry into the tree
    void remove(const T &entry); // remove entry from the tree
    void clear_tree();           // clear this object (delete all nodes etc.)

    bool contains(const T &entry) const; // true if entry can be found
    T &get(const T &entry);              // return a reference to entry
    const T &get(const T &entry) const;  // return a reference to entry
    T &get_existing(const T &entry);     // return a reference to entry
    Iterator find(const T &key);         // return an iterator to this key.
    //                                      //      NULL if not there.
    Iterator lower_bound(const T &key); // return first that goes NOT BEFORE
                                        //  key entry or next if does not
                                        //  exist: >= entry
    Iterator upper_bound(const T &key); // return first that goes AFTER key
                                        // exist or not, the next entry  >entry

    int size() const { return data_count; } // count the number of elements

    bool empty() const; // true if the tree is empty

    void print_tree(int level = 0,
                    ostream &outs = cout) const;
    friend ostream &operator<<(ostream &outs,
                               const BPlusTree<T> &print_me)
    {
        print_me.print_tree(0, outs);
        return outs;
    }

    bool is_valid()
    {
        return true;
    }
    string in_order();
    string pre_order();
    string post_order();

    Iterator begin();
    Iterator end();
    ostream &list_keys(Iterator from = NULL, Iterator to = NULL)
    {
        if (from == NULL)
            from = begin();
        if (to == NULL)
            to = end();
        for (Iterator it = from; it != to; it++)
            cout << *it << " ";
        return cout;
    }

private:
    static const int MINIMUM = 1;
    static const int MAXIMUM = 2 * MINIMUM;

    bool dups_ok;                   // true if duplicate keys are allowed
    int data_count;                 // number of data elementsf
    T data[MAXIMUM + 1];            // holds the keys
    int child_count;                // number of children
    BPlusTree *subset[MAXIMUM + 2]; // subtrees
    BPlusTree *next;
    bool is_leaf() const
    {
        return child_count == 0;
    } // true if this is a leaf node

    T *find_ptr(const T &entry); // return a pointer to this key.
    //  NULL if not there.

    // insert element functions
    void loose_insert(const T &entry); // allows MAXIMUM+1 data elements in
                                       //    the root
    void fix_excess(int i);            // fix excess in child i

    // remove element functions:
    void loose_remove(const T &entry); // allows MINIMUM-1 data elements
                                       //   in the root

    BPlusTree<T> *fix_shortage(int i); // fix shortage in child i
    // and return the smallest key in this subtree
    BPlusTree<T> *get_smallest_node();
    void get_smallest(T &entry);                 // entry := leftmost leaf
    void get_biggest(T &entry);                  // entry := rightmost leaf
    void remove_biggest(T &entry);               // remove the biggest child of tree->entry
    void transfer_left(int i);                   // transfer one element LEFT from child i
    void transfer_right(int i);                  // transfer one element RIGHT from child i
    BPlusTree<T> *merge_with_next_subset(int i); // merge subset i with  i+1
};

template <class T>
BPlusTree<T>::BPlusTree(bool dups)
{
    data_count = 0;
    child_count = 0;
    dups_ok = dups;
    next = nullptr;
}
template <class T>
BPlusTree<T>::BPlusTree(T *a, int size, bool dups)
{
    data_count = 0;
    child_count = 0;
    dups_ok = dups;
    // for (int i = 0; i < MAXIMUM + 2; i++)
    // {
    //     subset[i] = NULL;
    // }
    next = nullptr;
    for (int i = 0; i < size; i++)
    {
        insert(*(a + i));
    }
}

// BIG THREE
template <class T>
BPlusTree<T>::BPlusTree(const BPlusTree<T> &other)
{
    child_count = 0;
    data_count = 0;
    this->next = nullptr;
    copy_tree(other);
}

template <class T>
BPlusTree<T>::~BPlusTree()
{
    clear_tree();
}

template <class T>
BPlusTree<T> &BPlusTree<T>::operator=(const BPlusTree<T> &RHS)
{
    if (this == &RHS)
    {
        return *this;
    }
    if (this != &RHS)
    {
        this->clear_tree();
        copy_tree(RHS); // copies RHS to ME!
        return *this;
    }
    return *this;
}
template <class T>
void BPlusTree<T>::copy_tree(const BPlusTree<T> &other) // copy other into this object
{
    // if (!other.empty())
    // {
    //     copy_array(this->data, other.data, this->data_count, other.data_count);
    //     for (int i = 0; i < other.child_count; i++)
    //     {
    //         this->subset[i] = new BPlusTree<T>();
    //         this->subset[i]->copy_tree(*(other.subset[i]));
    //         child_count++;
    //     }
    // }
    BPlusTree<T> *temp = nullptr;
    copy_tree(other, temp);

    // deal with copying the linked lists too  ?
}
template <class T>
void BPlusTree<T>::copy_tree(const BPlusTree<T> &other, BPlusTree<T> *&last_node)
{
    if (!other.empty())
    {
        dups_ok = other.dups_ok;
        copy_array(data, other.data, data_count, other.data_count);
        child_count = other.child_count;
        next = nullptr;
        for (int i = 0; i < other.child_count; i++)
        {
            subset[i] = new BPlusTree<T>(other.dups_ok);
            subset[i]->copy_tree(*(other.subset[i]), last_node);
        }
        if (other.is_leaf())
        {
            if (last_node)
                last_node->next = this;
            last_node = this;
        }
    }
}

template <class T>
void BPlusTree<T>::insert(const T &entry)
{
    loose_insert(entry);

    if (data_count >= MAXIMUM + 1)
    {
        BPlusTree<T> *growth = new BPlusTree<T>();
        copy_array(growth->data, data, growth->data_count, data_count);
        if (!is_leaf())
        {
            copy_array(growth->subset, subset, growth->child_count, child_count);
        }
        data_count = 0;
        child_count = 1;
        subset[0] = growth;
        fix_excess(0);
    }
}

template <class T>
void BPlusTree<T>::remove(const T &entry) // remove entry from the tree
{

    // cout << "got to remove" << endl;

    loose_remove(entry);
    if (data_count == 0 && !is_leaf()) //<= MINIMUM) //&& child_count =1
    {
        BPlusTree<T> *shrink = subset[0];
        copy_array(data, shrink->data, data_count, shrink->data_count);
        if (!is_leaf())
        {
            copy_array(subset, shrink->subset, child_count, shrink->child_count);
        }
        shrink->data_count = 0;
        shrink->child_count = 0;
        delete shrink;
    }
}
template <class T>
void BPlusTree<T>::clear_tree() // clear this object (delete all nodes etc.)
{
    data_count = 0;
    for (int i = 0; i < child_count; i++)
    {
        if (!is_leaf())
        {
            subset[i]->clear_tree();
            delete subset[i];
            subset[i] = nullptr;
        }
    }
    child_count = 0;
}

template <class T>
bool BPlusTree<T>::contains(const T &entry) const // true if entry can be found
{
    int index = first_ge(data, data_count, entry);
    bool found = (index < data_count && data[index] == entry);

    if (found && is_leaf())
    {
        return true;
    }
    else if (!found && is_leaf())
    {
        return false;
    }
    else if (found && !is_leaf())
    {
        return subset[index + 1]->contains(entry);
    }
    else // if (!found && !is_leaf())
    {
        return subset[index]->contains(entry);
    }
    return false;
}

template <class T>
T &BPlusTree<T>::get(const T &entry) // return a reference to entry
{
    // If entry is not in the tree, add it to the tree
    // assert(contains(entry));
    // cout << "calling get in BplusTree" << endl;
    const bool debug = false;
    if (!contains(entry))
    {
        // cout << "not contain condition" << endl;
        insert(entry);
        // cout << "after inserting :" << entry << endl;
    }

    return get_existing(entry);
}

template <class T>
const T &BPlusTree<T>::get(const T &entry) const // return a reference to entry
{
    assert(contains(entry));

    const bool debug = false;
    int i = first_ge(data, data_count, entry);
    bool found = (i < data_count && data[i] == entry);
    if (is_leaf())
    {
        if (found)
        {
            return &data[i];
        }
        else
        {
            if (debug)
                cout << "get_existing was called with nonexistent entry" << endl;
            assert(found);
        }
    }
    if (found) // inner node
        return subset[i + 1]->get(entry);
    // or just return true?
    else // not found yet...
        return subset[i]->get(entry);
}

template <class T>
T &BPlusTree<T>::get_existing(const T &entry)
{
    // assert that entry is not in the tree.
    // assert(contains(entry));

    // cout << "calling get existing" << endl;
    const bool debug = false;
    int i = first_ge(data, data_count, entry);
    bool found = (i < data_count && data[i] == entry);
    if (is_leaf())
        if (found)
        {
            // cout << "the data is" << data[i] << endl;
            return data[i];
        }
        else
        {
            if (debug)
                cout << "get_existing was called with nonexistent entry" << endl;
            assert(found);
        }
    if (found) // inner node
    {
        return subset[i + 1]->get(entry);
    }
    // or just return true?
    else // not found yet...
    {
        return subset[i]->get(entry);
    }
}

template <class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::find(const T &key) // return an iterator to this key.
{
    // cout << "calling iter find" << endl;
    int index = first_ge(data, data_count, key);
    bool found = (index < data_count && data[index] == key);

    if (found && is_leaf())
    {
        return Iterator(this, index);
    }

    else if (!found && is_leaf())
    {
        return Iterator(NULL);
    }
    else if (found && !is_leaf())
    {
        return subset[index + 1]->find(key);
    }
    else //! found && !leaf
    {
        return subset[index]->find(key);
    }
    return Iterator(NULL);
}

template <class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::lower_bound(const T &key) // return first that goes NOT BEFORE
{
    return NULL;
} //  key entry or next if does not
  //  exist: >= entry
template <class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::upper_bound(const T &key) // return first that goes AFTER key
{
    return NULL;
}

template <class T>
bool BPlusTree<T>::empty() const
{
    return false;
}

template <class T>
void BPlusTree<T>::print_tree(int level, ostream &outs) const
{
    for (int i = data_count; i >= 0; i--)
    {
        if (i < data_count)
        {
            if (i == data_count - 1)
            {
                if (next != nullptr)
                {
                    outs << setw(4 * level) << ""
                         << "^" << endl;
                }
                outs << setw(4 * level) << ""
                     << "⎴" << endl;
            }
            outs << setw(4 * level) << "" << data[i] << endl;
            if (i == 0)
            {
                outs << setw(4 * level) << ""
                     << "⎵" << endl;
            }
        }
        if (!is_leaf())
        {
            subset[i]->print_tree(level + 1, outs);
        }
    }
}

template <class T>
string BPlusTree<T>::in_order()
{
    string save = "";
    for (int i = 0; i <= data_count; i++)
    {
        if (!is_leaf())
        {
            save += subset[i]->in_order();
        }
        if (i < data_count)
        {
            save += to_string(data[i]) + "|";
        }
    }
    return save;
}
template <class T>
string BPlusTree<T>::pre_order()
{
    string save = "";
    for (int i = 0; i <= data_count; i++)
    {
        if (i < data_count)
        {
            save += to_string(data[i]) + "|";
        }
        if (!is_leaf())
        {
            save += subset[i]->pre_order();
        }
    }
    return save;
}
template <class T>
string BPlusTree<T>::post_order()
{
    string save = "";
    for (int i = 0; i <= data_count; i++)
    {
        if (!is_leaf())
        {
            save += subset[i]->post_order();
        }
        if (i < data_count)
        {
            save += to_string(data[i]) + "|";
        }
    }
    return save;
}

template <class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::begin()
{
    BPlusTree<T> *hold = get_smallest_node();

    bool debug = false;
    if (debug)
    {
        cout << "Begin(): child count: " << hold->child_count << endl
             << "Begin(): data count: " << hold->data_count << endl;
    }

    return Iterator(hold, 0);
}

template <class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::end()
{
    return Iterator(nullptr);
}

template <class T>
T *BPlusTree<T>::find_ptr(const T &entry) // return a pointer to this key.
{
    // cout << "calling find_ptr" << endl;
    int index = first_ge(data, data_count, entry);
    bool found = (index < data_count && data[index] == entry);
    if (found && is_leaf())
    {
        // cout << "returning in findptr" << endl;
        return &data[index];
    }

    else if (!found && is_leaf())
    {
        // cout << "NULL in findptr" << endl;
        return NULL;
    }
    else if (found && !is_leaf())
    {
        // cout << "recursion on index +1" << endl;
        subset[index + 1]->find_ptr(entry);
    }
    else
    {
        // cout << "recursion on index" << endl;
        subset[index]->find_ptr(entry);
    }
    return NULL;
}

template <class T>
void BPlusTree<T>::loose_insert(const T &entry)
{
    // cout << "In loose insert" << endl;
    if (data_count == 0)
    {
        // cout << "inserting in empty" << endl;
        data[0] = entry;
        data_count++;
    }

    else
    {
        int index = first_ge(data, data_count, entry);
        bool found = (index < data_count && data[index] == entry);
        if (found && is_leaf())
        {
            // cout << "found && inserting at leaf" << endl;
            data[index] == entry;
        }

        else if (!found && is_leaf())
        {
            // cout << "not found && inserting at leaf" << endl;
            if (index == data_count)
            {
                // cout << "calling attach item" << endl;
                attach_item(data, data_count, entry);
            }
            else // if (index < data_count)
            {
                insert_item(data, index, data_count, entry);
            }
        }
        else if (found && !is_leaf())
        {
            // cout << "recursion for found && !leaf" << endl;
            subset[index + 1]->loose_insert(entry);
            if (subset[index + 1]->data_count >= MAXIMUM + 1)
            {
                fix_excess(index + 1);
            }
        }
        else // if (!found && !is_leaf()) // to get to the end of the tree
        {
            // cout << "recursion for !found && !leaf" << endl;
            subset[index]->loose_insert(entry);
            if (subset[index]->data_count >= MAXIMUM + 1)
            {
                fix_excess(index);
            }
        }
    }
    // cout << "----------------------finished with insert" << endl;
}

template <class T>
void BPlusTree<T>::fix_excess(int i)
{
    T entry;
    insert_item(subset, i + 1, child_count, new BPlusTree<T>());
    split(subset[i]->data, subset[i]->data_count, subset[i + 1]->data, subset[i + 1]->data_count);
    if (!subset[i]->is_leaf())
    {
        split(subset[i]->subset, subset[i]->child_count, subset[i + 1]->subset, subset[i + 1]->child_count);
    }
    detach_item(subset[i]->data, subset[i]->data_count, entry);
    ordered_insert(data, data_count, entry);
    if (subset[i + 1]->is_leaf())
    {
        BPlusTree<T> *hold = subset[i]->next;
        ordered_insert(subset[i + 1]->data, subset[i + 1]->data_count, entry);
        subset[i]->next = subset[i + 1];
        subset[i + 1]->next = hold;
    }
}

// remove element functions:

template <class T>
void BPlusTree<T>::loose_remove(const T &entry)
{
    T save;
    T smallest;
    int index = first_ge(data, data_count, entry);
    bool found = (index < data_count && data[index] == entry);

    if (found && !is_leaf())
    {
        subset[index + 1]->loose_remove(entry);
    }
    else if (found && is_leaf())
    {
        delete_item(data, index, data_count, save);
    }
    else // if (!found() && !is_leaf())
    {
        subset[index]->get_smallest(smallest);
        data[index] = smallest;
        if (subset[index]->data_count < MINIMUM)
        {
            fix_shortage(index);
        }
    }

    if (subset[index]->data_count < MINIMUM)
    {
        fix_shortage(index);
    }
}

template <class T>
BPlusTree<T> *BPlusTree<T>::fix_shortage(int i)
{
    if (i > 0 && subset[i - 1]->data_count > MINIMUM)
    {
        transfer_right(i);
    }
    else if (i < data_count && subset[i + 1]->data_count > MINIMUM)
    {
        transfer_left(i);
    }
    else if (i < data_count)
    {
        merge_with_next_subset(i);
    }
    else // if (i > 0 && subset[i + 1]->data_count >= MINIMUM)
    {
        merge_with_next_subset(i - 1);
    }
}

template <class T>
void BPlusTree<T>::remove_biggest(T &entry)
{
    if (!is_leaf())
    {
        subset[child_count - 1]->remove_biggest(entry);
        if (subset[child_count - 1]->data_count < MINIMUM)
        {
            fix_shortage(child_count - 1);
        }
    }
    else //    if (is_leaf())
    {
        entry = data[data_count - 1];
        data_count--;
    }
}

template <class T>
BPlusTree<T> *BPlusTree<T>::get_smallest_node()
{
    if (!is_leaf())
    {
        return subset[0]->get_smallest_node();
    }
    return this;
}

template <class T>
void BPlusTree<T>::get_smallest(T &entry) // entry := leftmost leaf
{
    if (!is_leaf())
    {
        subset[0]->get_smallest(entry);
    }
    entry = data[0];
}
template <class T>
void BPlusTree<T>::get_biggest(T &entry) // entry := rightmost leaf
{
    if (!is_leaf())
    {
        subset[child_count - 1]->get_smallest(entry);
    }
    entry = data[data_count - 1];
}

template <class T>
void BPlusTree<T>::transfer_left(int i) // transfer one element LEFT from child i
{
    T _delete;
    BPlusTree<T> *hold = subset[i]->next;
    delete_item(subset[i + 1]->data, 0, subset[i + 1]->data_count, _delete);
    ordered_insert(subset[i]->data, subset[i]->data_count, _delete);

    data[i] = _delete;

    subset[i]->next = subset[i + 1];
    subset[i + 1]->next = hold;
}
template <class T>
void BPlusTree<T>::transfer_right(int i) // transfer one element RIGHT from child i
{
    BPlusTree<T> *hold = subset[i]->next;
    T detach;
    detach_item(subset[i - 1]->data, subset[i - 1]->data_count, detach);
    ordered_insert(subset[i]->data, subset[i]->data_count, detach);

    data[i] = detach;
    subset[i]->next = subset[i + 1];
    subset[i + 1]->next = hold;
}

template <class T>
BPlusTree<T> *BPlusTree<T>::merge_with_next_subset(int i) // merge subset i with  i+1
{
    BPlusTree<T> *hold = subset[i]->next;
    T _delete;

    delete_item(data, i, data_count, _delete);
    merge(subset[i]->data, subset[i]->data_count, subset[i + 1]->data, subset[i + 1]->data_count);
    subset[i]->next = subset[i + 1];
    subset[i + 1]->next = hold;
}

#endif