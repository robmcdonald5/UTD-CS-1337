/*
// Original code by - Joshua McDonald
//
// 3/31/21
//  Built AnimalNode struct
//  Created initial function outline for looping user interaction
// 3/31/21
// 4/1/21
//  Added subroutine declarations for initial part of struct to allow program to
//  have a starting point questioning user.
// 4/1/21
// 4/2/21
//  Added special functions PromptUser() & StringToLower(). PromptUser is just a
//  prompting function for easier to read code.
// 4/2/21
// 4/3/21
//  Created proper looping of entire program from all end points
//  Setup recursive calling of nodes in AnimalNode struct to move through questioning
//  line for user.
// 4/3/21
// 4/4/21
//  Fixed bugs in AskQuestion recursive loop and AddAnimal function
//  Added tail ends of all sides of subroutine struct declarations to fix bugs that
//  were showing up.
// 4/4/21
// 4/5/21
//  Compacted questing loop down to two functions instead of 3(calling different parts
//  of the AnimalNode struct was creating bugs I could not fix).
// 4/5/21
*/

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

struct AnimalNode {
    string question;
    string guess;
    AnimalNode * yesAnswer;
    AnimalNode * noAnswer;
};

// PROTOTYPES
void showflow(string);
void Loop(AnimalNode currentAnimal, AnimalNode & previousAnimal, AnimalNode & newAnimal);
void AskQuestion(AnimalNode * currentAnimal, AnimalNode & previousAnimal, AnimalNode & newAnimal);
void GuessAnimal(AnimalNode * currentAnimal, AnimalNode & previousAnimal, AnimalNode & newAnimal);
void AddAnimal(AnimalNode * currentAnimal, AnimalNode & previousAnimal, AnimalNode & newAnimal, string);
void PromptUser();
string StringToLower(string);
// PROTOTYPES
// GLOBALS
bool gameActivated;
bool debug = false;
// GLOBALS

void showflow(string debugError) {
    if (debug == true) {
        cout << "--> " << debugError << endl;
    }
}//showflow

void Loop(AnimalNode currentAnimal, AnimalNode & previousAnimal, AnimalNode & newAnimal) {
    showflow("Entering initial loop");
    string answer;
    gameActivated = false;

    // Prompts user with iterated 'question' from Struct
    cout << currentAnimal.question << endl;
    cin >> answer;
    StringToLower(answer);
    cout << endl;

    //passes yesPointer or noPointer depending on where the program is pointing
    if (answer == "y") {
        AskQuestion(currentAnimal.yesAnswer, previousAnimal, newAnimal);
    } else if (answer == "n") {
        AskQuestion(currentAnimal.noAnswer, previousAnimal, newAnimal);
    }
}//Loop

void AskQuestion(AnimalNode * currentAnimal, AnimalNode & previousAnimal, AnimalNode & newAnimal) {
    showflow("Entering recursive loop");
    string answer;

    if ((currentAnimal->guess) == "continue") { //prints current question in struct
        cout << currentAnimal->question << endl;
        cin >> answer;
        StringToLower(answer);
        cout << endl;

        if (answer == "y") {
            AskQuestion(currentAnimal->yesAnswer, previousAnimal, newAnimal);
        } else if (answer == "n") {
            AskQuestion(currentAnimal->noAnswer, previousAnimal, newAnimal);
        }
    } else { //computer determined at end of question line-> now guessing animal
        GuessAnimal(currentAnimal, previousAnimal, newAnimal);
    }
}//AskQuestion

void GuessAnimal(AnimalNode * currentAnimal, AnimalNode & previousAnimal, AnimalNode & newAnimal) {
    showflow("Guessing animal");
    string answer;

    //prints current guess in Struct
    cout << "Was your animal a " << currentAnimal->guess << "?" << endl;
    cin >> answer;
    StringToLower(answer);
    cout << endl;

    //checks for yes or no string prompts
    if (answer == "y") {
        cout << "Sweet.. I guessed your animal.\nDo you want to play again?" << endl;
        cout << "(Y/N): ";
        cin >> answer;
        StringToLower(answer);

        if (answer == "y") {
            gameActivated = true;
        } else if (answer == "n") {
            exit (EXIT_FAILURE);
        }
    } else if (answer == "n") {
        AddAnimal(currentAnimal, previousAnimal, newAnimal, currentAnimal->guess);
    }
}//GuessAnimal

void AddAnimal(AnimalNode * currentAnimal, AnimalNode & previousAnimal, AnimalNode & newAnimal, string wrongAnimal) {
    showflow("Adding an animal");
    string newAnimalPick;
    string diffQuestion;
    string answer;
    string diffResponse;

    //prompts user to fill data needed to add an animal
    cout << "Darn.. What was your animal? ";
    cin >> newAnimalPick;
    cout << endl;
    cout << "What is a differentiating question of this animal from " << wrongAnimal << "? ";
    cin.ignore();
    getline(cin, diffQuestion);
    cout << endl;
    cout << "OK, now what is the answer to this question(Y/N)? ";
    cin >> diffResponse;
    StringToLower(diffResponse);
    cout << endl;

    //assigns animal to end of Struct with pointers
    newAnimal.guess = newAnimalPick;
    previousAnimal.guess = wrongAnimal;
    currentAnimal->guess = "continue";
    currentAnimal->question = diffQuestion;

    //checks for yes or no strings and assigns pointer based on results
    if (diffResponse == "y") {
        currentAnimal->yesAnswer = new AnimalNode;
        currentAnimal->yesAnswer = & newAnimal;
        currentAnimal->noAnswer = new AnimalNode;
        currentAnimal->noAnswer = & previousAnimal;
    } else if (diffResponse == "n") {
        currentAnimal->yesAnswer = new AnimalNode;
        currentAnimal->yesAnswer = & previousAnimal;
        currentAnimal->noAnswer = new AnimalNode;
        currentAnimal->noAnswer = & newAnimal;
    }

    cout << "Do you want to play again(Y/N)? " << endl;
    cin >> answer;
    StringToLower(answer);
    cout << endl;

    //checks for yes or no strings and Loop(s) OR exits program
    if (answer == "y") {
        gameActivated = true;
    } else if (answer == "n") {
        exit (EXIT_FAILURE);
    }
}//AddAnimal

void PromptUser() {
    cout << "Welcome to the animal guessing game!!" << endl << endl;
    cout << "Think of an animal and press enter when you are ready" << endl;
    cin.ignore();
}//PromptUser

string StringToLower(string currentString) {
    for (int i = 0; i < currentString.length(); i++) {
        currentString[i] = tolower(currentString[i]);
    } //for length of current string

    return currentString;
}//StringToLower

int main() {
    //subroutine
    AnimalNode firstAnimal = {"Is your animal cold blooded?", "", nullptr, nullptr};
    AnimalNode yFirstAnimal = {"Does your animal have fins?", "continue", nullptr, nullptr};
    AnimalNode ynFirstAnimal = {"", "shark", nullptr, nullptr}; // test
    AnimalNode yyFirstAnimal = {"", "shark", nullptr, nullptr};
    AnimalNode nFirstAnimal = {"Is your animal the dominant species on earth?", "continue", nullptr, nullptr};
    AnimalNode nnFirstAnimal = {"", "human", nullptr, nullptr};
    AnimalNode nyFirstAnimal = {"", "human", nullptr, nullptr};
    firstAnimal.yesAnswer = new AnimalNode;
    firstAnimal.yesAnswer = & yFirstAnimal;
    yFirstAnimal.yesAnswer = new AnimalNode;
    yFirstAnimal.yesAnswer = & yyFirstAnimal;
    yFirstAnimal.noAnswer = new AnimalNode;
    yFirstAnimal.noAnswer = & ynFirstAnimal;
    firstAnimal.noAnswer = new AnimalNode;
    firstAnimal.noAnswer = & nFirstAnimal;
    nFirstAnimal.yesAnswer = new AnimalNode;
    nFirstAnimal.yesAnswer = & nyFirstAnimal;
    nFirstAnimal.noAnswer = new AnimalNode;
    nFirstAnimal.noAnswer = & nnFirstAnimal;
    AnimalNode previousAnimal = {"", "", nullptr, nullptr};
    AnimalNode newAnimal = {"", "", nullptr, nullptr};
    //subroutine

    PromptUser();

    do {
        Loop(firstAnimal, previousAnimal, newAnimal);
    } while(gameActivated == true);

    showflow("Did not crash");

    return 0;
}//main
