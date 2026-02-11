//
// Created by Stella Perugi on 11/02/26.
//

#ifndef NOTEAPP_CPP_NOTESMANAGER_H
#define NOTEAPP_CPP_NOTESMANAGER_H


#pragma once

#include <string>
#include "Notebook.h"

class NotesManager {
public:
    NotesManager();

    const Notebook& mainNotebook() const;
    const Notebook& importantNotebook() const;

    void addNote(const std::string& title, const std::string& text);

    bool editNote(size_t index, const std::string& newTitle, const std::string& newText);
    bool lockNote(size_t index);
    bool removeNote(size_t index);
    bool toggleImportant(size_t index);

private:
    Notebook mainNb;
    Notebook importantNb;
};



#endif //NOTEAPP_CPP_NOTESMANAGER_H