#include"sievelib.h"

#include<cstdlib>

sieve_lib_t getNthPrimeNumber( sieve_lib_t n )
{
    if( n < 1 )
        return 0;
    if( n < 3 )
        return n + 1;
    sieve_lib_t maxPrime = ( n < 21 ) ? ( 2 * n * log( n ) ) : ( n * ( log( n ) + log( log( n ) ) - 0.5 ) ); //Nth pime number must be less than maxPrime
    sieve_lib_t currentN = 2;  //last prime we found is currentNth
    sieve_lib_t maybePrime[2] = {};
    bitarray arr( maxPrime / 3 );
    for( sieve_lib_t i = 6; i <= maxPrime; i += 6 )
    {
        maybePrime[0] = i - 1;
        maybePrime[1] = i + 1;
        for( sieve_lib_t j = 0; j < 2; j++ )    //both options for maybePrime
        {
            if( !arr.get( getIndexByNumber( maybePrime[j] ) ) )  // not crosed out
            {
                currentN++;
                if( currentN == n )
                    return maybePrime[j];
                for( sieve_lib_t k = maybePrime[j]; k <= maxPrime; k += maybePrime[j] )
                    arr.put( getIndexByNumber( k ), 1 );   //TODO: optimize for bad k
            }
        }
    }
    assert( 0 ); //shit happened
}


int printSieve( sieve_lib_t n, std::ofstream &fout )
{
    sieve_lib_t maxPrime = ( n < 21 ) ? ( 2 * n * log( n ) ) : ( n * ( log( n ) + log( log( n ) ) - 0.5 ) ); //Nth pime number must be less than maxPrime
    sieve_lib_t maxI = maxPrime / 6 + 1;
    sieve_lib_t currentN = 2;  //last prime we found is currentNth
    sieve_lib_t currentPrime = 3;
    bitarray sixIPlusOne( maxI );  //to save info about 6i+1
    bitarray sixIMinusOne( maxI ); //to save info about 6i-1
    bitarray *sieve[3] = { &sixIMinusOne, NULL, &sixIPlusOne };
    for( int i = 1; i <= n && i < 3; i++)
    {
        fout << i << ": " << i + 1 << std::endl;
        if( i == n )
            return 0;
    }
    for( sieve_lib_t i = 1; i <= maxI; i++ )
    {
        for( sieve_lib_t j = 0; j < 3; j+=2 )    //both options for maybePrime
        {
            if( !sieve[j]->get( i ) )  // 6*i + j - 1
            {
                currentN++;
                currentPrime = 6 * i + j - 1;
                fout << currentN << ": " << currentPrime << std::endl;
                if( currentN == n )
                    return 0;
                for( sieve_lib_t k = currentPrime; k <= maxPrime; k += currentPrime )
                {
                    switch( k % 6 )
                    {
                        case 5:
                            sieve[0]->put( ( k + 1 ) / 6, 1 );   //6k-1
                            break;
                        case 1:
                            sieve[2]->put( k / 6, 1 );           //6k+1
                            break;
                        default:
                            break;
                    }
                }
            }
        }
    }
    assert( 0 );
}


sieve_lib_t getIndexByNumber( sieve_lib_t number )
{
    if( number < 0 || ( ( number + 1 ) % 6 != 0 && ( number - 1 ) % 6 != 0 ) )  //we consider only 6*k+/-1, the others are useless and they are in arr[0]
        return 0;
    return (sieve_lib_t)( number / 3 );
}

sieve_lib_t getNumberByIndex( sieve_lib_t index )
{
    return index * 3 + 1 + index % 2;
}


//class sieve--------------------------------------------------------------------------------------------------

int sieve::create( sieve_lib_t numberOfPrime )
{
    if( n != 0 )
        return -1;
    n = numberOfPrime;
    if( numberOfPrime < 3 )
        return 0;
    sieve_lib_t maxPrime = estimateMaxPrime( n ); //Nth pime number must be less than maxPrime
    sieve_lib_t maxI = maxPrime / 6 + 1;
    sieve_lib_t currentN = 2;  //last prime we found is currentNth
    sieve_lib_t currentPrime = 3;
    sixPlusOne.create( maxI );  //to save info about 6i+1
    sixMinusOne.create( maxI ); //to save info about 6i-1
    sieve_arr[0] = &sixMinusOne;
    sieve_arr[1] = 0;
    sieve_arr[2] = &sixPlusOne;
    //
    for( sieve_lib_t i = 1; i <= maxI; i++ )
    {
        for( sieve_lib_t j = 0; j < 3; j += 2 )    //both options for maybePrime
        {
            assert( sieve_arr[j]->get( i ) != INCORRECT_INDEX );
            if( !sieve_arr[j]->get( i ) )  // 6*i + j - 1
            {
                currentN++;
                currentPrime = 6 * i + j - 1;
                if( currentN == n )
                    return 0;
                for( sieve_lib_t k = 2 * currentPrime; k <= maxPrime; k += currentPrime )
                {
                    switch( k % 6 )
                    {
                        case 5:
                            sieve_arr[0]->put( ( k + 1 ) / 6, 1 );   //6k-1
                            assert( sieve_arr[0]->put( ( k + 1 ) / 6, 1 ) != INCORRECT_INDEX );
                            break;
                        case 1:
                            sieve_arr[2]->put( k / 6, 1 );           //6k+1
                            assert( sieve_arr[2]->put( k / 6, 1 ) != INCORRECT_INDEX );
                            break;
                        default:
                            break;
                    }
                }
            }
        }
    }
    assert( 0 );
}

#if 0
sieve::sieve()
{
    n = 0;
    sieve_arr[0] = 0;
    sieve_arr[1] = 0;
    sieve_arr[2] = 0;
}

sieve::sieve( sieve_lib_t numberOfPrime )
{
    n = 0;
    sieve_arr[0] = 0;
    sieve_arr[1] = 0;
    sieve_arr[2] = 0;
    create( numberOfPrime );
    assert( n == numberOfPrime );
}

sieve::~sieve()
{
    n = -1;
    sieve_arr[0] = 0;
    sieve_arr[1] = 0;
    sieve_arr[2] = 0;
}
#endif

sieve_lib_t sieve::getNthPrime( sieve_lib_t numberOfPrime )
{
    if( numberOfPrime <= 0 || numberOfPrime > n  )
        return 0;
    if( numberOfPrime < 3 )
        return numberOfPrime + 1;
    sieve_lib_t maxPrime = estimateMaxPrime( numberOfPrime ); //Nth pime number must be less than maxPrime
    sieve_lib_t maxI = maxPrime / 6 + 1;
    sieve_lib_t currentN = 2;  //last prime we found is currentNth
    sieve_lib_t currentPrime = 3;
    //
    for( sieve_lib_t i = 1; i <= maxI; i++ )
    {
        for( sieve_lib_t j = 0; j < 3; j+=2 )    //both options for maybePrime
        {
            if( !sieve_arr[j]->get( i ) )  // 6*i + j - 1
            {
                currentN++;
                currentPrime = 6 * i + j - 1;
                if( currentN == numberOfPrime )
                    return currentPrime;
            }
        }
    }
    assert( 0 );
}

int sieve::test()
{
    if( n == 0 )
        return 0;
    for( sieve_lib_t j = 0; j < 5; j++ )
    {
        sieve_lib_t randomNumber = std::rand() % n;
        sieve_lib_t randomElementInSIeve = getNthPrimeNumber( randomNumber );
        if( !isPrime( randomElementInSIeve ) )
        {
            std::cerr << "Error: There is number " << randomNumber << " in the sieve which is not prime" << std::endl;
            return 1;
        }
    //std::cerr << "There's no mistake" << std::endl;    
    }
    return 0;
}

int sieve::isPrime( sieve_lib_t number )
{
    for( sieve_lib_t i = 2; i <= sqrt( number ); i++ )
    {
        if( number % i == 0 )
            return 0;
    }
    return 1;
}

inline sieve_lib_t sieve::estimateMaxPrime( sieve_lib_t n )
{
    if( n < 21 )
        return 2 * n * log( n );
    return n * ( log( n ) + log( log( n ) ) - 0.5 );
}


