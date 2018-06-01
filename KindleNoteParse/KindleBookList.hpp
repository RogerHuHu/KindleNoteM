#ifndef KINDLEBOOKLIST_HPP
#define KINDLEBOOKLIST_HPP

#include <list>
#include <map>
#include <string>
#include "KindleBook.hpp"

class KindleBookList
{
public:
    KindleBookList(const std::string &clippingsPath);
    ~KindleBookList();
    void LoadClippings();
    void GetBookNames(std::list<std::string> &bookNames);
    void GetBookNotes(const std::string &bookName, std::list<std::string> &bookNotes);

private:
    std::map<std::string, KindleBook *> bookMap;
    std::string clippingsPath;
};

#endif // KINDLEBOOKLIST_HPP
