#pragma once
#include <iostream>
using namespace std;
#include "Account.h"

class Bank 
{

    static int NumberOfAccounts; 

    private: 
    string bank_name = "Andy's Bank";
    
    public: 
    ///*****Constructors****/////
    Bank();
    ///*********************Member Functions*****************////////////////////

    //function to create an account
    void closeAccount();
    //delete an Account class object
    void deposit();
    //Read in data and store somewhere
    void withdraw();
    //read data stored in somewhere, remove it from storage, display to user
    void displayBalance();
    //function to check for valid name input
    bool validName(string name);
    void showAccounts();
    void createTransactionHistory(int accountNumber);
    void accountToFile(Account*& acc);
    void createAccount(string fname, string lname, float balance);
    ///*******************Destructors**********************/////////
    ~Bank();

};