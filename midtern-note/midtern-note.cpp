#include <iostream>
#include <vector>
#include <string>
#include <codecvt>
#include <io.h>
#include <fcntl.h>
#include <windows.h>

using namespace std;

class Note {
public:
	wstring getSolfege() {
		return solfege;
	}
protected:
	wchar_t symbol;
	wstring solfege;
	Note() {
		symbol = L'\0';
		solfege = L'\0';
	}
	wstring to_solfege(const char& pitch) {
		switch (pitch)
		{
		case 'C':
			return L"Do";
		case 'D':
			return L"Re";
		case 'E':
			return L"Mi";
		case 'F':
			return L"Fa";
		case 'G':
			return L"So";
		case 'A':
			return L"La";
		case 'B':
			return L"Si";
		}
		return L"";
	}
	friend const char& operator>>(const char& is, Note& note) {
		note.solfege = note.to_solfege(is);
		return is;
	}
	friend wostream& operator<<(wostream& os, Note& note) {
		os << note.symbol << "  ";
		return os;
	}
};

class Note4 :public Note {
public:
	Note4() {
		symbol = L'♩';
	}
};

class Note8 :public Note {
public:
	Note8() {
		symbol = L'♪';
	}
};
class Subsection {
private:
	static int Beat;
	vector<Note*> notes;
public:
	void setBeat(const int& Beat) {
		this->Beat = Beat;
	}
	~Subsection() {
		const size_t size = notes.size();
		for (int i = 0; i < size; i++) {
			wcout << notes.at(i)->getSolfege() << "  ";
			delete notes.at(i);
		}
		wcout << " ";
		notes.clear();
	}
	friend istream& operator>>(istream& is, Subsection& subsection) {
		float note_value = 0.0;
		float beats_sum = 0.0;
		for (float i = 0; i <= subsection.Beat; i += note_value) {
			char pitch;
			char input_note_value;
			Note* newNote;
			is >> pitch >> input_note_value;
			note_value = float(4.0 / (input_note_value - 48.0));
			if (note_value == 1.0)
				newNote = new Note4();
			else if (note_value == 0.5)
				newNote = new Note8();
			else
				exit(-1);
			beats_sum += note_value;
			pitch >> *newNote;
			subsection.notes.push_back(newNote);
			if (beats_sum == subsection.Beat)
				return is;
			else if (beats_sum > subsection.Beat)
				exit(-1);
		}
		return is;
	}
	friend wostream& operator<<(wostream& os, Subsection& subsection) {
		const size_t size = subsection.notes.size();
		for (int i = 0; i < size; i++)
			os << *subsection.notes.at(i);
		os << "|";
		return os;
	}
};

int Subsection::Beat = 0;

class Score {
private:
	int nSection = 0;
	vector<Subsection*> sections;
	void setSection(int nSection) {
		this->nSection = nSection;
	}
	void add(Subsection*& newSection) {
		sections.push_back(newSection);
	}
public:
	Score() {
		SetConsoleOutputCP(CP_UTF8);
		int error = _setmode(_fileno(stdout), _O_U8TEXT);
		if (error == -1)
			exit(-1);
	}
	~Score() {
		const size_t size = sections.size();
		for (int i = 0; i < size; i++)
			delete sections.at(i);
		sections.clear();
	}
	friend istream& operator>>(istream& is, Score& score) {
		int beat;
		is >> beat >> score.nSection;
		if (beat < 0 || score.nSection < 0)
			exit(-1);
		Subsection* newSection;
		for (int i = 0; i < score.nSection; i++) {
			newSection = new Subsection();
			newSection->setBeat(beat);
			is >> *newSection;
			score.add(newSection);
		}
		return is;
	}
	friend wostream& operator<<(wostream& os, Score& score) {
		for (int i = 0; i < score.nSection; i++)
			os << *score.sections.at(i);
		return os;
	}
};

int main()
{
	Score s;
	cin >> s;
	wcout << s << endl;
}