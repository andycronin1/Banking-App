#pragma once
#include <iostream>
using namespace std;

class Account
{
    private:
    
    string fname;
    string lname;
    float balance;
    int accountNumber;

    public:
    
    //static member so all classes have access to the counter for next account number
    static int nextAccountNumber;
    
    ////*****************Constructors******************////
    Account(string fname,string lname,float balance);
    

    ///*************Member Functions******************///////////
    friend ifstream;
    friend class Bank;
    friend void depositMoney();
    string getFName();
    string getLName();
    float getBalance();
    int getNextAccountNumber();
    int getAccNumber();

    friend ostream& operator<<(ostream& os, const Account& obj);

};