#include "mymatrix.h"
#include <iostream>


void MyMatrix::write( std::ostream &fout )
{
    for( int i = 0; i < column_size_; i++ )
    {
        for( int j = 0; j < row_size_; j++ )
            fout << matrix_[i][j] << " ";
        fout << std::endl;
    }
}

void MyMatrix::read( std::ifstream &fin )
{
    int value = 0;
    for( int i = 0; i < column_size_; i++ )
        for( int j = 0; j < row_size_; j++ )
        {
            fin >> value;
            matrix_[i][j] = value;
        }
}

void MyMatrix::swap( MyMatrix &rhs )
{
    MyMatrix tmp = std::move( *this );
    *this = std::move( rhs );
    rhs = std::move( tmp );
}

MyMatrix &MyMatrix::KroneckerProductEq( const MyMatrix &rhs )
{
    int res_column = column_size_ * rhs.column_size_, res_row = row_size_ * rhs.row_size_;
    MyMatrix tmp( res_column, res_row );
    tmp.swap( *this );
    //writing the result of Kronecker product
    for( int i_tmp = 0; i_tmp < tmp.column_size_; i_tmp++ )
        for( int j_tmp = 0; j_tmp < tmp.row_size_; j_tmp++ )
            for( int i_rhs = 0; i_rhs < rhs.column_size_; i_rhs++ )
                for( int j_rhs = 0; j_rhs < rhs.row_size_; j_rhs++ )
                    matrix_[i_tmp * rhs.column_size_ + i_rhs][j_tmp * rhs.row_size_ + j_rhs] = tmp.matrix_[i_tmp][j_tmp] * rhs.matrix_[i_rhs][j_rhs];
    
    return *this;
}

MyMatrix KroneckerProduct( const MyMatrix &a, const MyMatrix &b )
{
    MyMatrix tmp = a;
    return tmp.KroneckerProductEq( b );
}
