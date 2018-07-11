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

MyMatrix &MyMatrix::operator*=( const MyMatrix &rhs )
{
    assert( row_size_ == rhs.column_size_ );
    int res_column = column_size_, res_row = rhs.row_size_;
    MyMatrix tmp( res_column, res_row );
    std::swap( *this, tmp );
    // *this = tmp * rhs
    for( int i = 0; i < res_column; i++ )
    {
        for( int j = 0; j < res_row; j++ )
        {
            int value = 0;
            for( int k = 0; k < tmp.row_size_; k++ )
            {
                value += tmp.matrix_[i][k] * rhs.matrix_[k][j];
            }
            matrix_[i][j] = value;
        }
    }

    return *this;
}
    

MyMatrix &MyMatrix::KroneckerProductEq( const MyMatrix &rhs )
{
    int res_column = column_size_ * rhs.column_size_, res_row = row_size_ * rhs.row_size_;
    MyMatrix tmp( res_column, res_row );
    std::swap( *this, tmp );
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

MyMatrix operator+( const MyMatrix &a, const MyMatrix &b )
{
    MyMatrix tmp = a;
    return tmp += b;
}

MyMatrix operator*( const MyMatrix &a, const MyMatrix &b )
{
    MyMatrix tmp = a;
    return tmp *= b;
}

MyMatrix operator*( const int a, const MyMatrix &b )
{
    MyMatrix tmp = b;
    return tmp *= a;
}

MyMatrix operator*( const MyMatrix &a, const int b )
{
    MyMatrix tmp = a;
    return tmp *= b;
}

MyMatrix MyMatrix::getArithComp( const int row, const int column ) const
{
    assert( column_size_ > 1 && row_size_ > 1 );
    assert( check_index( row, column ) );

    MyMatrix arith_comp( column_size_ - 1, row_size_ - 1 );
    
    // [i][j] is for *this
    // [i_ac][j_ac] is for arith_comp
    for( int i = 0, i_ac = 0; i < column_size_; i++, i_ac++ )
    {
        for( int j = 0, j_ac = 0; j < row_size_; j++, j_ac++ )
        {
            if( i == row ) //exclude the row
            {
                i++;
            }
            if( j == column ) //exclude the column
            {
                j++;
            }
            arith_comp.matrix_[i_ac][j_ac] = matrix_[i][j];
        }
    }

    return arith_comp;
}

int MyMatrix::determinant() const
{
    assert( column_size_ == row_size_ );

    if( column_size_ == 1 )
    {
        return values_[0];
    }

    int result = 0;
    for( int j = 0; j < row_size_; j++ )
    {
        MyMatrix arith_comp = this->getArithComp( 0, j );

        if( j % 2 == 0 )
        {
            result += matrix_[0][j] * arith_comp.determinant();
        }
        else
        {
            result -= matrix_[0][j] * arith_comp.determinant();
        }
    }

    return result;
}

