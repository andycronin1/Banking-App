#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include<cctype>
#include "json.hpp"
#include<cstdlib>
using json = nlohmann::json;
using namespace std;

/********Classes**************/
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
    
    int getNextAccountNumber()
    {
        //increment the next account number and return it 
        return nextAccountNumber++;
    }


    friend ofstream; 
    friend ifstream;
    //Account needs to be able to: 
    //store money
    //store account data
    //Generate account number when created
};
int Account::nextAccountNumber = 1;
//AccountFunctions

class Bank 
{

    static int NumberOfAccounts; 

    private: 
    string bank_name = "Andy's Bank";

    protected:
    
    public: 
    ///*****Constructors****/////
    Bank()
    {
        //checking if file exits. If not, create empty array in file. 
    ifstream inputFile("AllAccountDetails.json");
    if(!inputFile.is_open())
    { 
    static ofstream ofs("AllAccountDetails.json", ios::app);
    json new_array = json::array();
    ofs << new_array;
    ofs.close();
    }
    }

    //creating a file to store accounts on creation of bank class
    //function to create an account
    void createAccount(string fname, string lname, float initBalance);
    void closeAccount();
    //delete an Account class object
    float deposit(int accountNumber, float depositAmount);
    //Read in data and store somewhere
    float withdraw();
    //read data stored in somewhere, remove it from storage, display to user
    int displayBalance();
    //function to check for valid name input
    bool validName(string name);
    void showAccounts();
    ~Bank()
    {

    }



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
void Bank::createAccount(string fname, string lname, float initBalance)
{

    //***Need to add in tests so it doesn't enter an infinite loop if you select the wrong data type for input***//

    //increasing number of accounts 
    NumberOfAccounts++;
    //generating new account with a unique pointer so data is deallocated from heap automatically after use. 
    unique_ptr<Account> acc(new Account(fname, lname, initBalance));

    //generating new account with a unique pointer so data is deallocated from heap automatically after use. 
    unique_ptr<json> newObj(new json{{"First Name", fname}, {"Last Name", lname}, {"Account Number", acc->accountNumber}});
    //now need to append this to 'newObj' that got created in the json file previously'
    //importing account details json file
    ifstream AccountDeets("AllAccountDetails.json");
    //creating a JSON object and pointer to store the account details in 
    unique_ptr<json> data(new json);
    //sending account details to the data stored inside the pointer 
    AccountDeets >> *data;
    //calling the push back function (-> used to call the member function of the data inside the pointer )
    data->push_back(*newObj);
    //sending to account details json file
    ofstream ofs("AllAccountDetails.json");
    //organising JSON data for readability
    ofs << data->dump(4);
    //closing file
    ofs.close();

    ///***
    //print the Account number on screen and confirm creation. 
    cout << "Account Created. Your Account Number is: " << acc->accountNumber << endl;
    cout << "Account Holder Name: " << fname << " " << lname << endl;

    //return acc;

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
float Bank::deposit(int accountNumber, float depositAmount)
{
   
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

