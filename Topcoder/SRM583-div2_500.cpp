#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

class IDNumberVerification{
public:
  string verify(string id, vector <string> rc);
};

bool isIn(string str, vector<string> rc)
{
    if(find(rc.begin(), rc.end(), str) != rc.end())
    {
        return true;
    }
    return false;
}

bool isLeap(int num)
{
    if((num%4==0&&num%100!=0)||num%400==0)
        return true;
    return false;
}

int flag(int num)
{
    if(num == 1 || num == 3 || num == 5 || num == 7
      || num == 8 || num == 10 || num == 12)
        return 1;
    else if(num == 2)
        return 2;
    else
        return 3;
}

int p[10] = {1, 10,100,1000,10000,100000,1000000,10000000};

int stringtoint(string num)
{
    int s = 0;
    int n = num.length();
    for(int i = 0; i < n; ++i)
        s += (num[i]-'0') * p[n-1-i];
    return s;
}

bool isvalidbirth(string birth)
{
    string year="", month="", day="";
    for(int i = 0; i < 4; ++i)
    {
        year += birth[i];
    }
    for(int i = 4; i < 6; ++i)
    {
        month += birth[i];
    }
    for(int i = 6; i < 8; ++i)
    {
        day += birth[i];
    }
    int yy, mm, dd;
    yy = stringtoint(year);
    mm = stringtoint(month);
    dd = stringtoint(day);
    //cout << yy << " " << mm << " " << dd << endl;
    if(yy < 1900 || yy > 2011)
        return false;
    if(mm<1||mm>12)
        return false;
    if (dd < 1)
        return false;
    //cout << yy << endl;
    int f = flag(mm);
    int t;
    //cout << f << endl;
    if(f == 1)
    {
        if(dd > 31)
            return false;
    }
    else if (f == 2)
    {
        if(isLeap(yy))
        {
            if(dd > 29)
                return false;
        }
        else
            if(dd > 28)
                return false;
    }
    else
    {
        if(dd > 30)
            return false;
    }
    return true;
}

bool ismod(string str, string& xingbie)
{
    int num = 0;
    int x;
    xingbie = "";
    int len = str.length();
    if(str[len-1] == 'X')
        x = 10;
    else
        x = str[len-1] - '0';
    for(int i = 0; i < len-1;++i)
    {
        num += (str[i]-'0')*(1<<(len-1-i));
    }
    num += x;
    string seq = "";
    for(int i = 14; i < len-1; ++i)
        seq += str[i];
    if(seq == "000")
        return false;
    //cout << seq << endl;
    int m = stringtoint(seq);
    if(num%11 == 1)
    {
        if (m%2 == 0)
            xingbie = "Female";
        else
            xingbie = "Male";
            return true;
    }
    return false;
}

string IDNumberVerification::verify(string id, vector <string> rc)
{
    int len = id.length();
    string code = "";
    string birth = "";
    for(int i = 0; i < 6;++i)
        code += id[i];
    for(int i = 6; i < 14; ++i)
        birth += id[i];
    bool ok1 = isIn(code, rc);
    bool ok2 = isvalidbirth(birth);
    string xingbie;
    bool ok3 = ismod(id, xingbie);
    //cout << ok3 << endl;
    if (ok1&&ok2&&ok3)
    {
        return xingbie;
    }
    else
        return "Invalid";
}
