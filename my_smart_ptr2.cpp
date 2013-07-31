/*
 * 智能指针实现.cpp
 * author: czg1989
 * time : 2012-7-10
 */

#include <iostream>
using namespace std;

template <class T>
class HasPtr;

template <class T>
class U_Ptr
{
    friend class HasPtr<T>;
    T *ip;
    size_t use;
    U_Ptr(T *p) : ip(p), use(1)
    {
        cout << "U_Ptr constructor called!" <<endl;
    }
    ~U_Ptr()
    {
        delete ip;
        cout << "U_Ptr distructor called!" << endl;
    }
};

template <class T>
class HasPtr
{
public:
    HasPtr(T *p, int v) : ptr(new U_Ptr<T>(p)), val(v)
    {
        cout << "HasPtr constructor called! " << " use = " << ptr->use << endl;
    }
    HasPtr(const HasPtr& orig) : ptr(orig.ptr), val(orig.val)
    {
        ++ptr->use;
        cout << "HasPtr copy constructor called! " << " use = " << ptr->use << endl;
    }
    HasPtr& operator=(const HasPtr&);
    ~HasPtr()
    {
        cout << "HasPtr distructor called ! " << "use = " << ptr->use << endl;
        if(--ptr->use==0)
        {
            delete ptr;
        }
    }
    T *get_ptr() const { return ptr->ip; }
    T get_int() const { return val; }
    void set_ptr(T *p) { ptr->ip = p; }
    void set_int(T v) { val = v; };
    T get_ptr_val() const { return *ptr->ip; }
    void set_ptr_val(T v) { *ptr->ip = v; }
private:
    U_Ptr<T>* ptr;
    T val;
};

template <class T>
HasPtr<T>& HasPtr<T>::operator=(const HasPtr& rhs)
{
    if(this == &rhs)
      return *this;
    ++rhs.ptr->use;
    if(--ptr->use==0)
       delete ptr;
    ptr = rhs.ptr;
    val = rhs.val;
    return *this;
}


int main()
{
    int *p = new int(42);
    //HasPtr a(p,1000);
    HasPtr<int> *hpa = new HasPtr<int>(p, 100);
    HasPtr<int> *hpb = new HasPtr<int>(*hpa);
    HasPtr<int> *hpc = new HasPtr<int>(*hpb);
    //HasPtr *hpb = new HasPtr(a);
    HasPtr<int> hpd = *hpa;
    cout << hpa->get_ptr_val() << " " << hpb->get_ptr_val() << endl;
    hpc->set_ptr_val(10000);
    cout << hpa->get_ptr_val() << " " << hpb->get_ptr_val() << endl;
    hpd.set_ptr_val(10);
    cout << hpa->get_ptr_val() << " " << hpb->get_ptr_val() << endl;
    delete hpa;
    delete hpb;
    delete hpc;
    cout << hpd.get_ptr_val() << endl;
    return 0;
}


