#include "TextProcess.h"


//分词,基于字符perm
std::vector<std::string> CText::split(const std::string& line, char perm)
{
	std::vector<std::string> words;
	size_t len = line.length();
	size_t index = 0;
	std::string mystr = line;
	while(1)
	{
		if(mystr.length() == 0)
			break;
		index = mystr.find_first_of(perm);
		if(index != std::string::npos)
		{
			words.push_back(mystr.substr(0, index));
			mystr = mystr.substr(index+1);
		}
		else
		{
			words.push_back(mystr);
			break;
		}
	}
	return words;
}

void CText::loadStopWords(const std::string& filename)
{
	stopWords.clear();
	std::ifstream readfile(filename.c_str(),std::ios::in);
	char line[1024]={0};
	assert(readfile);
	int i = 0;
	while(readfile.getline(line, sizeof(line)))
	{
		std::string str(line);
		//std::cout << str << std::endl;
		int len = str.length();
		int beg = 0;
		int end = len-1;
		for(int i = 0; i < len; ++i)
		{
			if(str[i] != ' ')
			{
				beg = i;
				break;;
			}
		}
		for(int j = len - 1; j >= 0; --j)
		{
			if(str[j] != ' ')
			{
				end = j;
				break;
			}
		}
		str = str.substr(beg, end-beg+1);
		if(str != "")
			stopWords.insert(str);
	}
}

std::vector<std::string> CText::extractWordsFromFile(const std::string& filename)
{
	std::vector<std::string> words;
	std::ifstream readfile(filename.c_str(),std::ios::in);
	char line[1024]={0};
	assert(readfile);
	while(readfile.getline(line, sizeof(line)))
	{
		std::string myline = line;
		if(myline.find(':') == std::string::npos)
			countWords(myline, words);
	}
	return words;
}

std::vector<std::string> CText::extractWordsFromLine(const std::string& line)
{
	std::vector<std::string> result;
	result.clear();
	countWords(line, result);
	return result;
}

std::string CText::processWord(const std::string& word)
{
	size_t index = 0;
	while(index < word.length())
	{
		if((word[index] >= '0' && word[index] <= '9') ||
			(word[index] >= 'a' && word[index] <= 'z') ||
			(word[index] >= 'A' && word[index] <= 'Z') ||
			word[index] == '_')
			return word.substr(index);
		else 
			++index;
	}
	return "";
}

void CText::countWords(const std::string& line, std::vector<std::string>& words)
{
	std::vector<std::string> mywords = split(line, ' ');
	for(size_t index = 0; index < mywords.size(); ++index)
	{
		std::string word = processWord(mywords[index]);
		std::cout << word << std::endl;
		if(!needFilter(word))
			words.push_back(word);
	}
}

int CText::getMaxValueIndex(const vector<int>& array)
{
	int maxId = 0;
	int maxvalue = 0;
	vector<int>::const_iterator it = array.begin();
	int index = 0;
	for(; it != array.end(); ++it)
	{
		if((*it) > maxvalue)
		{
			maxvalue = (*it);
			maxId = index;
		}
		++index;
	}
	return maxvalue;
}

bool CText::IsNumber(std::string str)
{
	boost::regex pat("[0-9]+");
	boost::smatch match;
	if(boost::regex_match(str, match, pat))
		return true;
	return false;
}

bool CText::needFilter(std::string str)
{
	if(stopWords.find(str) != stopWords.end())
		return true;
	if(str == "" || IsNumber(str) || str.length() == 1
		|| str.find(',') != std::string::npos ||
		str.find('.') != std::string::npos ||
		str.find('\'') != std::string::npos)
		return true;
	return false;
}
