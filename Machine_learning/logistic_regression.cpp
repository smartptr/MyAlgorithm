/*
 * function : logisitic regression
 * author : John_czg1989
 * time : 2013-07-15
 */

#include <string>
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
using namespace std;

#define NUM_CLASSFICATION 2   //二元分类
#define NUM_INDICATOR_OUTCOMES 2 //结果类别
#define NUM_EPOCHS 100 //迭代次数
#define alpha 0.0001 //步长


//获取每一类数据的类别
int getClass(ifstream& file)
{
	string line;
	getline(file, line);
	return line[line.length()-1]- '0';
}

//读取数据
void readData(vector< vector<int> >& data, vector<int>& classVector, int numVariables, int numRows,ifstream& file)
{
	for (int i = 0; i < numRows; ++i)
	{
		vector<int> vec;
		for (int j = 0; j < numVariables; ++j)
		{
			int v;
			file >> v;
			vec.push_back(v);
		}
		vec.push_back(1);//w=(w1, w2, w3....wn,b), x=(x1, x2, x3...xn,1)
		data.push_back(vec);
		classVector.push_back(getClass(file)); //获取类别
	}
}

//计算两个向量的内积
template <typename T1, typename T2>
double innerCross(const vector<T1>& p, const vector<T2>& q)
{
	double z = 0.f;
	int len = p.size();
	for (int i = 0; i < len ; ++i)
	{
		z += p[i] * q[i];
	}
	return z;
}

// cal 1/(1+exp(-z))
double sigmod(double z)
{
	return 1.0/(1.0+exp(-1.0*z));
}

//训练模型
void trainMode(vector<double>& betaVector, int numVaribles, ifstream& file)
{
	 int numRows;
	 file >> numRows;
	 vector<double> gradiet;  //梯度
	 vector<int> classVector;
	 vector< vector<int> > data;
	 readData(data, classVector, numVaribles, numRows, file);
	 for(int t = 0; t < NUM_EPOCHS;++t)
	 {
		 gradiet.clear();
		 gradiet.assign(numVaribles+1, 0);
		 for(int i = 0; i < numRows; ++i)
		 {
			 double z = innerCross(betaVector, data[i]);
			 double sig = sigmod(z);
			 for (int j = 0; j < numVaribles+1; ++j)
			 {
				 gradiet[j] += (double)data[i][j] * (classVector[i] - sig); // 计算梯度
			 }
		 }
		 for (int i = 0; i < numVaribles+1;++i)
		 {
			 betaVector[i] += alpha * gradiet[i];
		 }
		 //ostream_iterator<double> out_iter(cout, " ");
		 //copy(gradiet.begin(), gradiet.end(), out_iter);
		 //cout << endl;
	 }
}

// test mode
void testMode(ifstream& file, const vector<double>& betaVector, vector<int>& numTestPerClass, vector<int>& numCorrectPerClass)
{
	int numRows;
	int numVaribles;
	file >> numVaribles >> numRows;
	vector<int> curVec;
	numTestPerClass.assign(NUM_CLASSFICATION, 0);
	numCorrectPerClass.assign(NUM_CLASSFICATION,0);
	for (int i = 0; i < numRows; ++i)
	{
		curVec.clear();
		for (int j = 0; j < numVaribles; ++j)
		{
			int v;
			file >> v;
			curVec.push_back(v);
		}
		curVec.push_back(1);
		int realRes = getClass(file);
		numTestPerClass[realRes]++;
		double sum = innerCross(betaVector, curVec);
		double proba = sigmod(sum);
		int myRes = proba > 0.5 ? 1 : 0;
		if (myRes == realRes)
			numCorrectPerClass[myRes]++; 
	}
}

//output
void output(const vector<int>& numTestPerClass, const vector<int>& numCorrectPerClass)
{
	int totalTest = 0;
	int totalCorrect = 0;
	for(int i = 0; i < NUM_CLASSFICATION; ++i)
	{
		cout << "Class " << i << ": tested " << numTestPerClass[i] << ", correctly classified " << numCorrectPerClass[i] << "." << endl;
		totalTest += numTestPerClass[i];
		totalCorrect += numCorrectPerClass[i];
	}
	cout << "Overall: tested " << totalTest << ", correctly classified " << totalCorrect << "." << endl;
	cout << "Accuracy = " << (double)totalCorrect/(double)totalTest << endl;
}

// runtest
void runTest(const string& train, const string& test)
{
	ifstream trainFile(train.c_str());
	ifstream testFile(test.c_str());
	vector<int> numTestPerClass;
	vector<int> numCorrectPerClass;
	int numVaribles;
	trainFile >> numVaribles;
	vector<double> betaVector;
	betaVector.assign(numVaribles+1, 0);
	trainMode(betaVector, numVaribles, trainFile);
	/*ostream_iterator<double> out(cout, " ");
	copy(betaVector.begin(), betaVector.end(), out);
	cout << endl;   */
	testMode(testFile, betaVector, numTestPerClass, numCorrectPerClass);
	cout << "On " << test << ":" << endl;
	output(numTestPerClass, numCorrectPerClass);
}
