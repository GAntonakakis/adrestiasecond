#include <iostream>
#include <random>
#include <queue>
#include <string>
#include <cctype>
#include <thread>
#include <chrono>
#include <algorithm>

using namespace std;

// ANSI color codes
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"

class Product {
    private:
        string pName;
        int pPrice, pQuantity;
        bool isCan;

    public:
        
        Product() : pName(""), pPrice(0), pQuantity(0), isCan(true) {}
        // Constructor
        Product(string n, int p, int q, bool state)
            : pName(n), pPrice(p), pQuantity(q), isCan(state) {}

        // Getters & Setters
        string getName() const {
            return pName;
        }

        bool getIsCan() const {
            return isCan;
        }

        int getPrice() const {
            return pPrice;
        }

        int getQuantity() const {
            return pQuantity;
        }

        void setName(const string &n) {
            pName = n;
        }

        void setIsCan(bool state) {
            isCan = true;
        }

        void setPrice(int p) {
            pPrice = p;
        }

        void setQuantity(int q) {
            pQuantity = q;
        }
};
   

class Machine {
    private:
        static const int size = 4;
        Product productsInMachine[size];
        int balance;
    public:
        Machine() : productsInMachine(), balance (0) {} 
        //constructor
        Machine(const Product* prodArr, int b) : balance(b) {
                for (int i = 0; i < size; ++i){
                    productsInMachine[i] = prodArr[i];
                }
            }
        //getters & setters
        Product getProducts(int x) const {
            return productsInMachine[x];
        }
        int getBalance() const {
            return balance;
        }
        void setProducts(Product x, int y) {
            productsInMachine[y] = x;
        }
        void setBalance(int y) {
            balance = y;
        }
};      

// Function to convert a string to lowercase, for reading incesensitive inputs
string toLowercase(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return tolower(c); });
    return result;
}

// Function to resize a string to exactly n characters ---> used for making the startup graphic
string resizeString(const std::string& str, size_t n, char padChar = ' ') {
    if (str.size() > n) {
        // Truncate the string if it's longer than n
        return str.substr(0, n);
    } else if (str.size() < n) {
        // Pad the string with padChar if it's shorter than n
        return str + std::string(n - str.size(), padChar);
    }
    // Return the string as is if it's already n characters long
    return str;
}

int main(){
    string displayPName, userInput, userInputInsensitive;
    int displayPPrice, displayPQuantity, inputMoneyTest, oneEuros, twoEuros, fiveEuros;
    int displayVariance = 1;
    int checkDuplicates [5] = {0,0,0,0,0};
    int machineBalance = 0;
    int inputChoice = 0;
    bool displayIsCan;
    bool checkDuplicatesPassed = false;
    bool isValidInput = false;

    string input;
    size_t desiredLength = 11;

    // creating instances of our products
    Product topLeftProduct("Product", 1, 1, true);
    Product topRightProduct("Product", 1, 1, true);
    Product bottomLeftProduct("Product", 1, 1, true);
    Product bottomRightProduct("Product", 1, 1, true);
    Product productsAvailable[4] = {topLeftProduct, topRightProduct, bottomLeftProduct, bottomRightProduct};
    Machine vendingMachine(productsAvailable, 0);


    //randomness factor
    random_device rd;
    mt19937 rng(rd()); // Mersenne Twister
    uniform_int_distribution<int> productRandomness(1, 8); // Randomly pick one of random products between 1 and 8
    uniform_int_distribution<int> quantityRandomness(0, 6); // Pick a random quantity between 0 and 6

    //filling the machine with random products
    for (int i = 1; i <= 4; ++i) {
       
        //check for duplicates, so no 2 similar products are picked
        checkDuplicatesPassed = false;
        while (checkDuplicatesPassed == false){
            checkDuplicatesPassed = true;
            displayVariance = productRandomness(rng);
            for (int q = i-1; q >= 1; --q){
                if (displayVariance == checkDuplicates[q]){
                    checkDuplicatesPassed = false;
                }
            }
        }
        checkDuplicates[i] = displayVariance;
        displayPQuantity = quantityRandomness(rng);

        switch (displayVariance) {
            case 1:
                displayPName = "Coke";
                displayPPrice = 2;
                displayIsCan = true;
                break;
            case 2:
                displayPName = "Sprite";
                displayPPrice = 2;
                displayIsCan = true;
                break;
            case 3:
                displayPName = "Fanta";
                displayPPrice = 2;
                displayIsCan = true;
                break;
            case 4:
                displayPName = "Crisps";
                displayPPrice = 3;
                displayIsCan = false;
                break;
            case 5:
                displayPName = "Kit Kat";
                displayPPrice = 3;
                displayIsCan = false;
                break;
            case 6:
                displayPName = "Protein Bar";
                displayPPrice = 4;
                displayIsCan = false;
                break;
            case 7:
                displayPName = "Ice Cream";
                displayPPrice = 6;
                displayIsCan = false;
                break;
            case 8:
                displayPName = "Water";
                displayPPrice = 1;
                displayIsCan = true;
                break;
        }
        if (i==1){
            topLeftProduct.setName(displayPName);
            topLeftProduct.setPrice(displayPPrice);
            topLeftProduct.setIsCan(displayIsCan);
            topLeftProduct.setQuantity(displayPQuantity);
        } else if (i==2){
            topRightProduct.setName(displayPName);
            topRightProduct.setPrice(displayPPrice);
            topRightProduct.setIsCan(displayIsCan);
            topRightProduct.setQuantity(displayPQuantity);
        } else if (i==3){
            bottomLeftProduct.setName(displayPName);
            bottomLeftProduct.setPrice(displayPPrice);
            bottomLeftProduct.setIsCan(displayIsCan);
            bottomLeftProduct.setQuantity(displayPQuantity);
        } else if (i==4){
            bottomRightProduct.setName(displayPName);
            bottomRightProduct.setPrice(displayPPrice);
            bottomRightProduct.setIsCan(displayIsCan);
            bottomRightProduct.setQuantity(displayPQuantity);

        } else {}
       
    }

    // Ensure the string has exactly the desired length
    string resizedString1 = resizeString(topLeftProduct.getName(), desiredLength);
    string resizedString2 = resizeString(topRightProduct.getName(), desiredLength);
    string resizedString3 = resizeString(bottomLeftProduct.getName(), desiredLength);
    string resizedString4 = resizeString(bottomRightProduct.getName(), desiredLength);

    //graphics at start
    cout << " _______________________________________________________________________________________________________________" << endl;
    this_thread::sleep_for(chrono::milliseconds(100));
    cout << "|                                                                                                               |" << endl;
    this_thread::sleep_for(chrono::milliseconds(100));
    cout << "|                                              _________________                                                |" << endl;
    this_thread::sleep_for(chrono::milliseconds(100));
    cout << "|                                             |                 |                                               |" << endl;
    this_thread::sleep_for(chrono::milliseconds(100));
    cout << "|                                             |  " << CYAN << "Welcome to the " << RESET << "|                                               |" << endl;
    this_thread::sleep_for(chrono::milliseconds(100));
    cout << "|                                             | " << CYAN << "Vending Machine!" << RESET << "|                                               |" << endl;
    this_thread::sleep_for(chrono::milliseconds(100));
    cout << "|                                             |_________________|                                               |" << endl;
    this_thread::sleep_for(chrono::milliseconds(100));
    cout << "|                                                                                                               |" << endl;
    this_thread::sleep_for(chrono::milliseconds(100));
    cout << "|                                                                                                               |" << endl;
    this_thread::sleep_for(chrono::milliseconds(100));
    cout << "|                                                                                                               |" << endl;
    this_thread::sleep_for(chrono::milliseconds(100));
    cout << "|       __________________________                                             __________________________       |" << endl;
    this_thread::sleep_for(chrono::milliseconds(100));
    cout << "|      |                          |                                           |                          |      |" << endl;
    this_thread::sleep_for(chrono::milliseconds(100));
    cout << "|      |         " << MAGENTA << resizedString1 << RESET << "      |                                           |         " << MAGENTA << resizedString2 << RESET << "      |      |" << endl;
    this_thread::sleep_for(chrono::milliseconds(100));
    cout << "|      |             " << YELLOW << topLeftProduct.getPrice() << "$" << RESET << "           |                                           |             " << YELLOW << topRightProduct.getPrice() << "$" << RESET << "           |      |" << endl;
    this_thread::sleep_for(chrono::milliseconds(100));
    cout << "|      |__________________________|                                           |__________________________|      |" << endl;
    this_thread::sleep_for(chrono::milliseconds(100));
    cout << "|                                                                                                               |" << endl;
    this_thread::sleep_for(chrono::milliseconds(100));
    cout << "|                                                                                                               |" << endl;
    this_thread::sleep_for(chrono::milliseconds(100));
    cout << "|                                                                                                               |" << endl;
    this_thread::sleep_for(chrono::milliseconds(100));
    cout << "|       __________________________                                             __________________________       |" << endl;
    this_thread::sleep_for(chrono::milliseconds(100));
    cout << "|      |                          |                                           |                          |      |" << endl;
    this_thread::sleep_for(chrono::milliseconds(100));
    cout << "|      |         " << MAGENTA << resizedString3 << RESET << "      |                                           |         " << MAGENTA << resizedString4 << RESET << "      |      |" << endl;
    this_thread::sleep_for(chrono::milliseconds(100));
    cout << "|      |             " << YELLOW << bottomLeftProduct.getPrice() << "$" << RESET << "           |                                           |             " << YELLOW << bottomRightProduct.getPrice() << "$" << RESET << "           |      |" << endl;
    this_thread::sleep_for(chrono::milliseconds(100));
    cout << "|      |__________________________|                                           |__________________________|      |" << endl;
    this_thread::sleep_for(chrono::milliseconds(100));
    cout << "|                                                                                                               |" << endl;
    this_thread::sleep_for(chrono::milliseconds(100));
    cout << "|                                                                                                               |" << endl;
    this_thread::sleep_for(chrono::milliseconds(100));
    cout << "|_______________________________________________________________________________________________________________|" << endl;
    this_thread::sleep_for(chrono::milliseconds(300));

    cout << endl << YELLOW << "Please input currency into the machine. (Input a number)" << RESET << endl; 
    getline(cin, userInput);
    this_thread::sleep_for(chrono::milliseconds(500));

    while (isValidInput == false){
        // Validate input for integers only
        for (char c : userInput) {
            if (!isdigit(c)) {
                isValidInput = false;
                break;
            } else {
                isValidInput = true;
            }
        }
        if (isValidInput) {
            // Convert string to integer using std::stoi
            inputMoneyTest = stoi(userInput);
            vendingMachine.setBalance(inputMoneyTest);

            // convert in 1euros 2euros and 5euros
            fiveEuros = inputMoneyTest / 5;
            twoEuros = (inputMoneyTest - (fiveEuros * 5)) / 2;
            oneEuros = (inputMoneyTest - (fiveEuros * 5) - (twoEuros * 2)); 

            // Display the integer valuer
            if ((fiveEuros > 0) && (twoEuros > 0) && (oneEuros > 0)){
                cout << "You inserted " << YELLOW << fiveEuros << "x" << RESET << " " << "5$ note(s), " << YELLOW << twoEuros << "x" << RESET << " " << "2$ coin(s) and " << YELLOW << oneEuros << "x" << RESET << " " << "1$ coin! " << YELLOW << "(" << inputMoneyTest << "$)" << RESET << endl;
            } else if ((fiveEuros > 0) && (twoEuros > 0) && (oneEuros <= 0)){
                cout << "You inserted " << YELLOW << fiveEuros << "x" << RESET << " " << "5$ note(s) and " << YELLOW << twoEuros << "x" << RESET << " " << "2$ coin(s)! " << YELLOW << "(" << inputMoneyTest << "$)" << RESET << endl; 
            } else if ((fiveEuros > 0) && (twoEuros <= 0) && (oneEuros <= 0)){
                cout << "You inserted " << YELLOW << fiveEuros << "x" << RESET << " " << "5$ note(s)! " << YELLOW << "(" << inputMoneyTest << "$)" << RESET << endl; 
            } else if ((fiveEuros > 0) && (twoEuros <= 0) && (oneEuros > 0)){
                cout << "You inserted " << YELLOW << fiveEuros << "x" << RESET << " " << "5$ note(s) and " << YELLOW << oneEuros << "x" << RESET << " " << "1$ coin! " << YELLOW << "(" << inputMoneyTest << "$)" << RESET << endl;
            } else if ((fiveEuros <= 0) && (twoEuros > 0) && (oneEuros > 0)){
                cout << "You inserted " << YELLOW << twoEuros << "x" << RESET << " " << "2$ coin(s) and " << YELLOW << oneEuros << "x" << RESET << " " << "1$ coin! " << YELLOW << "(" << inputMoneyTest << "$)" << RESET << endl;
            } else if ((fiveEuros <= 0) && (twoEuros > 0) && (oneEuros <= 0)){
                cout << "You inserted " << YELLOW << twoEuros << "x" << RESET << " " << "2$ coin(s)! " << YELLOW << "(" << inputMoneyTest << "$)" << RESET << endl;
            } else {
                cout << "You inserted " << YELLOW << oneEuros << "x" << RESET << " " << "1$ coin(s)! " << YELLOW << "(" << inputMoneyTest << "$)" << RESET << endl;    
            }
        } else {
        cout << "This machine only accepts coins of 1$ and 2$ and notes of 5$. " << YELLOW << "(Please input a number)" << RESET << endl;
        getline(cin, userInput);
        }
    };
    
    // Wait
    this_thread::sleep_for(chrono::milliseconds(2300));

    do
    {
        cout << endl
             << "Your balance is : " << YELLOW << vendingMachine.getBalance() << "$" << RESET << "." << endl;
        this_thread::sleep_for(chrono::milliseconds(600));     
        cout << endl
             << "1. Buy " << GREEN << topLeftProduct.getName() << RESET << " for " << topLeftProduct.getPrice() << "$. ";
        if ((topLeftProduct.getQuantity()) == 0)
        {
            cout << RED;
        }
        else
        {
            cout << YELLOW;
        }
        cout << "(" << topLeftProduct.getQuantity() << " items left.)" << RESET << endl;
        this_thread::sleep_for(chrono::milliseconds(600));
        cout << "2. Buy " << GREEN << topRightProduct.getName() << RESET << " for " << topRightProduct.getPrice() << "$. ";
        if ((topRightProduct.getQuantity()) == 0)
        {
            cout << RED;
        }
        else
        {
            cout << YELLOW;
        }
        cout << "(" << topRightProduct.getQuantity() << " items left.)" << RESET << endl;
        this_thread::sleep_for(chrono::milliseconds(600));
        cout << "3. Buy " << GREEN << bottomLeftProduct.getName() << RESET << " for " << bottomLeftProduct.getPrice() << "$. ";
        if ((bottomLeftProduct.getQuantity()) == 0)
        {
            cout << RED;
        }
        else
        {
            cout << YELLOW;
        }
        cout << "(" << bottomLeftProduct.getQuantity() << " items left.)" << RESET << endl;
        this_thread::sleep_for(chrono::milliseconds(600));
        cout << "4. Buy " << GREEN << bottomRightProduct.getName() << RESET << " for " << bottomRightProduct.getPrice() << "$. ";
        if ((bottomRightProduct.getQuantity()) == 0)
        {
            cout << RED;
        }
        else
        {
            cout << YELLOW;
        }
        cout << "(" << bottomRightProduct.getQuantity() << " items left.)" << RESET << endl;
        this_thread::sleep_for(chrono::milliseconds(600));
        cout << "5. Don't buy anything." << endl;

        this_thread::sleep_for(chrono::milliseconds(1600));
        cout << endl
             << "What would you like to buy?" << YELLOW << " (Please input a number or the product name.)" << RESET << endl
             << endl;

        getline(cin, userInput);
        userInput = toLowercase(userInput);
        
        // Input a word and check if the word is in the string
        if ((userInput.find(toLowercase(topLeftProduct.getName())) != string::npos) || (userInput == "1")){
            if (topLeftProduct.getQuantity() <= 0){
                cout << RED << "Out of stock!" << RESET << endl;
            } else if (topLeftProduct.getPrice() > vendingMachine.getBalance()){
                cout << RED << "Insufficient funds in your balance!" << RESET << endl;
            } else {
                topLeftProduct.setQuantity(topLeftProduct.getQuantity() - 1);
                vendingMachine.setBalance(vendingMachine.getBalance() - topLeftProduct.getPrice());
                cout << "Transaction successful!" << endl << MAGENTA << "Enjoy your " << topLeftProduct.getName() << "!" << RESET << endl;
            }
            this_thread::sleep_for(chrono::milliseconds(2500));            
        } else if ((userInput.find(toLowercase(topRightProduct.getName())) != string::npos) || (userInput == "2")){
            if (topRightProduct.getQuantity() <= 0){
                cout << RED << "Out of stock!" << RESET << endl;
            } else if (topRightProduct.getPrice() > vendingMachine.getBalance()){
                cout << RED << "Insufficient funds in your balance!" << RESET << endl;
            } else {
                topRightProduct.setQuantity(topRightProduct.getQuantity() - 1);
                vendingMachine.setBalance(vendingMachine.getBalance() - topRightProduct.getPrice());
                cout << "Transaction successful!" << endl << MAGENTA << "Enjoy your " << topRightProduct.getName() << "!" << RESET << endl;
            }
            this_thread::sleep_for(chrono::milliseconds(2500));            
        } else if ((userInput.find(toLowercase(bottomLeftProduct.getName())) != string::npos) || (userInput == "3")){
            if (bottomLeftProduct.getQuantity() <= 0){
                cout << RED << "Out of stock!" << RESET << endl;
            } else if (bottomLeftProduct.getPrice() > vendingMachine.getBalance()){
                cout << RED << "Insufficient funds in your balance!" << RESET << endl;
            } else {
                bottomLeftProduct.setQuantity(bottomLeftProduct.getQuantity() - 1);
                vendingMachine.setBalance(vendingMachine.getBalance() - bottomLeftProduct.getPrice());
                cout << "Transaction successful!" << endl << MAGENTA << "Enjoy your " << bottomLeftProduct.getName() << "!" << RESET << endl;
            }
            this_thread::sleep_for(chrono::milliseconds(2500));            
        } else if ((userInput.find(toLowercase(bottomRightProduct.getName())) != string::npos) || (userInput == "4")){
            if (bottomRightProduct.getQuantity() <= 0){
                cout << RED << "Out of stock!" << RESET << endl;
            } else if (bottomRightProduct.getPrice() > vendingMachine.getBalance()){
                cout << RED << "Insufficient funds in your balance!" << RESET << endl;
            } else {
                bottomRightProduct.setQuantity(bottomRightProduct.getQuantity() - 1);
                vendingMachine.setBalance(vendingMachine.getBalance() - bottomRightProduct.getPrice());
                cout << "Transaction successful!" << endl << MAGENTA << "Enjoy your " << bottomRightProduct.getName() << "!" << RESET << endl;
            }
            this_thread::sleep_for(chrono::milliseconds(2500));            
        } else {
            if (userInput != "5"){
                cout << RED << "Incorrect choice / snack not found! Please choose again." << RESET << endl;
                this_thread::sleep_for(chrono::milliseconds(2500));
            }

        };
        
        
        
        
       

    } while (userInput != "5");

    // convert in 1euros 2euros and 5euros
    inputMoneyTest = vendingMachine.getBalance();
    fiveEuros = inputMoneyTest / 5;
    twoEuros = (inputMoneyTest - (fiveEuros * 5)) / 2;
    oneEuros = (inputMoneyTest - (fiveEuros * 5) - (twoEuros * 2)); 
    cout << CYAN << "Thank you!" << RESET << endl;
    this_thread::sleep_for(chrono::milliseconds(1000));
    cout << "You receive "; 
    if ((fiveEuros > 0) && (twoEuros > 0) && (oneEuros > 0)){
                cout << YELLOW << fiveEuros << "x" << RESET << " " << "5$ note(s), " << YELLOW << twoEuros << "x" << RESET << " " << "2$ coin(s) and " << YELLOW << oneEuros << "x" << RESET << " " << "1$ coin as change! " << YELLOW << "(" << inputMoneyTest << "$)" << RESET << endl;
            } else if ((fiveEuros > 0) && (twoEuros > 0) && (oneEuros <= 0)){
                cout << YELLOW << fiveEuros << "x" << RESET << " " << "5$ note(s) and " << YELLOW << twoEuros << "x" << RESET << " " << "2$ coin(s) as change! " << YELLOW << "(" << inputMoneyTest << "$)" << RESET << endl; 
            } else if ((fiveEuros > 0) && (twoEuros <= 0) && (oneEuros <= 0)){
                cout << YELLOW << fiveEuros << "x" << RESET << " " << "5$ note(s) as change! " << YELLOW << "(" << inputMoneyTest << "$)" << RESET << endl; 
            } else if ((fiveEuros > 0) && (twoEuros <= 0) && (oneEuros > 0)){
                cout << YELLOW << fiveEuros << "x" << RESET << " " << "5$ note(s) and " << YELLOW << oneEuros << "x" << RESET << " " << "1$ coin as change! " << YELLOW << "(" << inputMoneyTest << "$)" << RESET << endl;
            } else if ((fiveEuros <= 0) && (twoEuros > 0) && (oneEuros > 0)){
                cout << YELLOW << twoEuros << "x" << RESET << " " << "2$ coin(s) and " << YELLOW << oneEuros << "x" << RESET << " " << "1$ coin as change! " << YELLOW << "(" << inputMoneyTest << "$)" << RESET << endl;
            } else if ((fiveEuros <= 0) && (twoEuros > 0) && (oneEuros <= 0)){
                cout << YELLOW << twoEuros << "x" << RESET << " " << "2$ coin(s) as change! " << YELLOW << "(" << inputMoneyTest << "$)" << RESET << endl;
            } else {
                cout << YELLOW << oneEuros << "x" << RESET << " " << "1$ coin(s) as change! " << YELLOW << "(" << inputMoneyTest << "$)" << RESET << endl;    
            }


    return 0;
}