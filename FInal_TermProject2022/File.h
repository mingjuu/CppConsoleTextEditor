#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#define MAXBYTE 75
#define MAXLINE 20
using namespace std;

class File {
private:
    int curPageIndex = 0;
    string fileName;

    vector<string>* maxLines = new vector<string>;
    vector<vector<string>>* tablePage = new vector<vector<string>>;
    vector<vector<string>>* originalPage = new vector<vector<string>>;

public:
 
    string getFileName() {
        return fileName;
    }

    int getCurPageIndex() {
        return curPageIndex;
    }

    vector<string>* getMaxLines() {
        return maxLines;
    }

    vector<vector<string>>* getTablePage() {
        return tablePage;
    }

    vector<vector<string>>* getOriginalPage() {
        return originalPage;
    }

    void setCurPageIndex(int index) {
        this->curPageIndex = index;
    }

    bool plusPage() {
        if (curPageIndex >= (tablePage->size() - 2)) {
            *tablePage = *originalPage;
            if (curPageIndex == (tablePage->size() - 1)) { 
                return false;
            }
            curPageIndex++;
            return false;
        }
        curPageIndex++;
        return true;
    }

    bool minusPage() { 
        if (curPageIndex <= 1) {
            *tablePage = *originalPage;
            if (curPageIndex == 0) {
                return false;
            }
            curPageIndex--;
            return false; 
        }

        curPageIndex--;
        return true;
    }

    File(string filename) {  
        fstream f;

        this->fileName = filename;
        f.open((filename + ".txt").c_str());

        string text = "";
        char c;

        while (f.get(c)) {
            text += c;
            if (text.length() == MAXBYTE) {
                maxLines->push_back(text);
                if (maxLines->size() == MAXLINE) {
                    tablePage->push_back(*maxLines);
                    maxLines->clear();
                }
                text = "";
            }
        }

        if (text.length() != 0) {
            maxLines->push_back(text);
            tablePage->push_back(*maxLines);
            maxLines->clear();
        }


        *originalPage = *tablePage;

        f.close();
    }

    ~File() {
        delete maxLines;
        delete tablePage;
        delete originalPage;
    }
};
