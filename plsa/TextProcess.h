#ifndef _TEXTPROCESS_H_
#define _TEXTPROCESS_H_
#include "util.h"
#include <set>
#include <boost/regex.hpp>
#include <fstream>
using std::set;
using namespace boost;

class CText
{
public:
	CText() {};
	~CText() {};
public:
	void loadStopWords(const std::string& filename);
	int getMaxValueIndex(const vector<int>& array);
	bool IsNumber(std::string str);
	bool needFilter(std::string str);
	set<std::string> getStopWords() { return stopWords;}
	std::vector<std::string> extractWordsFromFile(const std::string& filename);
	std::vector<std::string> extractWordsFromLine(const std::string& line);
private:
	std::string processWord(const std::string& word);
	void countWords(const std::string& line, std::vector<std::string>& words);
	std::vector<std::string> split(const std::string& line, char perm);
	set<std::string> stopWords;
};
#endif
