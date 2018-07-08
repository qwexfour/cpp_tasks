#include <iostream>
#include <fstream>
#include "mymatrix.h"

const char * const INPUT = "input.txt";


int main()
{
    int column = 0, row = 0;
    std::ifstream fin( INPUT );
    fin >> column >> row;
    MyMatrix a( column, row );
    a.read( fin );
    fin >> column >> row;
    MyMatrix b( column, row );
    b.read( fin );
    fin.close();
    
    std::cout << "a:" << std::endl;
    a.write( std::cout );
    std::cout << "b:" << std::endl;
    b.write( std::cout );
    std::cout << std::endl;
    
    MyMatrix kp = KroneckerProduct( a, b );
    std::cout << "KroneckerProduct( a, b ):" << std::endl;
    kp.write( std::cout );
    std::cout << std::endl;
    
    a = a + a;
    b *= 3;
    std::cout << "a += a:" << std::endl;
    a.write( std::cout );
    std::cout << "b *= 3:" << std::endl;
    b.write( std::cout );
    std::cout << std::endl;

    MyMatrix mul = 10 * a * b * 10;
    std::cout << "10 * a * b * 10:" << std::endl;
    mul.write( std::cout );

    //a += b; //error

    return 0;
}
