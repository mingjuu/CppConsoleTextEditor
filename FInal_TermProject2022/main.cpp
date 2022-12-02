#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include "File.h"
#include "PrintFile.h"
#include "TextEditor.h"
#include "InputView.h"
#include "RequestParser.h"

using namespace std;

int main() {
    InputView inputView = InputView();

    string name="test";
   
    try {
        File* targetFile = new File(name); 
        PrintFile* printFile = new PrintFile;
        TextEditor* textEditor = TextEditor::getInstance(targetFile, printFile);


        textEditor->View();

        RequestParser parser = RequestParser();

        string messageToUser = "명령어를 입력하세요";



        while (true) {
            string userWriteMessage = inputView.printMenu(messageToUser);

            Command command = parser.RequestMapping(userWriteMessage);

            if (command == Command::NEXT) {
                messageToUser = textEditor->NextPage();
            }

            if (command == Command::PREVIOUS) {
                messageToUser = textEditor->PrevPage();
            }

            if (command == Command::INSERT) {
                vector<string> insertOrder = parser.ParseInsertOrder(userWriteMessage);
                if (insertOrder.size() < 3) {
                    messageToUser = "올바른 명령어 형식이 아닙니다.";
                    continue;
                }

                int pageLine = stoi(insertOrder[0]) - 1;
                int pageIndex = stoi(insertOrder[1]);
                string insertString = insertOrder[2];

                textEditor->inserText(pageLine, pageIndex, insertString);
                textEditor->View();
                messageToUser = "수정 완료";
            }

            if (command == Command::DDELETE) {
                vector<string> deleteOrder = parser.ParseDeleteOrder(userWriteMessage);
                if (deleteOrder.size() < 3) {
                    messageToUser = "올바른 명령어 형식이 아닙니다.";
                    continue;
                }
                int pageLine = stoi(deleteOrder[0]) - 1;
                int pageIndex = stoi(deleteOrder[1]);
                int deleteStringLength = stoi(deleteOrder[2]);

                textEditor->deleteText(pageLine, pageIndex, deleteStringLength);
                textEditor->View();
                messageToUser = "수정 완료.";
            }

            if (command == Command::CHANGE) {
                vector<string> changeOrder = parser.ParseChangeOrder(userWriteMessage);
                if (changeOrder.size() < 2) {
                    messageToUser = "올바른 명령어 형식이 아닙니다.";
                    continue;
                }
                string changeBefore = changeOrder[0];
                string changeAfter = changeOrder[1];

                textEditor->chageText(changeBefore, changeAfter);
                textEditor->View();
                messageToUser = changeBefore + "를" + changeAfter + "로 수정 완료.";
            }

            if (command == Command::SEARCH) {
                string searchOrder = userWriteMessage.substr(2, userWriteMessage.length() - 3);

                messageToUser = textEditor->searchText(searchOrder);
            }

            if (command == Command::SAVE_AND_EXIT) {
                textEditor->SaveAndExit();
                delete targetFile;
                delete printFile;
                delete textEditor;
                exit(0);
            }

            if (command == Command::NONE) {
                cout << "잘못된 명령어." << endl << endl;
            }
        }
    }
    catch (exception e) {
        cout << "오류입니다. 다시 입력해 주세요" << endl;
        Sleep(5000);
        main();
    }
}