// Author:     Rahib R Laghari
// Course:     CS1337.010
// Date:       3/29/2021
// Assignment: HW 5 - The animal guessing game
// Compiler:   Visual Studio Code

// Description:
// Using structs and the new function, this program will create a binary tree of answers and questions
// which can be searched with yes and no answers to find a certain animal, or allow you the option to add on
// if the animal isn't already stored

// Change log:
// Mar 29:
// Added struct for animalNode
// Added travelThroughTree, which basically travels through the binary tree
// Setup main function and initialized along with set up a few nodes for practice
// Mar 30:
// Added the "AddNewAnimals", and set up the variable prev and next Animal to allow it to be in full scope and change the program
// Got beginning nodes in place, along with finalizing all the functions and debugging to made sure it worked

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;
// (Got struct from hw)
struct animalNode {
 string question; //a question to ask the user
 string guess; //the name of an animal to guess
 animalNode* yesAnswer; //null or pointer to the “yes” animalNode
 animalNode* noAnswer; //null or pointer to the “no” animalNode
};

void BeginningPrompt(){
    cout << "Let's play the \"Guess the Animal\" game." << endl;
    cout << "Think of an animal and hit return when you’re ready. " << endl;
}
void AddNewAnimal(animalNode *Animal, animalNode &prevAnimal, animalNode &newAnimal, string guessAnimal){// added: animalNode *newAnimal, animalNode *prevAnimal,
    string rightAnswer;
    string differenciateQuestion;
    string differenciateAnswer;
    string playAgain;
    cout << "I must not have your animal yet! What was your animal? ";
    cin >> rightAnswer;
    cout << "What question would differenciate " << rightAnswer << " from " << guessAnimal << "?" << endl;
    // cin >> differenciateQuestion;
     cin.ignore();
     getline(cin, differenciateQuestion);
    cout << "And what answer would make this animal " << rightAnswer << "? ";
    cin >> differenciateAnswer;
    newAnimal.guess = rightAnswer;
    prevAnimal.guess = guessAnimal;
    Animal->guess = "N/A";
    Animal->question = differenciateQuestion;
    if(differenciateAnswer == "yes"){
        Animal->yesAnswer = new animalNode;
        Animal->yesAnswer = &newAnimal;
        //Animal->yesAnswer->guess = rightAnswer;
        Animal->noAnswer = new animalNode;
        Animal->noAnswer = &prevAnimal;
        //Animal->noAnswer->guess = guessAnimal;
        // cout << Animal->noAnswer->guess << endl;
        // cout << Animal->yesAnswer->guess << endl;
    }
    else{//(differenciateAnswer == "no")
        Animal->yesAnswer = new animalNode;
        Animal->yesAnswer = &prevAnimal;
        //Animal->yesAnswer->guess = guessAnimal;
        Animal->noAnswer = new animalNode;
        Animal->noAnswer = &newAnimal;
        //Animal->noAnswer->guess = rightAnswer;
        cout << Animal->guess << endl;
        cout << Animal->noAnswer->guess << endl;
        cout << Animal->yesAnswer->guess << endl;
    }
    /*animalNode nnnAnimal = {"", "Human", nullptr, nullptr};
        firstAnimal.yesAnswer = new animalNode;
        firstAnimal.yesAnswer = &yAnimal;
        yAnimal.yesAnswer = new animalNode;
        yAnimal.yesAnswer = &yyAnimal;*/
    cout << "Play again? ";
    cin >> playAgain;
    if(playAgain == "no"){
        exit(0);
    }
    // create new animal Node struct
    // create new Node for unanswered question
}

// travelThroughTree needed twice since after passing the first node in as struct animalNode, the rest are passed into it as
// a pointer to another node, so the regular node is used once and pointers used after
void travelThroughTree(animalNode *Animal,  animalNode &prevAnimal, animalNode &newAnimal){
    string questionAnswer;
    if((Animal->guess) == "N/A"){
        cout << Animal->question << endl;
        cin >> questionAnswer;
        if (questionAnswer == "yes"){
            travelThroughTree(Animal->yesAnswer, prevAnimal, newAnimal);
        }
        else if(questionAnswer == "no"){
            travelThroughTree(Animal->noAnswer, prevAnimal, newAnimal);
        }
    }
    else{
        cout << "Was your animal a " << Animal->guess << endl;
        cin >> questionAnswer;
        if(questionAnswer == "yes"){
            cout << "Good! I guessed your animal." << endl;
            cout << "Play again? ";
            cin >> questionAnswer;
            if(questionAnswer == "yes"){
                // automatically restarts from file
            }
            else{
                exit(0);
            }
        }
        else{
            AddNewAnimal(Animal, prevAnimal, newAnimal, Animal->guess);
        }
    }
}

void travelThroughTree(animalNode Animal, animalNode &prevAnimal, animalNode &newAnimal){
    string questionAnswer;
    cout << Animal.question << endl;
    cin >> questionAnswer;
    if (questionAnswer == "yes"){
        travelThroughTree(Animal.yesAnswer, prevAnimal, newAnimal);
    }
    else if(questionAnswer == "no"){
        travelThroughTree(Animal.noAnswer, prevAnimal, newAnimal);
    }
}

string correctAnswer(){
    string playAgain;
    cout << "Good! I have got your animal" << endl;
    cout << "Try again?" << endl;
    cin >> playAgain;
    return playAgain;
}

//int runOnce = 0;
//animalNode firstAnimal = {"Does your animal fly?", "", nullptr, nullptr};

int main(){
    string animal;
    string startQuestions;
    string questionAnswer;
    //First, I create a few animal nodes and link them (run once)
    //if (runOnce == 0){
        animalNode firstAnimal = {"Does your animal fly?", "", nullptr, nullptr};
        animalNode yAnimal = {"Is your animal an icon in american culture?", "N/A", nullptr, nullptr};
        animalNode yyAnimal = {"", "Bald Eagle", nullptr, nullptr};
        animalNode ynAnimal = {"", "Crow", nullptr, nullptr};
        animalNode nAnimal = {"Is your animal a common household pet?", "N/A", nullptr, nullptr};
        animalNode nyAnimal = {"Does your animal meow?", "N/A", nullptr, nullptr};
        animalNode nyyAnimal = {"", "Cat", nullptr, nullptr};
        animalNode nynAnimal = {"", "Dog", nullptr, nullptr};
        animalNode nnAnimal = {"Is your animal percieved as typically larger or longer than a human?", "N/A", nullptr, nullptr};
        animalNode nnyAnimal = {"", "Elephant", nullptr, nullptr};
        animalNode nnnAnimal = {"", "Human", nullptr, nullptr};
        firstAnimal.yesAnswer = new animalNode;
        firstAnimal.yesAnswer = &yAnimal;
        yAnimal.yesAnswer = new animalNode;
        yAnimal.yesAnswer = &yyAnimal;
        yAnimal.noAnswer = new animalNode;
        yAnimal.noAnswer = &ynAnimal;
        firstAnimal.noAnswer = new animalNode;
        firstAnimal.noAnswer = &nAnimal;
        nAnimal.yesAnswer = new animalNode;
        nAnimal.yesAnswer = &nyAnimal;
        nnAnimal.yesAnswer = new animalNode;
        nnAnimal.yesAnswer = &nnyAnimal;
        nnAnimal.noAnswer = new animalNode;
        nnAnimal.noAnswer = &nnnAnimal;
        nAnimal.noAnswer = new animalNode;
        nAnimal.noAnswer = &nnAnimal;
        nyAnimal.yesAnswer = new animalNode;
        nyAnimal.yesAnswer = &nyyAnimal;
        nyAnimal.noAnswer = new animalNode;
        nyAnimal.noAnswer = &nynAnimal;
    //}
    BeginningPrompt();
    getline(cin, startQuestions);
    animalNode newAnimal = {"", "", nullptr, nullptr};// added
    animalNode prevAnimal = {"", "", nullptr, nullptr};// added
    while(1){
        travelThroughTree(firstAnimal, prevAnimal, newAnimal);
    }
}
