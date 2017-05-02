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

#include "dictionary.h"

THESAURUS_NAMESPACE_BEGIN

Word::Word() {}
Word::Word(const String & data, const String & translation)
    : data(data), translation(translation) {}
Word::~Word() {}

Word & Word::operator =(const Word & rhs) {
    data = rhs.data;
    translation = rhs.translation;

    return *this;
}
bool Word::operator ==(const Word & rhs) {
    return data == rhs.data && translation == rhs.translation;
}
bool Word::operator !=(const Word & rhs) {
    return !(*this == rhs);
}
std::ostream & operator <<(std::ostream & lhs, const Word & rhs) {
    return lhs << rhs.data << ": " << rhs.translation;
}

Dictionary::Iterator::Iterator(Word * pointer) : pointer(pointer) {}

Dictionary::Iterator & Dictionary::Iterator::operator =(const Iterator & rhs) {
    pointer = rhs.pointer;

    return *this;
}
Dictionary::Iterator & Dictionary::Iterator::operator ++() {
    pointer = pointer->next;

    return *this;
}
Dictionary::Iterator Dictionary::Iterator::operator ++(int) {
    Iterator it(*this);

    pointer = pointer->next;

    return it;
}
Word & Dictionary::Iterator::operator *() {
    return *pointer;
}
bool Dictionary::Iterator::operator ==(const Iterator & rhs) {
    return pointer == rhs.pointer;
}
bool Dictionary::Iterator::operator !=(const Iterator & rhs) {
    return pointer != rhs.pointer;
}

Dictionary::ConstIterator::ConstIterator(Word * pointer) : pointer(pointer) {}

Dictionary::ConstIterator & Dictionary::ConstIterator::operator =(const ConstIterator & rhs) {
    pointer = rhs.pointer;

    return *this;
}
Dictionary::ConstIterator & Dictionary::ConstIterator::operator ++() {
    pointer = pointer->next;

    return *this;
}
Dictionary::ConstIterator Dictionary::ConstIterator::operator ++(int) {
    ConstIterator it(*this);

    pointer = pointer->next;

    return it;
}
const Word & Dictionary::ConstIterator::operator *() {
    return *pointer;
}
bool Dictionary::ConstIterator::operator ==(const ConstIterator & rhs) {
    return pointer == rhs.pointer;
}
bool Dictionary::ConstIterator::operator !=(const ConstIterator & rhs) {
    return pointer != rhs.pointer;
}

Dictionary::Dictionary() : size(0), begin(THESAURUS_NULL), end(THESAURUS_NULL) {}
Dictionary::Dictionary(const Dictionary & dictionary) {
    size = 0;
    begin = THESAURUS_NULL;
    end = THESAURUS_NULL;

    ConstIterator it = dictionary.getBegin();

    while (it != THESAURUS_NULL)
        push(*it++);
}
Dictionary::~Dictionary() {
    clear();
}

Dictionary & Dictionary::operator =(const Dictionary & rhs) {
    clear();

    ConstIterator it = rhs.getBegin();

    while (it != THESAURUS_NULL)
        push(*it++);

    return *this;
}
bool Dictionary::operator ==(const Dictionary & rhs) {
    if (size != rhs.getSize())
        return false;

    Iterator i = getBegin();
    ConstIterator j = rhs.getBegin();

    while (i != THESAURUS_NULL) {
        if (*i++ != *j++)
            return false;
    }

    return true;
}
bool Dictionary::operator !=(const Dictionary & rhs) {
    return !(*this == rhs);
}

Dictionary::Iterator Dictionary::getBegin() {
    return Iterator(begin);
}
Dictionary::Iterator Dictionary::getEnd() {
    return Iterator(end);
}
Dictionary::ConstIterator Dictionary::getBegin() const {
    return ConstIterator(begin);
}
Dictionary::ConstIterator Dictionary::getEnd() const {
    return ConstIterator(end);
}

Dictionary & Dictionary::push(const Word & word) {
    Word * node = new Word;

    *node = word;
    node->next = THESAURUS_NULL;

    if (end == THESAURUS_NULL)
        begin = node;
    else
        end->next = node;

    end = node;

    size++;

    return *this;
}
Dictionary & Dictionary::insertAscending(const Word & word) {
    if (isEmpty()) {
        push(word);

        return *this;
    }
    
    Word * node, * prevNode;

    node = begin;
    prevNode = THESAURUS_NULL;
    
    while (node != THESAURUS_NULL && word.data.compare(node->data) > 0) {
        prevNode = node;
        node = node->next;
    }
    
    if (prevNode == THESAURUS_NULL)
        insertFirst(word);
    else
        insertAfter(prevNode, word);
    
    return *this;
}
bool Dictionary::pop() {
    if (isEmpty())
        return false;

    Word * node = begin;
    begin = node->next;

    if (begin == THESAURUS_NULL)
        end = THESAURUS_NULL;

    delete node;

    size--;

    return true;
}
Dictionary & Dictionary::removeAfter(Word * node) {
    if (node == THESAURUS_NULL) {
        pop();

        return *this;
    }
    
    Word * nextNode = node->next;
    node->next = nextNode->next;

    if (nextNode == end)
        end = node;
    
    delete nextNode;
    
    size--;
    
    return *this;
}
Dictionary & Dictionary::clear() {
    while (pop());

    return *this;
}

size_t Dictionary::getSize() const {
    return size;
}
bool Dictionary::isEmpty() const {
    return begin == THESAURUS_NULL;
}

Dictionary & Dictionary::insertFirst(const Word & word) {
    Word * node = new Word;

    *node = word;
    node->next = begin;

    begin = node;

    size++;

    return *this;
}
Dictionary & Dictionary::insertAfter(Word * node, const Word & word) {
    Word * newNode = new Word;

    *newNode = word;
    newNode->next = node->next;

    node->next = newNode;

    if (end == node)
        end = newNode;

    size++;
    
    return *this;
}

THESAURUS_NAMESPACE_END