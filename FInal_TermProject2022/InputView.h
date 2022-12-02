#pragma once

#include <iostream>
#include <string.h>
using namespace std;

class InputView {

public:
    string printMenu(string message) {
        string command;
        cout << "---------------------------------------------------------------------------------" << endl;
        cout << "n: 다음페이지, p: 이전페이지, i: 삽입, d: 삭제, c: 변경, s: 찾기, t: 저장 후 종료" << endl;
        cout << "---------------------------------------------------------------------------------" << endl;
        cout << message << endl;
        cout << "---------------------------------------------------------------------------------" << endl;
        cout << "입력 : ";
        cin >> command;
        cout << "---------------------------------------------------------------------------------" << endl;

        return command;
    }

};

