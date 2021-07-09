/*
    Steven Kha
    CS320 
    Assignment: Classes (C++)
    RedID: 822700600
*/

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <unordered_map>

using namespace std;

class Guitar {
    public:
        Guitar();
        Guitar(const Guitar &copyGuitar);
        bool setFretBoardLength(const unsigned char numFrets);
        unsigned int getFretBoardLength();
        double pitchAt(const unsigned char& stringNumber, const unsigned char& fret);
        void tuneString(unsigned char& string, const double& pitch);
        pair<unsigned char, unsigned char> getStringAndFret(double pitch);
    private:
        unsigned int numberOfFrets;
        unordered_map<unsigned char, double> stringsAndPitch;
};

//constructor sets fret board length to a default of 21 and sets the corresponding strings to their default pitch
Guitar::Guitar() {
    setFretBoardLength(21);
    stringsAndPitch.insert(make_pair('1', 82.41));
    stringsAndPitch.insert(make_pair('2', 110));
    stringsAndPitch.insert(make_pair('3', 146.8));
    stringsAndPitch.insert(make_pair('4', 196));
    stringsAndPitch.insert(make_pair('5', 246.9));
    stringsAndPitch.insert(make_pair('6', 329.6));
}

//copy constructor
Guitar::Guitar(const Guitar &copyGuitar) {
    numberOfFrets = copyGuitar.numberOfFrets;
    for (int i = 1; i < 7; i++) {
        char string = i + '0';
        stringsAndPitch.insert(make_pair(copyGuitar.stringsAndPitch.find(string) -> first, copyGuitar.stringsAndPitch.find(string) -> second));
    }
}

//function sets the length of frets on the guitar
bool Guitar::setFretBoardLength(const unsigned char numFrets) {
    if (numFrets < 1 || numFrets > 24) {
        return false;
    }

    numberOfFrets = numFrets;
    return true;
}

//function returns the number of frets on the guitar
unsigned int Guitar::getFretBoardLength() {
    return numberOfFrets;
}

//function returns a double that is calculated to find the pitch of a combination of a string and a fret
double Guitar::pitchAt(const unsigned char& stringNumber, const unsigned char& fret) {
    double stringPitch = stringsAndPitch.find(stringNumber) -> second;
    unsigned int theFret = fret - '0';       
    return floor(((stringPitch * (pow(2, theFret/12.0)) * 100))) / 100;
}

//function returns a pair that gives the corresponding string and fret that most resembles the given pitch
pair<unsigned char, unsigned char> Guitar::getStringAndFret(double pitch) {
    double thePitch = floor(pitch * 100) / 100;
    pair<unsigned char, unsigned int> thePair;
    int currFret;
    unsigned char stringNum;
    unsigned char fret;
    double calc;
    //loop through every string and fret until pitch can be found
    for (int i = 1; i < stringsAndPitch.size() + 1; i++) {
        stringNum = i + '0';
        for (int j = 0; j < numberOfFrets + 1; j++) {
            fret = j + '0';
            calc = pitchAt(stringNum, fret);
            if (calc > thePitch) {
                currFret = j;
                goto endloop;
            } 
        }
    }

endloop:
    //checks for open string pitch
    int prevFret = currFret - 1;
    if (prevFret < 0) {
        prevFret = 0;
    }

    unsigned char charPrevFret = prevFret + '0';
    double prevPitch = pitchAt(stringNum, charPrevFret);
    if (calc - thePitch > thePitch - prevPitch) {
        thePair = make_pair(stringsAndPitch.find(stringNum) -> first, prevFret);
    } else {
        thePair = make_pair(stringsAndPitch.find(stringNum) -> first, currFret);
    }

    return thePair;
}

//sets the tune of the given string to the given pitch
void Guitar::tuneString(unsigned char& string, const double& pitch) {
    stringsAndPitch.emplace(string, pitch).first -> second = pitch;
}

//function checks if a given fret is within range of the fret board
bool fretChecker(unsigned int fret, Guitar &guitar) {
    if (fret > guitar.getFretBoardLength()) {
        return false;
    }

    return true;
}

/*
    ********************************************************************************************
    |Functions below are test functions for each method and will be called by the main function|
    ********************************************************************************************
*/
void setFretTest(Guitar &guitar) {
    cout << "Testing setFretBoardLength:" << endl;
    cout << "Enter a number between 1 and 24 for the fret length: ";
    int fretLength;
    cin >> fretLength;
    while (!guitar.setFretBoardLength(fretLength)) {
        cout << "Invalid length. Try another number ";
        cin >> fretLength;
        guitar.setFretBoardLength(fretLength);
    }
    
    cout << "The fret board length is: " << guitar.getFretBoardLength() << endl;
}

void pitchAtTest(Guitar &guitar) {
    cout << "Testing pitchAt:" << endl;
    cout << "Enter the string number: ";
    int string;
    cin >> string;
    while (string > 6) {
        cout << "Number too high pick a number between 1-6 ";
        cin >> string;
    }

    unsigned char charString= string + '0';
    cout << "Enter the fret number: ";
    unsigned int fret;
    cin >> fret;
    while (!fretChecker(fret, guitar)) {
        cout << "Entered fret is higher than the set length. Enter a fret within range ";
        cin >> fret;
        fretChecker(fret, guitar);
    }

    unsigned char theFret = fret + '0';
    cout << "The pitch at string " << charString << " and fret " << fret << " is " << guitar.pitchAt(charString, theFret) << endl;
}

void tuningTest(Guitar &guitar) {
    cout << "Testing Tuning:" << endl;
    cout << "Enter the string number: ";
    int string;
    cin >> string;
    while (string > 6) {
        cout << "Number too high pick a lower number ";
        cin >> string;
    }

    unsigned char charString= string + '0';
    cout << "Enter the pitch: ";
    double pitch;
    cin >> pitch;
    cout << "Original pitch of string " << charString << ": " << guitar.pitchAt(charString, '0') << endl;
    guitar.tuneString(charString, pitch);
    cout << "New pitch of string " << charString << ": " << guitar.pitchAt(charString, '0') << endl;
}

void testPair(Guitar &guitar) {
    cout << "Testing pair function:" << endl;
    cout << "Enter a pitch to be found: ";
    double pitch;
    cin >> pitch;
    pair<unsigned char, unsigned int> newPair = guitar.getStringAndFret(pitch);
    while (newPair.second > guitar.getFretBoardLength()) {
        cout << "Entered pitch is on a higher fret length than what is currently set. Please enter another pitch ";
        cin >> pitch;
        newPair = guitar.getStringAndFret(pitch);
    }

    cout << "The string for closest to that pitch is " << newPair.first << " :: The fret closes for that pitch is " << newPair.second << endl;
}

int main() {
    Guitar guitar;
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "+                     Guitar Demonstration                     +" << endl;
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "---------------------------------------------------------------" << endl;
    setFretTest(guitar);
    cout << "---------------------------------------------------------------" << endl;
    pitchAtTest(guitar);
    cout << "---------------------------------------------------------------" << endl;
    testPair(guitar);
    cout << "---------------------------------------------------------------" << endl;
    tuningTest(guitar);
    return 0;
}