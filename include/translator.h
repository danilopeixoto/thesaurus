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

#ifndef THESAURUS_TRANSLATOR_H
#define THESAURUS_TRANSLATOR_H

#include "global.h"

THESAURUS_NAMESPACE_BEGIN

class Translator {
public:
	enum Language {
		English = 0,
		Portuguese,
		Default
	};

	char * ADD;
	char * REMOVE;
	char * EDIT;
	char * SEARCH;
	char * LIST;
	char * EXPORT;
	char * PREFERENCES;
	char * ABOUT;
	char * EXIT;
	char * YES;
	char * NO;
	char * OK;
	char * CANCEL;
	char * WORD;
	char * TRANSLATION;
	char * WORD_COUNT;
	char * REMOVE_WORD;
	char * EDIT_WORD;
	char * SEARCH_ERROR;
	char * EXPORT_MESSAGE;
	char * EXPORT_ERROR;
	char * DEFAULT_LANGUAGE;
	char * DEFAULT_THEME;
	char * ENGLISH;
	char * PORTUGUESE;
	char * LIGHT;
	char * DARK;
	char * DEFAULT;
	char * SAVE;
	char * ABOUT_THESAURUS;
	char * COPYRIGHT;
	char * LICENSE;
	char * EXIT_MESSAGE;

    Translator();
    ~Translator();

    void setLanguage(const Language &);

private:
    void setEnglishLanguage();
    void setPortugueseLanguage();
};

THESAURUS_NAMESPACE_END

#endif