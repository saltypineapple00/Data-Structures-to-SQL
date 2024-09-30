#ifndef FILE_RECORD_H
#define FILE_RECORD_H

#include <iostream>
#include <iomanip>
#include <string.h>
#include <vector>
#include "utilities.h"

using namespace std;

class FileRecord
{
public:
    // when you construct a FileRecord, it's either empty or it
    //   contains a word
    FileRecord()
    {
        for (int i = 0; i < MAX + 1; i++)
        {
            for (int j = 0; j < MAX + 1; j++)
            {
                _record[i][j] = '\0';
            }
        }
        recno = -1;
        //['\0'|  | G | a | r | b | a   |  g  |  e |    ]
    }

    FileRecord(vector<string> str)
    {
        for (int i = 0; i < str.size(); i++)
        {
            strncpy(&_record[i][0], str[i].c_str(), str[i].length());
            _record[i][str[i].length()] = '\0';
        }
    }

    // FileRecord(string s)
    // {
    //     // strncpy(_record, s.c_str(), MAX);
    // }

    long write(fstream &outs);           // returns the record number
    long read(fstream &ins, long recno); // returns the number of bytes
                                         //       read = MAX, or zero if
                                         //       read passed the end of file

    friend ostream &operator<<(ostream &outs, const FileRecord &r);
    friend vector<string> get_value(FileRecord r, vector<int> fields);

private:
    static const int MAX = 100;
    int recno;
    char _record[MAX + 1][MAX + 1]; // NULL char
    // vector<string> vec;
};

#endif