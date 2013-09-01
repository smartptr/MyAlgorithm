#include <iostream>
#include <set>
#include <vector>
#include <iterator>
#include <ostream>
using namespace std;


class CException
{
public:
        CException(const char* str) : m_strErr(str) {}
        string GetErrInfo() { return m_strErr; }
private:
        std::string m_strErr;
};

int myatoi(const char* p)
{
        assert(p);
        int nFlg = 1;
        if ('-' == *p)
                nFlg = -1;
        if ('-' == *p || '+' == *p)
                p++;
        if ('\0' == *p)
                throw CException("Invalid expression");
        int nRet = 0;
        while('\0' != *p)
        {
                if (*p < '0' || *p > '9')
                        throw CException("Invalid character");
                int nVal = *p - '0';
                int nNew = nRet*10 + nFlg * nVal;
                if (nRet != 0 && ((nNew & 0x80000000) != (nRet & 0x80000000)))
                        throw CException("Integer over flow");
                nRet = nNew;
                p++;
        }
        return nRet;
}

int main()
{
    char *a = "-2147483648";
    cout << myatoi(a) << endl;
    return 0;
}
