#pragma once
#include <iostream>
#include <vector>
#include "File.h"
#include "PrintFile.h"
#define MAXBYTE 75
#define MAXLINE 20

class TextEditor {
private:
    static TextEditor* instance;
    File* textFile;
    PrintFile* viewFile;

    string getFileName() {
        return this->textFile->getFileName();
    }

    int getCurPageIndex() {
        return this->textFile->getCurPageIndex();
    }

    vector <string>* getMaxLines() {
        return this->textFile->getMaxLines();
    }

    vector <vector<string>>* getTablePage() {
        return this->textFile->getTablePage();
    }

    vector <vector<string>>* getOriginalPage() {
        return this->textFile->getOriginalPage();
    }

    void setCurrentPageIndex(int index) {
        this->textFile->setCurPageIndex(index);
    }

    bool plusPage() {
        return this->textFile->plusPage();
    }

    bool minusPage() {
        return this->textFile->minusPage();
    }

    //pc is pagesContainer and poc is PagesOriginalContent
    string getAllText(vector <vector<string>>* target) { // page정보를 갖고 있는 vector 가 갖고 있는 모든 내용을 string 으로 추출함.
        string allText = "";
        for (int i = 0; i < target->size(); i++) {
            for (int j = 0; j < target->at(i).size(); j++) {
                allText += target->at(i).at(j);
            }
        }

        return allText;
    }

    /*
    만약 텍스트가 수정되는 경우에, 규칙에 맞추어 페이징이 새로 수행되어야 함.
    reMake는 text file 의 allText 를 읽어와 pagesContainer 또는 pagesOriginalContent 를 규칙에 맞추어 새로 페이징 해주는 메소드
    */
    void reMake(string allText,vector <vector<string>>* target) { //pc is pagesContainer and poc is PagesOriginalContent
        getMaxLines()->clear();
        target->clear();

        string temp = "";
        for (int i = 0; i < allText.length(); i++) {
            temp += allText[i];

            if (temp.length() == 75) {
                this->getMaxLines()->push_back(temp);
                if (this->getMaxLines()->size() == MAXLINE) {
                    target->push_back(*this->getMaxLines());
                    this->getMaxLines()->clear();
                }
                temp = "";
            }
        }

        if (temp.length() != 0) {
            this->getMaxLines()->push_back(temp);
            target->push_back(*this->getMaxLines());
            this->getMaxLines()->clear();
        }
    }




public:
    static TextEditor* getInstance(File* textfile, PrintFile* viewfile) {
        if (instance != nullptr) {
            return instance;
        }
        else {
            instance = new TextEditor(textfile, viewfile);
            return instance;
        }
    }

    TextEditor(File* textfile, PrintFile* viewfile) {
        this->textFile = textfile;
        this->viewFile = viewfile;
    }

    std::string NextPage() {
        if (plusPage()) {
            View();
            return "You have moved to the next page.";
        }
        View();
        return "This is the last page.";
    }

    std::string PrevPage() {
        if (minusPage()) {
            View();
            return "This is the previous page.";
        }
        View();
        return "This is the first page!";
    }

    void inserText(int pageline, int index, string stringToInsert) {
        int current_idx = getCurPageIndex();
        std::string text = getTablePage()->at(current_idx).at(pageline);
        getTablePage()->at(current_idx).at(pageline) = text.substr(0, index) + stringToInsert + text.substr(index);

        reMake(getAllText(getTablePage()), getOriginalPage());
        reMake(getAllText(getTablePage()), getTablePage());
    }

    void deleteText(int pageline, int index, int deleteStringLength) {
        int current_idx = getCurPageIndex();
        std::string text = getTablePage()->at(current_idx).at(pageline);
        getTablePage()->at(getCurPageIndex()).at(pageline) =
            text.substr(0, index) + text.substr(index + deleteStringLength);

        reMake(getAllText(getTablePage()), getOriginalPage());
        reMake(getAllText(getTablePage()), getTablePage());
    }

    std::string searchText(std::string searchtarget) {
        string text = getAllText(getTablePage());
        string prevtext;
        string nexttext;

        int targetid = text.find(searchtarget);
        if (targetid != string::npos) {
            if (targetid > 0) {
                prevtext = text.substr(0, targetid - 1);
                nexttext = text.substr(text.find(searchtarget));

                while ((prevtext.length() % 1500) != 0) {
                    prevtext += text[targetid];
                    targetid++;
                }
                text = prevtext + nexttext;
                int keywordIndexZeroInFirstPage = prevtext.length() / 1500;
                reMake(text, getTablePage());
                setCurrentPageIndex(keywordIndexZeroInFirstPage);
                View();
                return searchtarget +" 발견";

            }
            else {
                setCurrentPageIndex(0);
            }
        }
        View();
        return "해당되는 단어가 없습니다.";
    }

    void SaveAndExit() {
        ofstream outfile;
        outfile.open((textFile->getFileName() + ".txt").c_str());
        outfile << getAllText(getOriginalPage());
        outfile.close();
    }

    void chageText(string bword, string aword) {
        string text = getAllText(getTablePage());

        string::size_type position;
        string::size_type offset = 0;
        while ((position = text.find(bword, offset)) != string::npos) {
            text.replace(text.begin() + position, text.begin() + position + bword.size(), aword);
            offset = position + aword.size();
        }

        this->getTablePage()->clear();
        this->getMaxLines()->clear();
        this->reMake(text, getTablePage());


        text = getAllText(getOriginalPage());
        offset = 0;
        while ((position = text.find(bword, offset)) != string::npos) {
            text.replace(text.begin() + position, text.begin() + position + bword.size(), aword);
            offset = position + aword.size();
        }

        this->getOriginalPage()->clear();
        this->getMaxLines()->clear();
        this->reMake(text, getOriginalPage());
    }

    void View() {
        this->viewFile->printContent(this->getTablePage(), this->getCurPageIndex());
    }
};

TextEditor* TextEditor::instance = nullptr;