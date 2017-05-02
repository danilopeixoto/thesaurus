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

#ifndef THESAURUS_VECTOR_H
#define THESAURUS_VECTOR_H

#include "global.h"

THESAURUS_NAMESPACE_BEGIN

template<typename T>
class Vector {
private:
	struct Node;

public:
	class Iterator {
	public:
		Node * pointer;

		Iterator(Node * pointer = THESAURUS_NULL) : pointer(pointer) {}

		Iterator & operator =(const Iterator & rhs) {
			pointer = rhs.pointer;

			return *this;
		}
		Iterator & operator ++() {
			pointer = pointer->next;

			return *this;
		}
		Iterator operator ++(int) {
			Iterator it(*this);

			pointer = pointer->next;

			return it;
		}
		T & operator *() {
			return pointer->data;
		}
		bool operator ==(const Iterator & rhs) {
			return pointer == rhs.pointer;
		}
		bool operator !=(const Iterator & rhs) {
			return pointer != rhs.pointer;
		}
	};

	class ConstIterator {
	public:
		Node * pointer;

		ConstIterator(Node * pointer = THESAURUS_NULL) : pointer(pointer) {}

		ConstIterator & operator =(const ConstIterator & rhs) {
			pointer = rhs.pointer;

			return *this;
		}
		ConstIterator & operator ++() {
			pointer = pointer->next;

			return *this;
		}
		ConstIterator operator ++(int) {
			ConstIterator it(*this);

			pointer = pointer->next;

			return it;
		}
		const T & operator *() {
			return pointer->data;
		}
		bool operator ==(const ConstIterator & rhs) {
			return pointer == rhs.pointer;
		}
		bool operator !=(const ConstIterator & rhs) {
			return pointer != rhs.pointer;
		}
	};

	Vector() : size(0), begin(THESAURUS_NULL), end(THESAURUS_NULL) {}
	Vector(const Vector & vec) {
		size = 0;
		begin = THESAURUS_NULL;
		end = THESAURUS_NULL;

		ConstIterator it = vec.getBegin();

		while (it != THESAURUS_NULL)
			push(*it++);
	}
	~Vector() {
		clear();
	}

	Vector & operator =(const Vector & rhs) {
		clear();

		ConstIterator it = rhs.getBegin();

		while (it != THESAURUS_NULL)
			push(*it++);

		return *this;
	}
	bool operator ==(const Vector & rhs) {
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
	bool operator !=(const Vector & rhs) {
		return !(*this == rhs);
	}

	Vector & push(const T & element) {
		Node * node = new Node;

		node->data = element;
		node->next = THESAURUS_NULL;

		if (end == THESAURUS_NULL)
			begin = node;
		else
			end->next = node;

		end = node;

		size++;

		return *this;
	}
	bool pop() {
		if (isEmpty())
			return false;

		Node * node = begin;
		begin = node->next;

		if (begin == THESAURUS_NULL)
			end = THESAURUS_NULL;

		delete node;

		size--;

		return true;
	}
	Vector & clear() {
		while (pop());

		return *this;
	}

	Iterator getBegin() {
		return Iterator(begin);
	}
	Iterator getEnd() {
		return Iterator(end);
	}
	ConstIterator getBegin() const {
		return ConstIterator(begin);
	}
	ConstIterator getEnd() const {
		return ConstIterator(end);
	}

	size_t getSize() const {
		return size;
	}
	bool isEmpty() const {
		return begin == THESAURUS_NULL;
	}

private:
	struct Node {
		T data;
		Node * next;
	};

	size_t size;
	Node * begin, * end;
};

THESAURUS_NAMESPACE_END

#endif