// SnakeGame - Orig from the Web
// Original code by N. Vitanovic
// Modified code by Joshua McDonald
// see his YouTube video here: https://bit.ly/29WZ5Ml
//      CHANGE-LOG
//
//   1/27/21 - 2/6/21
//
//  Cleaned up variable names(more specifically aligned many of the variables
//                            to be named with less arbitrary names and more
//                            representative of (x/y) plotting)
//
//  Changed the fruit position into a vector to make having multiple fruit easier
//  and allow for the number of fruit(vector size) to permeable. Originally I tried
//  this with arrays, but saw no way to let the user change the number of fruit
//  without convoluted code.
//
//  Added more global variables for game logic and settings.
//
//  Added showflow function to allow for user to enable and disable debug at the
//  start of the game.
//
//  Modified the board drawing function to work better with multiple fruit.
//  Applied generally the same methods from original code with easier to read
//  formatting and bug fixes. Adding in multiple fruit originally created many
//  spacing bugs, but adding in logic routines to check for special cases fixed this.
//
//  Added prototypes for all functions.
//
//  Added reset snake function to avoid errors when player prompted restart is activated.
//
//  Added fruit position function to avoid fruit generating on top of the borders
//
//  Created user input function to allow player to select settings for the game
//
//  Added game over condition function and game over prompt function for when game over
//  is detected.
//
//  Made key inputs case insensitive with --> tolower(_getch()). Also made user inputs
//  case insensitive with while statements and added ConvertToLowerCase function.
//
//  Added quit/pause/restart keystrokes to user input function. Menu setup is straight
//  forward outside of the pause operation. A secondary while loop was needed to have
//  the ability to resume.
//
//  Truncated the snake movement function into four separate functions for readability.
//  Not much about the logic was changed outside of adding in a special case if statement
//  for the snake head if the wall setting is set to true.
//
//  Added display options function to allow display settings to be modified without having
//  to change the draw board function.
//
//      CHANGE-LOG

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <stdio.h>
#include <ctype.h>
#include <cmath>

using namespace std;

const int boardWidth = 20;
const int boardHeight = 20;
const int maxTail = boardWidth * boardHeight;
int gameSpeed;
int snakeX, snakeY;
int snakeAtBorderX, snakeAtBorderY;
int fruitMaxQuantity = 150;
int score;
int tailX[maxTail], tailY[maxTail];
int tailLength;
bool gameOver = false;
bool gamePause = false;
bool debug;
bool wallSetting;
bool hitWall = false;
string debugS;
string wallSettingS;
string gameOverS;
vector <int> fruitX(fruitMaxQuantity);
vector <int> fruitY(fruitMaxQuantity);

enum eDirecton { NotMoving = 0, LEFT, RIGHT, UP, DOWN};
eDirecton snakeDirection;

//----------------- PROTOTYPES -----------------//
int main();
void showflow(string);
void ConvertToLowerCase(string &);
void ResetSnake();
void SetFruitPosition();
void DisplayGameOptions();
void GenerateTail();
void GenerateSnakeHead();
void CheckForGameOver();
void GameOverPrompts();
void HasFruitBeenEaten();
void UserPrompt();
void Setup();
void DrawBoard();
void CheckForUserInput();
void SnakeAndTailMovement();
//----------------- PROTOTYPES -----------------//

void showflow(string msg) {
    // this entire function is dedicated to debug
    if (debug == true) {
        cout << "--> " << msg << endl;
        Sleep(gameSpeed);
    }
}

void ConvertToLowerCase(string & str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
}

void ResetSnake() {
    //showflow("reseting snake position"); // debug

    gameOver = false;
    snakeDirection = NotMoving;
    snakeX = boardWidth / 2;
    snakeY = boardHeight / 2;
    tailLength = 0;
}

void SetFruitPosition() {
    //showflow("setting fruit position within board border"); // debug

    for (int i = 0; i < fruitMaxQuantity; i++) { // iterates over i fruit(s)
        // while loops check for fruit selections out of range
        while (fruitX[i] <= 0 || fruitX[i] >= boardWidth) {
            fruitX[i] = rand() % boardWidth;
        }
        while (fruitY[i] <= 0 || fruitY[i] >= boardHeight) {
            fruitY[i] = rand() % boardWidth;
        }
    }
}

void DisplayGameOptions() {
    cout << "Score: " << score << endl;
    cout << "Max Fruit: " << fruitMaxQuantity << endl;
    cout << "Wall Setting: " << wallSettingS << endl; // debug
    cout << "Debug Setting: " << debugS << endl; //debug
    cout << "Game Speed: " << gameSpeed << endl << endl;
    cout << "q--> QUIT    p--> PAUSE    r--> RESTART" << endl;

    // snake coordinate tracker
    cout << "Snake position: (" << snakeX << ", " << snakeY << ")" << endl; // debug
}

void GenerateTail() {
    //showflow("generating tail piece"); // debug

    int prevTailX = tailX[0];
    int prevTailY = tailY[0];
    int prevTail2X, prevTail2Y;
    tailX[0] = snakeX;
    tailY[0] = snakeY;

    for (int i = 1; i < tailLength; i++) { // iterates over i tail(s) to assign new tail position
        prevTail2X = tailX[i];
        prevTail2Y = tailY[i];
        tailX[i] = prevTailX;
        tailY[i] = prevTailY;
        prevTailX = prevTail2X;
        prevTailY = prevTail2Y;
    }
}

void GenerateSnakeHead() {
    //showflow("generating snake head"); // showflow debug

    int prevSnakeX = snakeX;
    int prevSnakeY = snakeY;

    switch (snakeDirection) {
    case LEFT:
        snakeX--;
        break;
    case RIGHT:
        snakeX++;
        break;
    case UP:
        snakeY--;
        break;
    case DOWN:
        snakeY++;
        break;
    default:
        break;
    }

    if (snakeX >= boardWidth)
        snakeX = 0;
    else if (snakeX < 0)
        snakeX = boardWidth - 1;
    if (snakeY >= boardHeight)
        snakeY = 0;
    else if (snakeY < 0)
        snakeY = boardHeight - 1;

    if (wallSetting == true) {
        if ((prevSnakeX - snakeX) == (abs(boardWidth - 1)) || (prevSnakeY - snakeY) == (abs(boardHeight - 1))) {
            showflow("snake hit right or bottom wall");

            hitWall = true;
        }
        if ((snakeX - prevSnakeX) == (abs(boardWidth -1)) || (snakeY - prevSnakeY) == (abs(boardHeight - 1))) {
            showflow("snake hit left or top wall");

            hitWall = true;
        }
    }
}

void CheckForGameOver() {
    //showflow("checking for game over"); // showflow debug

    // game over if hits own tail
    for (int i = 0; i < tailLength; i++)
        if (tailX[i] == snakeX && tailY[i] == snakeY) {
            showflow("hit tail game over prompted");

            cout << "You ran into your own tail!" << endl;
            GameOverPrompts();
        }
    // game over if hits wall
    if (wallSetting == true) {
        if (hitWall == true) {
            cout << "You ran into a wall!" << endl;
            hitWall = false;
            GameOverPrompts();
        }
    }
}

void GameOverPrompts() {
    cout << "Do you want to play again?" << endl;
    cout << "(Y/N)" << endl;
    cin >> gameOverS;
    ConvertToLowerCase(gameOverS);
    while (gameOverS != "y" && gameOverS != "n") {
        cout << "You must input either (Y/N)" << endl;
        cout << "Enter again: ";
        cin >> gameOverS;
        ConvertToLowerCase(gameOverS);
    }
    if (gameOverS == "y") {
        gameOver = false;
        main();
    } else {
        cout << "--QUITTING GAME--" << endl;
        exit (EXIT_FAILURE);
    }
}

void HasFruitBeenEaten() {
    //showflow("checking if fruit has been eaten"); // debug

    for (int i = 0; i < fruitMaxQuantity; i++) {
        if (snakeX == fruitX[i] && snakeY == fruitY[i]) {
            showflow("detected fruit has been eaten"); // debug

            score += 10;
            fruitX[i] = rand() % boardWidth;
            fruitY[i] = rand() % boardHeight;
            SetFruitPosition();
            tailLength++;
        }
    }
}

void UserPrompt() {
    // game start prompt //
    cout << string(39, '=') << endl;
    cout << "||WELCOME TO THE SNAKE GAME.. SSSSSSS||" << endl;
    cout << string(39, '=') << endl << endl;
    cout << "Your goal is to collect as many fruit pieces as possible\nand avoid violating game defined rules causing a game over" << endl;
    cout << "Controls--> WASD = movement" << endl << endl;
    // game start prompt //

    // max fruit user setting //
    cout << "Select max fruit game board can have(maximum of " << (boardHeight * boardWidth) / boardHeight << "): ";
    cin >> fruitMaxQuantity;
    while (fruitMaxQuantity <= 0 || fruitMaxQuantity > (boardHeight * boardWidth) / boardHeight) { // checks for invalid user input
        cout << "Fruit quantity must be greater than zero and less than " << ((boardHeight * boardWidth) / boardHeight) + 1 << endl;
        cout << "Enter a new quantity: ";
        cin >> fruitMaxQuantity;
    }
    cout << endl;
    // max fruit user setting //

    // game speed user setting //
    cout << "Select game speed: ";
    cin >> gameSpeed;
    while (gameSpeed <= 0 || gameSpeed > 100) { // checks for invalid user input
        cout << "Game speed must be greater than zero and less than or equal to 100" << endl;
        cout << "Enter a new quantity: ";
        cin >> gameSpeed;
    }
    cout << endl;
    // game speed user setting //

    // user wall setting //
    cout << "Should the game end if you hit a wall?\n(input T/F): ";
    cin >> wallSettingS;
    ConvertToLowerCase(wallSettingS);
    while (wallSettingS != "t" && wallSettingS != "f") { // checks for invalid user input
        cout << "A setting of (T/F) must be entered" << endl;
        cout << "Enter setting again: ";
        cin >> wallSettingS;
        ConvertToLowerCase(wallSettingS);
    }
    if (wallSettingS == "t")
        wallSetting = true;
    else
        wallSetting = false;
    cout << endl;
    // user wall setting //

    // user debug setting //
    cout << "Should the debugger(showflow) be on during the game?\n(input T/F): ";
    cin >> debugS;
    ConvertToLowerCase(debugS);
    while (debugS != "t" && debugS != "f") { // checks for invalid user input
        cout << "A setting of (T/F) must be entered" << endl;
        cout << "Enter setting again: ";
        cin >> debugS;
        ConvertToLowerCase(debugS);
    }
    if (debugS == "t")
        debug = true;
    else
        debug = false;
    // user debug setting //
}

void SetupGame() {
    gameOver = false;
    for (int i = 0; i < fruitMaxQuantity; i++) { // iterates over i fruit(s) to start fruit placement loop
        fruitX[i] = rand() % boardWidth;
        fruitY[i] = rand() % boardHeight;
    }
    SetFruitPosition(); // corrects for fruit placement errors
    score = 0;
}

void DrawBoard() {
    //showflow("drawing game board"); // showflow debug

    system("cls"); //system("clear");
    // bools for setting proper spacing when generating symbols
    bool snakeBool = false;
    bool tailBool = false;
    bool fruitBool = false;
    bool edgeBool = false;

    cout << string(boardWidth + 2, '#') << endl; // generates top of board

    for (int y = 0; y < boardHeight; y++) { // y axis of board
        for (int x = 0; x < boardWidth; x++) { // x axis of board
            if (x == 0) { // generates left border
                cout << "#";
            }
            if (y == snakeY && x == snakeX) { // generates snake on board
                cout << "S";
                if (snakeX == boardWidth - 1) { // special case- generates right board when at right border
                    cout << "#";
                    edgeBool = true;
                }
                snakeBool = true;
            }
            for (int j = 0; j < tailLength; j++) { // iterates over j number of tail pieces
                if (y == tailY[j] && x == tailX[j]) { // generates tail on board
                    cout << "o";
                    if (tailX[j] == 19) { // special case- generates right board when tail piece(s) at right border
                        cout << "#";
                        edgeBool = true;
                    }
                    tailBool = true;
                }
            }
            for (int i = 0; i < fruitMaxQuantity; i++) { // iterates over i number of fruit pieces
                if (y == fruitY[i] && x == fruitX[i]) { // generates fruit on board
                    cout << "F";
                    if (fruitX[i] == 19) { // special case- generates right board when fruit piece(s) at right border
                        cout << "#";
                        edgeBool = true;
                    }
                    fruitBool = true;
                }
            }
            cout << " ";
            if (x == boardWidth - 1) { // generates right border if not at special case
                if (edgeBool == false) {
                    cout << "#";
                } else {
                    edgeBool = false;
                }
            }
            // checks for special cases and backspaces for proper spacing if detected
            if (snakeBool == true) {
                cout << "\b";
                snakeBool = false;
            }
            if (tailBool == true) {
                cout << "\b";
                tailBool = false;
            }
            if (fruitBool == true) {
                cout << "\b";
                fruitBool = false;
            }
        }
        cout << endl;
    }

    cout << string(boardWidth + 2, '#') << endl; // generates bottom of board

    // Display Values
    DisplayGameOptions();
}

void CheckForUserInput() {
    //showflow("checking for user key strokes"); // showflow debug

    if (_kbhit()) {
        switch (tolower(_getch())) { // checks for valid game inputs
        case 'a':
            snakeDirection = LEFT;
            break;
        case 'd':
            snakeDirection = RIGHT;
            break;
        case 'w':
            snakeDirection = UP;
            break;
        case 's':
            snakeDirection = DOWN;
            break;
        case 'q':
            cout << "--QUITTING GAME--" << endl;
            exit (EXIT_FAILURE);
            break;
        case 'p': // this part of the menu is the keystroke for pause-game
            cout << "--GAME IS PAUSED--" << endl;
            gamePause = true;
            break;
        case 'r': // restarts program
            cout << "--RESTARTING GAME--" << endl;
            gameOver = false;
            main();
            break;
        }

        // waits for user to resume if game is paused
        while (gamePause == true) {
            if (_kbhit()) {
                cout << "--GAME RESUMING--" << endl;
                gamePause = false;
            }
        }
    }
}

void SnakeAndTailMovement() {
    //showflow("checking for snake movement"); // showflow debug

    // generate tail
    GenerateTail();

    // generate snake head
    GenerateSnakeHead();

    // checks for game over
    CheckForGameOver();

    // has fruit been eaten
    HasFruitBeenEaten();
}

int main() {
    system("cls"); // clears board just in case restart was activated

    ResetSnake();
    UserPrompt();
    SetupGame();

    while (!gameOver) {
        DrawBoard();
        CheckForUserInput();
        SnakeAndTailMovement();
        Sleep(gameSpeed);
        if (gameOver == true) {
            GameOverPrompts();
        }
    }
    return 0;
}
