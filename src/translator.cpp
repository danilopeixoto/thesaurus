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

#include "translator.h"
#include <locale>

THESAURUS_NAMESPACE_BEGIN

Translator::Translator() {
    setEnglishLanguage();
}
Translator::~Translator() {}

void Translator::setLanguage(const Language & language) {
	switch (language) {
	case Language::Portuguese:
		setPortugueseLanguage();
		break;
	default:
		setEnglishLanguage();
	}
}

void Translator::setEnglishLanguage() {
	setlocale(LC_ALL, "english");

	ADD = "Add";
	REMOVE = "Remove";
	EDIT = "Edit";
	SEARCH = "Search";
	LIST = "List";
	EXPORT = "Export";
	PREFERENCES = "Preferences";
	ABOUT = "About";
	EXIT = "Exit";
	YES = "Yes";
	NO = "No";
	OK = "OK";
	CANCEL = "Cancel";
	WORD = "Word:";
	TRANSLATION = "Translation:";
	WORD_COUNT = "Word count:";
	REMOVE_WORD = "Select a word to remove:";
	EDIT_WORD = "Select a word to edit:";
	SEARCH_ERROR = "Could not find word in the dictionary.";
	EXPORT_MESSAGE = "Enter with a filename to export the dictionary:";
	EXPORT_ERROR = "Could not export the dictionary to file.";
	DEFAULT_LANGUAGE = "Select a default language for application:";
	DEFAULT_THEME = "Select a default theme for application:";
	ENGLISH = "English";
	PORTUGUESE = "Portuguese";
	LIGHT = "White";
	DARK = "Dark";
	DEFAULT = "Default";
	SAVE = "Save";
	ABOUT_THESAURUS = "A simple translation dictionary.";
	COPYRIGHT = "Copyright (c) 2017, Danilo Peixoto. All rights reserved.";
	LICENSE = "Software developed under the BSD-3-Clause license.";
	EXIT_MESSAGE = "Are you sure about to close the application?";
}
void Translator::setPortugueseLanguage() {
	setlocale(LC_ALL, "portuguese");

	ADD = "Adicionar";
	REMOVE = "Remover";
	EDIT = "Editar";
	SEARCH = "Buscar";
	LIST = "Listar";
	EXPORT = "Exportar";
	PREFERENCES = "Preferências";
	ABOUT = "Sobre";
	EXIT = "Sair";
	YES = "Sim";
	NO = "Não";
	OK = "OK";
	CANCEL = "Cancelar";
	WORD = "Palavra:";
	TRANSLATION = "Tradução:";
	WORD_COUNT = "Contagem de palavras:";
	REMOVE_WORD = "Selecione uma palavra para remover:";
	EDIT_WORD = "Selecione uma palavra para editar:";
	SEARCH_ERROR = "Palavra não encontrada no dicionário.";
	EXPORT_MESSAGE = "Entre com um nome de arquivo para exportar o dicionário:";
	EXPORT_ERROR = "Dicionário não pôde ser exportado para arquivo.";
	DEFAULT_LANGUAGE = "Selecione o idioma padrão da aplicação:";
	DEFAULT_THEME = "Selecione o tema padrão da aplicação:";
	ENGLISH = "Inglês";
	PORTUGUESE = "Português";
	LIGHT = "Claro";
	DARK = "Escuro";
	DEFAULT = "Padrão";
	SAVE = "Salvar";
	ABOUT_THESAURUS = "Um dicionário simples de tradução.";
	COPYRIGHT = "Copyright (c) 2017, Danilo Peixoto. Todos os direitos reservados.";
	LICENSE = "Programa desenvolvido sob a licença BSD-3-Clause.";
	EXIT_MESSAGE = "Você tem certeza que deseja fechar a aplicação?";
}

THESAURUS_NAMESPACE_END