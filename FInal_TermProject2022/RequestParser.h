#include "Command.h"
#include <string>
#include <vector>

using namespace std;

class RequestParser {
 public:
    RequestParser() {}

    Command RequestMapping(string input) {
        if (input == string("n")) {
            return Command::NEXT;
        }

        if (input == string("p")) {
            return Command::PREVIOUS;
        }

        if (input[0] == 'i') {
            return Command::INSERT;
        }

        if (input[0] == 'd') {
            return Command::DDELETE;
        }

        if (input[0] == 's') {
            return Command::SEARCH;
        }

        if (input[0] == 'c') {
            return Command::CHANGE;
        }

        if (input[0] == 't') {
            return Command::SAVE_AND_EXIT;
        }

        return Command::NONE;
    }


    vector<string> ParseInsertOrder(string input) {
        string split = ",";
        int currentLocation = 0;
        int where = 0;
        vector<string> inputInsert;
        string inputTrim = input.substr(2, input.length() - 3);


        while ((where = inputTrim.find(split, currentLocation)) != string::npos) {
            int len = where - currentLocation;
            string result = inputTrim.substr(currentLocation, len);
            inputInsert.push_back(result);
            currentLocation = where + 1;
        }

        string result = inputTrim.substr(currentLocation);
        inputInsert.push_back(result);
        return inputInsert;
    }


    vector<string> ParseDeleteOrder(string input) {
        string split = ",";
        int currentLocation = 0;
        int where = 0;
        vector<string> inputDelete;
        string inputTrim = input.substr(2, input.length() - 3);

        while ((where = inputTrim.find(split, currentLocation)) != std::string::npos) {
            int len = where - currentLocation;
            string result = inputTrim.substr(currentLocation, len);
            inputDelete.push_back(result);
            currentLocation = where + 1;
        }
        string result = inputTrim.substr(currentLocation);
        inputDelete.push_back(result);
        return inputDelete;
    }

    vector<string> ParseChangeOrder(string input) {
        string split = ",";
        int currentLocation = 0;
        int where = 0;
        vector<string> inputChange; 
        string inputTrim = input.substr(2, input.length() - 3);

        while ((where = inputTrim.find(split, currentLocation)) != std::string::npos) {
            int len = where - currentLocation;
            string result = inputTrim.substr(currentLocation, len);
            inputChange.push_back(result);
            currentLocation = where + 1;
        }
        string result = inputTrim.substr(currentLocation);
        inputChange.push_back(result);
        return inputChange;
    }

};