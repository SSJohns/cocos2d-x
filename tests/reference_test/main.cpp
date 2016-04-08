//
//  main.cpp
//  Ref_Ptr_And_Objects
//
//  Created by Jonathan Baker on 12/3/15.
//  Copyright (c) 2015 JMB. All rights reserved.
//

#include <iostream>
#include "Ref_Ptr.h"
#include "CCMapJMB.h"
#include <fstream>
#include <sstream>
#include "CCVectorJMB.h"

int main(int argc, const char * argv[]) {
    
    // Driver to test the features of the new cocos2d::Vector<T> class
    
    // Declare multiple Vectors to test nesting and type allowances
    Vector<int> vecA;
    Vector<int> vecE;
    Vector<std::string> vecB;
    Vector<Vector<std::string>> vecC;
    Vector<std::vector<std::string>> vecD;
    std::vector<int> temp;
    
    Map<double, Vector<int>> temp_map;
    temp_map.insert(8, vecA);
    std::cout << temp_map.size() << std::endl;
    
    temp_map.erase(8);
    std::cout << temp_map.size() << std::endl;
    
    Map<int, int> temp2;
    temp2.insert(20, 19999);
    std::cout << temp2.size();
    std::cout << temp2.at(20);
    
    
    // Fill the vectors using multiple add operations
    for(int i = 0; i < 100; i++) {
        vecA.push_back(i);
        vecB.pushBack("a");
        vecC.pushBack(vecB);
    }
    
    // Test Assignment
    vecE = vecA;
    
    temp = vecA;
    vecA = temp;
    for(auto& x : vecA) {
        vecA.push_back(x);
    }
    std::cout << temp.size() << " " << vecA.size(); 

    
    std::cout << vecB.size() << std::endl;
    temp = vecA; 
    
    


}
