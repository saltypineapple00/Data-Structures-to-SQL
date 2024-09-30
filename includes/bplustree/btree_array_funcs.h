#ifndef BTREE_ARRAY_FUNCS_H
#define BTREE_ARRAY_FUNCS_H
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

template <class T>
T maximal(const T &a, const T &b); // return the larger of the two items

template <class T>
void swap(T &a, T &b); // swap the two items

template <class T>
int index_of_maximal(T data[], int n); // return index of the largest item in data

template <class T>
void ordered_insert(T data[], int &n, T entry); // insert entry into the sorted array
                                                // data with length n

template <class T>
int first_ge(const T data[], int n, const T &entry); // return the first element in data that is
                                                     // not less than entry

template <class T>
void attach_item(T data[], int &n, const T &entry); // append entry to the right of data

template <class T>
void insert_item(T data[], int i, int &n, T entry); // insert entry at index i in data

template <class T>
void detach_item(T data[], int &n, T &entry); // remove the last element in data and place
                                              // it in entry

template <class T>
void delete_item(T data[], int i, int &n, T &entry); // delete item at index i and place it in entry

template <class T>
void merge(T data1[], int &n1, T data2[], int &n2); // append data2 to the right of data1

template <class T>
void split(T data1[], int &n1, T data2[], int &n2); // move n/2 elements from the right of data1
                                                    // and move to data2

template <class T>
void copy_array(T dest[], const T src[],
                int &dest_size, int src_size); // copy src[] into dest[]

template <class T>
void print_array(const T data[], int n, int pos = -1); // print array data

template <class T>
bool is_gt(const T data[], int n, const T &item); // item > all data[i]

template <class T>
bool is_le(const T data[], int n, const T &item); // item <= all data[i]

//-------------- Vector Extra operators: ---------------------

template <typename T>
ostream &operator<<(ostream &outs, const vector<T> &list); // print vector list

template <typename T>
vector<T> _union(vector<T> r1, vector<T> r2);

template <typename T>
vector<T> _intersection(vector<T> r1, vector<T> r2);

template <typename T, typename K>
vector<T> &operator+=(vector<T> &list, const K &addme); // list.push_back addme

template <typename T>
vector<T> &operator+=(vector<T> &list, const vector<T> &addme);

//--------------------------------DEFINITIONS--------------------------------------------------
template <class T>
T maximal(const T &a, const T &b) // return the larger of the two items
{
    return max(a, b);
}

template <class T>
void swap(T &a, T &b) // swap the two items
{
    T temp;
    temp = a;
    a = b;
    b = temp;
}

template <class T>
int index_of_maximal(T data[], int n) // return index of the largest item in data
{
    // NOT WORKING
    T temp = data[0];
    int index = 0;
    for (int i = 1; i < n; i++)
    {
        if (data[i] < temp)
        {
            temp = data[1];
            index = i;
        }
    }
    return index;
}

template <class T>
void ordered_insert(T data[], int &n, T entry) // insert entry into the sorted array data with length n
{
    int index = first_ge(data, n, entry);
    insert_item(data, index, n, entry);
}

template <class T>
int first_ge(const T data[], int n, const T &entry) // return the first element in data that is not less than entry
{
    for (int i = 0; i < n; i++)
    {
        if (!(data[i] < entry)) // when there is no data bigger than entry return the last subset which is the size
        {
            return i;
        }
        // if (i == n - 1 && data[i] < entry) // if (data[i] < entry)
        // {
        //     return n;
        // }
    }
    // if you are here, size was zero
    return n;
}

template <class T>
void attach_item(T data[], int &n, const T &entry) // append entry to the right of data
{
    data[n] = entry;
    n++;
}

template <class T>
void insert_item(T data[], int i, int &n, T entry) // insert entry at index i in data
{
    // cout << "------------ARRAY FUNCTIONS" << endl;
    // cout << "insert item: i: " << i << ", n: " << n << endl;
    // cout << "The entry in insert is " << entry << endl;
    if (n == 0)
    {
        data[0] = entry;
        n++;
        // cout << __LINE__ << endl;
    }
    else
    {
        // print_array(data, n, 0);
        n++;
        for (int j = n - 1; j > i; j--)
        {
            // cout << "Before shifting" << endl;
            // print_array(data, n, 0);
            data[j] = data[j - 1];
            // cout << "after shifting" << endl;
            // print_array(data, n, 0);
        }
        // data[i] = entry;

        // cout << "done with loop in array insert" << endl;
    }
    // cout << "I am here!" << endl;
    data[i] = entry;
}

template <class T>
void detach_item(T data[], int &n, T &entry) // remove the last element in data and place it in entry
{
    entry = data[n - 1];
    n--;
}

template <class T>
void delete_item(T data[], int i, int &n, T &entry) // delete item at index i and place it in entry
{
    // cout << "Got into delete item" << endl;
    entry = data[i];
    if (n != 0)
    {
        for (int j = i; j < n; j++)
        {
            data[j] = data[j + 1];
        }
    }
    n--;
    // cout << "Done with delete item" << endl;
}

template <class T>
void merge(T data1[], int &n1, T data2[], int &n2) // append data2 to the right of data1
{
    int i = 0;
    while (i < n2)
    {
        data1[n1] = data2[i];
        i++;
        n1++;
    }
    n2 = 0;
}

template <class T>
void split(T data1[], int &n1, T data2[], int &n2) // move n/2 elements from the right of data1 and move to data2
{
    int i = n1 / 2;
    n2 = 0;
    if (n1 % 2 != 0)
    {
        for (int j = i + 1; j < n1; j++)
        {
            data2[n2] = data1[j];
            n2++;
        }
    }
    else if (n1 % 2 == 0)
    {
        for (int j = i; j < n1; j++)
        {
            data2[n2] = data1[j];
            n2++;
        }
    }
    n1 = n1 - i;
}

template <class T>
void copy_array(T dest[], const T src[], int &dest_size, int src_size) // copy src[] into dest[]
{
    for (int i = 0; i < src_size; i++)
    {
        dest[i] = src[i];
    }
    dest_size = src_size;
}

template <class T>
void print_array(const T data[], int n, int pos) // print array data
{
    for (int i = 0; i < n; i++)
    {
        cout << "[" << data[i] << "] ";
    }
    cout << endl;
}

template <class T>
bool is_gt(const T data[], int n, const T &item) // item > all data[i]
{
    bool check;
    for (int i = 0; i < n; i++)
    {
        if (data[i] > item)
        {
            check = true;
        }
        if (data[i] <= item)
        {
            check = false;
        }
    }
    return check;
}

template <class T>
bool is_le(const T data[], int n, const T &item) // item <= all data[i]
{
    bool check;
    for (int i = 0; i < n; i++)
    {
        if (data[i] > item)
        {
            check = false;
        }
        if (data[i] <= item)
        {
            check = true;
        }
    }
    return check;
}

template <typename T>
ostream &operator<<(ostream &outs, const vector<T> &list) // print vector list
{
    for (int i = 0; i < list.size(); i++)
    {
        cout << "[" << list[i] << "] ";
    }
    return outs;
}

template <typename T, typename K>
vector<T> &operator+=(vector<T> &list, const K &addme) // list.push_back addme
{
    list.push_back(addme);
    return list;
}

template <typename T>
vector<T> &operator+=(vector<T> &list, const vector<T> &addme) // list.push_back another list
{
    for (int i = 0; i < addme.size(); i++)
    {
        list.push_back(addme.at(i));
    }
    return list;
}
template <typename T>
vector<T> _union(vector<T> r1, vector<T> r2)
{
    vector<T> record_list;
    sort(r1.begin(), r1.end());
    sort(r2.begin(), r2.end());
    set_union(r1.begin(), r1.end(), r2.begin(), r2.end(), back_inserter(record_list));
    return record_list;
}

template <typename T>
vector<T> _intersection(vector<T> r1, vector<T> r2)
{
    vector<T> record_list;
    sort(r1.begin(), r1.end());
    sort(r2.begin(), r2.end());
    set_intersection(r1.begin(), r1.end(), r2.begin(), r2.end(), back_inserter(record_list));
    return record_list;
}
#endif