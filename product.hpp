#ifndef PRODUCT_hpp
#define PRODUCT_hpp

#include <fstream> // Provides classes for reading and writing into files or data streams.
#include <string>  // Provides std::string class.
#include <map>     // To store data in mapped method.

using namespace std;

class Product{
    public:
        string name;
        double price;
        int quantity;
        Product(string name, double price, int quantity);
        
        std::string getName() const { return name; }
        int getQuantity() const { return quantity; }
        double getPrice() const { return price; }
        void saveToFile(std::ofstream& outFile) const;
        void loadFromFile(std::ifstream& inFile);
};
    #endif