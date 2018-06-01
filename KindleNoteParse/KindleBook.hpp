#ifndef KINDLEBOOK_HPP
#define KINDLEBOOK_HPP

#include <list>
#include "KindleNote.hpp"

class KindleBook
{
public:
    KindleBook(const std::string &bookName);
	~KindleBook();
    bool ParseNotes(const std::list<std::string> &notes);
    void GetBookNotes(std::list<std::string> &bookNotes);
	void PrintBook();
 
private:
	std::string bookName;
	std::string notePath;
    std::list<KindleNote *> kindleNotes;
};

#endif // KINDLEBOOK_HPP
