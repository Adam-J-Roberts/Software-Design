#include <fstream>
#include <string>
#include <iostream>
#include <sstream> 
#include <algorithm>

using namespace std; 

int main(int argc, char* argv[])
{ 
    string temp;
    string text;
    int letterCount[45] = {0};

    //verify command line arguements
    if (argc < 2) {
        cout << "No file name entered. Exiting...";
        return -1; 
    }
    else if(argc > 2) {
        cout << "Too many files loaded Exiting...";
        return -1; 
    }
    //load file
    ifstream myfile(argv[1]); //open the file;
    //verify file opened
    if (myfile.is_open()) { 
        cout << "File is now open!\n";    
    } 
    else {
        cout << "Failed to open file..";
        return -1; 
    }
    //read file into string
    while(!myfile.eof())
    {
        getline(myfile, temp);
        text.append(temp); // Added this line
    }
    //close the file
    myfile.close();
    //create istringstream with string
    istringstream iss(text);
    //check each words letter count 
    while(!iss.eof()) {
        string word;
        iss >> word;
        //increase array count if is actual word
        if (isalpha(word[1])){
            letterCount[word.length()]++;
        }

    }
    //print out final count
    for(int i=0; i<45;i++){
        if(letterCount[i]>0){
            cout << letterCount[i] << " word(s) with "  << i << " letter(s)." << endl;
        }
    }

    return 0;
}
