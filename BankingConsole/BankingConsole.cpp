#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>
#include <io.h>
#include <stdio.h>
#include <filesystem>
using namespace std;

long double balance;
std::string user;
void setup();

// reads login + bank data and saves to new file

void writeFile(long double* balance, std::string* user)
{
    int checkpass;
    std::string newS;
    newS = *user;
    checkpass = newS.length();
    std::fstream customerFile;
    customerFile.open(".\\Data\\test.txt");
    if (customerFile.is_open()) {
        int x;
        x = *balance;
        std::string newStr = std::to_string(x);
        std::string line;
        std::fstream outfile(".\\Data\\temp.txt");

        while (std::getline(customerFile, line)) {
            if (line.substr(0, checkpass) == newS) {
                std::cout << "Saving, please wait.\n";
                outfile.open(".\\Data\\temp.txt", std::ios::app);
                outfile << newS << " " << newStr << std::endl;
                outfile.close();
                outfile.clear();
            }
            else if (line != newS + " " + newStr)
            {
                std::fstream outfile;
                outfile.open(".\\Data\\temp.txt", std::ios::app);
                outfile << line << std::endl;
                outfile.close();
                outfile.clear();
            }
        }
        customerFile.close();
        customerFile.close();
        remove(".\\Data\\test.txt");
        Sleep(300);
        int result;
        result = rename(".\\Data\\temp.txt", ".\\Data\\test.txt");
    }
}

//updates reference to their login username

void logUser(std::string* user, std::string old)
{
    *user = *user + old;
}

//reads and validates login information +  user balance

void readFile(std::string username, std::string password, long double* balance)
{
    std::fstream chadfile;
    chadfile.open(".\\Data\\test.txt");
    if (chadfile.is_open()) {
        std::string line;
        while (getline(chadfile, line)) {
            int checkpass;
            std::string userpass = username + " " + password;
            checkpass = userpass.length();
            if (line.substr(0,checkpass) == userpass)
            {
                system("cls");
                std::cout << "Welcome back, " << username <<"! Please type \"help\" for a list of commands.\n";
                *balance = *balance + std::stoi(line.substr(checkpass));

                chadfile.close();
                chadfile.clear();
                logUser(&user, userpass);
                setup();
            }

        }
    }
    else {
        std::cout << "Error opening file";

    }
}

//removes balance

int withdraw(long double amount, long double* balance)
{
    if (*balance >= amount)
    {
        std::cout << "\nSuccess!\nYou've withdrawn $" << amount << "!\n";
        *balance = *balance - amount;
        return(amount);
    }
    else
    {
        std::cout << "\nSorry! Insufficient funds!\n";
        return(amount);
    }
}

//adds balance

int deposit(long double amount, long double* balance)
{
    std::cout << "\nSuccess!\nYou've deposited $" << amount << "!\n";
    *balance = *balance + amount;
    return(amount);
}

//exit program with return code 0

void exit()
{
    system("cls");
    writeFile(&balance,&user);
    Sleep(1000);
    std::cout << "Goodbye!\n";
    Sleep(300);
}

//looks up pointer for balance information

int balanceCheck(long double* balance)
{
    std::cout << "\n\nYour balance is currently: $" << *balance << "\n";
    return(*balance);
    setup();
}

//commands list

void help()
{
    std::cout << "\n.........\nCommands:\n\nhelp\nwithdraw\ndeposit\nbalance\nexit\n.........\n\n";
    setup();
}

//login prompt

void startup()
{
    std::cout << "Hello! Please enter your username.\n";
    std::string username;
    std::string password;
    std::cin >> username;
    std::cout << "OK. Please enter your password.\n";
    std::cin >> password;
    readFile(username, password,&balance);
}

//setup prompt + command handling

void setup()
{
    std::string gamer;
    std::cin >> gamer;
    if (gamer == "help")
    {
        help();
    }
    else if (gamer == "withdraw")
    {
        std::cout << "How much do you want to withdraw?\n";
        long double amount;
        std::cin >> amount;
        withdraw(amount, &balance);
        setup();
    }
    else if (gamer == "deposit")
    {
        std::cout << "How much do you want to deposit?\n";
        long double amount;
        std::cin >> amount;
        deposit(amount, &balance);
        setup();
    }
    else if (gamer == "balance")
    {
        balanceCheck(&balance);
        setup();
    }
    else if (gamer == "exit")
    {
        exit();
    }
    else
    {
        setup();
    }
}

int main()
{
    SetConsoleTitle(TEXT("Banker C++"));
    startup();
}