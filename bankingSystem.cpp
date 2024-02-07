#include<iostream>
#include<string>
#include<map>
#include<cctype>
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
    };

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
    //Bank();
    Account createAccount(string fname, string lname, float initBalance);
    void closeAccount();
    //delete an Account class object
    int deposit();
    //Read in data and store somewhere
    int withdraw();
    //read data stored in somewhere, remove it from storage, display to user
    int displayBalance();
    //~Bank();
    bool validName(string name);


    //functions.....
    //Open an account
    //Deposit Money
    //withdraw Money
    //display balance 
    //Show accounts
    //close account 
      

};
int Bank::NumberOfAccounts = 0;
//creating account dynamically. Data will be stored in file, then account deleted. 
Account Bank::createAccount(string fname, string lname, float initBalance)
{

    //***Need to add in tests so it doesn't enter an infinite loop if you select the wrong data type for input***//

    //increasing number of accounts 
    NumberOfAccounts++;
    //generating new account
    Account acc = Account(fname, lname, initBalance);
    //creating a map with last name and account number included. This needs to be appended to a file. 
    map<string, string> AccountDetails;
    AccountDetails.insert(pair<string, string>("First Name", fname));
    AccountDetails.insert(pair<string, string>("Last Name", lname));
    //adding account number to map but converting number to string type for storage 
    AccountDetails.insert(pair<string, string>("Account Number", to_string(acc.accountNumber)));
    //..........................................................................................
    //print the Account number on screen and confirm creation. 
    
    cout << "Account Created. " << endl;
    cout << "Account Holder Name: " << fname << " " << lname << endl;
    cout << "Account Number: " << acc.accountNumber << endl << endl;
    //acc.getNextAccountNumber();

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
        else
        /*
        {
            if (name.empty()) {
            cout << "Empty name entered. Please enter valid name: " << endl;
            return false; 
            }
        }
        */
    }
    //return false if no invalid characters found
    return true;
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

