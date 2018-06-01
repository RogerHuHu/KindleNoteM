#include "KindleBook.hpp"
#include <fstream>
#include <iostream>

using std::list;
using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;

KindleBook::KindleBook(const std::string &bookName) :
                                   notePath(bookName) {
	//notes = new std::list<KindleNote*>();
}

KindleBook::~KindleBook() {
    std::list<KindleNote *>::iterator iter = kindleNotes.begin();
    for(; iter != kindleNotes.end(); ++iter) {
		KindleNote *note = *iter;
		delete note;
	}
}

bool KindleBook::ParseNotes(const std::list<std::string> &notes) {
    if(notes.empty())
		return false;

    KindleNote *note = new KindleNote();

    std::list<std::string>::const_iterator iter = notes.begin();
    for(; iter != notes.end(); ++iter)
        note->SetNote(*iter);

    kindleNotes.push_back(note);
	
	return true;
}

void KindleBook::GetBookNotes(std::list<std::string> &bookNotes) {
    std::list<KindleNote *>::iterator iter = kindleNotes.begin();
    for(; iter != kindleNotes.end(); ++iter) {
        bookNotes.push_back((*iter)->GetContent());
    }
}

void KindleBook::PrintBook() {
	std::cout << "BookName: " << bookName << std::endl;
    std::cout << "Note Number: " << kindleNotes.size() << std::endl;
    std::list<KindleNote *>::iterator iter = kindleNotes.begin();
    for(; iter != kindleNotes.end(); ++iter) {
		KindleNote *note = *iter;
		std::cout << "PageRange: " << note->GetPageRange() << "|" << std::endl;
		std::cout << "NoteType: " << note->GetNoteType() << "|" << std::endl;
		std::cout << "Time: " << note->GetTime() << "|" << std::endl;
		std::cout << "Content: " << note->GetContent() << std::endl;
	}
}
