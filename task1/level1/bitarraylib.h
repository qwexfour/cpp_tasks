#ifndef BITARRAYLIB
#define BITARRAYLIB

#include<cstdlib>

#define INCORRECT_INDEX -1

typedef int bitarr_arr_t;
typedef int bitarr_prop_t;

class bitarray
{
    private:
        bitarr_arr_t *array;     //bitarray based on this array
        bitarr_prop_t lengthOfArray;
        bitarr_prop_t lengthOfBitArray;
        bitarray( const bitarray & );
        bitarray &operator=( const bitarray & );
    public:
        bitarray(): array( 0 ), lengthOfArray( 0 ), lengthOfBitArray( 0 ) {}
        
        bitarray( bitarr_prop_t size ):
        lengthOfArray( size / sizeof( *array ) + 1 ), lengthOfBitArray( size )
        {
            array = new bitarr_arr_t[lengthOfArray] ();
        }
        
        ~bitarray()
        {
            delete[] array;
            array = NULL;
        }
        
        int create( bitarr_prop_t size );
        int get ( bitarr_prop_t index );
        int put ( bitarr_prop_t index, int value );
};

#endif
