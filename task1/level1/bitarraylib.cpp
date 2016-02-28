#include"bitarraylib.h"

#if 0
bitarray::bitarray( bitarr_prop_t size )
{
    lengthOfArray = size / sizeof( *array ) + 1;   //I know it is more than we need 
    lengthOfBitArray = size;
    array = new bitarr_arr_t[lengthOfArray];
    for( int i = 0; i < lengthOfArray; i++)
        array[i] = 0;
}

bitarray::bitarray()
{
    lengthOfArray = 0;
    lengthOfBitArray = 0;
    array = 0;
}

bitarray::~bitarray()
{
    lengthOfArray = lengthOfBitArray = 0;
    delete[] array;
}
#endif

int bitarray::create( bitarr_prop_t size )//Don't know how to avoid copy-past of constructor
{
    if( lengthOfArray || lengthOfBitArray || array )
        return -1;
    lengthOfArray = size / sizeof( *array ) + 1;   //I know it is more than we need 
    lengthOfBitArray = size;
    array = new bitarr_arr_t[lengthOfArray] ();
    return 0;
}

int bitarray::get( bitarr_prop_t index )
{
    if( index >= lengthOfBitArray || index < 0 )
        return INCORRECT_INDEX;
    bitarr_arr_t element = array[index / sizeof( *array )];  //the element of array with data we need
    int shift = index % sizeof( *array );
    int value = ( element >> shift ) % 2;
    return value;
}

int bitarray::put( bitarr_prop_t index, int value )
{
    if( index >= lengthOfBitArray || index < 0 )
        return INCORRECT_INDEX;
    bitarr_arr_t element = array[index / sizeof( *array )];  //the element of array with data we need
    int shift = index % sizeof( *array );
    value = !!value;        //make it boolean( this operation is not only for "if", I need these zeros at the head of number )
    if( value )
    {                       //we put 1
        value = value << shift;
        element = element | value;  //we've got what we need
    }
    else
    {
        value = ~( 1 << shift );    //all - '1' and '0' on the proper place
        element = element & value;  //we've got what we need
    }
    array[index / sizeof( *array )] = element;
    return 0;
}


