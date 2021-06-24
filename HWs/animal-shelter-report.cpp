//  ORIGINAL CODE BY JOSHUA MCDONALD
//
// 4/25/21
//  Setup base of header files for programs to read
//  Created header calls in main program
// 4/25/21
// 4/26/21
//  Setup call for file to read in data from the CSV file
//  Created predecs to look at the data and assign it to values
// 4/26/21
// 4/27/21
//  Setup report outputs for animals/cats/dogs/adoptable
// 4/27/21
// 4/28/21
//  Setup output text file to output interpolated data into txt file
// 4/28/21
// 5/1/21
//  Changed sound output default
// 5/1/21

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
//header files
#include "Animal.h"
#include "Cat.h"
#include "Dog.h"

using namespace std;

//animal header call
Animal::Animal() {
}

string Animal::Speaking() {
    return "Name:" + Name + ", Age:" + Age + ", Weight:" + Weight
           + ", Breed:" + Breed + ", Color:" + Color + ", Health:" + Health
           + ", Sound:" + Sound;
}

//cat header call
Cat::Cat() {
    CatInt = CountedCats;
    CountedCats++;
}

string Cat::Speaking() {
    return "Name:" + Name + ", Age:" + Age + ", Weight:" + Weight
           + ", Breed:" + Breed + ", Color:" + Color + ", Health:" + Health
           + ", Sound:" + Sound;
}

//dog header call
Dog::Dog() {
    DogInt = CountedDogs;
    CountedDogs++;
}
string Dog::Speaking() {
    return "Name:" + Name + ", Age:" + Age + ", Weight:" + Weight
           + ", Breed:" + Breed + ", Color:" + Color + ", Health:" + Health
           + ", Sound:" + Sound;
}

//PROTOTYPES
void showflow();
//PROTOTYPES

//GLOBALS
bool debug = false;
int Dog::CountedDogs = 0;
int Cat::CountedCats = 0;
//GLOBALS

void showflow(string debugMessage) {
    if (debug == true) {
        cout << "-->    " << debug << endl;
    }
} //showflow

int main() {
    //VARIABLE DECLARATIONS
    ifstream file;
    ofstream report;
    string filename;
    string line;
    string temp;
    string name;
    string type;
    string age;
    string weight;
    string color;
    string sound;
    string health;
    string breed;

    vector<Animal*> animals;
    vector<Cat*> cats;
    vector<Dog*> dogs;
    //VARIABLE DECLARATIONS

    //FILE OPEN
    cout << "Enter a CSV file you want looked at: ";
    cin >> filename;
    cout << endl;
    file.open(filename);

    if (!file) {
        cout << "File failed to open, re-enter a valid file name: ";
        cin >> filename;
        cout << endl;
        file.open(filename);
    }
    //FILE OPEN

    getline(file, line);
    getline(file, line);
    while (file) { // Continue if the line was successfully read.
        //LINE READER
        type = line.substr(0, line.find(','));
        line = line.erase(0, line.find(',') + 1);
        name = line.substr(0, line.find(','));
        line = line.erase(0, line.find(',') + 1);
        age = line.substr(0, line.find(','));
        line = line.erase(0, line.find(',') + 1);
        weight = line.substr(0, line.find(','));
        line = line.erase(0, line.find(',') + 1);
        breed = line.substr(0, line.find(','));
        line = line.erase(0, line.find(',') + 1);
        color = line.substr(0, line.find(','));
        line = line.erase(0, line.find(',') + 1);
        health = line.substr(0, line.find(','));
        sound = line.erase(0, line.find(',') + 1);
        //LINE READER

        //checks for different animal types
        Animal * obj;
        if (type == "cat") {
            obj = new Cat();
        } else if (type == "dog") {
            obj = new Dog();
        } else {
            obj = new Animal();
        }

        //assigns variables from pointers from header data
        obj->Age = age;
        obj->Breed = breed;
        obj->Color = color;
        obj->Health = health;
        obj->Name = name;
        obj->Sound = sound;
        obj->Type = type;
        obj->Weight = weight;

        animals.push_back(obj);
        if (type == "cat") {
            cats.push_back((Cat *)obj);
        } else if (type == "dog") {
            dogs.push_back((Dog *)obj);
        }
        getline(file, line);
    }

    report.open("report.txt");
    if (report) {
        //ANIMALS REPORT
        cout << "Total animals created: " << animals.size()<< ", Total cats created: "
             << cats.size() << ", Total dogs created: " << dogs.size() << endl << endl;

        report << "Total animals created: " << animals.size()<< ", Total cats created:"
               << cats.size() << ", Total dogs created:" << dogs.size() << endl << endl;

        cout << "Animals report:" << endl << endl;
        for (int i = 0; i < animals.size(); i++) {
            cout << animals[i]->Speaking() << endl;
            report << animals[i]->Speaking() << endl;
        } //for length of animals vector
        cout << endl << endl;
        //ANIMALS REPORT

        //CATS REPORT
        cout << "Cats report:" << endl << endl;
        for (int i = 0; i < cats.size(); i++) {
            cout << "Name:" + cats[i]->Name + ", Age:" + cats[i]->Age + ", Weight:"
                 + cats[i]->Weight + ", Breed:" + cats[i]->Breed + ", Color:" +
                 cats[i]->Color + ", Health:" + cats[i]->Health + ",Sound:" +
                 cats[i]->Sound << endl;

            report << "Name:" + cats[i]->Name + ", Age:" + cats[i]->Age + ", Weight:"
                   + cats[i]->Weight + ", Breed:" + cats[i]->Breed + ", Color:" +
                   cats[i]->Color + ", Health:" + cats[i]->Health + ", Sound:" +
                   cats[i]->Sound << endl;
        } //for length of cats vector
        cout << endl << endl;
        //CATS REPORT

        //DOGS REPORT
        cout << "Dogs report:" << endl << endl;
        for (int i = 0; i < dogs.size(); i++) {
            cout << "Name:" + dogs[i]->Name + ", Age:" + dogs[i]->Age + ", Weight:"
                 + dogs[i]->Weight + ", Breed:" + dogs[i]->Breed + ", Color:" +
                 dogs[i]->Color + ", Health:" + dogs[i]->Health + ", Sound:" +
                 dogs[i]->Sound << endl;

            report << "Name:" + dogs[i]->Name + ", Age:" + dogs[i]->Age + ", Weight:"
                   + dogs[i]->Weight + ", Breed:" + dogs[i]->Breed + ", Color:" +
                   dogs[i]->Color + ", Health:" + dogs[i]->Health + ", Sound:" +
                   dogs[i]->Sound << endl;
        } //for length of dogs vector
        cout << endl << endl;
        //DOGS REPORT

        //ADOPTABLE REPORT
        report << endl << "Adoptable animals are: " << endl;
        cout << "All adoptable cats are:" << endl << endl;
        for (int i = 0; i < cats.size(); i++) {
            if (cats[i]->Health == "good" || cats[i]->Health == "fair") {
                cout << cats[i]->Name << endl;

                report << cats[i]->Name << endl;
            } //if pointing at healthy cat
        } //for length of cats vector
        cout << endl;
        cout << "All adoptable dogs are:" << endl << endl;
        for (int i = 0; i < dogs.size(); i++) {
            if (dogs[i]->Health == "good" || dogs[i]->Health == "fair") {
                cout << dogs[i]->Name << endl;

                report << dogs[i]->Name << endl;
            } //if pointing at healthy dog
        } //for length of dogs vector
        //ADOPTABLE REPORT

        report.close();
    } else { //errors out if file issue detected
        cout << "There was an issue creating the report" << endl;
    }
    file.close();

    return 0;
} //main
