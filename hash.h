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
        unsigned long long w[5] = {0,0,0,0,0};
        int str_size = k.size();
        
        int num_w;
        if (str_size %6 != 0){
            num_w = str_size/6 + 1;
        } else {
            num_w = str_size/6;
        }

        std::string temp = k;
        for (int i = 0; i<num_w; i++){
            std::string this_str;
            int index = temp.size() - 6;
            if (index < 0){
                this_str = temp;
            } else {
                this_str = temp.substr(index);
            }
            
            unsigned long long t=0;
            int size = this_str.size();
            for (int j = 0; j < size; j++){
                t*=36;
                t+= letterDigitToNumber(this_str[j]);
            }
            w[4-i] = t;
            if (!(index < 0)){
                temp = temp.substr(0, index);
            } else {
                temp = "";
            }
        }

        //next, multiple values stored in w by those in r

        // for (int k = 0; k < 5; k++){
        //     std::cout<<"w[" << k << "] = "<< w[k] << "\n";
        // }
        // std::cout<< std::endl;

        unsigned long long sum = 0;
        for (int i = 0; i < 5; i++){
            sum += (w[i]* static_cast<unsigned long long>(rValues[i]));
        }
        return static_cast<HASH_INDEX_T>(sum);
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it

        if (letter >= 'a' && letter <= 'z'){
            return static_cast<HASH_INDEX_T>(letter - 'a');
        } else if (letter >= 'A' && letter <= 'Z'){
            char x = letter - 'A' + 'a';
            return static_cast<HASH_INDEX_T>(x -'a');    
        } else {
            return static_cast<HASH_INDEX_T>((letter - '0') + 26);
        }

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
