#include<iostream>
#include<stdlib.h>
#include"sievelib.h"




int main( int argc, const char** argv )
{
    int numberOfPrime = ( argc == 2 ) ? atoi( argv[1] ) : 0;
    if( numberOfPrime )
    {
        sieve just_sieve( numberOfPrime );
        just_sieve.test();
        std::cout << just_sieve.getNthPrime( numberOfPrime ) << std::endl;
    }
    return 0;
}
