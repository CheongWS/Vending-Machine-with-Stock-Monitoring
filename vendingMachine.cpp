// Programmers name (entire .cpp): LIM ZHAN HUNG
// Matrix ID                     : 23301019
// Purpose                       : This .cpp is to define the main functions of a fully functional vending machine. 
// Limitations                   : This program is not viable for the case of a forgotten password to prevent security breach.

#include "vendingMachine.hpp"       // Header file.
#include "payment.hpp"              // Header file.
#include "product.hpp"              // Header file.          
#include "staff.hpp"                // Header file.
#include <iostream>                 // To perform input and output operations.
#include <iomanip>                  // To assign precise decimal places and formatting stock display.               
#include <string>                   // Provides std::string class.
#include <vector>                   // To store data in a sequential container.
#include <fstream>                  // To perform input and output operations on files.
#include <limits>                   // Defines various properties and limitations of fundamental numeric types.
#include <algorithm>                // To perform a range of elements in a container.

using namespace std;

// Programmers name (this function): CHEONG WYE SHEN                           //
// Purpose                         : Constructor for the vendingMachine class. //
vendingMachine::vendingMachine() {
    // Attempt to load inventory from the file //
    loadInventory();

    // If the inventory is still empty (e.g., file not found), initialize default products //
    if (products.empty()) {
        initial(products);
    }
}

// Programmers name (this function): CHEONG WYE SHEN                               //
// Purpose                         : To load the inventory of the vending machine. //
void vendingMachine::loadInventory() {
    ifstream inputFile("inventory.txt");
    string line;
    products.clear();  // Clear the existing products.
    
    while (getline(inputFile, line)) {
        stringstream ss(line);
        string name, priceStr, quantityStr;
        double price;
        int quantity;

        // Parse the line using '|' as a delimiter //
        getline(ss, name, '|');
        getline(ss, priceStr, '|');
        getline(ss, quantityStr, '|');

        // Convert price and quantity to their respective types //
        price = stod(priceStr);
        quantity = stoi(quantityStr);

        // Add the product to the products vector //
        products.push_back(Product(name, price, quantity));
    }

    inputFile.close();
}

// To initialize the vending machine with default products if it is empty //
void vendingMachine::initial(vector<Product>& products) {
    if (products.empty()) {
        products.push_back(Product("Coca Cola", 2.00, 20));
        products.push_back(Product("Kit Kat", 1.50, 20));
        products.push_back(Product("Lays", 4.00, 20));
        products.push_back(Product("M&M", 2.00, 20));
        products.push_back(Product("Maggi Hot Cup", 3.00, 20));
        products.push_back(Product("Milo", 2.50, 20));
        products.push_back(Product("Nescafe Coffee", 3.00, 20));
        products.push_back(Product("Oreo", 2.00, 20));
        products.push_back(Product("Pepsi", 2.00, 20));
        products.push_back(Product("Sprite", 1.50, 20));
    }
}

// Programmers name (this function): CHEONG WYE SHEN           //
// Purpose                         : Populating the stock map. //
void vendingMachine::populateStockMap() {
    stock.clear(); // Clear the existing stock map
    for (const auto& product : products) {
        stock[product.getName()] = product.getQuantity();
    }
}
// Programmers name (this function): CHEONG WYE SHEN           //
// Purpose                         : Populating the price map. //
void vendingMachine::populatePriceMap() { 
    prices.clear(); // Clear the existing prices map
    for (const auto& product : products) {
        prices[product.getName()] = product.getPrice();
    }
}

// Displaying the products in the vending machine //
void vendingMachine::displayProducts() {
    loadInventory();
    cout << "==========================================================================================================" << endl;
    cout << "                                     Welcome to EE123 vending machine!                                    " << endl;
    cout << "==========================================================================================================" << endl;
    cout << "                                 Here are the list of products available:                                 " << endl;
    cout << "==========================================================================================================" << endl;
    cout << left << setw(34) << "Product Name" << setw(24) << "Price" << setw(15) << "Quantity" << endl;
    cout << "==========================================================================================================" << endl;

    for (int i = 0; i < 10; i++) {
        cout << setw(2) << (i+1) <<setw(1) << ". " << setw(30) << products[i].name
             << setw(27) << setprecision(2)<< fixed << products[i].price
             << setw(13) << products[i].quantity << endl;
    }

    cout << "11. Staff Menu" << endl;
    cout << "==========================================================================================================" << endl;
    cout << "Enter the product number (1-10). Enter 0 to exit the vending machine." << endl;
}


// Selecting the product from the vending machine //
void vendingMachine::selectProduct(string choice, int quantity, double money) {
    while (true) {
        cout << "Enter the product number (0 to exit, 1-10 to select a product, 11 for staff menu) > ";
        cin >> choice;

        if (choice.length() < 1 || choice.length() > 2 || !std::all_of(choice.begin(), choice.end(), ::isdigit)) {
            cout << "\nInvalid input! Please enter a valid number (1-11).\n";
            continue;
        }

        // Convert the input string to an integer
        int choiceNum = std::stoi(choice);

        // Check if the number is within the valid range
        if (choiceNum < 0 || choiceNum > 11) {
            cout << "\nInvalid input! Please enter a number between 0 and 11.\n";
            continue;
        }

        switch (choiceNum) {
            case 0:
                cout << "Thank you for using our vending machine!" << endl;
                return;  // Exit the vending machine.

            case 11:
                if (staffLogin()) {
                    staffMenu();  // Access the staff menu.
                    loadInventory();
                    displayProducts();
                    }
                break;

            default:
                // Handle product selection
                int productIndex = choiceNum - 1;

                enterQuantity(quantity); // Enter the quantity of the product.
                if (quantity == 0) {
                    displayProducts(); // If the user cancels, go back to the beginning of the loop.
                    break;
                }

                if (checkStock(products[productIndex], quantity)) { // Check if the product is in stock.
                    total_price(products[productIndex], quantity); // Calculate the total price.
                    enterMoney(money); // Enter the money
                        if (money == 0) {
                            displayProducts(); // If the user cancels, go back to the beginning of the loop.
                            break;
                        }
                        if (process_payment(products[productIndex], quantity, money)) { // Process the payment.
                            updateStock(products[productIndex], quantity); // Update the stock quantity.
                            cout << "Thank you for your purchase!" << endl; // Displayed when the payment is successful.
                            displayProducts(); // Exit the loop after a successful purchase.
                        } else {
                            cout << "Payment failed! Please try again." << endl; // Displayed when the payment is unsuccessful.
                            displayProducts(); // Go back to the beginning of the loop to select another product.
                        }
                } else {
                    cout << "Out of stock!" << endl; // Displayed when the product is out of stock.
                    displayProducts(); // Go back to the beginning of the loop to select another product.
                }
            break; // Exit the switch statement.          
        }   
    }
}

// Monitoring the stock of the vending machine //
void vendingMachine::updateStock(Product product, int quantity){
    for(int i = 0; i < 10; i++){
        if(products[i].name == product.name){
            products[i].quantity -= quantity;
            saveInventory();
        }
    }
}

// Checking the availabilty of the product in the vending machine //
bool vendingMachine::checkStock(Product product, int quantity){
    for(int i = 0; i < 10; i++){
        if(products[i].name == product.name){
            if(products[i].quantity >= quantity){
                return true;
            }
        }
    }
    return false;
}

// Entering quantity of the product to purchase //
void vendingMachine::enterQuantity(int& quantity) {
    while (true) {
        string input;
        cout << "Enter 0 to cancel purchase." << endl;
        cout << "Enter the quantity in unit(s) > ";
        cin >> input;
        
        // Check for decimal points in input //
        if (input.find('.') != string::npos) {
            cout << "Decimal numbers are not allowed! Please enter a whole number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        // Try to convert string to integer //
        try {
            quantity = stoi(input);
        } catch (const invalid_argument&) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a valid quantity." << endl;
            continue;
        }

        if (cin.fail()) {  // Check if the input is invalid (non-numeric).
            cin.clear(); // Clear the error flag.
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the input.
            cout << "Invalid input! Please enter a valid quantity." << endl;
            continue; // Continue to the next step if a valid quantity is entered.
        } else if (quantity == 0) { // Handle cancel purchase.
            cout << "Purchase cancelled!" << endl;
            return; // Exit the function after cancelling the purchase.
        } else if (quantity < 0) { // Check if quantity is negative.
            cout << "Quantity cannot be negative!" << endl;
            continue; // Continue to the next step if a valid quantity is entered.
        } else {
            break; // Exit the loop if a valid quantity is entered.
        }
    }
}


// Entering the money (payment) //
void vendingMachine::enterMoney(double& money) {
    while (true) { // Looping until the user enters a valid amount of money.
        cout << "Enter 0 to cancel purchase." << endl;
        cout << "Enter the money > RM ";
        cin >> money;
        
        if (cin.fail()) {  // Check if the input is invalid (non-numeric).
            cin.clear(); // Clear the error flag.
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the input.
            cout << "Invalid input! Please enter a valid amount of money." << endl;
            continue; // Continue to the next step if a valid amount of money is entered.
        } else if (money == 0) { // Handle cancel purchase.
            cout << "Purchase cancelled!" << endl;
            return; // Exit the function after cancelling the purchase.
        } else if (money < 0) { // Check if money is negative.
            cout << "Amount cannot be negative!" << endl;
            continue; // Continue to the next step if a valid amount of money is entered.
        } else {
            break; // Exit the loop if a valid amount of money is entered.
        }
    }
}

// Programmers name (this function): CHEONG WYE SHEN                          //
// Purpose                         : Updating the vector from the map         //
void vendingMachine::updateVectorFromMap(vector<Product>& products, const map<string, int>& stock, const map<string, double>& prices) {
    products.clear(); // Clear existing data in vector.
    
    // Loop through stock map //
    for (const auto& entry : stock) {
        string name = entry.first;
        int quantity = entry.second;
        double price = prices.at(name);  // Get price from prices map.

        // Create product and add to vector //
        products.push_back(Product{name, price, quantity});
    }
}

// Saving the inventory of the vending machine //
void vendingMachine::saveInventory(){
    ofstream outFile("inventory.txt");
        for(int i = 0; i < 10; i++){
            products[i].saveToFile(outFile); // Saving the products to the file.
        }
    outFile.close();
}
