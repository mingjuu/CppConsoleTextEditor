#pragma once

#include <iostream>
#include <string.h>
using namespace std;

class InputView {

public:
    string printMenu(string message) {
        string command;
        cout << "---------------------------------------------------------------------------------" << endl;
        cout << "n: ����������, p: ����������, i: ����, d: ����, c: ����, s: ã��, t: ���� �� ����" << endl;
        cout << "---------------------------------------------------------------------------------" << endl;
        cout << message << endl;
        cout << "---------------------------------------------------------------------------------" << endl;
        cout << "�Է� : ";
        cin >> command;
        cout << "---------------------------------------------------------------------------------" << endl;

        return command;
    }

};

