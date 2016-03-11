#include <iostream>
#include <fstream>
#include "mymatrix.h"

const char * const INPUT = "input.txt";


int main()
{
    int column = 0, row = 0;
    std::ifstream fin( INPUT );
    fin >> column >> row;
    MyMatrix a( column, row );
    a.read( fin );
    fin >> column >> row;
    MyMatrix b( column, row );
    b.read( fin );
    fin.close();
    MyMatrix res = KroneckerProduct( a, b );
    res.write( std::cout );
    return 0;
}
