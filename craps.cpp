#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>

using namespace std;

// Function Declarations
double getMoneyNumberFromUser();
double placeInitialBet(double betAmount);
bool isTransactionValid(double amt, double balance);
void updateBalance(double amt, double &balance);
void printInstructions();
int getDiceRoll();
int firstRollCheckGameState(int diceRoll);
void printBankBalance(double bal);
void placeBet(double betAmount, int betNumber, double &four, double &five, double &six, double &eight, double &nine, double &ten);
void printBets(double bal, int pt, double ptBet, double four, double five, double six, double eight, double nine, double ten);
void updateBalanceFromBets(double &bal, int roll, double four, double five, double six, double eight, double nine, double ten);
void updateBalanceFromBetsLoss(double &bal, double four, double five, double six, double eight, double nine, double ten);
void removeBet(double betAmount, int betNumber, double &four, double &five, double &six, double &eight, double &nine, double &ten);

int main()
{
    srand(time(0));

    bool gameOver = false;
    double balance = 1000.00;

    enum GameState
    {
        WON = 0,
        LOST = 1,
        CONTINUE = 2
    };

    cout << "Welcome to the Craps table!" << endl
         << endl;
    printInstructions();

    while (!gameOver)
    {
        int gameState = CONTINUE;
        int point = 0;
        double pointBet;

        printBankBalance(balance);
        pointBet = getMoneyNumberFromUser();
        cout << "Your bet is " << pointBet << endl;

        int diceRoll = getDiceRoll();
        cout << "Your dice roll is " << diceRoll << endl;

        if (diceRoll == 7 || diceRoll == 11)
        {
            gameState = WON;
            balance += pointBet;
            cout << "You've won!!!!!" << endl;
        }
        else if (diceRoll == 2 || diceRoll == 3 || diceRoll == 12)
        {
            gameState = LOST;
            balance -= pointBet;
            cout << "You lost :(" << endl;
        }
        else
        {
            cout << "Your point is " << diceRoll << endl;
            cout << "******************************" << endl;
            gameState = CONTINUE;
            point = diceRoll;
        }

        double fourBet = 0;
        double fiveBet = 0;
        double sixBet = 0;
        double eightBet = 0;
        double nineBet = 0;
        double tenBet = 0;

        while (gameState == CONTINUE)
        {

            bool wantToPlaceBet = true;
            while (wantToPlaceBet && gameState == CONTINUE)
            {
                printBets(balance, point, pointBet, fourBet, fiveBet, sixBet, eightBet, nineBet, tenBet);
                cout << "Would you like to place a bet? Enter y for yes, any other character for no." << endl;
                char wantBet;
                cin >> wantBet;
                if (wantBet == 'y')
                {
                    int numberBettingOn;
                    double betAmt;
                    cout << "What number would you like to bet on? 4, 5, 6, 8, 9, or 10?" << endl;
                    cin >> numberBettingOn;
                    betAmt = getMoneyNumberFromUser();
                    placeBet(betAmt, numberBettingOn, fourBet, fiveBet, sixBet, eightBet, nineBet, tenBet);
                }
                else
                {
                    wantToPlaceBet = false;
                }
            }

            bool wantToRemoveBet = true;
            while (wantToRemoveBet && gameState == CONTINUE)
            {
                printBets(balance, point, pointBet, fourBet, fiveBet, sixBet, eightBet, nineBet, tenBet);
                cout << "Would you like to remove a bet? Enter y for yes, any other character for no." << endl;
                char wantRemoveBet;
                cin >> wantRemoveBet;
                if (wantRemoveBet == 'y')
                {
                    int numberRemovingOn;
                    double betAmt;
                    cout << "What number would you like to remove a bet on? 4, 5, 6, 8, 9, or 10?" << endl;
                    cin >> numberRemovingOn;
                    betAmt = getMoneyNumberFromUser();
                    removeBet(betAmt, numberRemovingOn, fourBet, fiveBet, sixBet, eightBet, nineBet, tenBet);
                }
                else
                {
                    wantToRemoveBet = false;
                }
            }

            int diceRoll = getDiceRoll();
            cout << "Your dice roll is " << diceRoll << endl;
            cout << "******************************" << endl;

            if (diceRoll == 4 || diceRoll == 5 || diceRoll == 6 || diceRoll == 8 || diceRoll == 9 || diceRoll == 10)
            {
                gameState = CONTINUE;
                updateBalanceFromBets(balance, diceRoll, fourBet, fiveBet, sixBet, eightBet, nineBet, tenBet);
            }
            if (diceRoll == point)
            {
                gameState = WON;
                balance += pointBet;
                cout << "You've won!!!!!" << endl;
            }
            else if (diceRoll == 2 || diceRoll == 3 || diceRoll == 11 || diceRoll == 12)
            {
                gameState = CONTINUE;
            }
            else if (diceRoll == 7)
            {
                gameState = LOST;
                balance -= pointBet;
                cout << "You lost :(" << endl;
                updateBalanceFromBetsLoss(balance, fourBet, fiveBet, sixBet, eightBet, nineBet, tenBet);
            }
        }

        cout << "Your balance is " << balance << endl;

        char userDecision = 'x';
        cout << "Press q to quit, h for help, or any other letter to continue" << endl;
        cin >> userDecision;
        if (userDecision == 'q')
        {
            gameOver = true;
        }
        else if (userDecision == 'h')
        {
            printInstructions();
        }
    }

    return 0;
}

// Function Definitions

/****************************************************************
Function name: placeInitialBet
Description: Get's user to place a bet
input: double
output: double
****************************************************************/
void removeBet(double betAmount, int betNumber, double &four, double &five, double &six, double &eight, double &nine, double &ten)
{
    switch (betNumber)
    {
    case 4:
        if (betAmount < four) {
            four -= betAmount;
        }
        else {
            four = 0;
        }
        break;
    case 5:
        if (betAmount < five) {
            five -= betAmount;
        }
        else {
            five = 0;
        }
        break;
    case 6:
        if (betAmount < six) {
            six -= betAmount;
        }
        else {
            six = 0;
        }
        break;
    case 8:
        if (betAmount < eight) {
            eight -= betAmount;
        }
        else {
            eight = 0;
        }
        break;
    case 9:
        if (betAmount < nine) {
            nine -= betAmount;
        }
        else {
            nine = 0;
        }
        break;
    case 10:
        if (betAmount < ten) {
            ten -= betAmount;
        }
        else {
            ten = 0;
        }
        break;
    }
}

void updateBalanceFromBetsLoss(double &bal, double four, double five, double six, double eight, double nine, double ten)
{
    bal -= four;
    bal -= five;
    bal -= six;
    bal -= eight;
    bal -= nine;
    bal -= ten;
}

void updateBalanceFromBets(double &bal, int roll, double four, double five, double six, double eight, double nine, double ten)
{
    switch (roll)
    {
    case 4:
        bal += four * 1.8;
        break;
    case 5:
        bal += five * 1.4;
        break;
    case 6:
        bal += six * 1.2;
        break;
    case 8:
        bal += eight * 1.2;
        break;
    case 9:
        bal += nine * 1.4;
        break;
    case 10:
        bal += ten * 1.8;
        break;
    }
}

void printBets(double bal, int pt, double ptBet, double four, double five, double six, double eight, double nine, double ten)
{
    cout << "Your balance is " << bal << endl;
    cout << "Your bets: " << endl;
    cout << "Point bet on " << pt << " - " << ptBet << endl;
    cout << "Four - " << four << endl;
    cout << "Five - " << five << endl;
    cout << "Six - " << six << endl;
    cout << "Eight - " << eight << endl;
    cout << "Nine - " << nine << endl;
    cout << "Ten - " << ten << endl;
}

void placeBet(double betAmount, int betNumber, double &four, double &five, double &six, double &eight, double &nine, double &ten)
{
    switch (betNumber)
    {
    case 4:
        four = betAmount;
        break;
    case 5:
        five = betAmount;
        break;
    case 6:
        six = betAmount;
        break;
    case 8:
        eight = betAmount;
        break;
    case 9:
        nine = betAmount;
        break;
    case 10:
        ten = betAmount;
        break;
    }
}

void printBankBalance(double bal)
{
    cout << "Your bank balance is " << bal << endl;
}

double getMoneyNumberFromUser()
{
    bool noError = false;
    double money;
    while (!noError)
    {
        cout << "Enter amount" << endl;
        cin >> money;
        if (money >= 0)
            noError = true;
    }
    return money;
}

/****************************************************************
Function name: updateBalance
Description: Updates the user's bank balance
input: double, double
output: none
****************************************************************/
void updateBalance(double amt, double &balance)
{
    balance += amt;
}

/****************************************************************
Function name: printInstructions
Description: Prints game instructions to the user
input: none
output: none
****************************************************************/
void printInstructions()
{
    cout << "************************************" << endl;
    cout << "These are the instructions" << endl;
    cout << "************************************" << endl;
}

/****************************************************************
Function name: getDiceRoll
Description: Simulates a roll of two dice in the game
input: none
output: integer
****************************************************************/
int getDiceRoll()
{
    return (rand() % 6 + 1) + (rand() % 6 + 1);
}