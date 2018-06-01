#include "KindleBookList.hpp"

#include <map>
#include <fstream>
#include <QDebug>

using std::string;
using std::ifstream;

KindleBookList::KindleBookList(const std::string &clippingsPath) :
                clippingsPath(clippingsPath) {

}

KindleBookList::~KindleBookList() {
    std::map<std::string, KindleBook *>::iterator iter = bookMap.begin();
    for(; iter != bookMap.end(); ++iter) {
        KindleBook *book = iter->second;
        delete book;
    }
}

void KindleBookList::LoadClippings() {
    ifstream clippingsIn(clippingsPath);
    if(!clippingsIn)
        return;

    bool isBookName = true;
    std::string temp;
    KindleBook *book = NULL;
    std::list<std::string> notes;
    std::string bookName;
    QString qstr;
    while(std::getline(clippingsIn, temp)) {
        qstr = QString::fromStdString(temp);
        qstr = qstr.trimmed();
        if(isBookName) {
            isBookName = false;
            bookName = qstr.toStdString();

            std::map<std::string, KindleBook *>::iterator bookIter = bookMap.find(qstr.toStdString());
            if(bookIter != bookMap.end()) {
                book = bookIter->second;
            } else {
                book = new KindleBook(qstr.toStdString());
                bookMap.insert(std::make_pair(qstr.toStdString(), book));
            }
        } else {
            if(qstr.toStdString().size() <= 1)  //Empty line.
                continue;

            if(qstr.toStdString().substr(0, 3) == "===") { //When the line begins with "===", then the next line is the book name.
                isBookName = true;
                book->ParseNotes(notes);
                notes.clear();
            } else {
                notes.push_back(qstr.toStdString());
            }
        }
    }

    clippingsIn.close();
}

void KindleBookList::GetBookNames(std::list<std::string> &bookNames) {
    std::map<std::string, KindleBook *>::iterator iter = bookMap.begin();
    for(; iter != bookMap.end(); ++iter) {
        bookNames.push_back(iter->first);
    }
}

void KindleBookList::GetBookNotes(const std::string &bookName, std::list<std::string> &bookNotes) {
    std::map<std::string, KindleBook *>::iterator bookIter = bookMap.find(bookName);
    if(bookIter != bookMap.end()) {
        KindleBook *book = bookIter->second;
        book->GetBookNotes(bookNotes);
    }
}
