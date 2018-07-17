#ifndef MYMATRIX
#define MYMATRIX

#include <iostream>
#include <cstdlib>
#include <cassert>
#include <fstream>

template <typename T>
class MyMatrix final
{
    public:
        MyMatrix( size_t column_size, size_t row_size ) : column_size_( column_size ), row_size_( row_size )
        {
            size_t full_size = row_size * column_size;
            matrix_ = new T* [column_size];
            values_ = new T [full_size];
            for( size_t i = 0, k = 0; i < full_size; i += row_size, k++ )
            {
                matrix_[k] = &values_[i];
            }
        }
        /* //dangerous
        MyMatrix( T value ) : MyMatrix( 1, 1 )
        {
            values_[0] = value;    
        }
        */
        MyMatrix( const MyMatrix<T> &rhs ) : MyMatrix( rhs.column_size_, rhs.row_size_ )
        {
            for( size_t i = 0; i < column_size_; i++ )
                for( size_t j = 0; j < row_size_; j++ )
                    matrix_[i][j] = rhs.matrix_[i][j];
        }
        /*
        template <typename U>
        MyMatrix( const MyMatrix<U> &rhs ) : MyMatrix( rhs.column_size_, rhs.row_size_ )
        {
            std::cout << "It's me" << std::endl;
            for( size_t i = 0; i < column_size_; i++ )
                for( size_t j = 0; j < row_size_; j++ )
                    matrix_[i][j] = static_cast<T>( rhs.matrix_[i][j] );
        }
        */
        MyMatrix( MyMatrix<T> &&rhs )
        {
            std::printf( "rcopy\n" );
            column_size_ = rhs.column_size_;
            row_size_ = rhs.row_size_;
            matrix_ = rhs.matrix_;
            values_ = rhs.values_;
            /* to prevent rhs from using */
            rhs.column_size_ = 0;
            rhs.row_size_ = 0;
            rhs.matrix_ = NULL;
            rhs.values_ = NULL;
        }
        MyMatrix<T> &operator=( const MyMatrix<T> &rhs )
        {
            if( this == &rhs )
                return *this;
            MyMatrix<T> tmp = rhs;
            std::swap( *this, tmp );
            return *this;
        }
        /*
        template <typename U>
        MyMatrix<T> &operator=( const MyMatrix<U> &rhs )
        {
            MyMatrix<T> tmp = rhs;
            std::swap( *this, tmp );
            return *this;
        }
        */
        MyMatrix<T> &operator=( MyMatrix<T> &&rhs )
        {
            if( this == &rhs )
            {
                return *this;
            }
            if( matrix_ != NULL )
            {
                delete[] matrix_;
            }
            if( values_ != NULL )
            {
                delete[] values_;
            }
            column_size_ = rhs.column_size_;
            row_size_ = rhs.row_size_;
            matrix_ = rhs.matrix_;
            values_ = rhs.values_;
            /* to prevent rhs from using */
            rhs.column_size_ = 0;
            rhs.row_size_ = 0;
            rhs.matrix_ = NULL;
            rhs.values_ = NULL;
            return *this;
        }
        MyMatrix<T> &operator+=( const MyMatrix<T> &rhs )
        {
            assert( rhs.row_size_ == row_size_ );
            assert( rhs.column_size_ == column_size_ );
            
            for( size_t i = 0; i < column_size_; i++ )
                for( size_t j = 0; j < row_size_; j++ )
                {
                    matrix_[i][j] += rhs.matrix_[i][j];
                }

            return *this;
        }
        MyMatrix<T> &operator*=( const T value )
        {
            for( size_t i = 0; i < column_size_; i++ )
                for( size_t j = 0; j < row_size_; j++ )
                {
                    matrix_[i][j] *= value;
                }

            return *this;
        }
        MyMatrix<T> &operator*=( const MyMatrix<T> &rhs )
        {
            assert( row_size_ == rhs.column_size_ );
            MyMatrix tmp( column_size_, rhs.row_size_ );
            std::swap( *this, tmp );
            // *this = tmp * rhs
            for( size_t i = 0; i < column_size_; i++ )
            {
                for( size_t j = 0; j < row_size_; j++ )
                {
                    T value = 0;
                    for( size_t k = 0; k < tmp.row_size_; k++ )
                    {
                        value += tmp.matrix_[i][k] * rhs.matrix_[k][j];
                    }
                    matrix_[i][j] = value;
                }
            }

            return *this;
        }
        bool operator==( const MyMatrix<T> &rhs ) const
        {
            if( column_size_ != rhs.column_size_ && row_size_ != rhs.row_size_ )
            {
                return false;
            }
            for( size_t i = 0; i < column_size_; i++ )
            {
                for( size_t j = 0; j < row_size_; j++ )
                {
                    if( matrix_[i][j] != rhs.matrix_[i][j] )
                    {
                        return false;
                    }
                }
            }
            return true;
        }
        bool operator!=( const MyMatrix<T> &rhs ) const { return !( *this == rhs ); }
        size_t getRowSize() const { return row_size_; }
        size_t getColumnSize() const { return column_size_; }
        MyMatrix<T> &KroneckerProductEq( const MyMatrix<T> &rhs )
        {
            T res_column = column_size_ * rhs.column_size_, res_row = row_size_ * rhs.row_size_;
            MyMatrix<T> tmp( res_column, res_row );
            std::swap( *this, tmp );
            //writing the result of Kronecker product
            for( size_t i_tmp = 0; i_tmp < tmp.column_size_; i_tmp++ )
                for( size_t j_tmp = 0; j_tmp < tmp.row_size_; j_tmp++ )
                    for( size_t i_rhs = 0; i_rhs < rhs.column_size_; i_rhs++ )
                        for( size_t j_rhs = 0; j_rhs < rhs.row_size_; j_rhs++ )
                            matrix_[i_tmp * rhs.column_size_ + i_rhs][j_tmp * rhs.row_size_ + j_rhs] = tmp.matrix_[i_tmp][j_tmp] * rhs.matrix_[i_rhs][j_rhs];
    
            return *this;
        }
        MyMatrix<T> getLaplaceExpansion( const size_t row, const size_t column ) const //returns Laplace expansion for element [row][column]
        {
            assert( column_size_ > 1 && row_size_ > 1 );
            assert( check_coords( { row, column } ) );

            MyMatrix<T> lap_exp( column_size_ - 1, row_size_ - 1 );
    
            // [i][j] is for *this
            // [i_ac][j_ac] is for arith_comp
            for( size_t i = 0, i_ac = 0; i < column_size_; i++, i_ac++ )
            {
                for( size_t j = 0, j_ac = 0; j < row_size_; j++, j_ac++ )
                {
                    if( i == row ) //exclude the row
                    {
                        i++;
                    }
                    if( j == column ) //exclude the column
                    {
                        j++;
                    }
                    lap_exp.matrix_[i_ac][j_ac] = matrix_[i][j];
                }
            }

            return lap_exp;
        }
        T determinantLE() const
        {
            assert( column_size_ == row_size_ );

            if( column_size_ == 1 )
            {
                return values_[0];
            }

            T result = 0;
            for( size_t j = 0; j < row_size_; j++ )
            {
                MyMatrix<T> lap_exp = this->getLaplaceExpansion( 0, j );

                if( j % 2 == 0 )
                {
                    result += matrix_[0][j] * lap_exp.determinantLE();
                }
                else
                {
                    result -= matrix_[0][j] * lap_exp.determinantLE();
                }
            }

            return result;
        }
        void read( std::ifstream &fin )
        {
            T value = 0;
            for( size_t i = 0; i < column_size_; i++ )
            {
                for( size_t j = 0; j < row_size_; j++ )
                {
                    fin >> value;
                    matrix_[i][j] = value;
                }
            }
        }
        void write( std::ostream &fout )
        {
            for( size_t i = 0; i < column_size_; i++ )
            {
                for( size_t j = 0; j < row_size_; j++ )
                {
                    fout << matrix_[i][j] << " ";
                }
                fout << std::endl;
            }
        }
        ~MyMatrix()
        {
            if( matrix_ != NULL )
            {
                delete[] matrix_;
            }
            if( values_ != NULL )
            {
                delete[] values_;
            }
        }
    private:
        size_t column_size_, row_size_;  //the number of elements in column and row respectively
        T **matrix_;
        T *values_;

        /* technical stuff */
        struct coords_t { size_t row; size_t column; };
        struct row_t
        {
            row_t()
            {
                elems = new T [column_size_];
            }
            void rowFromMatrix( size_t row )
            {
                assert( row >= 0 && row < column_size_ );
                for( size_t j = 0; j < row_size_; ++j )
                {
                    elems[j] = matrix_[row][j];
                }
            }
            ~row_t()
            {
                delete[] elems;
            }
            private:
                T *elems;
        };
        bool check_coords( const coords_t coords ) const  //Is there such element [row][column] at all
        {
            return ( coords.row >= 0 && coords.row < column_size_ && coords.column >= 0 && coords.column < row_size_ );
        }
        coords_t findMax( const coords_t from, const coords_t to ) //from is left-top limit, to is right-bottom limit
        {
            assert( check_coords( from ) && check_coords( to ) );

            coords_t res = { from.row, from.column };
            T max = matrix_[from.row][from.column];
            for( size_t i = from.row; i < to.row; i++ )
            {
                for( size_t j = from.column; j < to.column; j++ )
                {
                    if( matrix_[i][j] > max )
                    {
                        max = matrix_[i][j];
                        res = {i,j};
                    }
                }
            }

            return res;
        }
        void swapRows( size_t first, size_t second );

    //friend class MyMatrix<double>;   //the crutchiest crutch
};

template <typename T>
MyMatrix<T> KroneckerProduct( const MyMatrix<T> &a, const MyMatrix<T> &b )
{
    MyMatrix<T> tmp = a;
    return tmp.KroneckerProductEq( b );
}

template <typename T>
MyMatrix<T> operator+( const MyMatrix<T> &a, const MyMatrix<T> &b )
{
    MyMatrix<T> tmp = a;
    return tmp += b;
}

template <typename T>
MyMatrix<T> operator*( const MyMatrix<T> &a, const MyMatrix<T> &b )
{
    MyMatrix<T> tmp = a;
    return tmp *= b;
}

template <typename T>
MyMatrix<T> operator*( const T a, const MyMatrix<T> &b )
{
    MyMatrix<T> tmp = b;
    return tmp *= a;
}

template <typename T>
MyMatrix<T> operator*( const MyMatrix<T> &a, const T b )
{
    MyMatrix<T> tmp = a;
    return tmp *= b;
}

#endif
