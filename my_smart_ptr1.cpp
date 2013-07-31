#include <iostream>
#include <stdexcept>
using namespace std;

#ifndef TEST_SMARTPTR
#define TEST_SMARTPTR
#endif

template <class T>
class smart_ptr;

//引用计数
template <class T>
class ref_count
{
    friend class smart_ptr<T>;
    T* ip;
    size_t refCnt;
    ref_count(T* p) : ip(p), refCnt(1) {}
    ~ref_count() { delete ip; }
};

template <class T>
class smart_ptr
{
public:
    explicit smart_ptr(T* p = NULL) : m_ptr(new ref_count<T>(p)) {}

    smart_ptr(const smart_ptr& p) : m_ptr(p.m_ptr)
    {
        ++m_ptr->refCnt;
    }

    smart_ptr& operator=(const smart_ptr& rhs);
    ~smart_ptr()
    {
    #ifdef TEST_SMARTPTR
        cout << "SmartPtr Object Free!" << endl;
    #endif
        if(--m_ptr->refCnt==0)
            delete m_ptr;
    }

    T* operator->() {
        if(m_ptr->ip)
            return m_ptr->ip;
        throw runtime_error("access through NULL pointer");
    }
    T& operator*(){
        if(m_ptr->ip)
            return *m_ptr->ip;
        throw runtime_error("access through NULL pointer");
    }
    const T* operator->() const {
        if(m_ptr->ip)
            return m_ptr->ip;
        throw runtime_error("access through NULL pointer");
    }
    const T& operator*() const {
        if(m_ptr->ip)
            return *m_ptr->ip;
        throw runtime_error("access through NULL pointer");
    }

private:
    ref_count<T>* m_ptr;
};

template <class T>
smart_ptr<T>& smart_ptr<T>::operator=(const smart_ptr& rhs)
{
    if(this == &rhs)
        return *this;
    ++rhs.m_ptr->refCnt;
    if(--m_ptr->refCnt==0)
        delete m_ptr;
    m_ptr = rhs.m_ptr;
    return *this;
}
//test
class CMyTest
{
public:
    CMyTest() { cout << "A CMyTest object was created." << endl; }
    virtual void Print() { cout << "CMyTest Print()" << endl; }
    virtual void Show() { cout << "CMyTest Show()" << endl; }
    ~CMyTest() { cout << "A CMyTest object was destroyed." << endl; }
};

class CMyTestSub : public CMyTest
{
public:
    CMyTestSub() { cout << "A CMyTestSub object was created." << endl; }
    virtual void Print() { cout << "CMyTestSub Print()" << endl; }
    void SubShow() { cout << "CMyTestSub Show()" << endl; }
    ~CMyTestSub() { cout << "A CMyTestSub object was destroyed." << endl; }
};

int main()
{
    try
    {
        smart_ptr<CMyTest> t;
        t->Print();
    }catch(const exception& e)
    {
        cout << e.what() << endl;
    }
    smart_ptr<CMyTest> t1(new CMyTest);
    t1->Print();
    smart_ptr<CMyTest> t2(t1);
    t2->Print();
    smart_ptr<CMyTest> t3(new CMyTest);
    t3 = t2;
    (*t3).Print();

    smart_ptr<CMyTestSub> t4(new CMyTestSub);
    t4->Print();
    t4->SubShow();
    t4->Show();
    smart_ptr<CMyTestSub> t5(t4);
    t5->SubShow();
    smart_ptr<CMyTestSub> t6 = t5;
    t6->Print();
    //smart_ptr<CMyTest> tt(t6);
    //tt->Print();
    //system("pause");
    return 0;
}
