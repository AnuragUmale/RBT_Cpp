// ==========================================
// Name: Anurag Prashant Umale              =
// Student Id: 1887255                      =
// E-mail: aumale@ucsc.edu                  =
// File: Dictionary.cpp						=
// Class: CSE 101 Spring 2023               =
// ==========================================

#include <iostream>
#include <string>
#include <stdexcept>
#include "Dictionary.h"

using namespace std;

int main()
{

    string S[] = {

        "plaices",
        "ambusher",
        "crosby",
        "wattles",
        "pardoner",
        "pythons",
        "second",
        "forms",
        "impales",
        "pic",
        "verticals",
        "recriminator",
        "depressants",
        "cul",
        "potables",
        "norm",
        "reinsurer",
        "deschooler",
        "recoining",
        "dissocialised",
        "cohabit",
        "hemiolia",
        "cantling",
        "glamorized",
        "millesimal",
        "glagolitic"};

    string T[] = {

        "second",
        "forms",
        "impales",
        "pic",
        "verticals",
        "recriminator",
        "depressants",
        "cul",
        "potables",
        "norm",
        "reinsurer",
        "deschooler",
        "recoining"};

    Dictionary A;
    Dictionary B;

    cout << endl;

    for (int i = 0; i < 26; i++)
    {
        A.setValue(S[i], i + 1);
    }

    B = A;

    B.setValue("deschooler", 101);
    B.setValue("reinsurer", 102);
    B.setValue("glagolitic", 103);
    B.setValue("cul", 104);
    B.setValue("ambusher", 105);

    Dictionary C = B;

    cout << "A.size() = " << A.size() << endl
         << A << endl;
    cout << "B.size() = " << B.size() << endl
         << B << endl;
    cout << "C.size() = " << C.size() << endl
         << C << endl;

    cout << "copy constructor creates identical trees: " << endl;
    cout << ((C.pre_string() == B.pre_string()) ? "true" : "false") << endl;
    cout << endl;

    cout << "A==B is " << (A == B ? "true" : "false") << endl;
    cout << "B==C is " << (B == C ? "true" : "false") << endl;
    cout << "C==A is " << (C == A ? "true" : "false") << endl
         << endl;

    cout << "A.getValue(\"hemiolia\") = " << A.getValue("hemiolia") << endl;
    A.getValue("hemiolia") *= 10;
    cout << "A.getValue(\"hemiolia\") = " << A.getValue("hemiolia") << endl
         << endl;

    cout << "A.size() = " << A.size() << endl
         << A << endl;
    cout << "A pre-order: " << endl
         << A.pre_string() << endl;

    for (int i = 0; i < 13; i++)
    {
        A.remove(T[i]);
    }

    cout << "A.size() = " << A.size() << endl
         << A << endl;
    cout << "A pre-order: " << endl
         << A.pre_string() << endl;

    cout << "forward iteration on B, changing values:" << endl;
    for (B.begin(); B.hasCurrent(); B.next())
    {
        cout << "(" + B.currentKey() + ", " << B.currentVal() << ") ";
        B.currentVal()++;
        cout << "(" + B.currentKey() + ", " << B.currentVal() << ")\n";
    }
    cout << endl;

    cout << "reverse iteration on C, changing values" << endl;
    for (C.end(); C.hasCurrent(); C.prev())
    {
        cout << "(" + C.currentKey() + ", " << C.currentVal() << ") ";
        C.currentVal()++;
        cout << "(" + C.currentKey() + ", " << C.currentVal() << ")\n";
    }
    cout << endl;

    cout << "test pre-condition errors:" << endl;
    try
    {
        A.getValue("blah");
    }
    catch (logic_error &e)
    {
        cout << e.what() << endl;
        cout << "   continuing without interruption" << endl;
    }
    try
    {
        A.remove("blah");
    }
    catch (logic_error &e)
    {
        cout << e.what() << endl;
        cout << "   continuing without interruption" << endl;
    }
    try
    {
        A.currentKey();
    }
    catch (logic_error &e)
    {
        cout << e.what() << endl;
        cout << "   continuing without interruption" << endl;
    }
    try
    {
        A.currentVal();
    }
    catch (logic_error &e)
    {
        cout << e.what() << endl;
        cout << "   continuing without interruption" << endl;
    }
    try
    {
        A.next();
    }
    catch (logic_error &e)
    {
        cout << e.what() << endl;
        cout << "   continuing without interruption" << endl;
    }
    try
    {
        A.prev();
    }
    catch (logic_error &e)
    {
        cout << e.what() << endl;
        cout << "   continuing without interruption" << endl;
    }
    cout << endl;
    Dictionary myDictionary;

    myDictionary.setValue("apple", 10);
    myDictionary.setValue("banana", 20);
    myDictionary.setValue("cherry", 30);

    cout << "Value of 'banana': " << myDictionary.getValue("banana") << endl;

    myDictionary.setValue("apple", 15);

    cout << "Key 'grape' exists: " << (myDictionary.contains("grape") ? "true" : "false") << endl;

    myDictionary.remove("cherry");

    cout << "Size of dictionary: " << myDictionary.size() << endl;

    cout << "Dictionary elements:" << endl;
    myDictionary.begin();
    while (myDictionary.hasCurrent())
    {
        cout << "Key: " << myDictionary.currentKey() << ", Value: " << myDictionary.currentVal() << endl;
        myDictionary.next();
    }
    return (EXIT_SUCCESS);
}
