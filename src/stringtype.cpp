// Copyright (c) 2017, Danilo Peixoto. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// * Neither the name of the copyright holder nor the names of its
//   contributors may be used to endorse or promote products derived from
//   this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "stringtype.h"

THESAURUS_NAMESPACE_BEGIN

String::Iterator::Iterator(Character * pointer) : pointer(pointer) {}

String::Iterator & String::Iterator::operator =(const Iterator & rhs) {
    pointer = rhs.pointer;

    return *this;
}
String::Iterator & String::Iterator::operator ++() {
    pointer = pointer->next;

    return *this;
}
String::Iterator String::Iterator::operator ++(int) {
    Iterator it(*this);

    pointer = pointer->next;
    
    return it;
}
char & String::Iterator::operator *() {
    return pointer->data;
}
bool String::Iterator::operator ==(const Iterator & rhs) {
    return pointer == rhs.pointer;
}
bool String::Iterator::operator !=(const Iterator & rhs) {
    return pointer != rhs.pointer;
}

String::ConstIterator::ConstIterator(Character * pointer) : pointer(pointer) {}

String::ConstIterator & String::ConstIterator::operator =(const ConstIterator & rhs) {
    pointer = rhs.pointer;

    return *this;
}
String::ConstIterator & String::ConstIterator::operator ++() {
    pointer = pointer->next;

    return *this;
}
String::ConstIterator String::ConstIterator::operator ++(int) {
    ConstIterator it(*this);

    pointer = pointer->next;

    return it;
}
const char & String::ConstIterator::operator *() {
    return pointer->data;
}
bool String::ConstIterator::operator ==(const ConstIterator & rhs) {
    return pointer == rhs.pointer;
}
bool String::ConstIterator::operator !=(const ConstIterator & rhs) {
    return pointer != rhs.pointer;
}

String::String() : size(0), begin(THESAURUS_NULL), end(THESAURUS_NULL) {}
String::String(const String & stringtype) {
    size = 0;
    begin = THESAURUS_NULL;
    end = THESAURUS_NULL;
    
    ConstIterator it = stringtype.getBegin();

    while (it != stringtype.getEnd())
        push(*it++);
}
String::String(const char * str) {
    size = 0;
    begin = THESAURUS_NULL;
    end = THESAURUS_NULL;

    char * c = (char *)&str[0];
    
    while (*c)
        push(*c++);
}
String::~String() {
    clear();
}

String & String::operator =(const String & rhs) {
    clear();

    ConstIterator it = rhs.getBegin();

    while (it != rhs.getEnd())
        push(*it++);

    return *this;
}
String & String::operator =(const char * rhs) {
    clear();
    
    char * c = (char *)&rhs[0];
    
    while (*c)
        push(*(c++));
    
    return *this;
}
bool String::operator ==(const String & rhs) {
    if (size != rhs.getSize())
        return false;

    Iterator i = getBegin();
    ConstIterator j = rhs.getBegin();

    while (i != getEnd()) {
        if (*i++ != *j++)
            return false;
    }
    
    return true;
}
bool String::operator !=(const String & rhs) {
    return !(*this == rhs);
}
std::ostream & operator <<(std::ostream & lhs, const String & rhs) {
    char * str = new char[rhs.getSize() + 1];

    rhs.getString(str, rhs.getSize());
    lhs << str;

    delete str;
    
    return lhs;
}

String::Iterator String::getBegin() {
    return Iterator(begin);
}
String::Iterator String::getEnd() {
    return Iterator(THESAURUS_NULL);
}
String::ConstIterator String::getBegin() const {
    return ConstIterator(begin);
}
String::ConstIterator String::getEnd() const {
    return ConstIterator(THESAURUS_NULL);
}

String & String::push(char character) {
    Character * node = new Character;

    node->data = character;
    node->next = THESAURUS_NULL;

    if (end == THESAURUS_NULL)
        begin = node;
    else
        end->next = node;

    end = node;

    size++;

    return *this;
}
bool String::pop() {
    if (isEmpty())
        return false;

    Character * node = begin;
    begin = node->next;
    
    if (begin == THESAURUS_NULL)
        end = THESAURUS_NULL;
    
    delete node;

    size--;

    return true;
}
String & String::clear() {
    while (pop());

    return *this;
}

int String::compare(const String & stringtype) const {
    ConstIterator i = getBegin();
    ConstIterator j = stringtype.getBegin();
    size_t ti, tj;

    while (i != getEnd() && j != stringtype.getEnd()) {
        ti = (size_t)*i++;
        tj = (size_t)*j++;

        if (ti < tj)
            return -1;
        else if (ti > tj)
            return 1;
    }

    ti = getSize();
    tj = stringtype.getSize();
    
    return (ti < tj) ? -1 : (ti > tj);
}

size_t String::getSize() const {
    return size;
}
bool String::isEmpty() const {
    return begin == THESAURUS_NULL;
}
void String::getString(char * str, size_t size) const {
    ConstIterator it = getBegin();
    size_t i = 0;
    
    while (it != getEnd() && i < size)
        str[i++] = *it++;
    
    str[i] = '\0';
}

THESAURUS_NAMESPACE_END