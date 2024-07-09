// Banking System

// Create a simple banking system application where users can open accounts, deposit and withdraw money, check account balances, and perform basic transactions.

// Use classes and inheritance to model different account types (e.g., savings account, checking account).

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <fstream>

using namespace std;

class Account
{
public:
    string account_owner_name;
    string account_type;
    double account_balance;
    Account() {}
    Account(string account_owner_name, string account_type, double account_balance)
    {
        this->account_owner_name = account_owner_name;
        this->account_type = account_type;
        this->account_balance = account_balance;
    }

    void deposit(double &balance, double amount)
    {
        balance += amount;
    }

    virtual void withdraw(double &balance, double amount)
    {
        if (balance < amount)
            cout << "Insufficient balance" << endl;
        else
            balance -= amount;
    };
};

class SavingsAccount : public Account
{
public:
    double rate;
    SavingsAccount() {}
    SavingsAccount(string account_owner_name, double account_balance, double rate) : Account(account_owner_name, "Savings Account", account_balance)
    {
        this->rate = rate;
    }
    void applyRate(double &balance, double rate)
    {
        balance += (balance / 100) * rate;
    }

    void diposit(double &balance, double amount)
    {
        balance += amount;
    }
    void withdraw(double &balance, double amount)
    {
        if (balance < amount)
            cout << "Insufficient balance" << endl;
        else
            balance -= amount;
    }
};

class CheckingAccount : public Account
{
public:
    double overdraftlimit;
    CheckingAccount() {}
    CheckingAccount(string account_owner_name, double account_balance, double overdraftlimit) : Account(account_owner_name, "Savings Account", account_balance)
    {
        this->overdraftlimit = overdraftlimit;
    }
    void diposit(double &balance, double amount)
    {
        balance += amount;
    }
    void withdraw(double &balance, double &overdraftlimit, double amount)
    {
        if (balance < amount)
        {
            if (balance + overdraftlimit < amount)
            {
                cout << "Insufficient balance" << endl;
            }
            else
            {
                int x = amount - balance;
                overdraftlimit -= x;
                balance = 0;
            }
        }
        else
            balance -= amount;
    }
};

void inputDetails(vector<Account> &account, vector<pair<string, double>> &account_name_rate)
{
    double rate;
    string name;
    char account_type;
    double balance;
    cout << "Enter name " << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, name);
    cout << "Enter type of Account " << endl
         << "Press S for Savings Account And C for Checking Account" << endl;
    cin >> account_type;
    cout << "Enter balance " << endl;
    cin >> balance;
    if (account_type == 'S')
    {
        srand(time(0));
        rate = rand() % 10;
        rate += 1;
        Account A(name, "Savings Account", balance);
        account.push_back(A);
        account_name_rate.emplace_back(name, rate);
    }
    else if (account_type == 'C')
    {
        srand(time(0));
        rate = rand() % (1000 - 500 + 1);
        rate += 500;
        Account A1(name, "Checking Account", balance);
        account.push_back(A1);
        account_name_rate.emplace_back(name, rate);
    }
    else
    {
        cout << "Invalid Choice" << endl
             << "Please Enter S or C" << endl;
    }
}

void ShowParticularPersonDetail(vector<Account> account, string name)
{
    int i;
    for (i = 0; i < account.size(); i++)
    {
        if (account[i].account_owner_name == name)
        {
            cout << "Name:" << account[i].account_owner_name << endl;
            cout << "Account Type " << account[i].account_type << endl;
            cout << "Balance:" << account[i].account_balance << endl;
            break;
        }
    }
    if (i == account.size())
        cout << "There is no account with holder " << name << endl;
}

void insertBankTxt(vector<Account> account, vector<pair<string, double>> &account_name_rate)
{
    ofstream out;
    out.open("BankingSystem.txt");
    for (int i = 0; i < account.size(); i++)
    {
        out << account[i].account_owner_name << "\n";
        out << account[i].account_type << "\n";
        out << account[i].account_balance << "\n";
        out << account_name_rate[i].second << "\n";
    }
    out.close();
}

void readBankTxt(vector<Account> &account, vector<pair<string, double>> &account_name_rate)
{
    ifstream in;
    in.open("BankingSystem.txt");
    string s;
    string owner_name;
    string type;
    double balance;
    double rate;
    int i = 0;
    while (in.eof() == 0)
    {
        switch (i)
        {
        case 0:
            getline(in, owner_name);
            i++;
            break;
        case 1:
            getline(in, type);
            i++;
            break;
        case 2:
            getline(in, s);
            balance = stod(s);
            i++;
            break;
        case 3:
            getline(in, s);
            rate = stod(s);
            i++;
            break;
        case 4:
            Account acc(owner_name, type, balance);
            account.push_back(acc);
            account_name_rate.emplace_back(owner_name, rate);
            i = 0;
            break;
        }
    }
}

int main()
{

    vector<Account> account;
    vector<pair<string, double>> account_name_rate;
    double rate;
    string name;
    double balance;
    char choice;
    SavingsAccount SA;
    CheckingAccount CA;
    bool x = true;
    int i;
    account.clear();
    account_name_rate.clear();
    readBankTxt(account, account_name_rate);
    do
    {
        cout << "Enter 1 to add a new bank account" << endl;
        cout << "Enter 2 to see details of particular account holder" << endl;
        cout << "Enter 3 to diposit money" << endl;
        cout << "Enter 4 to withdraw money" << endl;
        cout << "Enter 5 to delete account" << endl;
        cout << "Enter 6 to exit" << endl;
        cin >> choice;
        switch (choice)
        {
        case '1':
            inputDetails(account, account_name_rate);
            insertBankTxt(account, account_name_rate);
            break;
        case '2':
            cout << "Enter name of customer to see account details" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, name);
            ShowParticularPersonDetail(account, name);
            break;
        case '3':
            cout << "Enter name of account holder in which you want to diposit money" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, name);
            for (i = 0; i < account.size(); i++)
            {
                if (account[i].account_owner_name == name)
                {
                    cout << "Enter amount to diposit" << endl;
                    cin >> balance;
                    if (account[i].account_type == "Savings Account")
                    {
                        SA.deposit(account[i].account_balance, balance);
                    }
                    else if (account[i].account_type == "Checking Account")
                    {
                        CA.diposit(account[i].account_balance, balance);
                    }
                    break;
                }
            }
            if (i == account.size())
            {
                cout << "There is no account with owner name as " << name << endl;
            }
            insertBankTxt(account, account_name_rate);
            break;
        case '4':
            cout << "Enter name of account holder in which you want to withdraw money" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, name);
            for (i = 0; i < account.size(); i++)
            {
                if (account[i].account_owner_name == name)
                {
                    cout << "Enter amount to withdraw" << endl;
                    cin >> balance;
                    if (account[i].account_type == "Savings Account")
                    {
                        SA.withdraw(account[i].account_balance, balance);
                    }
                    else if (account[i].account_type == "Checking Account")
                    {
                        for (auto &it : account_name_rate)
                        {
                            if (it.first == name)
                            {
                                CA.withdraw(account[i].account_balance, it.second, balance);
                            }
                        }
                    }
                    break;
                }
            }
            if (i == account.size())
            {
                cout << "There is no account with owner name as " << name << endl;
            }
            insertBankTxt(account, account_name_rate);
            break;
        case '5':
            cout << "Enter name of person" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            for (i = 0; i < account.size(); i++)
            {
                if (account[i].account_owner_name == name)
                {
                    account.erase(account.begin() + i);
                    account_name_rate.erase(account_name_rate.begin() + i);
                    break;
                }
            }
            if (i == account.size())
                cout << "There is no account with holder name as " << name << endl;
            insertBankTxt(account, account_name_rate);
            break;
        case '6':
            x = false;
            break;
        }
    } while (x == true);

    return 0;
}
