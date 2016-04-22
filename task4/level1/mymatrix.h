#ifndef MYMATRIX
#define MYMATRIX

#include <cstdlib>
#include <cassert>
#include <fstream>

class MyMatrix final
{
    public:
        MyMatrix( int column_size, int row_size ) : column_size_( column_size ), row_size_( row_size )
        {
            int full_size = row_size * column_size;
            matrix_ = new int* [column_size];
            values_ = new int [full_size];
            for( int i = 0, k = 0; i < full_size; i += row_size, k++ )
            {
                matrix_[k] = &values_[i];
            }
        }
        MyMatrix( const MyMatrix &rhs ) : MyMatrix( rhs.column_size_, rhs.row_size_ )
        {
            for( int i = 0; i < column_size_; i++ )
                for( int j = 0; j < row_size_; j++ )
                    matrix_[i][j] = rhs.matrix_[i][j];
        }
        MyMatrix &operator=( const MyMatrix &rhs )
        {
            if( this == &rhs )
                return *this;
            column_size_ = rhs.column_size_;
            row_size_ = rhs.row_size_ ;
            for( int i = 0; i < column_size_; i++ )
                for( int j = 0; j < row_size_; j++ )
                    matrix_[i][j] = rhs.matrix_[i][j];
            return *this;
        }
        MyMatrix( MyMatrix &&rhs )
        {
            column_size_ = rhs.column_size_;
            row_size_ = rhs.row_size_;
            matrix_ = rhs.matrix_;
            values_ = rhs.values_;
            rhs.matrix_ = NULL;
            rhs.values_ = NULL;
        }
        MyMatrix &operator=( MyMatrix &&rhs )
        {
            if( this != &rhs )
            {
                column_size_ = rhs.column_size_;
                row_size_ = rhs.row_size_;
                delete[] matrix_;   //Or we will lose the memory
                delete[] values_;
                matrix_ = rhs.matrix_;
                values_ = rhs.values_;
                rhs.matrix_ = NULL;
                rhs.values_ = NULL;
            }
            return *this;
        }
        /* 
        void put( int row, int column, int value )
        {
            assert( row >= 0 && row < column_size_ && column >= 0 && column < row_size_ );
            matrix_[row][column] = value;
        }
        int get( int row, int column ) const
        {
            assert( row >= 0 && row < column_size_ && column >= 0 && column < row_size_ );
            return matrix_[row][column];
        }
        */
        int getRowSize() const { return row_size_; }
        int getColumnSize() const { return column_size_; }
        MyMatrix &KroneckerProductEq( const MyMatrix &a );
        void read( std::ifstream &fin );
        void write( std::ostream &fout );
        ~MyMatrix()
        {
            delete[] matrix_;
            delete[] values_;
        }
    private:
        int column_size_, row_size_;  //the number of elements in column and row respectively
        int **matrix_;
        int *values_;
        void swap( MyMatrix &rhs );
};

MyMatrix KroneckerProduct( const MyMatrix &a, const MyMatrix &b );
void printMatrix( const MyMatrix &a );


#endif
