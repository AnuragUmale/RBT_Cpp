// ==========================================
// Name: Anurag Prashant Umale              =
// Student Id: 1887255                      =
// E-mail: aumale@ucsc.edu                  =
// File: WordFrequency.cpp					=
// Class: CSE 101 Spring 2023               =
// ==========================================
#include <algorithm>
#include <fstream>
#include "Dictionary.h"
using namespace std;
#define MAX_LEN 300

int main(int argc, char *argv[])
{
    string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";
    int line_count;
    ifstream in;
    ofstream out;
    string line;
    string tokenBuffer;
    string token;
    size_t begin, end, len;
    if (argc != 3)
    {
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return (EXIT_FAILURE);
    }

    in.open(argv[1]);
    if (!in.is_open())
    {
        cerr << "Unable to open file " << argv[1] << " for reading" << endl;
        return (EXIT_FAILURE);
    }

    out.open(argv[2]);
    if (!out.is_open())
    {
        cerr << "Unable to open file " << argv[2] << " for writing" << endl;
        return (EXIT_FAILURE);
    }

    Dictionary D;

    line_count = 0;
    while (getline(in, line))
    {
        line_count++;
        len = line.length();
        begin = min(line.find_first_not_of(delim, 0), len);
        end = min(line.find_first_of(delim, begin), len);
        token = line.substr(begin, end - begin);
        while (token != "")
        {
            transform(token.begin(), token.end(), token.begin(), ::tolower); // Got help frm TA Amaan
            if (D.contains(token))
            {
                int &count = D.getValue(token);
                count++;
            }
            else
            {
                D.setValue(token, 1);
            }
            begin = min(line.find_first_not_of(delim, end + 1), len);
            end = min(line.find_first_of(delim, begin), len);
            token = line.substr(begin, end - begin);
        }
    }
    out << D;

    return (EXIT_SUCCESS);
}