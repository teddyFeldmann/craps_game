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

    cout << "88888888888              888      888          d8b               .d8888b.                    d8b" << endl;                   
    cout << "    888                  888      888          88P              d88P  Y88b                   Y8P"  << endl;           
    cout << "    888                  888      888          8P               888    888                       " << endl;             
    cout << "    888     .d88b.   .d88888  .d88888 888  888     .d8888b      888         8888b.  .d8888b  888 88888b.   .d88b.  " << endl;
    cout << "    888    d8P  Y8b d88  888 d88' 888 888  888     88K          888            '88b 88K      888 888 88b  d88''88b" << endl;
    cout << "    888    88888888 888  888 888  888 888  888     'Y8888b.     888    888 .d888888 'Y8888b. 888 888  888 888  888" << endl;
    cout << "    888    Y8b.     Y88b 888 Y88b 888 Y88b 888          X88     Y88b  d88P 888  888      X88 888 888  888 Y88..88P " << endl;
    cout << "    888     'Y8888   'Y88888  'Y88888  'Y88888      88888P'      'Y8888P'  'Y888888  88888P' 888 888  888  'Y88P' " << endl;  
    cout << "                                           888 " << endl;                                                                   
    cout << "                                     Y8b d88P  " << endl;                                                                   
    cout << "                                      'Y88P' " << endl;
    cout << "Welcome to the Craps table!" << endl
         << endl;
    printInstructions();

    while (!gameOver)
    {
        int gameState = CONTINUE;
        int point = 0;
        double pointBet;

        printBankBalance(balance);
        cout << "Initial Bet:" << endl;
        pointBet = getMoneyNumberFromUser();
        cout << "Your bet is " << pointBet << endl;
        cout << "******************************" << endl;
        balance -= pointBet;

        int diceRoll = getDiceRoll();
        cout << "Your dice roll is " << diceRoll << endl;

        if (diceRoll == 7 || diceRoll == 11)
        {
            gameState = WON;
            balance += pointBet * 2;
            cout << "You've won!!!!! Congratulations, you're a natural!" << endl;
        }
        else if (diceRoll == 2 || diceRoll == 3 || diceRoll == 12)
        {
            gameState = LOST;
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
                    balance -= betAmt;
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
                    balance += betAmt;
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
                balance += pointBet * 2;
                balance += (fourBet + fiveBet + sixBet + eightBet + nineBet + tenBet);
                cout << "You've won!!!!! You must spend a lot of time in the casino" << endl;
            }
            else if (diceRoll == 2 || diceRoll == 3 || diceRoll == 11 || diceRoll == 12)
            {
                gameState = CONTINUE;
            }
            else if (diceRoll == 7)
            {
                gameState = LOST;
                cout << "You lost :( The darn Seven! Better luck next time!" << endl;
                updateBalanceFromBetsLoss(balance, fourBet, fiveBet, sixBet, eightBet, nineBet, tenBet);
            }
        }

        cout << "Your balance is " << balance << endl;

        char userDecision = 'x';
        cout << "Press q to walk away from the table, h to ask the dealer how the game works, or any other letter to continue" << endl;
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
    cout << "How to Play Craps:" << endl;
    cout << "Place an initial bet." << endl;
    cout << "Once you've made a bet, the dice will be rolled." << endl;
    cout << "If this is a 7 or 11, you double your money, but if it is 2, 3, or 12, you lose." << endl;
    cout << "If any other number, this is your point." << endl;
    cout << "The game ends when a 7 is rolled, in which case you lose, or if your point number is rolled." << endl;
    cout << "You can place bets on other numbers as well, with the following payouts" << endl;
    cout << "   4 and 10 - 9:5" << endl;
    cout << "   5 and 9 - 7:5" << endl;
    cout << "   6 and 8 - 6:5" << endl;
    cout << "If a 2, 3, 11, or 12 are rolled, the dice are rolled again." << endl;
    cout << "You can remove a bet at any point." << endl;
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
    int roll = (rand() % 6 + 1) + (rand() % 6 + 1);
    switch (roll) {
        case 2:
            cout << "----- -----" << endl;
            cout << "|   | |   |" << endl;
            cout << "| O | | O |" << endl;
            cout << "|   | |   |" << endl;
            cout << "----- -----" << endl;
            break;
        case 3:
            cout << "----- -----" << endl;
            cout << "|O  | |   |" << endl;
            cout << "|   | | O |" << endl;
            cout << "|  O| |   |" << endl;
            cout << "----- -----" << endl;
            break;
        case 4:
            cout << "----- -----" << endl;
            cout << "|  O| |O  |" << endl;
            cout << "|   | |   |" << endl;
            cout << "|O  | |  O|" << endl;
            cout << "----- -----" << endl;
            break;
        case 5:
            cout << "----- -----" << endl;
            cout << "|O  | |  O|" << endl;
            cout << "| O | |   |" << endl;
            cout << "|  O| |O  |" << endl;
            cout << "----- -----" << endl;
            break;
        case 6:
            cout << "----- -----" << endl;
            cout << "|  O| |O  |" << endl;
            cout << "| O | | O |" << endl;
            cout << "|O  | |  O|" << endl;
            cout << "----- -----" << endl;
            break;
        case 7:
            cout << "----- -----" << endl;
            cout << "|O  | |O O|" << endl;
            cout << "| O | |   |" << endl;
            cout << "|  O| |O O|" << endl;
            cout << "----- -----" << endl;
            break;
        case 8:
            cout << "----- -----" << endl;
            cout << "|O O| |O O|" << endl;
            cout << "|   | |   |" << endl;
            cout << "|O O| |O O|" << endl;
            cout << "----- -----" << endl;
            break;
        case 9:
            cout << "----- -----" << endl;
            cout << "|O O| |O O|" << endl;
            cout << "|   | | O |" << endl;
            cout << "|O O| |O O|" << endl;
            cout << "----- -----" << endl;
            break;
        case 10:
            cout << "----- -----" << endl;
            cout << "|O O| |O O|" << endl;
            cout << "| O | | O |" << endl;
            cout << "|O O| |O O|" << endl;
            cout << "----- -----" << endl;
            break;
        case 11:
            cout << "----- -----" << endl;
            cout << "|O O| |O O|" << endl;
            cout << "|O O| | O |" << endl;
            cout << "|O O| |O O|" << endl;
            cout << "----- -----" << endl;
            break;
        case 12:
            cout << "----- -----" << endl;
            cout << "|O O| |O O|" << endl;
            cout << "|O O| |O O|" << endl;
            cout << "|O O| |O O|" << endl;
            cout << "----- -----" << endl;
            break;
    }
    return roll;
}