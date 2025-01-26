// Programmers name (entire .cpp): LIM ZHAN HUNG
// Matrix ID                     : 23301019
// Purpose                       : This .cpp file is to define the functions for the payment process of the vending machine.

#include "product.hpp"          // Header file.
#include "vendingMachine.hpp"   // Header file.
#include <iostream>             // To perform input and output operations.
#include <iomanip>              // To assign precise decimal places for the prices.
#include <fstream>              // Provides classes for reading and writing into files or data streams.
#include <string>               // Provides std::string class.

using namespace std;

// Initializing the vending machine with products //
Product::Product(string name, double price, int quantity){
    this->name = name;
    this->price = price;
    this->quantity = quantity;
}

// Saving the products to the file //
void Product::saveToFile(ofstream& outFile) const{
    outFile << name << "|" << setprecision(2)<< price << "|" << quantity << endl;
}

// Loading the products from the file //
void Product::loadFromFile(ifstream& inFile){
    inFile >> name >> setprecision(2)>> price >> quantity;
}
