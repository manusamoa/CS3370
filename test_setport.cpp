#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <fstream>

using namespace std;

//add parameter(any parameter) to program call to test languages.
int main(int argc, char *args[]) {
    ifstream testFile("testFile.txt");
    string line;

    while(getline(testFile,line)){
        cout << line << endl;
        system(line.c_str());
    }
    testFile.close();
    
    ifstream langTestFile("langTestFile.txt");
    
    while(getline(langTestFile,line)){
        cout << line << endl;
        system(line.c_str());
    }
    langTestFile.close();
    
    return 0;
}