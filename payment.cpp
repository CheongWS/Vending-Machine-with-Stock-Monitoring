// Programmers name (entire .cpp): LIM ZHAN HUNG
// Matrix ID                     : 23301019
// Purpose                       : This .cpp file is to define the functions for the payment process of the vending machine.
// Limitations                   : This program is not viable for the case where QRpay or a banking card payment is used. 

#include "payment.hpp"      // Header file.
#include "product.hpp"      // Header file.
#include <iostream>         // To perform input and output operations.
#include <iomanip>          // To assign precise decimal places for the prices.

using namespace std;

// Calculating the total price //
void total_price (Product product, int quantity){
    double total = product.price * quantity;
    cout << "Total price: RM " << setprecision(2) << total << endl;
}

// Calculating the change to return to customer //
void calc_change (double price, double money){
    double change = money - price;
    cout << "Change: RM " << setprecision(2) << change << endl;
}

// Processing the payment //
bool process_payment (Product product, int quantity, double money){
    double total = product.price * quantity;
    if(money >= total){ // To check if the payment is sufficient.
        cout << "Payment successful!" << endl; 
        calc_change(total, money);
        saveSales(product, quantity);
        return true;
    }
    else{
        cout << "Insufficient payment!" << endl;
        cout << "Returning money..." << endl;
        return false;
    }
}

//Saving the sales to the file
void saveSales(Product product, int quantity){
    ofstream outFile("sales.txt", ios::app);
    outFile << product.name << "|" << product.price << "|" << quantity << "|" << product.price * quantity << endl;
    outFile.close();
}
