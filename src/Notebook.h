#ifndef NOTEAPP_CPP_NOTEBOOK_H
#define NOTEAPP_CPP_NOTEBOOK_H

#pragma once


#include <string>
#include <vector>
#include <memory>
#include "Note.h"
#include "NotebookObserver.h"

class Notebook {
public:
    explicit Notebook(const std::string& name); // inizializza il notebook con un nome

    const std::string& getName() const;

    bool addNote(const std::shared_ptr<Note>& note);

    bool removeNote(const std::shared_ptr<Note>& note);

    size_t size() const;

    bool contains(const std::shared_ptr<Note>& note) const;// Verifica se una determinata nota è contenuta nel notebook

    const std::vector<std::shared_ptr<Note>>& getNotes() const;
    std::shared_ptr<Note> getNoteAt(size_t index) const;
    bool removeNoteAt(size_t index);

    void addObserver(NotebookObserver* observer);

    void removeObserver(NotebookObserver* observer);

private:
    void notifyObservers();

    std::string name;

    std::vector<std::shared_ptr<Note>> notes;

    std::vector<NotebookObserver*> observers;
};

#endif //NOTEAPP_CPP_NOTEBOOK_H