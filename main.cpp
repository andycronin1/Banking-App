#include<iostream>
#include "includes/Bank.h"
#include "includes/Bank.cpp"
#include "includes/Account.cpp"
#include "includes/Account.h"
using namespace std;

//****************************************************Structs***************************************************//

struct Transaction
{
    double transaction_amount;
    string date;
    string description;
};

//**********************************************Main**********************************************************//
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
        while(true)
        {
            cout << "Please Enter Your Last Name: ";
            cin >> lname;
            if(b.validName(lname))
            {
                break;
            }
        }
        cout << "How much would you like to deposit?: ";
        cin >> balance;
        b.createAccount(string(fname), string(lname), float(balance));
        //b.createTransactionHistory();
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
        b.closeAccount();
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

