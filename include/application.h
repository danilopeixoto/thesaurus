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

#ifndef THESAURUS_APPLICATION_H
#define THESAURUS_APPLICATION_H

#include "global.h"
#include "stringtype.h"
#include "vectortype.h"
#include "dictionary.h"
#include "translator.h"
#include <cstdio>

THESAURUS_NAMESPACE_BEGIN

class Application {
public:
    enum Theme {
        Light = 0,
        Dark,
        Default
    };

    struct Preferences {
        Preferences(const Translator::Language & = Translator::Language::Default,
            const Theme & = Theme::Default);
        ~Preferences();

        Translator::Language language;
        Theme theme;
    };

    Application();
    ~Application();

    void execute();

private:
    size_t option;

    Dictionary dictionary;
    Translator translator;
    Preferences preferences;

    FILE * preferenceFile;

    void setTheme(const Theme &);
    void requestText(String &);
    void requestOption();

    void createTitle();
    void createMenu(const Vector<String> &);
    void print(const String &);
    void separator();
    void clear();

    bool isUInt(const String &) const;

    void addAction();
    void removeAction();
    void editAction();
    void searchAction();
    void listAction();
    void exportAction();
    void preferencesAction();
    void aboutAction();
    void exitAction();
};

THESAURUS_NAMESPACE_END

#endif