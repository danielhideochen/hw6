#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
            // w[0..4], where w[4] is last 6 chars
        unsigned long long w[5] = {0ULL,0ULL,0ULL,0ULL,0ULL};

        int wi = 4;
        int end = (int)k.size();
        while(end > 0 && wi >= 0) {
            int start = std::max(0, end - 6);
            unsigned long long x = 0ULL;

            // base-36 conversion left->right: x = x*36 + val
            for(int i = start; i < end; i++) {
                x = x * 36ULL + (unsigned long long)letterDigitToNumber(k[(size_t)i]);
            }

            w[wi] = x;
            end = start;
            wi--;
        }

        unsigned long long h =
            (unsigned long long)rValues[0] * w[0] +
            (unsigned long long)rValues[1] * w[1] +
            (unsigned long long)rValues[2] * w[2] +
            (unsigned long long)rValues[3] * w[3] +
            (unsigned long long)rValues[4] * w[4];

        return (HASH_INDEX_T)h;
    


    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
            // normalize case
        if(letter >= 'A' && letter <= 'Z') letter = char(letter - 'A' + 'a');

        if(letter >= 'a' && letter <= 'z') {
            return (HASH_INDEX_T)(letter - 'a');           // a=0..z=25
        }
        // digits '0'..'9' -> 26..35
        return (HASH_INDEX_T)(26 + (letter - '0'));

    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
