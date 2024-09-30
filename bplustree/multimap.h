#ifndef MULTIMAP_H
#define MULTIMAP_H
#include <cassert>
#include <iostream>
#include <iomanip>
#include <vector>
#include "../../includes/bplustree/btree_array_funcs.h"
#include "../../includes/bplustree/bplustree.h"
using namespace std;

template <typename K, typename V>
struct MPair
{
    K key;
    vector<V> value_list;

    //--------------------------------------------------------------------------------
    /*      MPair CTORs:
     *  must have these CTORs:
     *  - default CTOR / CTOR with a key and no value: this will create an empty vector
     *  - CTOR with a key AND a value: pushes the value into the value_list
     *  _ CTOR with a key and a vector of values (to replace value_list)
     */
    //--------------------------------------------------------------------------------
    MPair(const K &k = K())
    {
        key = k;
    }
    MPair(const K &k, const V &v)
    {
        key = k;

        value_list += v;
    }
    MPair(const K &k, const vector<V> &vlist)
    {
        key = k;
        value_list.clear();
        for (int i = 0; i < vlist.size(); i++)
        {
            value_list.push_back(vlist[i]);
        }
    }
    //--------------------------------------------------------------------------------

    // You'll need to overlod << for your vector:
    friend ostream &operator<<(ostream &outs, const MPair<K, V> &print_me)
    {
        outs << print_me.key << setw(5) << ": " << print_me.value_list; // << " " << endl;
        // cout << endl;
        return outs;
    }

    friend bool operator==(const MPair<K, V> &lhs, const MPair<K, V> &rhs)
    {
        return lhs.key == rhs.key;
    }
    friend bool operator<(const MPair<K, V> &lhs, const MPair<K, V> &rhs)
    {
        return lhs.key < rhs.key;
    }
    friend bool operator<=(const MPair<K, V> &lhs, const MPair<K, V> &rhs)
    {
        return lhs.key <= rhs.key;
    }
    friend bool operator>(const MPair<K, V> &lhs, const MPair<K, V> &rhs)
    {
        return lhs.key > rhs.key;
    }
    friend MPair<K, V> operator+(const MPair<K, V> &lhs, const MPair<K, V> &rhs) // append teh entry to the end
    {
        MPair<K, V> newm(lhs.key, lhs.value_list);
        for (int i = 0; i < rhs.value_list.size(); i++)
        {
            newm.value_list.push_back(rhs.value_list[i]);
        }
        return newm;
    }
};

template <typename K, typename V>
class MMap
{
public:
    typedef BPlusTree<MPair<K, V>> map_base;
    class Iterator
    {
    public:
        friend class MMap;
        Iterator(typename map_base::Iterator it = typename map_base::Iterator())
        {
            _it = it;
        }
        Iterator operator++(int unused)
        {
            Iterator temp = _it;
            ++_it;
            return temp;
        }
        Iterator operator++()
        {
            ++_it;
            return *this;
        }
        MPair<K, V> operator*()
        {
            return *_it;
        }
        friend bool operator==(const Iterator &lhs, const Iterator &rhs)
        {
            return lhs._it == rhs._it;
        }
        friend bool operator!=(const Iterator &lhs, const Iterator &rhs)
        {
            return lhs._it != rhs._it;
        }

    private:
        typename map_base::Iterator _it;
    };

    MMap() {}

    //  Iterators
    Iterator begin()
    {
        return Iterator(mmap.begin());
    }
    Iterator end()
    {
        return Iterator(mmap.end());
    }

    void print_lookup() // multimap function to print mmap as a table
    {
        for (Iterator it = begin(); it != end(); ++it)
        {
            cout << *it << setw(5);
        }
    }
    //  Capacity
    int size() const
    {
        return mmap.size();
    }
    bool empty() const
    {
        if (size() == 0)
        {
            return true;
        }
        return false;
    }

    //  Element Access
    const vector<V> &operator[](const K &key) const
    {
        return at(key);
    }
    vector<V> &operator[](const K &key)
    {
        // return mmap.get(key).value_list;
        return at(key);
    }

    vector<V> &at(const K &key)
    {
        return mmap.get(key).value_list;
    }
    const vector<V> &at(const K &key) const
    {
        return mmap.get(key).value_list;
    }
    //  Modifiers
    void insert(const K &k, const V &v)
    {
        mmap.insert(MPair<K, V>(k, v));
    }
    void erase(const K &key)
    {
    }
    void clear()
    {
        mmap.clear_tree();
    }

    //  Operations:
    bool contains(const K &key) const
    {
        return mmap.contains(key);
    }
    vector<V> &get(const K &key)
    {
        return mmap.get(key).value_list;
    }

    Iterator find(const K &key)
    {
        return Iterator(mmap.find(key));
    }
    // int count(const K &key);
    //  I have not writtent hese yet, but we will need them:
    int count(const K &key)
    {
        // Iterator it;
        // while (it = begin(), it != end(), it++)
        // {
        //     key_count++;
        // }
        // return key_count;
        return -1;
    }
    Iterator lower_bound(const K &key)
    {
        Iterator it = mmap.end();
        for (it = mmap.begin(); it != mmap.end(); it++)
        {
            if (*it > key)
            {
                return it;
            }
            if (*it == key)
            {
                return it;
            }
        }
        return it;
    }
    Iterator upper_bound(const K &key)
    {
        Iterator it = mmap.end();
        for (it = mmap.begin(); it != mmap.end(); it++)
        {
            if (*it > key)
            {
                return it;
            }
        }
        return it;
    }
    // int equal_range(const K &key)
    // {
    //     return -1;
    // }

    bool is_valid() { return true; }

    friend ostream &operator<<(ostream &outs, const MMap<K, V> &print_me)
    {
        outs << print_me.mmap; // << endl;
        return outs;
    }

private:
    BPlusTree<MPair<K, V>> mmap;
};

#endif