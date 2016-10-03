#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <fstream>

using namespace std;

int main(int argc, char *args[]) {
    ifstream testFile("testFile.txt");
    string line;
    while(getline(testFile,line)){
        cout << line << endl;
        system(line.c_str());
    }
    testFile.close();
    
    return 0;
}