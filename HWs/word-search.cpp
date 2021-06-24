/*
 Original code by Joshua D. McDonald

  2/23/21
   Created base functions for program to operate
   Defined global variables for to-be read files and to-be populated vectors
   Created extra 'check_number' function for functions to call to see if a
        string has an integer
  2/23/21
   Created functions to filter file and generate 2D matrix of only alphanumeric
   characters in the file that are not preceded by comment indicators or numerals.
   Created secondary functions to populate a 2D matrix of just the character list
   and to create a 1D string vector of all movies in the file.
  2/24/21
   Created a function that looks at every movie and feeds that movie as a string to
   secondary functions. Lots of issues came up on the other end of this involving
   proper iterative loops when looking at the characters in the string. Scrapping
   this looping method for now.
  2/24/21
   Created a new replacement function that takes first character of every movie,
   feeds it to a secondary function that looks for every possible starter position
   in the 2D vector matrix.
   Created another function for that data to be pumped into to look for word matches.
   Could not figure out how to iterate over this data without creating bounding errors
   in for loops(crashing program often). Scrapping this function for a new one.
  2/24/21
   Created a new replacement function that has iterative for loops for every single
   lateral direction. Function currently can't get past two characters when trying
   to match words. Tried implement several secondary functions to fix this with no
   luck.
  2/26/21
   Fixed N/S/E/W for loops. Seems to be finding movies and passing them to be appended
   to the final list. Fixed several bugs in lateral loops that cause errors to appear
   less, but still crashes program. Bug seems to be related to bounding of the x/y of
   the 2D character matrix. Commented out this part of the code to let the program
   function. Still looking for fix to this part of the code.
  2/26/21
*/


#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// PROTOTYPES //
void showflow(string);
void ReadFile();
void AnalyzeFile();
void ScanLine(string);
void PopulateMatrix();
void PopulateMovieList();
void AnalyzeStartPositions();
void BuildString();
void CheckStartPositions(int, int, string);
void GenerateMatrixCords(string);
void DisplayResults();
void FindCharInMatrix(char currentChar, string);
void AppendCorrectMovie(int, int, string, string);
// PROTOTYPES //

// GLOBAL VARS //
bool debug = false;
string filename;
string filepath;
ifstream file;
ofstream outputfile;
int xMatrix, yMatrix;
vector <char> OneDCharList;
vector <vector<char>> TwoDCharList;
vector <vector<char>> Matrix;
vector <string> MovieList;
vector <string> ChosenList;
vector <string> ChosenDirection;
vector <int> ChosenCords;
vector <char> PossibleStart;
// GLOBAL VARS //

void showflow(string msg) {
    // this entire function is dedicated to debug
    if (debug == true) {
        cout << "--> " << msg << endl;
    }
} //showflow

void ReadFile() {
    outputfile.open ("output.txt");

    cout << "Enter text file you want word searched: ";
    outputfile << "Enter text file you want word searched: " << endl << endl;
    cin >> filename;
    cout << endl;
    file.open(filename);

    while (!file) { // errors user until valid file entered
        showflow("failed to read file");

        cout << "Error, can't open the specified input file: No such file or directory" << endl;
        cout << "The file name used was: " << filename << endl;
        cout << "Enter a new file name to use (or quit/exit): ";
        outputfile << "Error, can't open the specified input file: No such file or directory" << endl;
        outputfile << "The file name used was: " << filename << endl;
        outputfile << "Enter a new file name to use (or quit/exit): " << endl;
        cin >> filename;
        cout << endl;
        file.open(filename);

        if (filename == "exit" || filename == "quit") {
            file.close();
            outputfile.close();
            cout << "EXITING PROGRAM" << endl;
            exit (EXIT_FAILURE);
        } //if user prompts exit
    }
} //ReadFile

void AnalyzeFile() {
    string line;

    while (getline(file, line)) {
        showflow("reading line from file");

        ScanLine(line);
    }

    file.close();
} //AnalyzeFile

void ScanLine(string currentLine) {
    showflow("scanning current line");

    for (int i = 0; i < currentLine.length(); i++) {
        while (currentLine[i] == '\n') {
            i++;
        }
        if (isdigit(currentLine[i])) {
            showflow("generating matrix xy cords");

            GenerateMatrixCords(currentLine);

            break;
        }
        if (currentLine[i] == '#') {
            showflow("skipping comment line");

            break;
        } else if (isalpha(currentLine[i])) {
            OneDCharList.push_back(currentLine[i]);
        }
    } //for current line length do 'x'

    if (!OneDCharList.empty()) {
        TwoDCharList.push_back(OneDCharList);
    }
    OneDCharList.clear();
} //ScanLine

void PopulateMatrix() {
    vector <char> temp1DVector;

    for (int i = 0; i < yMatrix; i++) {
        for (int j = 0; j < xMatrix; j++) {
            temp1DVector.push_back(TwoDCharList[i][j]);
        }
        Matrix.push_back(temp1DVector);
        temp1DVector.clear();
    } // for max matrix xLength
} //PopulateMatrix

void PopulateMovieList() {
    int i;
    string tempOne;

    i = yMatrix;
    for (yMatrix; i < TwoDCharList.size(); i++) {
        for (int j = 0; j < (TwoDCharList[i].size()); j++) {
            tempOne = tempOne + TwoDCharList[i][j];
        }
        MovieList.push_back(tempOne);
        tempOne.clear();
    } //for size of global vector
} //PopulateMovieList

void AnalyzeStartPositions() {
    string direction;
    //vector <vector<int>> startPositionCords2D;
    vector <int> currentCords;
    string currentMovie;

    for (int i = 0; i < MovieList.size(); i++) {
        showflow("ENTERED FIRST FOR LOOP");

        currentMovie = MovieList[i];
        // sends first character of current movie to be analyzed
        FindCharInMatrix(currentMovie[0], currentMovie);

        showflow(" ONE FULL MOVIE LOOKED AT");
        //cout << endl << endl << endl << endl; // debug
    } //for size of MovieList vector
} //AnalyzeStartPositions

void FindCharInMatrix(char currentChar, string currentMovie) {
    for (int i = 0; i < yMatrix; i++) {
        for (int j = 0; j < xMatrix; j++) {
            if (currentChar == Matrix[i][j]) {
                //cout << "                   FOUND A START POSITION FOR '" << currentChar << "' AT " << j << "/" << i << endl; // debug
                //cout << "                   THE MATRIX CHAR THERE IS " << Matrix[i][j] << endl; // debug
                //cout << "                   CURRENT MOVIE IS " << currentMovie << endl; // debug
                CheckStartPositions(j, i, currentMovie);
            } //if found send to next function
        } //for xMatrix
    } //for yMatrix
} //FindCharInMatrix

void CheckStartPositions(int xInt, int yInt, string currentMovie) {
    showflow("        ARRIVED AT CHECK POSITION");

    int charTicker;
    int i;
    int j;
    char currentChar;
    string currentStr;
    string direction;
    //showflow("        FINISHED DECLARATIONS");

    //checks for words in N/S/E/W/NE/NW/SE/SW directions
    //N
    charTicker = 0;
    currentChar = currentMovie[charTicker];
    currentStr.clear();
    i = yInt;
    for (i; i > 0; i--) {
        if (Matrix[i][xInt] == currentChar) {
            //cout << "               FOUND LETTER: " << Matrix[i][xInt] << " AT NORTH" << endl; // debug
            currentStr = currentStr + Matrix[i][xInt];
            charTicker++;
            currentChar = currentMovie[charTicker];

            if (currentStr == currentMovie) {
                direction = "NORTH";
                //cout << "                       FOUND " << currentMovie << " HEADING " << direction << endl; // debug
                AppendCorrectMovie(xInt, yInt, currentMovie, direction);
                break;
            }
        } else if (Matrix[i][xInt] != currentChar) {
            break;
        }
    }
    //cout << "               6-->FINISHED NORTH" << endl; // debug
    //S
    charTicker = 0;
    currentChar = currentMovie[charTicker];
    currentStr.clear();
    i = yInt;
    for (i; i < yMatrix; i++) {
        if (Matrix[i][xInt] == currentChar) {
            //cout << "\n               FOUND LETTER: " << Matrix[i][xInt] << " AT SOUTH" << endl; // debug
            currentStr = currentStr + Matrix[i][xInt];
            charTicker++;
            currentChar = currentMovie[charTicker];

            if (currentStr == currentMovie) {
                direction = "SOUTH";
                //cout << "                       FOUND " << currentMovie << " HEADING " << direction << endl; // debug
                AppendCorrectMovie(xInt, yInt, currentMovie, direction);
                break;
            }
        } else if (Matrix[i][xInt] != currentChar) {
            break;
        }
    }
    //cout << "               6-->FINISHED SOUTH!!" << endl; // debug
    //E
    charTicker = 0;
    currentChar = currentMovie[charTicker];
    currentStr.clear();
    i = xInt;
    for (i; i < xMatrix; i++) {
        if (Matrix[xInt][i] == currentChar) {
            //cout << "\n               FOUND LETTER: " << Matrix[xInt][i] << " AT EAST" << endl; // debug
            currentStr = currentStr + Matrix[i][xInt];
            charTicker++;
            currentChar = currentMovie[charTicker];

            if (currentStr == currentMovie) {
                direction = "EAST";
                //cout << "                       FOUND " << currentMovie << " HEADING " << direction << endl; // debug
                AppendCorrectMovie(xInt, yInt, currentMovie, direction);
                break;
            }
        } else if (Matrix[i][xInt] != currentChar) {
            break;
        }
    }
    //W
    charTicker = 0;
    currentChar = currentMovie[charTicker];
    currentStr.clear();
    i = xInt;
    for (i; i > 0; i--) {
        if (Matrix[xInt][i] == currentChar) {
            //cout << "\n               FOUND LETTER: " << Matrix[xInt][i] << " AT WEST" << endl; // debug
            currentStr = currentStr + Matrix[i][xInt];
            charTicker++;
            currentChar = currentMovie[charTicker];

            if (currentStr == currentMovie) {
                direction = "WEST";
                //cout << "                       FOUND " << currentMovie << " HEADING " << direction << endl; // debug
                AppendCorrectMovie(xInt, yInt, currentMovie, direction);
                break;
            }
        } else if (Matrix[i][xInt] != currentChar) {
            break;
        }
    }
    //NE
    /* // CODE IS BUGGED //
    charTicker = 0;
    currentChar = currentMovie[charTicker];
    currentStr.clear();
    i = xInt;
    j = yInt;
    for (i; i < x; i++) {
        if (Matrix[j][i] == currentChar) {
            //cout << "               FOUND LETTER: " << Matrix[j][i] << " AT NORTH-EAST" << endl; // debug
            currentStr = currentStr + Matrix[j][i];
            charTicker++;
            currentChar = currentMovie[charTicker];

            if (currentStr == currentMovie) {
                direction = "NORTH-EAST";
                //cout << "                       FOUND " << currentMovie << " HEADING " << direction << endl; // debug
                AppendCorrectMovie(j, yInt, currentMovie, direction);
                break;
            }
        }
        else if (Matrix[j][i] != currentChar) {
            break;
        }

        j--;
        if (j < 0) {
            break;
        }
    }
    //NW
    charTicker = 0;
    currentChar = currentMovie[charTicker];
    currentStr.clear();
    i = xInt;
    j = yInt;
    for (i; i > 0; i--) {
        if (Matrix[j][i] == currentChar) {
            //cout << "               FOUND LETTER: " << Matrix[j][i] << " AT NORTH-WEST" << endl; // debug
            currentStr = currentStr + Matrix[j][i];
            charTicker++;
            currentChar = currentMovie[charTicker];

            if (currentStr == currentMovie) {
                direction = "NORTH-WEST";
                //cout << "                       FOUND " << currentMovie << " HEADING " << direction << endl; // debug
                AppendCorrectMovie(j, yInt, currentMovie, direction);
                break;
            }
        }
        else if (Matrix[j][i] != currentChar) {
            break;
        }

        j--;
        if (j < 0) {
            break;
        }
    }
    //SE
    charTicker = 0;
    currentChar = currentMovie[charTicker];
    currentStr.clear();
    i = xInt;
    j = yInt;
    for (i; i < y; i++) {
        if (Matrix[j][i] == currentChar) {
            //cout << "               FOUND LETTER: " << Matrix[j][i] << " AT SOUTH-EAST" << endl; // debug
            currentStr = currentStr + Matrix[j][i];
            charTicker++;
            currentChar = currentMovie[charTicker];

            if (currentStr == currentMovie) {
                direction = "SOUTH-EAST";
                //cout << "                       FOUND " << currentMovie << " HEADING " << direction << endl; // debug
                AppendCorrectMovie(j, yInt, currentMovie, direction);
                break;
            }
        }
        else if (Matrix[j][i] != currentChar) {
            break;
        }

        j++;
        if (j > y) {
            break;
        }
    }
    //SW
    charTicker = 0;
    currentChar = currentMovie[charTicker];
    currentStr.clear();
    i = xInt;
    j = yInt;
    for (i; i > 0; i--) {
        if (Matrix[j][i] == currentChar) {
            //cout << "               FOUND LETTER: " << Matrix[j][i] << " AT SOUTH-WEST" << endl; // debug
            currentStr = currentStr + Matrix[j][i];
            charTicker++;
            currentChar = currentMovie[charTicker];

            if (currentStr == currentMovie) {
                direction = "SOUTH-WEST";
                //cout << "                       FOUND " << currentMovie << " HEADING " << direction << endl; // debug
                AppendCorrectMovie(j, yInt, currentMovie, direction);
                break;
            }
        }
        else if (Matrix[j][i] != currentChar) {
            break;
        }

        j++;
        if (j > y) {
            break;
        }
    }
    */ // CODE IS BUGGED //

    showflow("        FINISHED CHECK POSITION");
    //cout << endl << endl; // debug
} //CheckStartPosition

void AppendCorrectMovie(int xChar, int yChar, string currentMovie, string direction) {
    //appends correct move along with x/y coordinate and direction to final print vectors
    ChosenDirection.push_back(direction);
    ChosenCords.push_back(xChar);
    ChosenCords.push_back(yChar);
    ChosenList.push_back(currentMovie);
} //AppendCorrectMovie

void GenerateMatrixCords(string currentLine) {
    int i = 0;
    string xCord, yCord;

    while (isdigit(currentLine[i])) {
        xCord = xCord + currentLine[i];
        i++;
    } //while looking at x cord append x string
    i++;
    while (isdigit(currentLine[i])) {
        yCord = yCord + currentLine[i];
        i++;
    } //while looking at y cord append y string

    xMatrix = stoi(xCord);
    yMatrix = stoi(yCord);
} //GenerateMatrixCords

void DisplayResults() {
    cout << "x Rows: " << xMatrix << "; y Cols: " << yMatrix << endl;
    outputfile << "x Rows: " << xMatrix << "; y Cols: " << yMatrix << endl;
    for (int i = 0; i < yMatrix; i++) {
        for (int j = 0; j < xMatrix; j++) {
            cout << Matrix[i][j];
            outputfile << Matrix[i][j];
        } //for xMatrix
        cout << endl;
        outputfile << endl;
    } //for yMatrix
    cout << endl;
    outputfile << endl;

    if (ChosenCords.size() == 0) {
        cout << "No words from the movie list could be matched to the character matrix" << endl;
        outputfile << "No words from the movie list could be matched to the character matrix" << endl;
    } //if chosen vector empty
    else {
        for (int i = 0; i < ChosenList.size(); i++) {
            cout << ChosenList[i] << " found at " << ChosenCords[i] << ", " << ChosenCords[i+1] << ": (direction = " << ChosenDirection[i] << ")" << endl;
            outputfile << ChosenList[i] << " found at " << ChosenCords[i] << ", " << ChosenCords[i+1] << ": (direction = " << ChosenDirection[i] << ")" << endl;
        } //for chosen vector size print 'x'
    }

    outputfile.close();
} //DisplayResults

int main() {
    ReadFile();
    AnalyzeFile();
    PopulateMatrix();
    PopulateMovieList();
    AnalyzeStartPositions();
    DisplayResults();

    showflow("DID NOT CRASH");

    return 0;
} //main
