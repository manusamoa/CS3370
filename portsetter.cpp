#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <fstream>
#include <regex>

using namespace std;

vector<string> _port = {"-p", "--port"};
vector<string> _help = {"-h", "--help", "-?"};
vector<string> _about = {"-!", "--about"};
vector<string> _version = {"-v", "--version"};
string _language = "en";

enum {
    ERROR,
    TOO_MANY_PARAMETERS,
    INVALID_FLAG,
    NO_PORT,
    INVALID_PORT,
    LISTENING_PORT
};

vector<string> enResponse = {
        "Error. ",
        "Too many parameters.\n",
        "Invalid flag used.\n",
        "No port number given.\n",
        "Invalid port.\n",
        "Listening on port "
};

vector<string> esResponse = {
    "Error. ",
    "Demasiados parámetros.\n",
    "Bandera no válido utilizado.\n",
    "No se da el número de puerto.\n",
    "Puerto no válido.\n",
    "Escucha en el puerto "
};

vector<string> _outputText = enResponse;


bool isFlagValid(string);
bool isFlagHelp(string);
bool isFlagPort(string);
bool isFlagAbout(string);
bool isFlagVersion(string);
bool isPortValid(string);
bool argumentErrorCatch(int, char**);
string getEnvLanguage();
bool nullLanguage(char*);
void setLanguage(string);
void printUsageRules();
void printAboutMe();
void printVersion();
void printPortsetter(string);

int main(int argc, char *args[]) {

    setLanguage(getEnvLanguage());
    if(!argumentErrorCatch(argc, args)) {
        string flag = args[1];

        if(isFlagPort(flag)) {
            string eFlag = args[2];
            if(eFlag.compare("-e") == 0) {
                if(argc != 4) printPortsetter(getenv("PORT"));
                else printPortsetter(getenv(args[3]));
            }
            else printPortsetter(args[2]);
        }
        if(isFlagHelp(flag)) printUsageRules();
        if(isFlagAbout(flag)) printAboutMe();
        if(isFlagVersion(flag)) printVersion();
        
        return 0;
    }
    else return 4;
}

bool isFlagValid(string flag) {
    if(isFlagHelp(flag)) return true;
    if(isFlagPort(flag)) return true;
    if(isFlagAbout(flag)) return true;
    if(isFlagVersion(flag)) return true;
    return false;
}
bool isFlagHelp(string flag) {

    for(int i = 0; i < _help.size(); ++i) {
        if(flag.compare(_help[i]) == 0) return true;
    }
    
    return false;
}

bool isFlagPort(string flag) {

    for(int i = 0; i < _port.size(); ++i) {
        if(flag.compare(_port[i]) == 0) return true;
    }
    
    return false;
}

bool isFlagAbout(string flag) {
    for(int i = 0; i < _about.size(); ++i) {
        if(flag.compare(_about[i]) == 0) return true;
    }
    
    return false;
}

bool isFlagVersion(string flag) {
    for(int i = 0; i < _version.size(); ++i) {
        if(flag.compare(_version[i]) == 0) return true;
    }
    
    return false;
}

bool isPortValid(string port) {
    
    int portNum;
    try {
        size_t index;
        portNum = stoi(port, &index);
        if(index != port.length() || portNum < 1 || portNum >= 65000) 
            throw invalid_argument("Invalid port: addition characters found.");
    }
    catch (const invalid_argument& ia) {
        return false;
    }

    return true;
}

bool argumentErrorCatch(int argc, char* args[]) {
    
    if(argc <= 1) {
        printUsageRules();
        return true;
    }
    
    string flag = args[1];

    try {
        if(argc >= 5) throw 1;
        if(!isFlagValid(flag)) throw 2;
        if((isFlagHelp(flag) || isFlagAbout(flag) || isFlagVersion(flag)) && argc > 2) throw 1;
        if(isFlagPort(flag) && argc <= 2) throw 3;
        if(isFlagPort(flag) && !isPortValid(args[2])) {
            string eFlag = args[2];
            if(eFlag.compare("-e") != 0) throw 4;
        }
    }
    catch(int e) {
        //printOutError(e);
        cout << _outputText[ERROR];
        if(e == 1) cout << _outputText[TOO_MANY_PARAMETERS] << endl;
        if(e == 2) cout << _outputText[INVALID_FLAG] << endl;
        if(e == 3) cout << _outputText[NO_PORT] << endl;
        if(e == 4) cout << _outputText[INVALID_PORT] << endl;
        
        printUsageRules();
        return true;
    }
    
    return false;
}

string getEnvLanguage() {
    
    if(!nullLanguage(getenv("LANGUAGE"))) return getenv("LANGUAGE");
    if(!nullLanguage(getenv("LC_ALL"))) return getenv("LC_ALL");
    if(!nullLanguage(getenv("LC_MESSAGES"))) return getenv("LC_MESSAGES");
    if(!nullLanguage(getenv("LANG"))) return getenv("LANG");
    
    return _language;
}

bool nullLanguage(char* env) {
    if (env == NULL) return true;
    string envValue(env);
    if(envValue.empty()) return true;
    if(envValue.compare("C.UTF-8") == 0) return true;
    if(envValue.compare("C") == 0) return true;
    return false;
}

void setLanguage(string language) {
    
    if(language != _language) {
        regex reg("([a-z][a-z])(_[A-Z][A-Z](.UTF-8)?)?");
        bool isMatch = regex_match(language,reg);
        if(isMatch) {
            if(language.substr(0,2).compare("es") == 0) {
                _outputText = esResponse;
                _language = "es";
                return;
            }
            else cout << "Missing pl translation files. Using English." << endl;
        }
        else cout << "Bad Language specified. Using English." << endl;
    }
    
    _language = language;
}

void printUsageRules() {
    ifstream usageFile("portsetter.usage_" + _language + ".txt");
    string line;
    while(getline(usageFile,line)){
        cout << line << endl;
    }
    usageFile.close();
}

void printAboutMe() {
    ifstream aboutFile("portsetter.about_" + _language + ".txt");
    string line;
    while(getline(aboutFile,line)){
        cout << line << endl;
    }
    aboutFile.close();
}

void printVersion() {
    cout << "v1.3.0.0.1" << endl;
}

void printPortsetter(string port) {
    cout << _outputText[LISTENING_PORT] << port << "." << endl;
}