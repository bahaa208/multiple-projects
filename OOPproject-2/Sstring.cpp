#include "Sstring.h"
//
// Created by bhaa on 15/4/2022.
//
Sstring::Sstring (string* s) : p(s), count(new unsigned) {*count = 1;}
 
Sstring& Sstring::operator= (const Sstring& rcp) {
    ++(*(rcp.count));
    --(*count);
    checkIfScavengable();
    p = rcp.p;
    count = rcp.count;
    return *this;
}