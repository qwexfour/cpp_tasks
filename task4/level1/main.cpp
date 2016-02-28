#include <iostream>
#include <fstream>
#include "mymatrix.h"

const char * const INPUT = "input.txt";

inline MyMatrix inMatrix( std::ifstream &fin )
{
    int column = 0, row = 0, value = 0;
    fin >> column;
    fin >> row;
    MyMatrix a( column, row );
    for( int i = 0; i < column; i++ )
        for( int j = 0; j < row; j++ )
        {
            fin >> value;
            a.put( i, j, value );
        }
    return a;
}

int main()
{
    std::ifstream fin( INPUT );
    MyMatrix a = inMatrix( fin );
    MyMatrix b = inMatrix( fin );
    fin.close();
    printMatrix( KroneckerProduct( a, b ) );
    return 0;
}
