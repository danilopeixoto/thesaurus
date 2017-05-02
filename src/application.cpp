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

#include "application.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <fstream>

THESAURUS_NAMESPACE_BEGIN

Application::Preferences::Preferences(const Translator::Language & language,
	const Theme & theme) : language(language), theme(theme) {}
Application::Preferences::~Preferences() {}

Application::Application() {
	preferenceFile = fopen("preferences", "rb+");

	if (preferenceFile != THESAURUS_NULL) {
		fread(&preferences, sizeof(Preferences), 1, preferenceFile);
	}
	else {
		preferenceFile = fopen("preferences", "wb+");

		if (preferenceFile != THESAURUS_NULL)
			fwrite(&preferences, sizeof(Preferences), 1, preferenceFile);
	}

	fclose(preferenceFile);

	translator.setLanguage(preferences.language);
	setTheme(preferences.theme);

	clear();
}
Application::~Application() {
	if (preferenceFile != THESAURUS_NULL)
		fclose(preferenceFile);
}

void Application::execute() {
	clear();

	createTitle();
	separator();

	Vector<String> menu;
	menu.push(translator.ADD);
	menu.push(translator.REMOVE);
	menu.push(translator.EDIT);
	menu.push(translator.SEARCH);
	menu.push(translator.LIST);
	menu.push(translator.EXPORT);
	menu.push(translator.PREFERENCES);
	menu.push(translator.ABOUT);
	menu.push(translator.EXIT);

	createMenu(menu);
	separator();

	requestOption();

	switch (option) {
	case 1:
		addAction();
		break;
	case 2:
		removeAction();
		break;
	case 3:
		editAction();
		break;
	case 4:
		searchAction();
		break;
	case 5:
		listAction();
		break;
	case 6:
		exportAction();
		break;
	case 7:
		preferencesAction();
		break;
	case 8:
		aboutAction();
		break;
	case 9:
		exitAction();
		break;
	default:
		execute();
	}
}

void Application::setTheme(const Theme & theme) {
	switch (theme) {
	case Theme::Dark:
		system("color 0F");
		break;
	default:
		system("color F0");
	}
}
void Application::requestText(String & str) {
	char c = (char)std::getchar();
	
	while (c != '\n') {
		str.push(c);
		c = (char)std::getchar();
	}
}
void Application::requestOption() {
	String optionString;

	requestText(optionString);
	
	size_t count = 0;

	while (optionString.getSize() > THESAURUS_MAX_OPTION_LENGTH) {
		if (count < THESAURUS_MAX_OPTION_LENGTH) {
			optionString.push(*optionString.getBegin());
			
			count++;
		}
		
		optionString.pop();
	}

	option = 0;
	
	if (!isUInt(optionString))
		return;
	
	String::Iterator it = optionString.getBegin();
	count = optionString.getSize();

	while (count != 0) {
		option += (size_t)std::pow(10, count - 1) * ((size_t)(*it++) - 48);
		count--;
	}
}

void Application::createTitle() {
	print("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *");
	print("*                                  THESAURUS                                  *");
	print("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *");
}
void Application::createMenu(const Vector<String> & menu) {
	Vector<String>::ConstIterator it = menu.getBegin();

	for (size_t i = 0; i < menu.getSize(); i++)
		std::cout << i + 1 << ". " << *it++ << std::endl;
}
void Application::print(const String & str) {
	std::cout << str << std::endl;
}
void Application::separator() {
	std::cout << std::endl;
}
void Application::clear() {
	system("cls");
}

bool Application::isUInt(const String & str) const {
	String::ConstIterator it = str.getBegin();
	size_t c;

	while (it != THESAURUS_NULL) {
		c = (size_t)*it++;

		if (c < 48 || c > 57)
			return false;
	}
	
	return !str.isEmpty();
}

void Application::addAction() {
	clear();

	createTitle();
	separator();

	print(translator.ADD);
	separator();

	Word word;

	print(translator.WORD);
	
	requestText(word.data);
	separator();

	print(translator.TRANSLATION);

	requestText(word.translation);
	separator();

	Vector<String> menu;
	menu.push(translator.ADD);
	menu.push(translator.CANCEL);
	menu.push(translator.EXIT);

	createMenu(menu);
	separator();

	requestOption();
	separator();

	switch (option) {
	case 1:
		dictionary.insertAscending(word);
		execute();

		break;
	case 2:
		execute();
		break;
	case 3:
		exitAction();
		break;
	default:
		addAction();
	}
}
void Application::removeAction() {
	clear();

	createTitle();
	separator();

	print(translator.REMOVE);
	separator();

	String str;

	print(translator.WORD);

	requestText(str);
	separator();

	Vector<Dictionary::Iterator> temp;

	Dictionary::Iterator it = dictionary.getBegin();
	Dictionary::Iterator prevIt;

	size_t i = 1;

	while (it != THESAURUS_NULL) {
		if ((*it).data == str) {
			std::cout << i++ << ". " << *it << std::endl;
			temp.push(prevIt);
		}

		prevIt = it;
		it++;
	}

	Vector<String> menu;

	if (temp.isEmpty()) {
		print(translator.SEARCH_ERROR);
		separator();

		menu.push(translator.OK);
		menu.push(translator.REMOVE);
		menu.push(translator.EXIT);

		createMenu(menu);
		separator();

		requestOption();
		separator();

		switch (option) {
		case 1:
			execute();
			break;
		case 2:
			removeAction();
			break;
		case 3:
			exitAction();
			break;
		default:
			removeAction();
		}
	}
	else {
		separator();

		size_t wordOption;

		do {
			print(translator.REMOVE_WORD);

			requestOption();
			separator();

			wordOption = option;
		} while (wordOption < 1 || wordOption > temp.getSize());

		menu.push(translator.REMOVE);
		menu.push(translator.CANCEL);
		menu.push(translator.EXIT);

		createMenu(menu);
		separator();

		requestOption();
		separator();

		Vector<Dictionary::Iterator>::Iterator tempIt;

		switch (option) {
		case 1:
			tempIt = temp.getBegin();
			i = 1;

			while (i < wordOption) {
				tempIt++;
				i++;
			}

			dictionary.removeAfter((*tempIt).pointer);
			
			execute();

			break;
		case 2:
			execute();
			break;
		case 3:
			exitAction();
			break;
		default:
			removeAction();
		}
	}
}
void Application::editAction() {
	clear();

	createTitle();
	separator();

	print(translator.EDIT);
	separator();

	String str;

	print(translator.WORD);

	requestText(str);
	separator();

	Vector<Dictionary::Iterator> temp;

	Dictionary::Iterator it = dictionary.getBegin();
	Dictionary::Iterator prevIt;

	size_t i = 1;

	while (it != THESAURUS_NULL) {
		if ((*it).data == str) {
			std::cout << i++ << ". " << *it << std::endl;
			temp.push(prevIt);
		}

		prevIt = it;
		it++;
	}

	Vector<String> menu;

	if (temp.isEmpty()) {
		print(translator.SEARCH_ERROR);
		separator();

		menu.push(translator.OK);
		menu.push(translator.EDIT);
		menu.push(translator.EXIT);

		createMenu(menu);
		separator();

		requestOption();
		separator();

		switch (option) {
		case 1:
			execute();
			break;
		case 2:
			editAction();
			break;
		case 3:
			exitAction();
			break;
		default:
			editAction();
		}
	}
	else {
		separator();

		size_t wordOption;

		do {
			print(translator.EDIT_WORD);

			requestOption();
			separator();

			wordOption = option;
		}
		while (wordOption < 1 || wordOption > temp.getSize());
		
		Word word;

		print(translator.WORD);
		
		requestText(word.data);
		separator();

		print(translator.TRANSLATION);

		requestText(word.translation);
		separator();

		menu.push(translator.EDIT);
		menu.push(translator.CANCEL);
		menu.push(translator.EXIT);

		createMenu(menu);
		separator();

		requestOption();
		separator();

		Vector<Dictionary::Iterator>::Iterator tempIt;

		switch (option) {
		case 1:
			tempIt = temp.getBegin();
			i = 1;

			while (i < wordOption) {
				tempIt++;
				i++;
			}

			dictionary.removeAfter((*tempIt).pointer);
			dictionary.insertAscending(word);

			execute();

			break;
		case 2:
			execute();
			break;
		case 3:
			exitAction();
			break;
		default:
			editAction();
		}
	}
}
void Application::searchAction() {
	clear();

	createTitle();
	separator();

	print(translator.SEARCH);
	separator();

	String word;

	print(translator.WORD);

	requestText(word);
	separator();

	Dictionary::Iterator it = dictionary.getBegin();
	size_t i = 1;

	while (it != THESAURUS_NULL) {
		if ((*it).data == word)
			std::cout << i++ << ". " << *it << std::endl;

		it++;
	}

	if (i == 1)
		print(translator.SEARCH_ERROR);

	separator();

	Vector<String> menu;
	menu.push(translator.OK);
	menu.push(translator.SEARCH);
	menu.push(translator.EXIT);

	createMenu(menu);
	separator();

	requestOption();
	separator();

	switch (option) {
	case 1:
		execute();
		break;
	case 2:
		searchAction();
		break;
	case 3:
		exitAction();
		break;
	default:
		searchAction();
	}
}
void Application::listAction() {
	clear();

	createTitle();
	separator();

	print(translator.LIST);
	separator();

	std::cout << translator.WORD_COUNT << " " << dictionary.getSize() << std::endl;
	separator();

	Dictionary::Iterator it = dictionary.getBegin();

	for (size_t i = 1; i < dictionary.getSize() + 1; i++)
		std::cout << i << ". " << *it++ << std::endl;

	if (!dictionary.isEmpty())
		separator();
	
	Vector<String> menu;
	menu.push(translator.OK);
	menu.push(translator.EXIT);

	createMenu(menu);
	separator();

	requestOption();
	separator();

	switch (option) {
	case 1:
		execute();
		break;
	case 2:
		exitAction();
		break;
	default:
		listAction();
	}
}
void Application::exportAction() {
	clear();

	createTitle();
	separator();

	print(translator.EXPORT);
	separator();

	print(translator.EXPORT_MESSAGE);

	String filename;
	std::fstream file;

	requestText(filename);
	separator();

	String::Iterator it = filename.getBegin();
	size_t count = 0;

	Vector<String> menu;
	menu.push(translator.EXPORT);
	menu.push(translator.CANCEL);
	menu.push(translator.EXIT);

	createMenu(menu);
	separator();

	requestOption();
	separator();

	switch (option) {
	case 1:
		char temp[THESAURUS_MAX_PATH_LENGTH + 1];

		while (it != THESAURUS_NULL && count != THESAURUS_MAX_PATH_LENGTH)
			temp[count++] = *it++;

		temp[count] = '\0';

		file.open(temp, std::fstream::out);

		if (file.is_open()) {
			Dictionary::Iterator itd = dictionary.getBegin();

			while (itd != THESAURUS_NULL)
				file << *itd++ << std::endl;

			file.close();

			execute();
		}
		else
			exportAction();
		
		break;
	case 2:
		execute();
		break;
	case 3:
		exitAction();
		break;
	default:
		exportAction();
	}
}
void Application::preferencesAction() {
	clear();

	createTitle();
	separator();

	print(translator.PREFERENCES);
	separator();

	print(translator.DEFAULT_LANGUAGE);
	separator();

	Vector<String> menu;
	menu.push(translator.ENGLISH);
	menu.push(translator.PORTUGUESE);
	menu.push(translator.DEFAULT);

	createMenu(menu);
	separator();

	requestOption();
	separator();

	if (option < 1 || option > menu.getSize())
		preferencesAction();

	preferences.language = (Translator::Language)(option - 1);

	print(translator.DEFAULT_THEME);
	separator();

	menu.clear();
	menu.push(translator.LIGHT);
	menu.push(translator.DARK);
	menu.push(translator.DEFAULT);

	createMenu(menu);
	separator();

	requestOption();
	separator();

	if (option < 1 || option > menu.getSize())
		preferencesAction();

	preferences.theme = (Theme)(option - 1);

	menu.clear();
	menu.push(translator.SAVE);
	menu.push(translator.CANCEL);
	menu.push(translator.EXIT);

	createMenu(menu);
	separator();

	requestOption();

	switch (option) {
	case 1:
		preferenceFile = fopen("preferences", "wb+");

		if (preferenceFile != THESAURUS_NULL)
			fwrite(&preferences, sizeof(Preferences), 1, preferenceFile);

		fclose(preferenceFile);

		translator.setLanguage(preferences.language);
		setTheme(preferences.theme);

		execute();

		break;
	case 2:
		execute();
		break;
	case 3:
		exitAction();
		break;
	default:
		preferencesAction();
	}
}
void Application::aboutAction() {
	clear();

	createTitle();
	separator();

	print(translator.ABOUT);
	separator();

	print(translator.ABOUT_THESAURUS);
	separator();

	print(translator.COPYRIGHT);
	print(translator.LICENSE);
	separator();

	Vector<String> menu;
	menu.push(translator.OK);
	menu.push(translator.EXIT);

	createMenu(menu);
	separator();

	requestOption();
	separator();

	switch (option) {
	case 1:
		execute();
		break;
	case 2:
		exitAction();
		break;
	default:
		aboutAction();
	}
}
void Application::exitAction() {
	clear();

	createTitle();
	separator();

	print(translator.EXIT);
	separator();

	print(translator.EXIT_MESSAGE);
	separator();

	Vector<String> menu;
	menu.push(translator.YES);
	menu.push(translator.NO);

	createMenu(menu);
	separator();

	requestOption();
	separator();

	switch (option) {
	case 1:
		exit(0);
		break;
	case 2:
		execute();
		break;
	default:
		exitAction();
	}
}

THESAURUS_NAMESPACE_END