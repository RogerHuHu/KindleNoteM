#include "KindleNote.hpp"
#include <iostream>

using namespace std;

using std::string;

KindleNote::KindleNote(const std::string &str) {
	SetNote(str);
}

void KindleNote::SetNote(const std::string &str) {
	if(str.empty())
		return;
		
	if(str[0] == '-')
		ParseTitle(str);
	else
		content = str;
}

void KindleNote::ParseTitle(const std::string &str) {
	if(str.empty())
		return;
	ParsePageRange(str);
	ParseType(str);
	ParseTime(str);
}

void KindleNote::ParsePageRange(const std::string &str) {
	std::string pageBegin = "您在第 ";
	std::string pageEnd = " 页的";
	size_t pos1 = str.find(pageBegin, 1);
	size_t posPageRangeBegin = pos1 + pageBegin.size();
	size_t pos2 = str.find(pageEnd, posPageRangeBegin);
	pageRange = str.substr(posPageRangeBegin, pos2 - posPageRangeBegin);
}

void KindleNote::ParseType(const std::string &str) {
	std::string typeBegin = "页的";
	size_t pos = str.find(typeBegin, 1);
	size_t posNoteTypeBegin = pos + typeBegin.size();
	type = str.substr(posNoteTypeBegin, 6);
}

void KindleNote::ParseTime(const std::string &str) {
	std::string timeBegin = "添加于 ";
	size_t pos = str.find(timeBegin, 1);
	size_t posNoteTimeBegin = pos + timeBegin.size();
	noteTime = str.substr(posNoteTimeBegin, str.size() - posNoteTimeBegin);
}

