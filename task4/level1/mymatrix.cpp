#include "mymatrix.h"
#include <iostream>


void printMatrix( const MyMatrix &a )
{
    int column = a.getColumnSize();
    int row = a.getRowSize();
    for( int i = 0; i < column; i++ )
    {
        for( int j = 0; j < row; j++ )
            std::cout << a.get( i, j ) << " ";
        std::cout << std::endl;
    }
}


MyMatrix KroneckerProduct( const MyMatrix &a, const MyMatrix &b )
{
    int a_column = a.getColumnSize();
    int a_row = a.getRowSize();
    int b_column = b.getColumnSize();
    int b_row = b.getRowSize();
    MyMatrix res( a_column * b_column, a_row * b_row );
    for( int i_a = 0; i_a < a_column; i_a++ )
        for( int j_a = 0; j_a < a_row; j_a++ )
            for( int i_b = 0; i_b < b_column; i_b++ )
                for( int j_b = 0; j_b < b_row; j_b++ )
                    res.put( i_a * b_column + i_b, j_a * b_row + j_b, a.get( i_a, j_a ) * b.get( i_b, j_b ) );
    return res;
}
