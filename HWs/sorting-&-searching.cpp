/*
 original code by Joshua McDonald

 3/4/21
    Setup preliminary functions for 1) looping user input 2) generating a vector
    of random values based on that input 3) prompting user for a search of values
    within the generated vector.
 3/4/21
 3/8/21
    Finished setting up proper input loop for program.
    Finished functions for generating and displaying vectors.
    Created rough framework for user inputed search function. This function
    calls a secondary function that will do bi-section search on the current
    vector. After this it will use a pass back of an INT to display how many
    times the currently searched INT is found.
 3/8/21
 3/10/21
    Finished all parts of display output functions.
    Created function to create non-dupe version of vector.
 3/10/21
 3/12/21
    Finished code for binary search related to user inputed INT and fixed some bugs within it.
 3/12/21
 3/13/21
    Converted dupe deletion function to binary search method.
    Fixed more bugs in binary search of user inputed INT(s).
    Added proper sort function that does not rely on sort().
 3/13/21

*/

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <algorithm>

using namespace std;

// PROTOTYPE FUNCTIONS //
void showflow(string, int);
void UserInputLoop();
vector <int> GenerateVectors(int, int);
vector <int> DisplayVectors(vector <int>);
void CheckNumber(vector <int>, int &);
bool UserInputSearch(vector <int>);
void DisplayNonDupes(vector <int>);
void DeleteDupes(vector <int> &);
// PROTOTYPE FUNCTIONS //

// GLOBAL VARIABLES //
bool debug = false;
// GLOBAL VARIABLES //

void showflow (string debugMessage, int num) {
    if (debug == true) {
        if (num == -1000) {
            cout << "--> " << debugMessage << endl;
        } else {
            cout << "--> " << debugMessage << num << endl;
        }
    }
} //showflow

void UserInputLoop () {
    int randValQuant;
    int randValSize;
    char userInput;
    vector <int> tempVector;

    // USER PROMPT //
    cout << "How many random numbers should be generated? --> ";
    cin >> randValQuant;
    cout << endl;
    while (randValQuant <= 0 || randValQuant >= 100) {
        cout << "Number quantity must be greater than 0 and less than 100, enter a valid input. --> ";
        cin >> randValQuant;
        cout << endl;
    }
    cout << "What should the max length of each number be? --> ";
    cin >> randValSize;
    cout << endl;
    while (randValSize <= 0 || randValSize > 20) {
        cout << "Random value length must be greater than 0 and no greater than 20, enter a valid input. --> ";
        cin >> randValSize;
        cout << endl;
    }
    // USER PROMPT //

    // calls functions to 1) generate initial vector 2) modify and display it with a copy
    tempVector = GenerateVectors(randValQuant, randValSize);
    tempVector = DisplayVectors(tempVector);

    while(UserInputSearch(tempVector)) {
    }

    // calls function to modify and display the vector without duplicates
    DisplayNonDupes(tempVector);

    // USER PROMPT //
    cout << "Do you want to search a new set of numbers?" << endl;
    cout << "(Y/N): ";
    cin >> userInput;
    cout << endl;
    // USER PROMPT //

    // OUTPUT DISPLAY //
    if (tolower(userInput) == 'y') {
        UserInputLoop();
    } else {
        cout << "EXITING PROGRAM" << endl;
    }
    // OUTPUT DISPLAY //
} //UserInputLoop

vector <int> GenerateVectors (int randValQuant, int randValSize) {
    vector<int> tempVector;

    srand(time(nullptr));
    for (int i = 0; i < randValQuant; i++) {
        tempVector.push_back(rand() & randValSize);
    } //for user input value length

    return tempVector;
} //GenerateVectors

vector <int> DisplayVectors (vector <int> tempVector) {
    // OUTPUT DISPLAY //
    cout << "Random generated numbers V" << endl << endl;
    cout << "| ";
    for (int i = 0; i < tempVector.size(); i++) {
        cout << tempVector[i] << " | ";
    } //for length of random generated vector
    cout << endl << endl << "Vector size is: " << tempVector.size() << endl;
    cout << "Vector capacity is: " << tempVector.capacity() << endl;
    //sort(tempVector.begin(), tempVector.end());
    // OUTPUT DISPLAY //
    // BUBBLE SORT //
    bool swapped;
    for (int i = 0; i < tempVector.size()-1; i++) {
        swapped = false;
        for (int j = 0; j < tempVector.size()-1; j++) {
            if (tempVector[j] > tempVector[j+1]) {
                swap(tempVector[j], tempVector[j+1]);
                swapped = true;
            } //for length of random generated vector
        }
        if (swapped == false) {
            break;
        }
    } //for length of random generated vector
    // BUBBLE SORT //
    // OUTPUT DISPLAY //
    cout << "\nBubble sorted numbers V" << endl << endl;
    cout << "| ";
    for (int i = 0; i < tempVector.size(); i++) {
        cout << tempVector[i] << " | ";
    } //for length of random generated vector
    cout << endl << endl;
    // OUTPUT DISPLAY //

    return tempVector;
} //DisplayVectors

bool UserInputSearch (vector <int> tempVector) {
    int userInput;

    // USER PROMPT //
    cout << "Would you like to search for a specific number in the number list?" << endl;
    cout << "If not type (-1) to stop looking at the current list: ";
    cin >> userInput;
    cout << endl;
    if (userInput == -1) {
        return false;
    } else if (userInput >= 0 && userInput <= tempVector.back()) {
        CheckNumber(tempVector, userInput);
        cout << "That number was found " << userInput << " times" << endl;
    } else {
        cout << "Numbers being searched must be equal to or greater than 0 and less than or equal to " << tempVector.back() << endl;
    }
    // USER PROMPT //

    return true;
} //UserInputSearch

void CheckNumber (vector <int> tempVector, int & userInput) {
    int ticker = 0;
    int i = (tempVector.size()-1)/2; //sets first middle selection for binary search
    int tickerMax = 0;
    showflow("User inputed INT = ", userInput);

    do {
        if (tempVector[i] == userInput) { //if value found
            showflow("user input was found, userInput: ", userInput);
            ticker++;
            int firsti = i;
            while (tempVector[i] == tempVector[i-1]) {
                i--;
                ticker++;
            }
            i = firsti;
            while (tempVector[i] == tempVector[i+1]) {
                i++;
                ticker++;
            }
            break;
        } else if (tempVector[i] > userInput) { //if value not found and > userInput
            showflow("binary search going west", -1000);
            i = i/2;
        } else { // if value not found and < userInput
            showflow("binary search going east", -1000);
            i = i+(((tempVector.size()-1)-i)/2);
        }

        if (tickerMax == tempVector.size()-1) { //prevents infinite looping
            break;
        }
        tickerMax++;

    } while (tempVector[i] != tempVector[0] || tempVector[i] != tempVector[tempVector.size()-1]);

    if (ticker > 0) {
        userInput = ticker;
    } else {
        userInput = 0;
    }
} //CheckNumber

void DisplayNonDupes (vector <int> tempVector) {
    DeleteDupes(tempVector);

    // OUTPUT DISPLAY //
    cout << "List without duplicates V" << endl << endl;
    cout << "| ";
    for (int i = 0; i < tempVector.size(); i++) {
        cout << tempVector[i] << " | ";
    } //for length of random generated vector
    cout << endl << endl;
    // OUTPUT DISPLAY //
} //DisplayNonDupes

void DeleteDupes (vector <int> & tempVector) {
    int i = 0;

    while (i <= tempVector.size()-1) {
        if (tempVector[i] != tempVector[i+1]) {
            i++;
        } else {
            if (i == tempVector.size()-1) {
                break;
            }
            showflow("Deleting dupe at ", i);
            tempVector.erase(tempVector.begin()+i);
        }
    }
} //DeleteDupes

int main () {
    UserInputLoop();

    return 0;
} //main
