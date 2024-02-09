#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include<cctype>
#include "json.hpp"
using json = nlohmann::json;
using namespace std;

/***************Functions************************/

bool validName(string name)
{
    getline(cin >> ws, name); // Use getline to handle spaces in input
    for (int i = 0; i < name.length(); i++) {
        if (name[i] == ' ' || name[i] == '.') {
            //return false if invalid characters found
            cout << "Please Enter a Valid Name: " << endl;
            return false;
        }
    }
    //return true if valid characters found
    return true;
}


class Account
{
    private:
    
    string firstName;
    string lastName;
    float balance;

    public:
    
    //static member so all classes have access to the counter for next account number
    static int nextAccountNumber;
    //individual objet account number 
    int accountNumber;
    
    //constructor to create object instance 
    Account(string fname,string lname,float balance)
    {
        //gather the next account number for the next object instance. Using the function. 
        accountNumber = getNextAccountNumber();
    }

    int storeMoney();

    int getNextAccountNumber()
    {
        //increment the next account number and return it 
        return nextAccountNumber++;
    }

    

    //Account needs to be able to: 
    //store money
    //store account data
    //Generate account number when created



};
int Account::nextAccountNumber = 1;

class Bank 
{

    static int NumberOfAccounts; 

    private: 
    string bank_name = "Andys Bank";

    protected:
    
    public: 
    ///*****Constructors****/////
    Bank()
    {
    static ofstream ofs("AllAccountDetails.json", ios::app);
    json new_array = json::array();
    ofs << new_array;
    ofs.close();
    }

    //creating a file to store accounts on creation of bank class
    //function to create an account
    Account createAccount(string fname, string lname, float initBalance);
    void closeAccount();
    //delete an Account class object
    float deposit();
    //Read in data and store somewhere
    float withdraw();
    //read data stored in somewhere, remove it from storage, display to user
    int displayBalance();
    //function to check for valid name input
    bool validName(string name);
    void showAccounts();



    //functions.....
    //Open an account
    //Deposit Money
    //withdraw Money
    //display balance 
    //Show accounts
    //close account 
      

};
int Bank::NumberOfAccounts = 0;
//Bank Functions
Account Bank::createAccount(string fname, string lname, float initBalance)
{

    //***Need to add in tests so it doesn't enter an infinite loop if you select the wrong data type for input***//

    //increasing number of accounts 
    NumberOfAccounts++;
    //generating new account
    Account acc = Account(fname, lname, initBalance);
    ///**

    json newObj = {{"First Name", fname}, {"Last Name", lname}, {"Account Number", acc.accountNumber}};
    //now need to append this to 'new_array' that got created in the json file previously'
    ifstream AccountDeets("AllAccountDetails.json");
    json data;
    AccountDeets >> data;
    data.push_back(newObj);
    ofstream ofs("AllAccountDetails.json");
    ofs << data.dump(4);
    ofs.close();

    ///***
    //print the Account number on screen and confirm creation. 
    cout << "Account Created. Your Account Number is: " << acc.accountNumber << endl;
    cout << "Account Holder Name: " << fname << " " << lname << endl;

    return acc;

}
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
    json UserAcc;
    infile >> UserAcc;
    cout << UserAcc;
    if(infile.eof()) cout << "End of File";
    infile.close();   
}

int main()
{
   int selectedOption;
   Bank b;
   string fname, lname;
   float balance;

   while(selectedOption!=7)
   {  
   cout << "***Banking System***" << "\n" <<endl;
 
   cout << "Select one option below:" << "\n";
   cout << "1. Open Account" << endl; 
   cout << "2. Balance enquriy" << endl;
   cout << "3. Deposit" << endl; 
   cout << "4. Withdraw" << endl;
   cout << "5. Close an Account" << endl;
   cout << "6. Show all Accounts" << endl;
   cout << "7. Quit" << endl;
   cout << "What would you like to do?: " ;
   try
   {
      cin >> selectedOption;
      if(selectedOption > 7)
        throw (101);
   }
   catch (int e)
   {
     cout << "Invalid entry. Please try again: " << "error code " << e;
   }
   switch(selectedOption)
   {
    case 1:
        while(true)
        {
            cout << "Please Enter Your First Name: ";
            cin >> fname;
            if(b.validName(fname))
            {
                break;
            }
        }
        cout << "Please Enter Your Last Name: ";
        cin >> lname; 
        cout << "How much would you like to deposit?: ";
        cin >> balance;
        b.createAccount(string(fname), string(lname), float(balance));
            break;           
    case 2: cout << "Balance enquiry";
        break;   
    case 3: cout << "Deposit";
        break;   
    case 4: cout << "Withdraw";
        break;   
    case 5: cout << "Close an Account";
        break;   
    case 6: cout << "Show all Accounts";
        b.showAccounts();
        break;   
    case 7: cout << "Quit";
        break;   
   }
   }

   

   return 0; 
}

//What we want 
//1. Open Account 
//2. Balance enquriy 
//3. Deposit 
//4. Withrdrawl 
//5. Close an Account 
//6. Show all Accounts 
//7. Quit

