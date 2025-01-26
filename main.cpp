//================================================================================================================================================//
// Project Title: Vending Machine with Stock monitoring 
// Group Members: 1. LIM ZHAN HUNG (23301019)
//                2. CHEONG WYE SHEN (23302183)
//                3. MUHAMMAD SYABIL BIN MOHAMAD SHAHIMI (23303676)
//                4. WAN YAZAFRINA BINTI WAN YAZAIRI (23303505)
//                5. IMAN DANIAL BIN ABDUL MALEK (23304282)
//                6. GOH DE SHENG (23301529)
//
// Project Description: This project is a vending machine program that allows user to select the product and quantity they want to purchase. The program will then calculate the total price of the product and prompt the user to enter the money. If the money entered is sufficient, the program will update the stock and return the change to the user. The program also allows the user to save the inventory and load the inventory.
//================================================================================================================================================//

#include "vendingMachine.hpp"   // Header file.
#include <iostream>             // To perform input and output operations.
#include <string>               // Provides std::string class.
#include <vector>               // To store data in a sequential container.

using namespace std;

int main(){

    vendingMachine vm;
    int choice;
    int quantity;
    double money;

    vm.displayProducts();
    void loadInventory();
    vm.selectProduct(to_string(choice), quantity, money);
    
    return 0;
}
