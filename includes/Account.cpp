#include <iostream>
#include<fstream>
#include "json.hpp"
using json = nlohmann::json;
#include "Account.h"

//***********Account Constructor*************///

    Account::Account(string fname,string lname,float balance)
    {
        //gather the next account number for the next object instance. Using the function. 

        this->accountNumber = getNextAccountNumber();
        this->fname = fname;
        this->lname = lname;
        this->balance = balance;
    }

int Account::getNextAccountNumber()
{
        //increment the next account number and return it 
        return nextAccountNumber++;
}

//initialise the account number
int Account::nextAccountNumber = 1;
//AccountFunctions
ostream& operator<<(ostream& os, const Account& obj) {
    os << "your first name is: " << obj.fname;
    return os;
}

string Account::getFName() {return fname;}
string Account::getLName() {return lname;}
float Account::getBalance() {return balance;}
int Account::getAccNumber() {return accountNumber;}
