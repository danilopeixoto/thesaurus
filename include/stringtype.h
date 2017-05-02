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

#ifndef THESAURUS_STRING_H
#define THESAURUS_STRING_H

#include "global.h"
#include <ostream>

THESAURUS_NAMESPACE_BEGIN

class String {
private:
    struct Character;

public:
    class Iterator {
    public:
        Character * pointer;

        Iterator(Character * = THESAURUS_NULL);

        Iterator & operator =(const Iterator &);
        Iterator & operator ++();
        Iterator operator ++(int);
        char & operator *();
        bool operator ==(const Iterator &);
        bool operator !=(const Iterator &);
    };

    class ConstIterator {
    public:
        Character * pointer;

        ConstIterator(Character * = THESAURUS_NULL);

        ConstIterator & operator =(const ConstIterator &);
        ConstIterator & operator ++();
        ConstIterator operator ++(int);
        const char & operator *();
        bool operator ==(const ConstIterator &);
        bool operator !=(const ConstIterator &);
    };
    
    String();
    String(const String &);
    String(const char *);
    ~String();

    String & operator =(const String &);
    String & operator =(const char *);
    bool operator ==(const String &);
    bool operator !=(const String &);
    friend std::ostream & operator <<(std::ostream & lhs, const String & rhs);
    
    String & push(char);
    bool pop();
    String & clear();

    int compare(const String &) const;

    Iterator getBegin();
    Iterator getEnd();
    ConstIterator getBegin() const;
    ConstIterator getEnd() const;

    size_t getSize() const;
    bool isEmpty() const;

private:
    struct Character {
        char data;
        Character * next;
    };

    size_t size;
    Character * begin, * end;
};

THESAURUS_NAMESPACE_END

#endif