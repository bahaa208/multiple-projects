#include <iostream>
#include <string>
using namespace std;

/* this class we use like regular string */
/* this class we make referens count to count the pointer in the string */
class Sstring {
    string* p;
    unsigned* count; /* the number of pointer in the same string */
void checkIfScavengable() {
    if (*count == 0) {
        delete count;
        delete p;
    }
}
public:
    Sstring (string* s);
    Sstring (const Sstring& rcp) :
    p(rcp.p), count(rcp.count)
    { ++(*count); }
    int getCountOfREf()const{return *count;}
    ~Sstring() { --(*count); checkIfScavengable(); }
    

    string& operator*() const {return *p;}
    string* operator->() const {return p;}

    Sstring& operator= (const Sstring& rcp);
    bool operator== (const Sstring& ptr) const
    {   return ptr.p == p;}
    bool operator!= (const Sstring& ptr) const
    {   return ptr.p != p;}

};
