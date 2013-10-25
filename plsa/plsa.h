#ifndef _PLSA_H_
#define _PLSA_H_

#include <iterator>
#include <string>
#include <set>
#include "util.h"
#include <boost/regex.hpp>
#include "Document.h"
using std::iterator;
using namespace CZG;

class CPlsa
{
public:
	CPlsa() {}
	CPlsa(int _topicNum):topicNum(_topicNum){
		docNum = 0;
	}
	~CPlsa() {}

public:
	int getDocNum() { return docNum; }
	int getTopicNum() { return topicNum; }
	int getWordNum() { return wordNum; }
	vector<std::string> getWordSets() { return wordSets; }
	vector< vector<real> > getDocTopicPros() { return docTopicProMatrix;}
	vector< vector<real> > getTopicWordPros() {return topicWordProMatrix; }

public:
	void train(std::vector<CDoc>& documents, int maxIters);
	std::vector<real> getTopicWordPro(std::string word);
protected:
	void EM();

private:
	std::vector<std::string> getAllWords(std::vector<CDoc>& docs);
private:
	int topicNum;    // topic num;
	int docNum;	     // document num
	int wordNum;	 // word num
	vector< vector<int> > docWordMatrix;
	vector< vector<real> > docTopicProMatrix;  //p(z|d);
	vector< vector<real> > topicWordProMatrix; //p(w|z);
	vector< vector< vector<real> > > docWordTopicMatrix; //p(z|d,w);
	vector< std::string > wordSets;  
};

#endif
