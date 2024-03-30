#include <iostream>
#include<fstream>
#include "json.hpp"
using json = nlohmann::json;
#include "Bank.h"
#include "Account.h"

    ///*****Bank Constructor****/////
    Bank::Bank()
    {
    //checking if file exits. If not, create empty array in file. 
    ifstream inputFile("AllAccountDetails.json");
    if(!inputFile.is_open())
    { 
    static ofstream ofs("AllAccountDetails.json", ios::app);
    json new_object = json::object();
    new_object["Accounts"] = json::array();
    new_object["Transactions"] = json::array();
    ofs << new_object;
    ofs.close();
    }
    }

    //Bank initialisors 
int Bank::NumberOfAccounts = 0;
//Bank Functions
bool Bank::validName(string name)
{   
    // Use getline to handle spaces in input
    for (char c : name) {
        if (!isalpha(c)) {
            //return true if invalid characters found
            cout << "Please Enter a valid Name: " << endl;
            return false;
        }
    }
    //return false if no invalid characters found
    return true;
}
void Bank::showAccounts()
{
    ifstream infile; 
    infile.open("AllAccountDetails.json");
    if(!infile)
    {
        cout << "File cannot be opened";
    }
    unique_ptr<json> UserAcc(new json);
    infile >> *UserAcc;
    cout << "***Accounts***" << "\n";
    for(auto &it : (*UserAcc)["Accounts"])
        cout << "Last Name" << it["Last Name"] && cout << "Account Number: " << it["Account Number"] << "\n";
    if(infile.eof()) cout << "End of File";
    infile.close();   
}
void Bank::displayBalance()
{
   int accountNumber;
   bool validAccount = false;
   ifstream AccountDeets("AllAccountDetails.json");
   unique_ptr<json> AccountData(new json);
   AccountDeets >> *AccountData;
   while(validAccount != true)
   {
   cout << "Please enter your account number: " << endl;
   cin >> accountNumber;
   for(auto &it : (*AccountData)["Accounts"])
   {
        if(it["Account Number"] == accountNumber)
        {
        cout << "Your balance is: " << it["Balance"] << endl;
        validAccount = true;
        break;
        }
   }
    if(validAccount !=  true)
   {
    std::cout << "Please enter valid account number: " << endl;
   }
   }
}
void Bank::deposit()
{
   int accountNumber;
   float depositAmount;
   bool validAccount = false;
   //importing json file
   ifstream AccountDeets("AllAccountDetails.json");
   //creating new unqiue pointer and storing JSON data inside for modification
   unique_ptr<json> AccountData(new json);
   AccountDeets >> *AccountData;
   //setting up while loop to find account and add money 
   while(validAccount != true)
   {
   cout << "Please enter your account number: " << endl;
   cin >> accountNumber;
   for(auto &it : (*AccountData)["Accounts"])
   {
        if(it["Account Number"] == accountNumber)
        {
        validAccount = true;
        cout << "How much would you like to deposit?: " << endl;
        cin >> depositAmount;
        cout << "Your original balance was: " << it["Balance"] << endl;
        float oldAmount = it["Balance"];
        auto newAmount = oldAmount + depositAmount;
        it["Balance"] = newAmount;
        cout << "Your deposit amount is: " << depositAmount << endl;
        cout << "Your new balance is: " << it["Balance"] << endl;
        break;
        }
   }
    if(validAccount !=  true)
   {
    std::cout << "Please enter valid account number: " << endl;
   }
   }
   
   //sending details back to the file
    ofstream ofs("AllAccountDetails.json");
    //organising JSON data for readability
    ofs << AccountData->dump(4);
    //closing file
    ofs.close();

}
void Bank::withdraw()
{
   int accountNumber;
   float oldAmount;
   float withdrawAmount;
   bool validAccount = false;
   //importing json file
   ifstream AccountDeets("AllAccountDetails.json");
   //creating new unqiue pointer and storing JSON data inside for modification
   unique_ptr<json> AccountData(new json);
   AccountDeets >> *AccountData;
   //setting up while loop to find account and add money 
   while(validAccount != true)
   {
   cout << "Please enter your account number: " << endl;
   cin >> accountNumber;
   for(auto &it : (*AccountData)["Accounts"])
   {
        if(it["Account Number"] == accountNumber)
        {
        validAccount = true;
           cout << "How much would you like to withdraw?: " << endl;
        cin >> withdrawAmount;
        cout << "Your original balance was: " << it["Balance"] << endl;
        oldAmount = it["Balance"];
        auto newAmount = oldAmount - withdrawAmount;
        if(newAmount < 0)
        {
            cout << "you do not have sufficient funds for this withdrawl. Please try again" << "\n";
            cin.ignore();
            break;
        }
        else
        {
        it["Balance"] = newAmount;
        cout << "You have withdrawn " << withdrawAmount << endl;
        cout << "Your new balance is: " << it["Balance"] << endl;
        validAccount = true;
        break;
        }
        }
   }
       if(validAccount !=  true)
   {
    std::cout << "Please enter valid account number: " << endl;
   }
   }
   
   //sending details back to the file
    ofstream ofs("AllAccountDetails.json");
    //organising JSON data for readability
    ofs << AccountData->dump(4);
    //closing file
    ofs.close();

}
void Bank::closeAccount()
{
   int accountNumber;
   float depositAmount;
   bool validAccount = false;
   //importing json file
   ifstream AccountDeets("AllAccountDetails.json");
   //creating new unqiue pointer and storing JSON data inside for modification
   unique_ptr<json> AccountData(new json);
   AccountDeets >> *AccountData;
   //setting up while loop to find account and add money 
   while(validAccount != true)
   {
   cout << "Please enter your account number: " << endl;
   cin >> accountNumber;
   
    for (auto it = (*AccountData)["Accounts"].begin(); it != (*AccountData)["Accounts"].end(); ++it)
    {
        if ((*it)["Account Number"] == accountNumber)
        {
            validAccount = true;
            (*AccountData)["Accounts"].erase(it); // Remove the account from the array
            std::cout << "Account " << accountNumber << " removed." << std::endl;
            break;
        }
    }

    if(validAccount !=  true)
   {
    std::cout << "Please enter valid account number: " << endl;
   }
   }
   
   //sending details back to the file
    ofstream ofs("AllAccountDetails.json");
    //organising JSON data for readability
    ofs << AccountData->dump(4);
    //closing file
    ofs.close();
}
void Bank::createTransactionHistory(int accountNumber)
{
    //importing account details json file
    ifstream AccountDeets("AllAccountDetails.json");
    //creating a JSON object and pointer to store the account details in 
    unique_ptr<json> data(new json);
    //sending account details to the data stored inside the pointer 
    AccountDeets >> *data;
    json new_object = json::object();
    new_object[accountNumber] = json::array();
    (*data)["Transactions"].push_back(new_object);
    //sending to account details json file
    ofstream ofs("AllAccountDetails.json");
    //organising JSON data for readability
    ofs << data->dump(4);
    //closing file
    ofs.close();
}


void Bank::createAccount(string fname, string lname, float balance)
{
    //generating new account and assinging to heap
    Account* acc = new Account(fname, lname, balance);
    accountToFile(acc);
    //removing from heap
    delete acc;
}

void Bank::accountToFile(Account*& acc)
{
    //generating new account with a unique pointer so data is deallocated from heap automatically after use.
    unique_ptr<json> newObj(new json{{"First Name", acc->getFName()}, {"Last Name", acc->getLName()}, {"Account Number", acc->getAccNumber()}, {"Balance", acc->getBalance()}});
    //now need to append this to 'newObj' that got created in the json file previously'
    //importing account details json file
    cout << *newObj;
    ifstream AccountDeets("AllAccountDetails.json");
    //creating a JSON object and pointer to store the account details in 
    unique_ptr<json> data(new json);
    //sending account details to the data stored inside the pointer 
    AccountDeets >> *data;
    //calling the push back function (-> used to call the member function of the data inside the pointer )
    (*data)["Accounts"].push_back(*newObj);
    //(*data)["Accounts"].push_back(AccountDicObj);
    //sending to account details json file
    ofstream ofs("AllAccountDetails.json");
    //organising JSON data for readability
    ofs << data->dump(4);
    //closing file
    ofs.close();

}

    //**********Bank Destructor**************//
    Bank::~Bank()
    {
        cout << "Bank Class Destroyed" << "\n";
    }