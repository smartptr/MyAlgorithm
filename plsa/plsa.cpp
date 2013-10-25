#include "plsa.h"

void CPlsa::train(std::vector<CDoc>& documents, int maxIters)
{
	 if(documents.size() == 0)
	 {	
		 std::cout << "The documents sets is empty!" << std::endl;
		 return;
	 }
	 wordSets = getAllWords(documents);
	 wordNum = wordSets.size();
	 docNum = documents.size();
	 std::cout << "docnum = " << docNum << "; wordnum = " << wordNum << std::endl;
	 docWordMatrix.clear();
	 docWordMatrix.resize(docNum);
	 for (size_t docid = 0; docid < docNum; ++docid)
	 {
		 docWordMatrix[docid].resize(wordNum, 0);
	 }
	 for (size_t docid = 0; docid < docNum; ++docid)
	 {
		 std::vector<std::string> words = documents[docid].getWords();
		 for(size_t wordid = 0; wordid < words.size(); ++wordid)
		 {
			 std::vector<std::string>::iterator it = std::find(wordSets.begin(), wordSets.end(), words[wordid]);
			 if(it != wordSets.end())
			 {
				 docWordMatrix[docid][it-wordSets.begin()] += 1;
			 }
		 }
		 documents[docid].freeWords();
	 }
	 //test
	 for (size_t docid = 0; docid < docNum; ++docid)
	 {
		 for(size_t wordid = 0; wordid < wordSets.size(); ++wordid)
		 {
			 std::cout << wordSets[wordid] << ": " << docWordMatrix[docid][wordid] << "\t";
		 }
		 std::cout << std::endl;
	 }
	 docTopicProMatrix.resize(docNum);
	 topicWordProMatrix.resize(topicNum);
	 docWordTopicMatrix.resize(docNum);
	 for(size_t docid = 0; docid < docNum; ++docid)
		docWordTopicMatrix[docid].resize(wordNum);
	 for(size_t docid = 0; docid < docNum; ++docid)
		 docTopicProMatrix[docid].resize(topicNum, 0.f);
	 for(size_t topicid = 0; topicid < topicNum; ++topicid)
		 topicWordProMatrix[topicid].resize(wordNum, 0.f);
	 for(size_t docid = 0; docid < docNum; ++docid)
		 for(size_t wordid = 0; wordid < wordNum; ++wordid)
			 docWordTopicMatrix[docid][wordid].resize(topicNum, 0.f);
	 //p(z|d)
	 for(size_t docid = 0; docid < docNum; ++docid)
	 {
		 std::vector<real> pros = CZG::randomPro(topicNum);
		 for(size_t topicid = 0; topicid < topicNum; ++topicid)
			 docTopicProMatrix[docid][topicid] = pros[topicid];
	 }
	 //p(w|z)
	 for(size_t topicid = 0; topicid < topicNum; ++topicid)
	 {
		 std::vector<real> pros = CZG::randomPro(wordNum);
		 for(size_t wordid = 0; wordid < wordNum; ++wordid)
			 topicWordProMatrix[topicid][wordid] = pros[wordid];
	 }
	 std::cout << "em begin: " << std::endl;
	 for(int times = 0; times < maxIters; ++times)
	 {
		 EM();
		 std::cout << "the " << times+1 << " iter";
		 if(times != 0) std::cout << "s" << std::endl;
		 else std::cout << std::endl;
	 }
	 std::cout << "em ends!" << std::endl;
}

void CPlsa::EM()
{	 
	/*E-step*/
	/*cal the p(z|d,w)*/
	for(int docId = 0; docId < docNum; ++docId)
	{
		for(int wordId = 0; wordId < wordNum; ++wordId)
		{
			real total = 0;
			vector<real> perpros(topicNum,0);
			for(int topicId = 0; topicId < topicNum; ++topicId)
			{
				perpros[topicId] = docTopicProMatrix[docId][topicId] * topicWordProMatrix[topicId][wordId];
				total += perpros[topicId];
			}
			if(CZG::isZero(total))	// total is zero
				total = CZG::EPS;
			for(int topicId = 0; topicId < topicNum; ++topicId)
			{
				docWordTopicMatrix[docId][wordId][topicId] = perpros[topicId] / total;
			}
		}
	}
	/*M-step*/
	// update p(z|d),p(w|z) 
	// update p(z|d)
	for(size_t docid = 0; docid < docNum; ++docid)
	{
		double sum = 0.0;
		for(size_t topicid = 0; topicid < topicNum; ++topicid)
		{
			double mysum = 0.0;
			for(size_t wordid = 0; wordid < wordNum; ++wordid)
			{
				mysum += docWordMatrix[docid][wordid] * docWordTopicMatrix[docid][wordid][topicid];
			}
			docTopicProMatrix[docid][topicid] = mysum;
			sum += mysum;
		}
		
		if(CZG::isZero(sum))
			sum = CZG::EPS;
		for (size_t topicid = 0; topicid < topicNum; ++topicid)
		{
			 docTopicProMatrix[docid][topicid] /= sum;
		}
	}

	//update p(w|z)
	for (size_t topicid = 0; topicid < topicNum; ++topicid)
	{
		real sum = 0;
		for(size_t wordid = 0; wordid < wordNum; ++wordid)
		{
			real mysum = 0;
			for(size_t docid = 0; docid < docNum; ++docid)
			{
				mysum += docWordMatrix[docid][wordid] * docWordTopicMatrix[docid][wordid][topicid];
			}
			topicWordProMatrix[topicid][wordid] = mysum;
			sum += mysum;
		}
		if(CZG::isZero(sum))
			sum = CZG::EPS;
		for (size_t wordid = 0; wordid < wordNum; ++wordid)
		{
			topicWordProMatrix[topicid][wordid] /= sum;
		}
	}
}

std::vector<std::string> CPlsa::getAllWords(std::vector<CDoc>& docs)
{
	assert(docs.size() > 0);
	std::set<std::string> uniqwords;
	std::vector<CDoc>::iterator it = docs.begin();
	for(; it != docs.end(); ++it)
	{
		std::vector<std::string> words = it->getWords();
		std::vector<std::string>::iterator it_word = words.begin(); 
		for (; it_word != words.end(); ++it_word)
		{
		   uniqwords.insert(*it_word);
		}
	}
	//std::cout << "total word num: " << uniqwords.size() << std::endl;
	return std::vector<std::string>(uniqwords.begin(), uniqwords.end());
}

std::vector<real> CPlsa::getTopicWordPro(std::string word)
{
	std::vector<real> topicsPro;
	topicsPro.clear();
	int index;
	std::vector<std::string>::iterator it = std::find(wordSets.begin(), wordSets.end(), word);
	if(it == wordSets.end())
		return topicsPro;
	index = it - wordSets.begin();
	topicsPro.resize(topicNum, 0);
	for (size_t topicid = 0; topicid < topicNum; ++topicid)
	{
		topicsPro.push_back(topicWordProMatrix[topicid][index]);
	}
	return topicsPro;
}

