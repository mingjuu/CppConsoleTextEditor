#pragma once
#include <iostream>
#include <vector>
#define MAXBYTE 75
#define MAXLINE 20
using namespace std;

class PrintFile { 
public:
    void printContent(vector<vector<string>>* content, int curPage) {
        system("cls");
        if (curPage > 0) {
            int index = content->at(curPage).size();
            if (index < MAXLINE) {
                for (int i = index; i < MAXLINE; i++) {
                    cout << i - (index)+1 << " | " << content->at(curPage - 1).at(i) << endl;
                }

                for (int i = 0; i < index; i++) {
                    cout << 21 - (index)+i << " | " << content->at(curPage).at(i) << endl;
                }
            }
            else {
                for (int i = 0; i < content->at(curPage).size(); i++) {
                    cout << i + 1 << " | " << content->at(curPage).at(i) << endl;
                }
            }
        }
        else {
            for (int i = 0; i < content->at(curPage).size(); i++) {
                cout << i + 1 << " | " << content->at(curPage).at(i) << endl;
            }
        }
    }
};