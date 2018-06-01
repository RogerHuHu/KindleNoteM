#ifndef KINDLENOTE_HPP
#define KINDLENOTE_HPP

#include <string>

enum NoteType {
	LABEL,
	NOTE
};

class KindleNote
{
public:
	KindleNote() {}
	KindleNote(const std::string &str);
	~KindleNote() {}
	void SetNote(const std::string &str);
	std::string GetPageRange() const { return pageRange; }
	std::string GetNoteType() const { return type; }
	std::string GetTime() const { return noteTime; }
	std::string GetContent() const { return content; }

private:
	void ParseTitle(const std::string &str);
	void ParsePageRange(const std::string &str);
	void ParseType(const std::string &str);
	void ParseTime(const std::string &str);
	std::string pageRange;
	std::string type;
	std::string noteTime;
	std::string content;
};

#endif // KINDLENOTE_HPP
