#ifndef SIEVE_LIB
#define SIEVE_LIB

#include<math.h>
#include<iostream>
#include<fstream>
#include<assert.h>

#include"bitarraylib.h"

typedef int sieve_lib_t;

sieve_lib_t getNthPrimeNumber( sieve_lib_t );

int printSieve( sieve_lib_t, std::ofstream& );

sieve_lib_t getIndexByNumber( sieve_lib_t );

sieve_lib_t getNumberByIndex( sieve_lib_t );

class sieve
{
    private:
        bitarray sixMinusOne;
        bitarray sixPlusOne;
        bitarray *sieve_arr[3];  //={ sixMinusOne, 0, sixPlusOne )
        sieve_lib_t n;          //number of prime nubers
        int isPrime( sieve_lib_t );  //returns 1 if varible is prime else 0
        inline sieve_lib_t estimateMaxPrime( sieve_lib_t );
        sieve( const sieve & );
        sieve &operator=( const sieve & );
    public:
        sieve( sieve_lib_t numberOfPrime = 0 ): sixMinusOne(), sixPlusOne(), n( 0 )
        {
            sieve_arr[0] = 0;
            sieve_arr[1] = 0;
            sieve_arr[2] = 0;
            if( numberOfPrime > 0 )
            {
                create( numberOfPrime );
                assert( n == numberOfPrime );
            }
        }
        int create( sieve_lib_t );
        sieve_lib_t getNthPrime( sieve_lib_t );
        int test();          //returns 1 if there is mistake
        ~sieve() {}
};

#endif
