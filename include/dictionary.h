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

#ifndef THESAURUS_DICTIONARY_H
#define THESAURUS_DICTIONARY_H

#include "global.h"
#include "stringtype.h"
#include <ostream>

THESAURUS_NAMESPACE_BEGIN

struct Word {
    String data, translation;
    Word * next;
    
    Word();
    Word(const String &, const String &);
    ~Word();

    Word & operator =(const Word &);
    bool operator ==(const Word &);
    bool operator !=(const Word &);
    friend std::ostream & operator <<(std::ostream & lhs, const Word & rhs);
};

class Dictionary {
public:
    class Iterator {
    public:
        Word * pointer;

        Iterator(Word * = THESAURUS_NULL);

        Iterator & operator =(const Iterator &);
        Iterator & operator ++();
        Iterator operator ++(int);
        Word & operator *();
        bool operator ==(const Iterator &);
        bool operator !=(const Iterator &);
    };

    class ConstIterator {
    public:
        Word * pointer;

        ConstIterator(Word * = THESAURUS_NULL);

        ConstIterator & operator =(const ConstIterator &);
        ConstIterator & operator ++();
        ConstIterator operator ++(int);
        const Word & operator *();
        bool operator ==(const ConstIterator &);
        bool operator !=(const ConstIterator &);
    };

    Dictionary();
    Dictionary(const Dictionary &);
    ~Dictionary();

    Dictionary & operator =(const Dictionary &);
    bool operator ==(const Dictionary &);
    bool operator !=(const Dictionary &);

    Dictionary & push(const Word &);
    Dictionary & insertAscending(const Word &);
    bool pop();
    Dictionary & removeAfter(Word *);
    Dictionary & clear();
    
    Iterator getBegin();
    Iterator getEnd();
    ConstIterator getBegin() const;
    ConstIterator getEnd() const;

    size_t getSize() const;
    bool isEmpty() const;

private:
    size_t size;
    Word * begin, * end;
    
    Dictionary & insertFirst(const Word &);
    Dictionary & insertAfter(Word *, const Word &);
};

THESAURUS_NAMESPACE_END

#endif