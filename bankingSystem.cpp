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
    
    string fname;
    string lname;
    float balance;
    int accountNumber;

    public:
    
    //static member so all classes have access to the counter for next account number
    static int nextAccountNumber;
    
    ////*****************Constructors******************/////////////////////
    //constructor to create object instance 
    Account(string fname,string lname,float balance)
    {
        //gather the next account number for the next object instance. Using the function. 
        accountNumber = getNextAccountNumber();
        this->fname = fname;
        this->lname = lname;
        this->balance = balance;
    }
    
    int getNextAccountNumber()
    {
        //increment the next account number and return it 
        return nextAccountNumber++;
    }

    ///*************Member Functions******************///////////
    friend ifstream;
    friend class Bank;
    friend void depositMoney();
    //friend void accountToFile(Account *acc);
    string getFName() const {return fname;}
    string getLName() const {return lname;}
    float getBalance() const {return balance;}
    int getAccNumber() const {return accountNumber;}

    friend ostream& operator<<(ostream& os, const Account& obj);

};
//initialise the account number
int Account::nextAccountNumber = 1;
//AccountFunctions
void depositMoney(){
}
ostream& operator<<(ostream& os, const Account& obj) {
    os << "your first name is: " << obj.fname;
    return os;
}
void accountToFile(Account*& acc)
{
    //generating new account with a unique pointer so data is deallocated from heap automatically after use. 
    cout << acc->getFName();
    unique_ptr<json> newObj(new json{{"First Name", acc->getFName()}, {"Last Name", acc->getLName()}, {"Account Number", acc->getAccNumber()}, {"Balance", acc->getBalance()}});
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

}

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
    ///*********************Member Functions*****************////////////////////

    //function to create an account
    void createAccount(string fname, string lname, float initBalance);
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

    ///*******************Destructors**********************/////////
    ~Bank()
    {

    }

};
//Bank initialisors 
int Bank::NumberOfAccounts = 0;
//Bank Functions
void Bank::createAccount(string fname, string lname, float balance)
{
    //generating new account and assinging to heap
    Account* acc = new Account(fname, lname, balance);
    accountToFile(acc);
    //removing from heap
    delete acc;
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
void Bank::displayBalance()
{
   int accountNumber;
   ifstream AccountDeets("AllAccountDetails.json");
   unique_ptr<json> AccountData(new json);
   AccountDeets >> *AccountData;
   while(accountNumber != true)
   {
   cout << "Please enter your account number: " << endl;
   cin >> accountNumber;
   for(auto &it : *AccountData)
   {
        if(it["Account Number"] == accountNumber)
        {
        cout << "Your balance is: " << it["Balance"] << endl;
        accountNumber = true;
        break;
        }
   }
   cout << "Please enter valid account number: " << endl;
   }
   accountNumber = false;
   
   

}
void Bank::deposit()
{
   int accountNumber;
   float oldAmount;
   float depositAmount;
   float newAmount;
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
   cout << "How much would you like to deposit?: " << endl;
   cin >> depositAmount;
   for(auto &it : *AccountData)
   {
        if(it["Account Number"] == accountNumber)
        {
        validAccount = true;
        cout << "Your original balance was: " << it["Balance"] << endl;
        oldAmount = it["Balance"];
        newAmount = oldAmount + depositAmount;
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
   
   //sending details back to the file
    ofstream ofs("AllAccountDetails.json");
    //organising JSON data for readability
    ofs << AccountData->dump(4);
    //closing file
    ofs.close();

}
}
void Bank::withdraw()
{
   int accountNumber;
   float oldAmount;
   float withdrawAmount;
   float newAmount;
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
   cout << "How much would you like to withdraw?: " << endl;
   cin >> withdrawAmount;
   for(auto &it : *AccountData)
   {
        if(it["Account Number"] == accountNumber)
        {
        validAccount = true;
        cout << "Your original balance was: " << it["Balance"] << endl;
        oldAmount = it["Balance"];
        newAmount = oldAmount - withdrawAmount;
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
    case 1: //create an account
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
    case 2: //balance enquiry
        b.displayBalance();
        break;   
    case 3: //deposit
        b.deposit();
        break;   
    case 4:
        b.withdraw(); //Withdraw
        break;   
    case 5: //close Accounts
        break;   
    case 6: //Show All Accounts
        b.showAccounts();
        break;   
    case 7: //Quit
        cout << "Thanks for using my Banking App! " << "\n";
        exit(0);   
   }
   }

   

   return 0; 
}

