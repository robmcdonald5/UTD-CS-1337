//  ORIGINAL CODE BY JOSHUA MCDONALD
//
// 3/23/21 //
//  Created function for reading user text file
//  Created function for turning test file into both a 1D vector of strings
//  and a 2D vector of strings.
//  Created outline for all functions related to string text conversion.
// 3/23/21 //
//  Finished logic for half of text conversion functions.
//  Created sub functions for all needed primary text conversion functions.
// 3/24/21 //
//  Fixed bugs in multiple sub functions for proper title conversions
// 3/24/21 //
// 3/25/21 //
//  Added extra sub functions to assist in leet speak conversion
//  Changed text output to for loop for leet speak(inserting or appending
//  to the current line string caused bugs/bounding errors I could not fix)
// 3/25/21 //

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

// PROTOTYPES //
void showflow(string, int);
void ReadFile();
void GenerateVector(ifstream&, string);
void AnalyzeAndOutput(vector <string>, vector<vector<string>>);
void FindCharCount(string);
void FindStringCount(vector <vector<string>>, int);
void FindLongestWord(vector <vector<string>>, int);
void FindSpecialChars(string);
void ConvertLineToTitleCase(string);
void ConvertLineToSentenceCase(string);
bool CheckForProperNoun(string);
void ConvertLineToToggleCase(string);
void ConvertLineToMockingCase(string);
void CheckIfLeetCharShouldRun(string);
void ConvertLineToLeetSpeak(vector <string>, string);
string CheckForLeetSpeak(vector <string>, char, bool &);
// PROTOTYPES //

// GLOBAL VARS //
bool debug = false;
// GLOBAL VARS //

void showflow(string debugMessage, int debugInt) {
    if (debug == true) {
        if (debugInt != -1000) {
            cout << "----> " << debugMessage << debugInt << endl;
        } else {
            cout << "----> " << debugMessage << endl;
        }
    }
} //showflow

void ReadFile() {
    showflow("Reading File", -1000);
    string fileName;
    ifstream file;

    cout << "Input the text file you want read: ";
    cin >> fileName;
    cout << endl;
    file.open(fileName);

    while (!file) {
        cout << "That is either an invalid file or it does not exist, re-enter a new file name: ";
        cin >> fileName;
        cout << endl;
        file.open(fileName);
    }

    GenerateVector(file, fileName);
    file.close();
} //ReadFile

void GenerateVector(ifstream &file, string currentLine) {
    showflow("Generating Vector", -1000);
    vector<string> vector1D;
    vector<vector<string>> vector2D;
    string lineSec;

    //builds 1D vector from text file
    while (getline(file, currentLine)) {
        vector1D.push_back(currentLine);
    }

    //builds 2D vector from 1D vector
    vector2D.resize(vector1D.size());
    for (int i = 0; i < vector1D.size(); i++) {
        showflow("In upper for loop current line = ", i+1);
        string currentString;
        lineSec = vector1D[i];
        for (int j = 0; j < lineSec.length(); j++) {
            if (!isalpha(lineSec[j])) {
                showflow("Line end at char = ", j+1);
                while (!isalpha(lineSec[j])) {
                    j++;
                }
                vector2D[i].push_back(currentString);
                currentString.clear();
            }
            currentString = currentString + lineSec[j];
            showflow("In inner for loop current char = ", j+1);
        } //for length of current line
    } //for length of 1D vector

    AnalyzeAndOutput(vector1D, vector2D);
} //GenerateVector

void AnalyzeAndOutput(vector <string> vector1D, vector<vector<string>> vector2D) {
    showflow("Analyzing Line By Line", -1000);
    //calls all secondary functions to analyze and output info and text on the vector strings
    for (int i = 0; i < vector1D.size(); i++) {
        cout << "Line #" << i+1 << ": " << vector1D[i] << endl;
        FindCharCount(vector1D[i]);
        FindStringCount(vector2D, i);
        FindLongestWord(vector2D, i);
        FindSpecialChars(vector1D[i]);
        ConvertLineToTitleCase(vector1D[i]);
        ConvertLineToSentenceCase(vector1D[i]);
        ConvertLineToToggleCase(vector1D[i]);
        ConvertLineToMockingCase(vector1D[i]);
        CheckIfLeetCharShouldRun(vector1D[i]);
        cout << endl;
    } //for length of 1D vector
} //AnalyzeAndOutput

void FindCharCount(string currentLine) {
    showflow("Counting characters in current line", -1000);
    cout << "   The number in chars in this line: " << currentLine.length() << endl;
} //FindCharCount

void FindStringCount(vector <vector<string>> vector2D, int lineNumber) {
    showflow("Counting strings in current line", -1000);
    cout << "   The number of strings in this line: " << vector2D[lineNumber].size() << endl;
} //FindStringCount

void FindLongestWord(vector <vector<string>> vector2D, int lineNumber) {
    showflow("Finding longest word in current line", -1000);
    string currentString;
    string currentLongest = vector2D[lineNumber][0];

    // counts number of strings in current line(ignores all non alpha characters)
    for (int i = 1; i < vector2D[lineNumber].size(); i++) {
        currentString = vector2D[lineNumber][i];
        if (currentString.length() > currentLongest.length()) {
            currentLongest = currentString;
        }
    } //for length of strings in current line in 2D vector

    cout << "   The longest string in this line: " << currentLongest << endl;
} //FindLongestWord

void FindSpecialChars(string currentLine) {
    showflow("Counting special chars in current line", -1000);
    string vowels = "aeiouyw";
    string blankSpace = " ";
    string punctuation = ".,;:?!'_()[]\"\"-";
    int vowelsTicker = 0, blankSpaceTicker = 0, punctuationTicker = 0, consonantTicker = 0, otherTicker = 0;

    //looks at every char in current line and iterates tickers
    for (int i = 0; i < currentLine.length(); i++) {
        if (vowels.find(currentLine[i]) != string::npos) {
            showflow("  found a vowel at ", i);
            vowelsTicker++;
        } else if (isalpha(currentLine[i])) {
            showflow("  found a consonant at ", i);
            consonantTicker++;
        } else if (currentLine[i] == ' ') {
            showflow("  found blank space at ", i);
            blankSpaceTicker++;
        } else if (punctuation.find(currentLine[i]) != string::npos) {
            showflow("  found punctuation at ", i);
            punctuationTicker++;
        } else {
            showflow("  found other at ", i);
            otherTicker++;
        }
    } //for length of current line

    cout << "   Vowels: " << vowelsTicker << " | Consonants: " << consonantTicker << " | Blank space: " << blankSpaceTicker
         << " | Punctuation: " << punctuationTicker << " | Other: " << otherTicker << endl;
} //FindSpecialChars

void ConvertLineToTitleCase(string currentLine) {
    showflow("Converting and outputting to title case", -1000);
    //applies title case rules to current line
    for (int i = 0; i < currentLine.length(); i++) {
        if (currentLine[i] == ' ') {
            while (!isalpha(currentLine[i])) {
                i++;
                if (isalpha(currentLine[i])) {
                    char currentChar = toupper(currentLine[i]);
                    currentLine[i] = currentChar;
                } else if (i == currentLine.length()) {
                    break;
                }
            }
        }
    } //for length of current line

    cout << "   " << currentLine << " | Title Case"<< endl;
} //ConvertLineToTitleCase

void ConvertLineToSentenceCase(string currentLine) {
    showflow("Converting and outputting sentence case", -1000);
    string currentString;

    //applies sentence case rules to current line
    currentLine[0] = toupper(currentLine[0]);
    for (int i = 1; i < currentLine.length(); i++) {
        if (currentLine[i] == ' ') {
            int firstChar = i;
            while (!isalpha(currentLine[i])) {
                i++;
                if (i == currentLine.length()) {
                    break;
                }
            }
            while (isalpha(currentLine[i])) {
                currentString = currentString + currentLine[i];
                i++;
            }
            if (!CheckForProperNoun(currentString)) {
                currentLine[firstChar] = tolower(currentLine[firstChar]);
            }
            currentString.clear();
        }
    } //for length of current line

    cout << "   " << currentLine << " | Sentence Case" << endl;
} //ConvertLineToSentenceCase

bool CheckForProperNoun(string currentString) {
    showflow("Checking for a proper noun", -1000);
    vector <string> properNouns {"My", "Amy", "Spain", "Suzy", "Becky", "Billy", "Dan", "Fred", "Fritos",
                                 "Friday", "Rudolph", "Hertford", "Hereford", "Hampshire", "Professor",
                                 "Henry", "Higgins", "Fair", "Lady", "Liza", "Cockney", "Rhine"};

    // checks if current string is in properNouns vector list
    auto it = find(properNouns.begin(), properNouns.end(), currentString);
    if (it != properNouns.end()) {
        showflow("  proper noun found", -1000);
        return true;
    } else {
        return false;
    }
} //CheckForProperNoun

void ConvertLineToToggleCase(string currentLine) {
    showflow("Converting and outputting to toggle case", -1000);
    //applies toggle case rules to current line
    currentLine[0] = tolower(currentLine[0]);
    for (int i = 1; i < currentLine.length(); i++) {
        if (isalpha(currentLine[i])) {
            currentLine[i] = toupper(currentLine[i]);
        }
        while (currentLine[i] == ' ') {
            i++;
            while (!isalpha(currentLine[i])) {
                i++;
            }
            if (isalpha(currentLine[i])) {
                currentLine[i] = tolower(currentLine[i]);
                break;
            }
            if (i == currentLine.length()) {
                break;
            }
        }
    } //for length of current line

    cout << "   " << currentLine << " | Toggle Case" << endl;
} //ConvertLineToToggleCase

void ConvertLineToMockingCase(string currentLine) {
    showflow("Converting and outputting to mocking case", -1000);
    //applies toggle case rules to current line
    for (int i = 0; i < currentLine.length(); i++) {
        if (isalpha(currentLine[i])) {
            if ((rand() % 2) + 1 == 2) {
                currentLine[i] = toupper(currentLine[i]);
            } else {
                currentLine[i] = tolower(currentLine[i]);
            }
        }
    } //for length of current line

    cout << "   " << currentLine << " | Mocking Case" << endl;
} //ConvertLineToMockingCase

void CheckIfLeetCharShouldRun(string currentLine) {
    string fileName = "leetchars.txt";
    ifstream file;
    string currentString;

    file.open(fileName);
    if (file) { //runs leet subroutine if a leetchars file is found
        showflow("  leet text file found", -1000);
        vector <string> leetChars;

        while (getline(file, currentString)) {
            leetChars.push_back(currentString);
        }
        ConvertLineToLeetSpeak(leetChars, currentLine);
    } else {
        cout << "Could not locate leetchars text file" << endl;
    }
    file.close();
} //CheckIfLeetCharShouldRun

void ConvertLineToLeetSpeak(vector <string> leetChars, string currentLine) {
    showflow("Converting and outputting leet speak", -1000);
    bool found;

    cout << "   ";
    for (int i = 0; i < currentLine.length(); i++) {
        if (isalpha(currentLine[i])) {
            string leetConvert = CheckForLeetSpeak(leetChars, currentLine[i], found);

            if (found == true) {
                cout << leetConvert;
            } else {
                cout << currentLine[i];
            }
        } else {
            cout << currentLine[i];
        }
    } //for length of current line
    cout << " | Leet Speak" << endl;
} //ConvertLineToLeetSpeak

string CheckForLeetSpeak(vector <string> leetChars, char currentChar, bool & found) {
    currentChar = toupper(currentChar);

    for (int i = 0; i < leetChars.size(); i++) {
        string currentString = leetChars[i];
        if (currentString[0] == currentChar) {
            showflow("  leet char found", -1000);
            currentString.erase(0,2);

            found = true;
            return currentString;
        }
    } //for length of leetChars container
    found = false; //prevents false positives
} //CheckForLeetSpeak

int main() {
    ReadFile();

    showflow("DID NOT CRASH!!", -1000);

    return 0;
} //main
