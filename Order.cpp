// ==========================================
// Name: Anurag Prashant Umale              =
// Student Id: 1887255                      =
// E-mail: aumale@ucsc.edu                  =
// File: Order.cpp						    =
// Class: CSE 101 Spring 2023               =
// ==========================================

#include <fstream>  // including the fstream header file
#include "Dictionary.h"  // including the dictionary header file

int main(int argc, char *argv[])
{
    std::ifstream in;  // input file stream object
    std::ofstream out;  // output file stream object

    // Checking if the correct number of command-line arguments is provided
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " <input file> <output file>" << std::endl;
        return (EXIT_FAILURE);
    }

    // Opening the input file
    in.open(argv[1]);
    if (!in.is_open())
    {
        std::cerr << "Unable to open file " << argv[1] << " for reading" << std::endl;
        return (EXIT_FAILURE);
    }

    // Opening the output file
    out.open(argv[2]);
    if (!out.is_open())
    {
        std::cerr << "Unable to open file " << argv[2] << " for writing" << std::endl;
        return (EXIT_FAILURE);
    }

    std::string line;
    int line_count = 0;

    Dictionary D;  // Creating an instance of the Dictionary class

    // Reading each line from the input file
    while (getline(in, line))
    {
        line_count++;

        // Setting the value of each line as the line number in the Dictionary
        D.setValue(line, line_count);
    }

    // Writing the Dictionary to the output file
    out << D << std::endl;

    // Writing the pre-order string representation of the Dictionary to the output file
    out << D.pre_string() << std::endl;

    // Closing the input and output files
    in.close();
    out.close();
}
