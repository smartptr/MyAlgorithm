#ifndef _DOCUMENT_H_
#define _DOCUMENT_H_

#include <vector>
#include <string>
using std::vector;


class CDoc
{
public:
	CDoc() {}
	CDoc(std::string _docname, vector<std::string>& _words)
		:  docName(_docname), words(_words) {}
	~CDoc(){}

public:
	std::string getDocName() { return docName; }
	vector<std::string> getWords() {return words; }
	void setDocName(std::string _docname) { docName = _docname; }
	void setWords(vector<std::string>& _words){
		words = _words;
	}
	void freeWords() { words.clear();}
private:
	vector<std::string> words;
	std::string docName;
};
#endif
